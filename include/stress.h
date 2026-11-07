/* stress.h: using up resources on purpose, to test how a program copes
 * (STRESS.DLL, Windows 3.1 SDK). Written for clang-dos from the published
 * API; AGPL-3.0-only, see the win16-sdk LICENSE. */
#ifndef _STRESS_H
#define _STRESS_H
#define _INC_STRESS

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EDS_WIN 1
#define EDS_CUR 2
#define EDS_TEMP 3

#if WINVER >= 0x030A
BOOL WINAPI AllocMem(DWORD);
void WINAPI FreeAllMem(void);
int WINAPI AllocFileHandles(int);
void WINAPI UnAllocFileHandles(void);
int WINAPI GetFreeFileHandles(void);
int WINAPI AllocDiskSpace(long, UINT);
void WINAPI UnAllocDiskSpace(UINT);
BOOL WINAPI AllocUserMem(UINT);
void WINAPI FreeAllUserMem(void);
BOOL WINAPI AllocGDIMem(UINT);
void WINAPI FreeAllGDIMem(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _STRESS_H */
