# What the Win16 SDK is made of

Every file of the Win16 SDK can be passed on freely. None of it is taken
from Microsoft's SDKs: the headers were written for clang-dos from the
published API, and the import lists are lists of function names and
ordinals.

| Part | Where it is | From | Licence |
| --- | --- | --- | --- |
| Windows API headers (`windows.h`, `windowsx.h`, `commdlg.h`, `mmsystem.h`, `winsock.h`, ...) | `i8086-msdos/include/` | clang-dos/win16-sdk, written from the published API | AGPL-3.0-only (`LICENSE`) |
| Import lists | `i8086-msdos/lib/win16/windows*.lnk` | clang-dos/win16-sdk, generated from Wine's `.spec` files (names and ordinals) and, for 1.x to 3.0, from the names and ordinals in those SDKs' import libraries | AGPL-3.0-only (`LICENSE`) |
| Config files, checkers | `bin/win*.cfg`, `share/clang-dos/` | clang-dos/win16-sdk | AGPL-3.0-only (`LICENSE`) |
| C library, start-up code | `i8086-msdos/lib/win16/<model>/libc.a`, `crt0.obj`, `libentry.obj` | picolibc, with clang-dos's DOS and Windows layer | BSD-style (`COPYING.picolibc`) |
| Compiler builtins, libc++, libc++abi | `i8086-msdos/lib/win16/<model>/lib*.a` | LLVM | Apache 2.0 with LLVM exception (`LLVM-LICENSE.TXT`) |

Passing the SDK on means keeping these notices with it (they are in
`share/licenses/win16-sdk/`). Programs built with it link parts of
picolibc, whose licences are BSD-style; several of them ask that a program
shipped in binary form reproduce their notice in its documentation, so
ship `COPYING.picolibc` with such a program. The LLVM parts that programs
link need no notice, thanks to the LLVM exception.

## How the headers were written

The headers were written for clang-dos from the documented Windows API,
not copied from any SDK. `tools/check-headers.py` checks them against two
independent sources, without taking text from either:

- every function, against Wine's `.spec` files (the DLL that exports it,
  the calling convention, and the size of each argument and of the
  result), and against the import list of each Windows version it is
  declared for;
- every integer constant, against mingw-w64's headers (public domain),
  allowing for the values that Win32 changed.

`tests/win16/sizes.c` checks the size of each structure against Wine's
16-bit definitions.

The DLLs that programs call (KERNEL, USER, GDI, COMMDLG, MMSYSTEM, ...)
are part of Windows and are not in the SDK. `WINSOCK.DLL` comes with the
network software.
