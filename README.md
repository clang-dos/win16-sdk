# win16-sdk

The 16-bit Windows (Windows 1.x to 3.x) part of the clang-dos SDK, for
`clang --target=i8086-pc-win16` from [clang-dos/llvm](https://github.com/clang-dos/llvm):
`<windows.h>`, the import lists of the Windows API, the scripts that build
the Windows libraries into a DOS sysroot, the config files, the checkers
and the tests. It was split out of
[clang-dos/dos-sdk](https://github.com/clang-dos/dos-sdk), which still
builds the DOS sysroot these libraries go into and the toolchain packages.

```
include/windows.h          16-bit Windows API declarations
lib/windows.lnk            imports of the Windows 3.1 API
lib/windows300.lnk         ... for Windows 3.0
lib/windows200.lnk         ... for Windows 2.x
lib/windows100.lnk         ... for Windows 1.x
build-sysroot.sh           builds <sysroot>/lib/win16 (see below)
cfg/                       --config files for the toolchain package
tools/ne-check.py          checks an NE program for a Windows version
tools/win16-imports.py     import list for a DLL
tools/gen-win16-imports.py makes lib/*.lnk
tests/                     the tests, run in Wine
```

A sysroot built with it holds, next to the DOS libraries:

```
<sysroot>/include/windows.h
<sysroot>/lib/win16/windows*.lnk
<sysroot>/lib/win16/<model>/       crt0.obj, libentry.obj (DLLs), libc.a,
                                   libclang_rt.builtins.a, libc++.a, libc++abi.a
<sysroot>/lib/win16/<model>/dll/   the libraries again for DLLs in the
                                   small and medium models
```


## Using it

`--target=i8086-pc-win16` makes Windows 3.x programs and DLLs (NE
executables) in the small, medium, compact and large models. Windows runs
them in protected mode, where segment arithmetic is invalid, so there is no
tiny or huge model.

```sh
clang --target=i8086-pc-win16 --sysroot=<sysroot> -Os hello.c -o hello.exe
clang --target=i8086-pc-win16 -mcmodel=large --sysroot=<sysroot> -Os \
    -shared mylib.c -o MYLIB.DLL
```

- A program has `WinMain` (from `<windows.h>`) or `main`. The C library is
  the DOS one: `printf` and files go through DOS, which Windows provides to
  programs (standard output is wherever Windows sends it; under Wine, the
  terminal). `malloc` takes memory from Windows (`GlobalAlloc` in compact
  and large, `LocalAlloc` in DGROUP otherwise).
- `<windows.h>` declares the common types, messages and KERNEL, USER and
  GDI functions. Every Windows 3.1 API function is in `lib/win16/windows.lnk`
  (generated from Wine's `.spec` files by `tools/gen-win16-imports.py`),
  which clang passes to the linker, so declaring a function with `WINAPI`
  (`__far __pascal`) is enough to call it.
- The driver passes `-mwindows-prologue=exported`, so `__export` functions
  (window procedures, DLL entry points) get the Windows entry sequence.
- `-shared` makes a DLL. Its startup code (`libentry.obj`) sets up the local
  heap and runs constructors, then calls
  `int __far __pascal LibMain(HINSTANCE, WORD ds, WORD heapsize, LPSTR cmdline)`
  if the DLL has one; `WEP` runs destructors when it is unloaded. Export
  functions with `__export __far __pascal`. To link a program with a DLL,
  `python3 tools/win16-imports.py MYLIB.DLL > mylib.lnk` lists its
  exports as linker directives; pass them with `-Wl,@mylib.lnk`.
- A DLL runs on the stack of the program that calls it, so `SS` is not
  `DS`. The compiler reaches locals through `SS`: far pointers to locals
  (all data pointers in compact and large) carry `SS`, structures are
  returned through far pointers, `va_list` is a far pointer, and copies
  and fills of locals are done inline. These hold in programs too, so the
  same libraries serve both. In the small and medium models a near
  pointer means `DS`, so DLL code (`-shared`, or `-mwindows-dll` when
  compiling with `-c`) keeps every local whose address escapes the
  function in a frame in DGROUP instead, and near pointers to locals, and
  C++ objects on the stack, work as in a program. Each task that calls
  the DLL gets its own 4 KiB region for these frames, from the DLL's heap;
  a DLL that needs more defines
  `unsigned short __win16_dll_frame_size = 8192;`. The C and C++ libraries
  for this are in `lib/win16/<model>/dll`, which clang links with
  `-shared`. Compact and large DLLs need none of it.
- `__near`, `__far` and `__huge` after the parameter list of a member
  function qualify `this`, as in Microsoft C++ 7: `int get() __far` takes
  a far `this`, so it works on an object anywhere, and `S() __far`
  constructs one. Before the name they choose the call, as for other
  functions (`int __far f()` is called with CALL FAR). A virtual function,
  or a member function that a pointer to member points to, uses the memory
  model's call, since vtables and member pointers hold code pointers of
  that kind. A later declaration without `__near` or `__far` keeps the
  first one's.
- Resources: `llvm-rc -win16` compiles a resource script to a 16-bit
  `.res` file (menus, dialogs, string tables, accelerators, icons,
  cursors, bitmaps, version information and raw data; not the 32-bit
  `MENUEX` and `DIALOGEX`). Strings are 8-bit, in the script's code page.
  `windows.h` can be included in the script (it defines the constants
  only when `RC_INVOKED` is set, as llvm-rc does). Give the `.res` file
  to clang with the objects, and the linker puts the resources in the NE
  file:

  ```sh
  llvm-rc -win16 -I <sysroot>/include -FO app.res app.rc
  clang --target=i8086-pc-win16 --sysroot=<sysroot> app.c app.res -o app.exe
  ```

  `llvm-windres --target=i8086-pc-win16 app.rc app.res` does the same.
- C++ works as on DOS, without exceptions or RTTI by default.
  `-fexceptions` works in programs, and in compact and large DLLs; an
  exception must not cross from a DLL to its caller or back.
- Wine reports 0 as the exit code of every 16-bit program.

### Windows versions

`i8086-pc-win16` with no version makes programs for protected mode, the
only mode of Windows 3.1 and later: the NE header expects Windows 3.0 and
is marked protected mode only, so Windows 3.0 runs the program in standard
or 386 enhanced mode and refuses to start it in real mode. A version after
`win16` sets the version the header expects, and Windows refuses a program
that expects a newer one. The minor version has two digits, as Windows
writes it: 3.10 is Windows 3.1.

| Triple | Windows | Header |
| --- | --- | --- |
| `i8086-pc-win16` | 3.0 (standard, 386 enhanced), 3.1, 3.11, 9x, NT | expects 3.0, protected mode only |
| `i8086-pc-win163.10` | 3.1 and later | expects 3.10, protected mode only |
| `i8086-pc-win163.00` | 3.0 in any mode, 3.1 and later | expects 3.0, real-mode safe |
| `i8086-pc-win162.03` | 2.x (2.03, 2.1, /286, /386), 3.x | expects 2.03, real-mode safe |
| `i8086-pc-win161.01` | 1.x, 2.x, 3.x | expects 1.01, real-mode safe |

Windows 3.x gives a program that expects a version before 3.0 the fixed
system font it was made for, and Windows 3.0 warns before it starts one.

Before 3.10 a program must also work in real mode, which Windows 1.x and
2.x always use and Windows 3.0 uses on an 8086 or with `win /r`. Real-mode
Windows moves and discards segments to make room, and only updates the
references it knows about: entry points, far pointers to them, and the
frames on the stack. So for these versions:

- Code segments are fixed, so they never move, and so are data segments in
  the compact and large models and in DLLs, where far pointers or code
  hold the data segment's address. clang asks the linker for this
  explicitly, although JWlink and wlink make a program's segments fixed
  unless told otherwise; a `-Wl,segment` directive that makes code
  moveable breaks real mode.
- Every far call is a single far-pointer relocation (also in the other
  targets), which real-mode Windows points at a thunk that loads the
  target's segment if it was discarded.
- A program lists only the modules it imports from. (JWlink used to list
  every module named in `windows.lnk`, so every program needed SHELL,
  TOOLHELP, MMSYSTEM and the other Windows 3.1 DLLs to load. This needs
  the fix in clang-dos/jwlink#3.)
- Before Windows 3.0, Windows loads an imported module from `MODULE.EXE`,
  not `MODULE.DLL`, so name a DLL for Windows 1.x and 2.x `MYLIB.EXE`
  (`clang -shared ... -o MYLIB.EXE`).
- `tools/ne-check.py --real-mode PROGRAM.EXE` checks a program for this:
  no moveable code, no protected-mode flag, and no separate segment or
  offset relocation to an import or a moveable segment. `--version 2.03`
  checks the expected version and `--protmode` the flag. It also lists the
  imported modules, and notes the ones that came with Windows 3.1 (SHELL,
  COMMDLG, TOOLHELP, VER, LZEXPAND, MMSYSTEM, ...).

The API follows the version too:

- `__WIN16_VERSION__` is the version from the triple (`0x0203` for
  `win162.03`, `0x030A` without one), and `<windows.h>` makes it `WINVER`
  unless the program sets that itself. Functions that came later are not
  declared (`GetWinFlags`, `wsprintf` and `lstrcmpi` need 3.0, for one).
- clang links a program for 1.x with `lib/win16/windows100.lnk`, one for
  2.x with `windows200.lnk` and one for 3.0 with `windows300.lnk`, which
  have the functions of that version, so a call to one that came later
  fails to link instead of failing to load on the old Windows. They also
  import the functions where the old version has them: in 1.x and 2.x,
  `AnsiNext`, `AnsiPrev`, `AnsiUpper`, `AnsiLower` and `lstrcmp` are KERNEL
  functions (Windows 3.0 moved them to USER), and up to 3.0 `RectVisible`
  is GDI.104, not GDI.465. The lists come from the import libraries of the
  Windows 1.04, 2.03 and 3.0 SDKs (`SLIBW.LIB`, `LIBW.LIB`):
  `python3 tools/gen-win16-imports.py --from-lib <SDK>/LIB/SLIBW.LIB
  <wine-src>/dlls`. (The 1.01 and 1.03 SDKs have the same list as 1.04.)
- `llvm-rc -win16-version 2.03` (or `llvm-windres
  --target=i8086-pc-win162.03`) writes resources for Windows 1.x and 2.x,
  and its preprocessor sees the same `WINVER`. Menus have no header and a
  byte of flags per item. Icons, cursors and bitmaps are the files of the
  1.x and 2.x SDK's icon editor (ICONEDIT), each one resource, with no icon
  or cursor groups; a Windows 3.x `.ico`, `.cur` or `.bmp` file is refused.
  Dialogs have no `FONT` or combo boxes, which it refuses too, and a
  `LISTBOX` is sorted and has a scroll bar (`LBS_STANDARD`) unless its
  style says otherwise, as the old resource compilers make it. Menus,
  dialogs, strings,
  accelerators, raw data, icons, cursors and bitmaps come out byte for byte
  as the resource compilers of the 1.04 and 2.03 SDKs write them, run in
  DOSBox, on the samples of the 2.03 SDK. Where they differ, the 2.03 one
  is wrong: it leaves the last two bytes off a bitmap (llvm-rc writes all
  of it, as the 1.04 one does), and gives a `LISTBOX` the text of the
  control before it. The old compilers let a script leave out commas, as in
  `CTEXT "Hello" -1, 0, 5, 154, 8`, which llvm-rc does not; add them. Wine
  does not load 1.x and 2.x icons, cursors or bitmaps, so these are checked
  as data only.

All of this is checked only in Wine, which runs every 16-bit program in
protected mode (it does load imported modules and reads menus the way the
expected version says, and reports the closest Windows version it has);
the programs have not been run on real Windows 1.x, 2.x or 3.0.


## Building the Windows libraries

They go into a DOS sysroot, so build that with clang-dos/dos-sdk and give
it this checkout; its `scripts/build-sysroot.sh` runs `build-sysroot.sh`
here after the DOS libraries:

```sh
LLVM_SRC=~/llvm-project PICOLIBC_SRC=~/picolibc BIN=~/llvm-build/bin \
WIN16_SDK=~/win16-sdk SYSROOT=$PWD/sysroot sh ~/dos-sdk/scripts/build-sysroot.sh
```

or on its own, into a sysroot that has the DOS libraries already:

```sh
LLVM_SRC=~/llvm-project PICOLIBC_SRC=~/picolibc BIN=~/llvm-build/bin \
DOS_SDK=~/dos-sdk SYSROOT=$PWD/sysroot sh build-sysroot.sh
```

picolibc's DOS layer serves Windows too (Windows programs call DOS for
files and the clock), with picolibc's `cross-clang-i8086-win16-<model>.txt`
cross files. The builtins and libc++ are built again with dos-sdk's
`scripts/build-builtins.sh` and `scripts/build-libcxx.sh` (`OS=win16`), as
Windows returns structures through far pointers in every model.
`DOS_SDK` defaults to `../dos-sdk` next to this checkout. `WIN16_MODELS=`
picks the models (default: small medium compact large) and `NO_CXX=1`
skips libc++.

## Tests

The tests run in Wine (with 16-bit support, as in the 32-bit or WoW64
builds):

```sh
BIN=~/llvm-build/bin SYSROOT=$PWD/sysroot LD=/path/to/jwlink \
DOS_SDK=~/dos-sdk sh tests/run-tests.sh
```

They build each test for the small, medium, compact and large models at
`-O0`, `-Os` and `-O2` (`MODELS=` and `OPTS=` pick others):

- `tests/win16/hello.c`: `main`, arguments, the heap, files and the clock.
- `tests/win16/api.c`: `WinMain` and KERNEL and USER calls through
  `<windows.h>`.
- `tests/win16/testdll.c` with `tests/win16/dllapp.c`: a DLL with
  `LibMain`, exports and static data, called from a program, and its use
  of locals on the caller's stack, through far pointers and near ones
  (handed to the C library too).
- `tests/win16/cxxdll.cpp` with `tests/win16/cxxdllapp.c`: a C++ DLL with
  objects, strings and vectors on its stack.
- `tests/win16/res.rc` with `tests/win16/res.c`: resources compiled by
  `llvm-rc -win16`: strings, a menu, accelerators, a dialog, an icon, raw
  data and version information.
- dos-sdk's `tests/libc/nearfar.c`, `tests/libc/random.c` and
  `tests/cxx/except.cpp`, built for Windows.
- `tests/win16/gui.c`: a window, its message loop, painting and a timer.
  It needs a display: `DISPLAY`, or `xvfb-run` on `PATH`. `NO_GUI=1` skips
  it.

## CI

dos-sdk's `.github/workflows/toolchain.yml` takes this repository at `main`
(or the `win16_sdk_ref` it is given) and dos-sdk's toolchain
workflow with this commit: it builds the toolchain package with every
sysroot and runs its smoke test, which builds a program for each Windows
version, checks it with `ne-check.py` and runs it in Wine.

## License

BSD 3-Clause (see `LICENSE`).
