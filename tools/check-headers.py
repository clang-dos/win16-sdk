#!/usr/bin/env python3
"""Check the 16-bit Windows headers against independent sources.

    check-headers.py --clang CLANG --wine <wine-src>/dlls
                     [--mingw-sysroot DIR]

For each Windows version the headers know (1.01, 2.03, 3.00, 3.10) it
compiles every header for that version and checks each function that they
declare:

 * the import list of that version (lib/windows*.lnk) has it, so that a
   program for 2.x cannot call a function that only came in 3.0;
 * Wine's .spec file for its module agrees on the calling convention and
   on the size of each argument and of the result (word or long), which
   is what the 16-bit stack frame depends on.

With --mingw-sysroot (a mingw-w64 sysroot, such as win32-sdk builds) it
also compares the value of every integer constant that the 32-bit
headers have too, apart from the ones that 16-bit Windows defines
differently (DIFFERENT_IN_WIN16 below).

It prints the problems it finds and exits with 1 if there are any.
"""
import argparse
import json
import os
import re
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)

# Every header, in an order that works (some include others).
HEADERS = [
    "windows.h", "windowsx.h", "commdlg.h", "cderr.h", "dlgs.h",
    "shellapi.h", "mmsystem.h", "toolhelp.h", "ver.h", "lzexpand.h",
    "dde.h", "ddeml.h", "print.h", "stress.h", "winsock.h",
]

HEADERS = [h for h in HEADERS
           if os.path.exists(os.path.join(ROOT, "include", h))]

# Defined by the program or DLL, not imported.
NOT_IMPORTED = {"WinMain", "LibMain", "WEP"}

VERSIONS = [("1.01", 0x0101, "windows100.lnk"),
            ("2.03", 0x0203, "windows200.lnk"),
            ("3.00", 0x0300, "windows300.lnk"),
            ("3.10", 0x030A, "windows.lnk")]

# Modules and their Wine spec files (as tools/gen-win16-imports.py).
SPECS = {
    "KERNEL": "krnl386.exe16/krnl386.exe16.spec",
    "USER": "user.exe16/user.exe16.spec",
    "GDI": "gdi.exe16/gdi.exe16.spec",
    "KEYBOARD": "keyboard.drv16/keyboard.drv16.spec",
    "SOUND": "sound.drv16/sound.drv16.spec",
    "SHELL": "shell.dll16/shell.dll16.spec",
    "COMMDLG": "commdlg.dll16/commdlg.dll16.spec",
    "TOOLHELP": "toolhelp.dll16/toolhelp.dll16.spec",
    "MMSYSTEM": "mmsystem.dll16/mmsystem.dll16.spec",
    "VER": "ver.dll16/ver.dll16.spec",
    "LZEXPAND": "lzexpand.dll16/lzexpand.dll16.spec",
    "DDEML": "ddeml.dll16/ddeml.dll16.spec",
    "STRESS": "stress.dll16/stress.dll16.spec",
    "WINSOCK": "winsock.dll16/winsock.dll16.spec",
}

ARG_SIZE = {"word": 2, "s_word": 2, "long": 4, "ptr": 4, "str": 4,
            "segptr": 4, "segstr": 4}

# Wine's spec is wrong or looser than the documented API for these.
SPEC_EXCEPTIONS = {
}

# Constants whose 16-bit value is not the 32-bit one.
DIFFERENT_IN_WIN16 = {
    "DMBIN_LAST", "DMPAPER_LAST",  # later versions added more
    "DM_SPECVERSION",       # 0x030A for 3.1 drivers
    "MAXERRORLENGTH",       # 128 in 3.1
    "MIDIERR_LASTERROR", "MMSYSERR_LASTERROR",  # more errors later
    "AF_MAX", "PF_MAX",     # more families later
    "IPPROTO_GGP",          # 2 in Windows Sockets 1.1 (BSD 4.2); 3 later
    "MAX_PATH",             # toolhelp.h: 255 (Win32 uses 260)
    "CW_USEDEFAULT",        # (int)0x8000
    "WM_CTLCOLOR",          # 0x0019; Win32 split it into WM_CTLCOLOR*
    "GMEM_DDESHARE", "GMEM_NOT_BANKED", "GMEM_NOTIFY", "GMEM_LOWER",
    "GMEM_INVALID_HANDLE", "GMEM_DISCARDED", "GMEM_LOCKCOUNT",
    "LMEM_DISCARDED", "LMEM_LOCKCOUNT", "LMEM_INVALID_HANDLE",
    "HFILE_ERROR",          # (HFILE)-1, 16 bits
    "INVALID_HANDLE_VALUE",
    "MAKEINTATOM", "MAKEINTRESOURCE",
    "SIZEFULLSCREEN", "SIZEZOOMSHOW",  # same names, not in mingw
    "WINVER",
    "QS_ALLINPUT",          # no QS_RAWINPUT and so on
    "SM_CMETRICS",          # the number of metrics
    "WM_MOUSELAST",         # no WM_MOUSEWHEEL
    "HKEY_CLASSES_ROOT",    # 1
}

# Groups of constants that 16-bit Windows numbers its own way.
DIFFERENT_PREFIXES = (
    "CBR_",                 # baud rate indexes, not rates
)

# The documented result is a word, where Wine's function returns a long
# (the high word is of no use).
RETURNS_WORD = {
    "GetModuleHandle",  # HMODULE in AX (DX has the instance)
    "LocalLock",        # a near pointer
    "GetCurrentTask",   # HTASK
    "GetCurrentPDB",    # the PDB selector
    "GetCodeHandle",    # HGLOBAL
    "Catch",            # int
    "Escape",           # int
    # VER: BOOL and UINT, where Wine's functions return a DWORD.
    "GetFileResource", "GetFileVersionInfo", "VerFindFile",
    "VerLanguageName", "VerQueryValue",
    # WINSOCK: int, where Wine's functions return a DWORD.
    "gethostname", "WSAStartup", "WSACleanup",
}

# Functions that return a far pointer, where Wine's spec says -ret16.
RETURNS_DWORD = {
    "WSASetBlockingHook",  # FARPROC, the previous hook
}

# Modules whose Wine spec does not give the size of the result.
NO_RESULT_SIZES = {"STRESS", "MMSYSTEM"}

# The control messages were WM_USER + n until Win32 numbered them from
# these instead.
WM_USER_BASED = {"BM_": 0xF0, "EM_": 0xB0, "LB_": 0x17F, "CB_": 0x140,
                 "STM_": 0x170}

AS = {"0": "__near", "1": "__near", "2": "__far", "3": "__huge",
      "5": "__far"}


def spec_entries(dlls):
    """NAME (upper case) -> (module, kind, ret16, [arg sizes]) for every
    entry point of the modules above."""
    out = {}
    entry = re.compile(r"^\s*(\d+)\s+(pascal|cdecl|varargs)((?:\s+-[\w=]+)*)"
                       r"\s+([\w@?$]+)\s*\(([^)]*)\)")
    stub = re.compile(r"^\s*(\d+)\s+stub\s+(\w+)")
    for module, spec in SPECS.items():
        path = os.path.join(dlls, spec)
        if not os.path.exists(path):
            continue
        for line in open(path):
            m = stub.match(line)
            if m and int(m.group(1)) < 1000:
                # Wine does not implement it: nothing to compare.
                out.setdefault(m.group(2).upper(),
                               (module, "pascal", None, None))
                continue
            m = entry.match(line)
            if not m:
                continue
            _, kind, flags, name, args = m.groups()
            sizes = [ARG_SIZE.get(a, 0) for a in args.split()]
            key = name.upper() if kind == "pascal" else name.lstrip("_")
            out.setdefault(key, (module, kind, "-ret16" in flags, sizes))
    return out


def import_list(path):
    names = set()
    for line in open(path):
        m = re.match(r"import (\S+) (\w+)\.(\d+)", line)
        if m:
            names.add(m.group(1))
    return names


def run_clang(clang, version, src, extra=()):
    triple = "i8086-pc-win16" + version
    # WINVER too, for a clang from before __WIN16_VERSION__.
    major, minor = version.split(".")
    winver = "-DWINVER=0x%02X%02X" % (int(major), int(minor))
    cmd = [clang, "--target=" + triple, winver, "-fsyntax-only", "-I",
           os.path.join(ROOT, "include"), "-Xclang", "-ast-dump=json",
           *extra, src]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        sys.stderr.write(r.stderr)
        sys.exit(f"{' '.join(cmd)} failed")
    return json.loads(r.stdout)


def our_file(loc, state):
    """Track the file of AST nodes (the JSON gives it only when it
    changes) and say whether it is one of our headers."""
    f = loc.get("file")
    if f is None and "spellingLoc" in loc:
        f = loc["spellingLoc"].get("file")
    if f is None and "expansionLoc" in loc:
        f = loc["expansionLoc"].get("file")
    if f is not None:
        state["file"] = f
    return state.get("file", "").startswith(os.path.join(ROOT, "include"))


def c_type(t):
    """A type string from the AST, back in C (address spaces as the 16-bit
    keywords)."""
    return re.sub(r"__attribute__\(\(address_space\((\d+)\)\)\)",
                  lambda m: AS[m.group(1)], t)


def return_type(ftype):
    """The result type in a function type string such as
    'int (__attribute__((address_space(5)))(HWND) __attribute__((pascal))'
    (clang prints the far function's address space with an unmatched
    parenthesis)."""
    m = re.match(r"^(.*?)\s*\(__attribute__\(\(address_space\(\d+\)\)\)\(",
                 ftype)
    if m:
        return m.group(1)
    t = re.sub(r"\s*__attribute__\(\(pascal\)\)\s*$", "", ftype)
    t = re.sub(r"\s*__attribute__\(\(\w+\)\)\s*$", "", t)

    def group_start(t):
        depth = 0
        for i in range(len(t) - 1, -1, -1):
            if t[i] == ")":
                depth += 1
            elif t[i] == "(":
                depth -= 1
                if depth == 0:
                    return i
        return 0
    t = t[:group_start(t)].rstrip()       # the parameters
    if t.endswith(")"):                   # (__attribute__((address_space)))
        i = group_start(t)
        if "address_space" in t[i:]:
            t = t[:i].rstrip()
    return t


def functions(ast):
    """(name, pascal?, return type, [parameter types], variadic) of the
    functions declared in our headers."""
    out = []
    state = {}
    for n in ast.get("inner", []):
        mine = our_file(n.get("loc", {}), state)
        if n.get("kind") != "FunctionDecl" or not mine:
            continue
        if n.get("isImplicit") or n.get("storageClass") == "static":
            continue
        if n.get("inline"):
            continue
        ftype = n["type"]["qualType"]
        params = [p["type"]["qualType"] for p in n.get("inner", [])
                  if p.get("kind") == "ParmVarDecl"]
        ret = return_type(ftype)
        out.append((n["name"], "pascal" in ftype, ret, params,
                    n.get("variadic", False) or "..." in ftype))
    return out


def sizes(clang, version, types):
    """sizeof each type, in the small model (where a near pointer is
    2 bytes, so that a missing __far shows)."""
    types = sorted(set(types))
    with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False) as f:
        f.write("".join(f'#include <{h}>\n' for h in HEADERS))
        for i, t in enumerate(types):
            f.write(f"enum {{ __size_{i} = sizeof({c_type(t)}) }};\n")
        src = f.name
    try:
        ast = run_clang(clang, version, src)
    finally:
        os.unlink(src)
    out = {}

    def value(n):
        if n.get("kind") == "ConstantExpr":
            return int(n["value"])
        for c in n.get("inner", []):
            v = value(c)
            if v is not None:
                return v
        return None
    for n in ast.get("inner", []):
        if n.get("kind") != "EnumDecl":
            continue
        for c in n.get("inner", []):
            m = re.match(r"__size_(\d+)$", c.get("name", ""))
            if m:
                out[types[int(m.group(1))]] = value(c)
    return out


def check_functions(args, problems):
    spec = spec_entries(args.wine)
    declared = {}
    lists = {}
    for vname, winver, lnk in VERSIONS:
        version = vname
        imports = import_list(os.path.join(ROOT, "lib", lnk))
        with tempfile.NamedTemporaryFile("w", suffix=".c",
                                         delete=False) as f:
            f.write("".join(f'#include <{h}>\n' for h in HEADERS))
            src = f.name
        try:
            ast = run_clang(args.clang, version, src)
        finally:
            os.unlink(src)
        funcs = functions(ast)
        declared[vname] = {n for n, *_ in funcs}
        lists[vname] = imports
        size = sizes(args.clang, version,
                     [t for _, _, r, ps, _ in funcs for t in ps + [r]
                      if t != "void"])
        for name, pascal, ret, params, variadic in funcs:
            if name in NOT_IMPORTED:
                continue
            sym = name.upper() if pascal else "_" + name
            key = name.upper() if pascal else name
            where = f"{name} (Windows {vname})"
            if sym not in imports and name.upper() not in imports:
                problems.append(f"{where}: not in lib/{lnk}")
            e = spec.get(key) or spec.get(name.upper())
            if e is None:
                problems.append(f"{where}: not in Wine's specs")
                continue
            module, kind, ret16, want = e
            if key in SPEC_EXCEPTIONS:
                continue
            if (kind == "pascal") != pascal:
                problems.append(f"{where}: Wine has it {kind}")
                continue
            if kind == "varargs" or variadic or want is None:
                continue
            # A BYTE or char argument is pushed as a word.
            have = [max(size.get(p) or 0, 2) for p in params]
            if have != want:
                problems.append(f"{where}: argument sizes {have}, "
                                f"{module} has {want}")
            r = 0 if ret == "void" else size.get(ret)
            if module in NO_RESULT_SIZES:
                continue
            if r == 4 and ret16 and name not in RETURNS_DWORD:
                problems.append(f"{where}: returns 4 bytes, Wine 2")
            if r == 2 and not ret16 and name not in RETURNS_WORD:
                problems.append(f"{where}: returns 2 bytes, Wine 4")
    # A function left out for a version that has it.
    newest = VERSIONS[-1][0]
    for name in sorted(declared[newest]):
        for vname, _, lnk in VERSIONS[:-1]:
            sym = name.upper()
            if (sym in lists[vname] or "_" + name in lists[vname]) and \
                    name not in declared[vname]:
                problems.append(f"{name}: Windows {vname} has it "
                                f"(lib/{lnk}), but it is not declared for it")
                break


# A small evaluator for the constants of the two header sets.
CAST = re.compile(r"\(\s*(?:const\s+)?[A-Z_][A-Za-z0-9_]*\s*\**\s*\)|"
                  r"\(\s*(?:unsigned|signed|int|long|short|char)"
                  r"(?:\s+(?:int|long|short|char))*\s*\)")


def macros(cmd):
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        sys.stderr.write(r.stderr)
        sys.exit(f"{' '.join(cmd)} failed")
    out = {}
    for line in r.stdout.splitlines():
        m = re.match(r"#define (\w+) (.+)$", line)
        if m:
            out[m.group(1)] = m.group(2)
    return out


def evaluate(name, defs, depth=0):
    body = defs.get(name)
    if body is None or depth > 20:
        return None
    body = re.sub(r"MAKEINTRESOURCE[AW]?\(", "(", body)
    body = re.sub(r"MAKEINTATOM\(", "(", body)
    body = CAST.sub("", body)
    body = re.sub(r"\b(0[xX][0-9a-fA-F]+|\d+)[uUlL]+\b", r"\1", body)

    def sub(m):
        v = evaluate(m.group(0), defs, depth + 1)
        if v is None:
            raise ValueError
        return str(v)
    try:
        body = re.sub(r"\b[A-Za-z_]\w*\b", sub, body)
        if not re.fullmatch(r"[\s0-9a-fA-FxX()+\-*/|&~<>^]*", body):
            return None
        return int(eval(body.replace("/", "//"), {}, {}))
    except Exception:
        return None


def check_constants(args, problems):
    with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False) as f:
        f.write("".join(f'#include <{h}>\n' for h in HEADERS))
        ours_src = f.name
    with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False) as f:
        f.write("#include <windows.h>\n#include <commdlg.h>\n"
                "#include <cderr.h>\n#include <dlgs.h>\n"
                "#include <shellapi.h>\n#include <mmsystem.h>\n"
                "#include <lzexpand.h>\n#include <dde.h>\n"
                "#include <ddeml.h>\n#include <winsock.h>\n"
                "#include <tlhelp32.h>\n#include <winver.h>\n")
        theirs_src = f.name
    try:
        ours = macros([args.clang, "--target=i8086-pc-win16", "-E", "-dM",
                       "-I", os.path.join(ROOT, "include"), ours_src])
        theirs = macros([args.clang, "--target=i686-w64-windows-gnu",
                         "--sysroot", args.mingw_sysroot,
                         "-D_WIN32_WINNT=0x0400", "-DWINVER=0x0400",
                         "-E", "-dM", theirs_src])
    finally:
        os.unlink(ours_src)
        os.unlink(theirs_src)
    checked = 0
    for name in sorted(set(ours) & set(theirs)):
        if (name in DIFFERENT_IN_WIN16 or name.startswith("_") or
                name.startswith(DIFFERENT_PREFIXES)):
            continue
        a, b = evaluate(name, ours), evaluate(name, theirs)
        if a is None or b is None:
            continue
        checked += 1
        base = [b for p, b in WM_USER_BASED.items() if name.startswith(p)]
        if base and a >= 0x400:
            if a - 0x400 + base[0] != b:
                problems.append(f"{name}: WM_USER+{a - 0x400:#x} here, "
                                f"{b:#x} in mingw-w64")
            continue
        if a != b and (a - b) % 0x10000 != 0:
            problems.append(f"{name}: {a:#x} here, {b:#x} in mingw-w64")
        elif a != b and abs(a) > 0xFFFF:
            problems.append(f"{name}: {a:#x} here, {b:#x} in mingw-w64")
    print(f"{checked} constants compared with mingw-w64")


def main():
    p = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    p.add_argument("--clang", required=True)
    p.add_argument("--wine", required=True, help="<wine-src>/dlls")
    p.add_argument("--mingw-sysroot")
    args = p.parse_args()
    problems = []
    check_functions(args, problems)
    if args.mingw_sysroot:
        check_constants(args, problems)
    for line in problems:
        print(line)
    print(f"{len(problems)} problems")
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
