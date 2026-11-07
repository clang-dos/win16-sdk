/* lzexpand.h: reading files compressed by COMPRESS.EXE (LZEXPAND.DLL,
 * Windows 3.1). Written for clang-dos from the published API; AGPL-3.0-only, see
 * the win16-sdk LICENSE. */
#ifndef _LZEXPAND_H
#define _LZEXPAND_H
#define _INC_LZEXPAND

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LZERROR_BADINHANDLE (-1)
#define LZERROR_BADOUTHANDLE (-2)
#define LZERROR_READ (-3)
#define LZERROR_WRITE (-4)
#define LZERROR_GLOBALLOC (-5)
#define LZERROR_GLOBLOCK (-6)
#define LZERROR_BADVALUE (-7)
#define LZERROR_UNKNOWNALG (-8)

#if WINVER >= 0x030A
int WINAPI LZStart(void);
void WINAPI LZDone(void);
LONG WINAPI CopyLZFile(HFILE, HFILE);
LONG WINAPI LZCopy(HFILE, HFILE);
HFILE WINAPI LZInit(HFILE);
int WINAPI GetExpandedName(LPCSTR, LPSTR);
HFILE WINAPI LZOpenFile(LPCSTR, OFSTRUCT FAR *, UINT);
LONG WINAPI LZSeek(HFILE, LONG, int);
int WINAPI LZRead(HFILE, void FAR *, int);
void WINAPI LZClose(HFILE);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _LZEXPAND_H */
