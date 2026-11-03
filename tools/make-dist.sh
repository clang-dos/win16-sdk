#!/bin/sh
# Make the redistributable Win16 SDK archive from an assembled clang-dos
# package (dos-sdk's packaging/assemble.sh):
#
#   tools/make-dist.sh PACKAGE OUTPUT.tar.xz
#
# The archive unpacks over a clang-dos package, which has the DOS headers
# and libraries that these build on:
#   bin/win*.cfg                    the --config files of the Windows targets
#   i8086-msdos/include/            the Windows headers (include/ here)
#   i8086-msdos/lib/win16/          the import lists and the libraries of
#                                   every memory model
#   share/clang-dos/                ne-check.py, win16-imports.py,
#                                   check-headers.py, docs/win16-README.md
#   share/licenses/win16-sdk/       the licences (see NOTICE.md)
set -e
pkg=${1:?usage: make-dist.sh PACKAGE OUTPUT.tar.xz} out=${2:?}
here=$(cd "$(dirname "$0")/.." && pwd)
lib=$pkg/i8086-msdos/lib/win16
[ -d "$lib" ] || { echo "no $lib: not a clang-dos package" >&2; exit 1; }
stage=$(mktemp -d)
trap 'rm -rf "$stage"' EXIT
d=$stage/win16-sdk
mkdir -p "$d/bin" "$d/i8086-msdos/include" "$d/i8086-msdos/lib" \
  "$d/share/clang-dos/docs" "$d/share/licenses/win16-sdk"
cp "$here"/cfg/*.cfg "$d/bin/"
cp "$here"/include/*.h "$d/i8086-msdos/include/"
cp -R "$lib" "$d/i8086-msdos/lib/"
# The import lists and headers of this checkout, over the package's.
cp "$here"/lib/*.lnk "$d/i8086-msdos/lib/win16/"
cp "$here/tools/ne-check.py" "$here/tools/win16-imports.py" \
  "$here/tools/check-headers.py" "$d/share/clang-dos/"
cp "$here/README.md" "$d/share/clang-dos/docs/win16-README.md"
l=$d/share/licenses/win16-sdk
cp "$here/LICENSE" "$l/LICENSE"
cp "$here/NOTICE.md" "$l/NOTICE.md"
for f in LLVM-LICENSE.TXT COPYING.picolibc; do
  [ -f "$pkg/share/licenses/$f" ] ||
    { echo "no $pkg/share/licenses/$f" >&2; exit 1; }
  cp "$pkg/share/licenses/$f" "$l/"
done
mkdir -p "$(dirname "$out")"
out=$(cd "$(dirname "$out")" && pwd)/$(basename "$out")
tar -C "$d" -cf - . | xz -T0 -9 >"$out"
echo "$out: $(du -h "$out" | cut -f1)"
