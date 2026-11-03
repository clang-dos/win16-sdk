/* windows.h for 16-bit Windows (clang --target=i8086-pc-win16).
 *
 * The Windows 1.x to 3.1 API of KERNEL, USER, GDI, KEYBOARD and SOUND:
 * types, structures, constants and functions. The other parts of the API
 * have their own headers: commdlg.h, cderr.h, dlgs.h, shellapi.h,
 * mmsystem.h, toolhelp.h, ver.h, lzexpand.h, dde.h, ddeml.h, print.h,
 * stress.h, winsock.h, and windowsx.h for the message crackers.
 *
 * WINVER is the oldest Windows the program is for, from the target
 * (--target=i8086-pc-win162.03 makes it 0x0203); functions that came
 * later are left out, here and in the import list (lib/win16/windows.lnk
 * for 3.1, windows300.lnk for 3.0, windows200.lnk for 2.x,
 * windows100.lnk for 1.x). Define STRICT for distinct handle types, as
 * with the Windows 3.1 SDK. Resource scripts can include it too (llvm-rc
 * -win16 defines RC_INVOKED): they get the constants only.
 *
 * Written for clang-dos from the published API; checked against Wine's
 * import specifications and mingw-w64's constants by
 * tools/check-headers.py. BSD 3-Clause, see the win16-sdk LICENSE. */
#ifndef _WINDOWS_H
#define _WINDOWS_H
#define _INC_WINDOWS

#ifndef __WINDOWS__
#error "windows.h is for --target=i8086-pc-win16"
#endif

#ifndef WINVER
#ifdef __WIN16_VERSION__
#define WINVER __WIN16_VERSION__
#else
#define WINVER 0x030A
#endif
#endif

#ifdef RC_INVOKED
/* The resource compiler gets the constants only. */
#define NOATOM
#define NOGDI
#define NOGDICAPMASKS
#define NOMETAFILE
#define NOMINMAX
#define NOMSG
#define NOOPENFILE
#define NORASTEROPS
#define NOSCROLL
#define NOSOUND
#define NOSYSMETRICS
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOLOGERROR
#define NOPROFILER
#define NOMEMMGR
#define NOLFILEIO
#endif

#ifndef RC_INVOKED
#pragma pack(push, 1)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Calling conventions and pointer sizes. */
#define FAR __far
#define NEAR __near
#define HUGE __huge
#ifndef _far
#define _far __far
#endif
#ifndef _near
#define _near __near
#endif
#ifndef _huge
#define _huge __huge
#endif
#ifndef _pascal
#define _pascal __pascal
#endif
#ifndef _cdecl
#define _cdecl __cdecl
#endif
#define PASCAL __pascal
#define CDECL __cdecl
#define WINAPI __far __pascal
#define CALLBACK __far __pascal
#define API __far __pascal
#ifndef _export
#define _export __export
#endif
#ifndef _loadds
#define _loadds __loadds
#endif
#define VOID void
#define CONST const

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif
#define FALSE 0
#define TRUE 1

#ifndef RC_INVOKED
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef long LONG;
typedef char NEAR *PSTR;
typedef char NEAR *NPSTR;
typedef char FAR *LPSTR;
typedef const char FAR *LPCSTR;
typedef char __huge *HPSTR;
typedef BYTE NEAR *PBYTE;
typedef BYTE FAR *LPBYTE;
typedef int NEAR *PINT;
typedef int FAR *LPINT;
typedef WORD NEAR *PWORD;
typedef WORD FAR *LPWORD;
typedef long NEAR *PLONG;
typedef long FAR *LPLONG;
typedef DWORD NEAR *PDWORD;
typedef DWORD FAR *LPDWORD;
typedef BOOL NEAR *PBOOL;
typedef BOOL FAR *LPBOOL;
typedef UINT NEAR *PUINT;
typedef UINT FAR *LPUINT;
typedef void FAR *LPVOID;
typedef const void FAR *LPCVOID;

typedef UINT WPARAM;
typedef long LPARAM;
typedef long LRESULT;

/* Handles: plain words, or with STRICT, near pointers to a distinct
 * structure for each kind, so that the compiler catches mixed-up
 * handles. Either way a handle is 16 bits. */
#ifdef STRICT
typedef const void NEAR *HANDLE;
#define DECLARE_HANDLE(name)                                                   \
  struct name##__ {                                                            \
    int unused;                                                                \
  };                                                                           \
  typedef const struct name##__ NEAR *name
#define DECLARE_HANDLE32(name)                                                 \
  struct name##__ {                                                            \
    int unused;                                                                \
  };                                                                           \
  typedef const struct name##__ FAR *name
#else
typedef UINT HANDLE;
#define DECLARE_HANDLE(name) typedef UINT name
#define DECLARE_HANDLE32(name) typedef DWORD name
#endif
typedef HANDLE NEAR *PHANDLE;
typedef HANDLE FAR *LPHANDLE;

DECLARE_HANDLE(HWND);
DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE;
DECLARE_HANDLE(HTASK);
DECLARE_HANDLE(HDC);
DECLARE_HANDLE(HMENU);
DECLARE_HANDLE(HICON);
typedef HICON HCURSOR;
DECLARE_HANDLE(HGDIOBJ);
DECLARE_HANDLE(HBRUSH);
DECLARE_HANDLE(HPEN);
DECLARE_HANDLE(HFONT);
DECLARE_HANDLE(HBITMAP);
DECLARE_HANDLE(HRGN);
DECLARE_HANDLE(HPALETTE);
DECLARE_HANDLE(HRSRC);
DECLARE_HANDLE(HACCEL);
DECLARE_HANDLE(HMETAFILE);
DECLARE_HANDLE(HDWP);
DECLARE_HANDLE32(HHOOK); /* 32 bits */
DECLARE_HANDLE(HDRVR);
DECLARE_HANDLE32(HGLOBAL32);
typedef HANDLE HGLOBAL;
typedef HANDLE HLOCAL;
typedef HANDLE GLOBALHANDLE;
typedef HANDLE LOCALHANDLE;
typedef int HFILE;
typedef UINT ATOM;
typedef DWORD COLORREF;
typedef COLORREF FAR *LPCOLORREF;
#define HFILE_ERROR ((HFILE)-1)

/* Procedures. A FARPROC takes any arguments, as in the Windows SDK. */
typedef int(CALLBACK *FARPROC)();
typedef int(NEAR PASCAL *NEARPROC)();
typedef LRESULT(CALLBACK *WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef BOOL(CALLBACK *DLGPROC)(HWND, UINT, WPARAM, LPARAM);
#endif /* RC_INVOKED */

#define LOBYTE(w) ((BYTE)(w))
#define HIBYTE(w) ((BYTE)((UINT)(w) >> 8))
#define LOWORD(l) ((WORD)(DWORD)(l))
#define HIWORD(l) ((WORD)((DWORD)(l) >> 16))
#define MAKEWORD(lo, hi) ((WORD)(((BYTE)(lo)) | ((WORD)((BYTE)(hi))) << 8))
#define MAKELONG(lo, hi) ((LONG)(((WORD)(lo)) | ((DWORD)((WORD)(hi))) << 16))
#define MAKELPARAM(lo, hi) ((LPARAM)MAKELONG(lo, hi))
#define MAKELRESULT(lo, hi) ((LRESULT)MAKELONG(lo, hi))
#ifndef NOMINMAX
#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif
#endif

/* Far pointers: selector and offset. */
#define MAKELP(sel, off) ((void FAR *)MAKELONG((off), (sel)))
#define SELECTOROF(lp) HIWORD(lp)
#define OFFSETOF(lp) LOWORD(lp)
#define FIELDOFFSET(type, field) ((int)(&((type NEAR *)1)->field) - 1)

#ifndef RC_INVOKED
typedef struct tagPOINT {
  int x;
  int y;
} POINT;
typedef POINT NEAR *PPOINT;
typedef POINT NEAR *NPPOINT;
typedef POINT FAR *LPPOINT;

typedef struct tagSIZE {
  int cx;
  int cy;
} SIZE;
typedef SIZE NEAR *PSIZE;
typedef SIZE FAR *LPSIZE;

typedef struct tagRECT {
  int left;
  int top;
  int right;
  int bottom;
} RECT;
typedef RECT NEAR *PRECT;
typedef RECT NEAR *NPRECT;
typedef RECT FAR *LPRECT;
typedef const RECT FAR *LPCRECT;

#define MAKEPOINT(l) (*((POINT FAR *)&(l)))
#endif /* RC_INVOKED */

#define RGB(r, g, b)                                                           \
  ((COLORREF)(((BYTE)(r) | ((WORD)(g) << 8)) | (((DWORD)(BYTE)(b)) << 16)))
#define PALETTERGB(r, g, b) (0x02000000L | RGB(r, g, b))
#define PALETTEINDEX(i) ((COLORREF)(0x01000000L | (DWORD)(WORD)(i)))
#define GetRValue(rgb) ((BYTE)(rgb))
#define GetGValue(rgb) ((BYTE)(((WORD)(rgb)) >> 8))
#define GetBValue(rgb) ((BYTE)((rgb) >> 16))

#define MAKEINTRESOURCE(i) ((LPCSTR)MAKELP(0, (i)))
#define MAKEINTATOM(i) ((LPCSTR)MAKELP(0, (i)))

/****************************************************************************
 * KERNEL
 ****************************************************************************/

#ifndef RC_INVOKED
/* Versions and the system. */
DWORD WINAPI GetVersion(void);
#if WINVER >= 0x0300
DWORD WINAPI GetWinFlags(void);
#endif
#define WF_PMODE 0x0001
#define WF_CPU286 0x0002
#define WF_CPU386 0x0004
#define WF_CPU486 0x0008
#define WF_STANDARD 0x0010
#define WF_WIN286 0x0010
#define WF_ENHANCED 0x0020
#define WF_WIN386 0x0020
#define WF_CPU086 0x0040
#define WF_CPU186 0x0080
#define WF_LARGEFRAME 0x0100
#define WF_SMALLFRAME 0x0200
#define WF_80x87 0x0400
#define WF_PAGING 0x0800
#define WF_WLO 0x8000

#if WINVER >= 0x0300
LPSTR WINAPI GetDOSEnvironment(void);
#endif
DWORD WINAPI GetTickCount(void); /* both in USER */
DWORD WINAPI GetCurrentTime(void);
#if WINVER >= 0x0300
UINT WINAPI GetWindowsDirectory(LPSTR, UINT);
UINT WINAPI GetSystemDirectory(LPSTR, UINT);
#endif
#if WINVER >= 0x030A
UINT WINAPI GetFreeSystemResources(UINT);
#endif
#define GFSR_SYSTEMRESOURCES 0x0000
#define GFSR_GDIRESOURCES 0x0001
#define GFSR_USERRESOURCES 0x0002

void WINAPI FatalExit(int);
#if WINVER >= 0x0300
void WINAPI FatalAppExit(UINT, LPCSTR);
void WINAPI DebugBreak(void);
#endif
#if WINVER >= 0x0200
void WINAPI OutputDebugString(LPCSTR);
UINT WINAPI SetErrorMode(UINT);
#endif
#define SEM_FAILCRITICALERRORS 0x0001
#define SEM_NOGPFAULTERRORBOX 0x0002
#define SEM_NOOPENFILEERRORBOX 0x8000

/* Tasks and modules. */
HTASK WINAPI GetCurrentTask(void);
#if WINVER >= 0x0200
UINT WINAPI GetNumTasks(void);
#endif
#if WINVER >= 0x030A
BOOL WINAPI IsTask(HTASK);
#endif
void WINAPI Yield(void);
#if WINVER >= 0x0200
void WINAPI DirectedYield(HTASK);
#endif
UINT WINAPI GetCurrentPDB(void);

HINSTANCE WINAPI LoadModule(LPCSTR, LPVOID);
void WINAPI FreeModule(HINSTANCE);
HINSTANCE WINAPI LoadLibrary(LPCSTR);
void WINAPI FreeLibrary(HINSTANCE);
#if WINVER >= 0x0300
UINT WINAPI WinExec(LPCSTR, UINT);
#endif
HMODULE WINAPI GetModuleHandle(LPCSTR);
int WINAPI GetModuleUsage(HINSTANCE);
int WINAPI GetModuleFileName(HINSTANCE, LPSTR, int);
FARPROC WINAPI GetProcAddress(HINSTANCE, LPCSTR);
int WINAPI GetInstanceData(HINSTANCE, BYTE NEAR *, int);
HGLOBAL WINAPI GetCodeHandle(FARPROC);
FARPROC WINAPI MakeProcInstance(FARPROC, HINSTANCE);
void WINAPI FreeProcInstance(FARPROC);
#if WINVER >= 0x0200
WORD WINAPI GetExeVersion(void);
#endif
#if WINVER >= 0x0300
WORD WINAPI GetExpWinVer(HINSTANCE);
#endif

typedef struct tagSEGINFO {
  UINT offSegment;
  UINT cbSegment;
  UINT flags;
  UINT cbAlloc;
  HGLOBAL h;
  UINT alignShift;
  UINT reserved[2];
} SEGINFO;
typedef SEGINFO FAR *LPSEGINFO;
#if WINVER >= 0x0200
void WINAPI GetCodeInfo(FARPROC, SEGINFO FAR *);
#endif

/* Catch and Throw. */
typedef int CATCHBUF[9];
typedef int FAR *LPCATCHBUF;
int WINAPI Catch(int FAR *);
void WINAPI Throw(const int FAR *, int);

/* The global heap. */
#define GMEM_FIXED 0x0000
#define GMEM_MOVEABLE 0x0002
#define GMEM_NOCOMPACT 0x0010
#define GMEM_NODISCARD 0x0020
#define GMEM_ZEROINIT 0x0040
#define GMEM_MODIFY 0x0080
#define GMEM_DISCARDABLE 0x0100
#define GMEM_NOT_BANKED 0x1000
#define GMEM_SHARE 0x2000
#define GMEM_DDESHARE 0x2000
#define GMEM_NOTIFY 0x4000
#define GMEM_LOWER GMEM_NOT_BANKED
#define GHND (GMEM_MOVEABLE | GMEM_ZEROINIT)
#define GPTR (GMEM_FIXED | GMEM_ZEROINIT)
#define GMEM_DISCARDED 0x4000
#define GMEM_LOCKCOUNT 0x00FF

HGLOBAL WINAPI GlobalAlloc(UINT, DWORD);
HGLOBAL WINAPI GlobalReAlloc(HGLOBAL, DWORD, UINT);
HGLOBAL WINAPI GlobalFree(HGLOBAL);
void FAR *WINAPI GlobalLock(HGLOBAL);
BOOL WINAPI GlobalUnlock(HGLOBAL);
DWORD WINAPI GlobalSize(HGLOBAL);
DWORD WINAPI GlobalHandle(UINT);
UINT WINAPI GlobalFlags(HGLOBAL);
DWORD WINAPI GlobalCompact(DWORD);
#define GlobalDiscard(h) GlobalReAlloc((h), 0L, GMEM_MOVEABLE)
#if WINVER >= 0x0200
void WINAPI GlobalNotify(FARPROC);
HGLOBAL WINAPI GlobalLRUNewest(HGLOBAL);
HGLOBAL WINAPI GlobalLRUOldest(HGLOBAL);
void FAR *WINAPI GlobalWire(HGLOBAL);
BOOL WINAPI GlobalUnWire(HGLOBAL);
#endif
#if WINVER >= 0x0300
void WINAPI GlobalFix(HGLOBAL);
void WINAPI GlobalUnfix(HGLOBAL);
UINT WINAPI GlobalPageLock(HGLOBAL);
UINT WINAPI GlobalPageUnlock(HGLOBAL);
DWORD WINAPI GlobalDosAlloc(DWORD);
UINT WINAPI GlobalDosFree(UINT);
DWORD WINAPI GetFreeSpace(UINT);
#endif
UINT WINAPI LockSegment(UINT);
void WINAPI UnlockSegment(UINT);
#define LockData(dummy) LockSegment((UINT)-1)
#define UnlockData(dummy) UnlockSegment((UINT)-1)

/* Selectors (protected mode). */
#if WINVER >= 0x0300
UINT WINAPI AllocSelector(UINT);
UINT WINAPI FreeSelector(UINT);
UINT WINAPI AllocDStoCSAlias(UINT);
UINT WINAPI PrestoChangoSelector(UINT, UINT);
DWORD WINAPI GetSelectorBase(UINT);
UINT WINAPI SetSelectorBase(UINT, DWORD);
DWORD WINAPI GetSelectorLimit(UINT);
UINT WINAPI SetSelectorLimit(UINT, DWORD);
#endif
#if WINVER >= 0x030A
void WINAPI hmemcpy(void __huge *, const void __huge *, long);
long WINAPI _hread(HFILE, void __huge *, long);
long WINAPI _hwrite(HFILE, const void __huge *, long);
#endif

/* The local heap. */
#define LMEM_FIXED 0x0000
#define LMEM_MOVEABLE 0x0002
#define LMEM_NOCOMPACT 0x0010
#define LMEM_NODISCARD 0x0020
#define LMEM_ZEROINIT 0x0040
#define LMEM_MODIFY 0x0080
#define LMEM_DISCARDABLE 0x0F00
#define LHND (LMEM_MOVEABLE | LMEM_ZEROINIT)
#define LPTR (LMEM_FIXED | LMEM_ZEROINIT)
#define NONZEROLHND LMEM_MOVEABLE
#define NONZEROLPTR LMEM_FIXED
#define LMEM_DISCARDED 0x4000
#define LMEM_LOCKCOUNT 0x00FF

BOOL WINAPI LocalInit(UINT, UINT, UINT);
HLOCAL WINAPI LocalAlloc(UINT, UINT);
HLOCAL WINAPI LocalReAlloc(HLOCAL, UINT, UINT);
HLOCAL WINAPI LocalFree(HLOCAL);
void NEAR *WINAPI LocalLock(HLOCAL);
BOOL WINAPI LocalUnlock(HLOCAL);
UINT WINAPI LocalSize(HLOCAL);
HLOCAL WINAPI LocalHandle(UINT);
UINT WINAPI LocalFlags(HLOCAL);
UINT WINAPI LocalCompact(UINT);
#define LocalDiscard(h) LocalReAlloc((h), 0, LMEM_MOVEABLE)
#if WINVER >= 0x0200
UINT WINAPI LocalShrink(HLOCAL, UINT);
#endif

/* Resources. */
#define RT_CURSOR MAKEINTRESOURCE(1)
#define RT_BITMAP MAKEINTRESOURCE(2)
#define RT_ICON MAKEINTRESOURCE(3)
#define RT_MENU MAKEINTRESOURCE(4)
#define RT_DIALOG MAKEINTRESOURCE(5)
#define RT_STRING MAKEINTRESOURCE(6)
#define RT_FONTDIR MAKEINTRESOURCE(7)
#define RT_FONT MAKEINTRESOURCE(8)
#define RT_ACCELERATOR MAKEINTRESOURCE(9)
#define RT_RCDATA MAKEINTRESOURCE(10)
#define RT_GROUP_CURSOR MAKEINTRESOURCE(12)
#define RT_GROUP_ICON MAKEINTRESOURCE(14)

HRSRC WINAPI FindResource(HINSTANCE, LPCSTR, LPCSTR);
HGLOBAL WINAPI LoadResource(HINSTANCE, HRSRC);
void FAR *WINAPI LockResource(HGLOBAL);
#define UnlockResource(h) GlobalUnlock(h)
BOOL WINAPI FreeResource(HGLOBAL);
DWORD WINAPI SizeofResource(HINSTANCE, HRSRC);
int WINAPI AccessResource(HINSTANCE, HRSRC);
HGLOBAL WINAPI AllocResource(HINSTANCE, HRSRC, DWORD);
typedef HGLOBAL(CALLBACK *RSRCHDLRPROC)(HGLOBAL, HINSTANCE, HRSRC);
RSRCHDLRPROC WINAPI SetResourceHandler(HINSTANCE, LPCSTR, RSRCHDLRPROC);

/* Atoms. */
#ifndef NOATOM
BOOL WINAPI InitAtomTable(int);
ATOM WINAPI AddAtom(LPCSTR);
ATOM WINAPI DeleteAtom(ATOM);
ATOM WINAPI FindAtom(LPCSTR);
UINT WINAPI GetAtomName(ATOM, LPSTR, int);
HLOCAL WINAPI GetAtomHandle(ATOM);
#endif

/* Strings. */
int WINAPI lstrlen(LPCSTR);
LPSTR WINAPI lstrcpy(LPSTR, LPCSTR);
LPSTR WINAPI lstrcat(LPSTR, LPCSTR);
#if WINVER >= 0x030A
LPSTR WINAPI lstrcpyn(LPSTR, LPCSTR, int);
#endif
int WINAPI lstrcmp(LPCSTR, LPCSTR); /* KERNEL in 1.x and 2.x, USER from 3.0 */
#if WINVER >= 0x0300
int WINAPI lstrcmpi(LPCSTR, LPCSTR);
#endif
LPSTR WINAPI AnsiUpper(LPSTR); /* also KERNEL in 1.x and 2.x */
LPSTR WINAPI AnsiLower(LPSTR);
LPSTR WINAPI AnsiNext(LPCSTR);
LPSTR WINAPI AnsiPrev(LPCSTR, LPCSTR);
#if WINVER >= 0x030A
BOOL WINAPI IsDBCSLeadByte(BYTE);
#endif

/* Profiles (WIN.INI and private .INI files). */
UINT WINAPI GetProfileInt(LPCSTR, LPCSTR, int);
int WINAPI GetProfileString(LPCSTR, LPCSTR, LPCSTR, LPSTR, int);
BOOL WINAPI WriteProfileString(LPCSTR, LPCSTR, LPCSTR);
#if WINVER >= 0x0300
UINT WINAPI GetPrivateProfileInt(LPCSTR, LPCSTR, int, LPCSTR);
int WINAPI GetPrivateProfileString(LPCSTR, LPCSTR, LPCSTR, LPSTR, int,
                                   LPCSTR);
BOOL WINAPI WritePrivateProfileString(LPCSTR, LPCSTR, LPCSTR, LPCSTR);
#endif

/* Files. */
#ifndef NOLFILEIO
#define READ 0
#define WRITE 1
#define READ_WRITE 2
#define OF_READ 0x0000
#define OF_WRITE 0x0001
#define OF_READWRITE 0x0002
#define OF_SHARE_COMPAT 0x0000
#define OF_SHARE_EXCLUSIVE 0x0010
#define OF_SHARE_DENY_WRITE 0x0020
#define OF_SHARE_DENY_READ 0x0030
#define OF_SHARE_DENY_NONE 0x0040
#define OF_PARSE 0x0100
#define OF_DELETE 0x0200
#define OF_VERIFY 0x0400
#define OF_SEARCH 0x0400
#define OF_CANCEL 0x0800
#define OF_CREATE 0x1000
#define OF_PROMPT 0x2000
#define OF_EXIST 0x4000
#define OF_REOPEN 0x8000

typedef struct tagOFSTRUCT {
  BYTE cBytes;
  BYTE fFixedDisk;
  UINT nErrCode;
  BYTE reserved[4];
  char szPathName[128];
} OFSTRUCT;
typedef OFSTRUCT NEAR *POFSTRUCT;
typedef OFSTRUCT FAR *LPOFSTRUCT;

HFILE WINAPI OpenFile(LPCSTR, OFSTRUCT FAR *, UINT);
HFILE WINAPI _lopen(LPCSTR, int);
HFILE WINAPI _lcreat(LPCSTR, int);
HFILE WINAPI _lclose(HFILE);
LONG WINAPI _llseek(HFILE, LONG, int);
UINT WINAPI _lread(HFILE, void __huge *, UINT);
UINT WINAPI _lwrite(HFILE, const void __huge *, UINT);
#define lopen _lopen
#define lcreat _lcreat
#define lclose _lclose
#define llseek _llseek
#define lread _lread
#define lwrite _lwrite

BYTE WINAPI GetTempDrive(char);
int WINAPI GetTempFileName(BYTE, LPCSTR, UINT, LPSTR);
#define TF_FORCEDRIVE ((BYTE)0x80)
#if WINVER >= 0x0300
UINT WINAPI SetHandleCount(UINT);
UINT WINAPI GetDriveType(int);
#endif
#define DRIVE_REMOVABLE 2
#define DRIVE_FIXED 3
#define DRIVE_REMOTE 4
#endif /* NOLFILEIO */

#if WINVER >= 0x0200
void WINAPI DOS3Call(void);
void WINAPI NetBIOSCall(void);
#endif

/* Errors reported by LogError (WINVER 3.1) and LogParamError. */
#if WINVER >= 0x030A && !defined(NOLOGERROR)
void WINAPI LogError(UINT, void FAR *);
void WINAPI LogParamError(UINT, FARPROC, void FAR *);
BOOL WINAPI IsBadReadPtr(const void FAR *, UINT);
BOOL WINAPI IsBadWritePtr(void FAR *, UINT);
BOOL WINAPI IsBadHugeReadPtr(const void __huge *, DWORD);
BOOL WINAPI IsBadHugeWritePtr(void __huge *, DWORD);
BOOL WINAPI IsBadCodePtr(FARPROC);
BOOL WINAPI IsBadStringPtr(const void FAR *, UINT);
#endif

#endif /* RC_INVOKED */

/****************************************************************************
 * USER
 ****************************************************************************/

#ifndef RC_INVOKED
/* Callbacks. Without STRICT they are FARPROCs, as in the Windows SDK, so
 * that the result of MakeProcInstance can be passed as it is; with STRICT
 * each has its prototype. */
#ifdef STRICT
typedef BOOL(CALLBACK *WNDENUMPROC)(HWND, LPARAM);
typedef void(CALLBACK *TIMERPROC)(HWND, UINT, UINT, DWORD);
typedef LRESULT(CALLBACK *HOOKPROC)(int, WPARAM, LPARAM);
typedef BOOL(CALLBACK *GRAYSTRINGPROC)(HDC, LPARAM, int);
typedef BOOL(CALLBACK *PROPENUMPROC)(HWND, LPCSTR, HANDLE);
typedef int(CALLBACK *EDITWORDBREAKPROC)(LPSTR, int, int, int);
#else
typedef FARPROC WNDENUMPROC;
typedef FARPROC TIMERPROC;
typedef FARPROC HOOKPROC;
typedef FARPROC GRAYSTRINGPROC;
typedef FARPROC PROPENUMPROC;
typedef FARPROC EDITWORDBREAKPROC;
#endif

/* Messages. */
typedef struct tagMSG {
  HWND hwnd;
  UINT message;
  WPARAM wParam;
  LPARAM lParam;
  DWORD time;
  POINT pt;
} MSG;
typedef MSG NEAR *PMSG;
typedef MSG NEAR *NPMSG;
typedef MSG FAR *LPMSG;
#endif /* RC_INVOKED */

#define WM_NULL 0x0000
#define WM_CREATE 0x0001
#define WM_DESTROY 0x0002
#define WM_MOVE 0x0003
#define WM_SIZE 0x0005
#define WM_ACTIVATE 0x0006
#define WM_SETFOCUS 0x0007
#define WM_KILLFOCUS 0x0008
#define WM_ENABLE 0x000A
#define WM_SETREDRAW 0x000B
#define WM_SETTEXT 0x000C
#define WM_GETTEXT 0x000D
#define WM_GETTEXTLENGTH 0x000E
#define WM_PAINT 0x000F
#define WM_CLOSE 0x0010
#define WM_QUERYENDSESSION 0x0011
#define WM_QUIT 0x0012
#define WM_QUERYOPEN 0x0013
#define WM_ERASEBKGND 0x0014
#define WM_SYSCOLORCHANGE 0x0015
#define WM_ENDSESSION 0x0016
#define WM_SYSTEMERROR 0x0017
#define WM_SHOWWINDOW 0x0018
#define WM_CTLCOLOR 0x0019
#define WM_WININICHANGE 0x001A
#define WM_DEVMODECHANGE 0x001B
#define WM_ACTIVATEAPP 0x001C
#define WM_FONTCHANGE 0x001D
#define WM_TIMECHANGE 0x001E
#define WM_CANCELMODE 0x001F
#define WM_SETCURSOR 0x0020
#define WM_MOUSEACTIVATE 0x0021
#define WM_CHILDACTIVATE 0x0022
#define WM_QUEUESYNC 0x0023
#define WM_GETMINMAXINFO 0x0024
#define WM_PAINTICON 0x0026
#define WM_ICONERASEBKGND 0x0027
#define WM_NEXTDLGCTL 0x0028
#define WM_SPOOLERSTATUS 0x002A
#define WM_DRAWITEM 0x002B
#define WM_MEASUREITEM 0x002C
#define WM_DELETEITEM 0x002D
#define WM_VKEYTOITEM 0x002E
#define WM_CHARTOITEM 0x002F
#define WM_SETFONT 0x0030
#define WM_GETFONT 0x0031
#define WM_QUERYDRAGICON 0x0037
#define WM_COMPAREITEM 0x0039
#define WM_COMPACTING 0x0041
#define WM_COMMNOTIFY 0x0044
#define WM_WINDOWPOSCHANGING 0x0046
#define WM_WINDOWPOSCHANGED 0x0047
#define WM_POWER 0x0048
#define WM_NCCREATE 0x0081
#define WM_NCDESTROY 0x0082
#define WM_NCCALCSIZE 0x0083
#define WM_NCHITTEST 0x0084
#define WM_NCPAINT 0x0085
#define WM_NCACTIVATE 0x0086
#define WM_GETDLGCODE 0x0087
#define WM_NCMOUSEMOVE 0x00A0
#define WM_NCLBUTTONDOWN 0x00A1
#define WM_NCLBUTTONUP 0x00A2
#define WM_NCLBUTTONDBLCLK 0x00A3
#define WM_NCRBUTTONDOWN 0x00A4
#define WM_NCRBUTTONUP 0x00A5
#define WM_NCRBUTTONDBLCLK 0x00A6
#define WM_NCMBUTTONDOWN 0x00A7
#define WM_NCMBUTTONUP 0x00A8
#define WM_NCMBUTTONDBLCLK 0x00A9
#define WM_KEYFIRST 0x0100
#define WM_KEYDOWN 0x0100
#define WM_KEYUP 0x0101
#define WM_CHAR 0x0102
#define WM_DEADCHAR 0x0103
#define WM_SYSKEYDOWN 0x0104
#define WM_SYSKEYUP 0x0105
#define WM_SYSCHAR 0x0106
#define WM_SYSDEADCHAR 0x0107
#define WM_KEYLAST 0x0108
#define WM_INITDIALOG 0x0110
#define WM_COMMAND 0x0111
#define WM_SYSCOMMAND 0x0112
#define WM_TIMER 0x0113
#define WM_HSCROLL 0x0114
#define WM_VSCROLL 0x0115
#define WM_INITMENU 0x0116
#define WM_INITMENUPOPUP 0x0117
#define WM_MENUSELECT 0x011F
#define WM_MENUCHAR 0x0120
#define WM_ENTERIDLE 0x0121
#define WM_MOUSEFIRST 0x0200
#define WM_MOUSEMOVE 0x0200
#define WM_LBUTTONDOWN 0x0201
#define WM_LBUTTONUP 0x0202
#define WM_LBUTTONDBLCLK 0x0203
#define WM_RBUTTONDOWN 0x0204
#define WM_RBUTTONUP 0x0205
#define WM_RBUTTONDBLCLK 0x0206
#define WM_MBUTTONDOWN 0x0207
#define WM_MBUTTONUP 0x0208
#define WM_MBUTTONDBLCLK 0x0209
#define WM_MOUSELAST 0x0209
#define WM_PARENTNOTIFY 0x0210
#define WM_MDICREATE 0x0220
#define WM_MDIDESTROY 0x0221
#define WM_MDIACTIVATE 0x0222
#define WM_MDIRESTORE 0x0223
#define WM_MDINEXT 0x0224
#define WM_MDIMAXIMIZE 0x0225
#define WM_MDITILE 0x0226
#define WM_MDICASCADE 0x0227
#define WM_MDIICONARRANGE 0x0228
#define WM_MDIGETACTIVE 0x0229
#define WM_MDISETMENU 0x0230
#define WM_DROPFILES 0x0233
#define WM_CUT 0x0300
#define WM_COPY 0x0301
#define WM_PASTE 0x0302
#define WM_CLEAR 0x0303
#define WM_UNDO 0x0304
#define WM_RENDERFORMAT 0x0305
#define WM_RENDERALLFORMATS 0x0306
#define WM_DESTROYCLIPBOARD 0x0307
#define WM_DRAWCLIPBOARD 0x0308
#define WM_PAINTCLIPBOARD 0x0309
#define WM_VSCROLLCLIPBOARD 0x030A
#define WM_SIZECLIPBOARD 0x030B
#define WM_ASKCBFORMATNAME 0x030C
#define WM_CHANGECBCHAIN 0x030D
#define WM_HSCROLLCLIPBOARD 0x030E
#define WM_QUERYNEWPALETTE 0x030F
#define WM_PALETTEISCHANGING 0x0310
#define WM_PALETTECHANGED 0x0311
#define WM_PENWINFIRST 0x0380
#define WM_PENWINLAST 0x038F
#define WM_COALESCE_FIRST 0x0390
#define WM_COALESCE_LAST 0x039F
#define WM_USER 0x0400

/* WM_ACTIVATE. */
#define WA_INACTIVE 0
#define WA_ACTIVE 1
#define WA_CLICKACTIVE 2
/* WM_SIZE. */
#define SIZE_RESTORED 0
#define SIZE_MINIMIZED 1
#define SIZE_MAXIMIZED 2
#define SIZE_MAXSHOW 3
#define SIZE_MAXHIDE 4
#define SIZENORMAL SIZE_RESTORED
#define SIZEICONIC SIZE_MINIMIZED
#define SIZEFULLSCREEN SIZE_MAXIMIZED
#define SIZEZOOMSHOW SIZE_MAXSHOW
#define SIZEZOOMHIDE SIZE_MAXHIDE
/* WM_SHOWWINDOW. */
#define SW_PARENTCLOSING 1
#define SW_OTHERZOOM 2
#define SW_PARENTOPENING 3
#define SW_OTHERUNZOOM 4
/* WM_NCHITTEST. */
#define HTERROR (-2)
#define HTTRANSPARENT (-1)
#define HTNOWHERE 0
#define HTCLIENT 1
#define HTCAPTION 2
#define HTSYSMENU 3
#define HTGROWBOX 4
#define HTSIZE HTGROWBOX
#define HTMENU 5
#define HTHSCROLL 6
#define HTVSCROLL 7
#define HTMINBUTTON 8
#define HTREDUCE HTMINBUTTON
#define HTMAXBUTTON 9
#define HTZOOM HTMAXBUTTON
#define HTLEFT 10
#define HTRIGHT 11
#define HTTOP 12
#define HTTOPLEFT 13
#define HTTOPRIGHT 14
#define HTBOTTOM 15
#define HTBOTTOMLEFT 16
#define HTBOTTOMRIGHT 17
#define HTBORDER 18
#define HTSIZEFIRST HTLEFT
#define HTSIZELAST HTBOTTOMRIGHT
/* WM_MOUSEACTIVATE. */
#define MA_ACTIVATE 1
#define MA_ACTIVATEANDEAT 2
#define MA_NOACTIVATE 3
/* Mouse message wParam. */
#define MK_LBUTTON 0x0001
#define MK_RBUTTON 0x0002
#define MK_SHIFT 0x0004
#define MK_CONTROL 0x0008
#define MK_MBUTTON 0x0010
/* WM_CTLCOLOR. */
#define CTLCOLOR_MSGBOX 0
#define CTLCOLOR_EDIT 1
#define CTLCOLOR_LISTBOX 2
#define CTLCOLOR_BTN 3
#define CTLCOLOR_DLG 4
#define CTLCOLOR_SCROLLBAR 5
#define CTLCOLOR_STATIC 6
/* WM_SYSCOMMAND. */
#define SC_SIZE 0xF000
#define SC_MOVE 0xF010
#define SC_MINIMIZE 0xF020
#define SC_MAXIMIZE 0xF030
#define SC_NEXTWINDOW 0xF040
#define SC_PREVWINDOW 0xF050
#define SC_CLOSE 0xF060
#define SC_VSCROLL 0xF070
#define SC_HSCROLL 0xF080
#define SC_MOUSEMENU 0xF090
#define SC_KEYMENU 0xF100
#define SC_ARRANGE 0xF110
#define SC_RESTORE 0xF120
#define SC_TASKLIST 0xF130
#define SC_SCREENSAVE 0xF140
#define SC_HOTKEY 0xF150
#define SC_ICON SC_MINIMIZE
#define SC_ZOOM SC_MAXIMIZE
/* WM_POWER. */
#define PWR_OK 1
#define PWR_FAIL (-1)
#define PWR_SUSPENDREQUEST 1
#define PWR_SUSPENDRESUME 2
#define PWR_CRITICALRESUME 3
/* WM_QUEUESYNC, WM_COMMNOTIFY. */
#define CN_RECEIVE 0x0001
#define CN_TRANSMIT 0x0002
#define CN_EVENT 0x0004

#ifndef RC_INVOKED
#ifndef NOMSG
BOOL WINAPI GetMessage(MSG FAR *, HWND, UINT, UINT);
BOOL WINAPI PeekMessage(MSG FAR *, HWND, UINT, UINT, UINT);
BOOL WINAPI TranslateMessage(const MSG FAR *);
LONG WINAPI DispatchMessage(const MSG FAR *);
BOOL WINAPI PostMessage(HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI SendMessage(HWND, UINT, WPARAM, LPARAM);
BOOL WINAPI PostAppMessage(HTASK, UINT, WPARAM, LPARAM);
void WINAPI PostQuitMessage(int);
void WINAPI WaitMessage(void);
void WINAPI ReplyMessage(LRESULT);
BOOL WINAPI InSendMessage(void);
DWORD WINAPI GetMessagePos(void);
LONG WINAPI GetMessageTime(void);
#if WINVER >= 0x030A
LPARAM WINAPI GetMessageExtraInfo(void);
#endif
#if WINVER >= 0x0200
DWORD WINAPI GetQueueStatus(UINT);
BOOL WINAPI SetMessageQueue(int);
BOOL WINAPI GetInputState(void);
#endif
UINT WINAPI RegisterWindowMessage(LPCSTR);
BOOL WINAPI CallMsgFilter(MSG FAR *, int);
#endif /* NOMSG */
#define PM_NOREMOVE 0x0000
#define PM_REMOVE 0x0001
#define PM_NOYIELD 0x0002
#define QS_KEY 0x0001
#define QS_MOUSEMOVE 0x0002
#define QS_MOUSEBUTTON 0x0004
#define QS_MOUSE (QS_MOUSEMOVE | QS_MOUSEBUTTON)
#define QS_POSTMESSAGE 0x0008
#define QS_TIMER 0x0010
#define QS_PAINT 0x0020
#define QS_SENDMESSAGE 0x0040
#define QS_ALLINPUT 0x007F
#define HWND_BROADCAST ((HWND)0xFFFF)

/* Window classes. */
typedef struct tagWNDCLASS {
  UINT style;
  WNDPROC lpfnWndProc;
  int cbClsExtra;
  int cbWndExtra;
  HINSTANCE hInstance;
  HICON hIcon;
  HCURSOR hCursor;
  HBRUSH hbrBackground;
  LPCSTR lpszMenuName;
  LPCSTR lpszClassName;
} WNDCLASS;
typedef WNDCLASS NEAR *PWNDCLASS;
typedef WNDCLASS NEAR *NPWNDCLASS;
typedef WNDCLASS FAR *LPWNDCLASS;
typedef const WNDCLASS FAR *LPCWNDCLASS;

ATOM WINAPI RegisterClass(const WNDCLASS FAR *);
#if WINVER >= 0x0300
BOOL WINAPI UnregisterClass(LPCSTR, HINSTANCE);
BOOL WINAPI GetClassInfo(HINSTANCE, LPCSTR, WNDCLASS FAR *);
#endif
int WINAPI GetClassName(HWND, LPSTR, int);
WORD WINAPI GetClassWord(HWND, int);
WORD WINAPI SetClassWord(HWND, int, WORD);
LONG WINAPI GetClassLong(HWND, int);
LONG WINAPI SetClassLong(HWND, int, LONG);
#endif /* RC_INVOKED */

#define CS_VREDRAW 0x0001
#define CS_HREDRAW 0x0002
#define CS_KEYCVTWINDOW 0x0004
#define CS_DBLCLKS 0x0008
#define CS_OWNDC 0x0020
#define CS_CLASSDC 0x0040
#define CS_PARENTDC 0x0080
#define CS_NOKEYCVT 0x0100
#define CS_NOCLOSE 0x0200
#define CS_SAVEBITS 0x0800
#define CS_BYTEALIGNCLIENT 0x1000
#define CS_BYTEALIGNWINDOW 0x2000
#define CS_GLOBALCLASS 0x4000
#define GCL_MENUNAME (-8)
#define GCW_HBRBACKGROUND (-10)
#define GCW_HCURSOR (-12)
#define GCW_HICON (-14)
#define GCW_HMODULE (-16)
#define GCW_CBWNDEXTRA (-18)
#define GCW_CBCLSEXTRA (-20)
#define GCL_WNDPROC (-24)
#define GCW_STYLE (-26)
#define GCW_ATOM (-32)

/* Window styles. */
#define WS_OVERLAPPED 0x00000000L
#define WS_POPUP 0x80000000L
#define WS_CHILD 0x40000000L
#define WS_CLIPSIBLINGS 0x04000000L
#define WS_CLIPCHILDREN 0x02000000L
#define WS_VISIBLE 0x10000000L
#define WS_DISABLED 0x08000000L
#define WS_MINIMIZE 0x20000000L
#define WS_MAXIMIZE 0x01000000L
#define WS_CAPTION 0x00C00000L
#define WS_BORDER 0x00800000L
#define WS_DLGFRAME 0x00400000L
#define WS_VSCROLL 0x00200000L
#define WS_HSCROLL 0x00100000L
#define WS_SYSMENU 0x00080000L
#define WS_THICKFRAME 0x00040000L
#define WS_MINIMIZEBOX 0x00020000L
#define WS_MAXIMIZEBOX 0x00010000L
#define WS_GROUP 0x00020000L
#define WS_TABSTOP 0x00010000L
#define WS_OVERLAPPEDWINDOW                                                    \
  (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | \
   WS_MAXIMIZEBOX)
#define WS_POPUPWINDOW (WS_POPUP | WS_BORDER | WS_SYSMENU)
#define WS_CHILDWINDOW WS_CHILD
#define WS_TILED WS_OVERLAPPED
#define WS_ICONIC WS_MINIMIZE
#define WS_SIZEBOX WS_THICKFRAME
#define WS_TILEDWINDOW WS_OVERLAPPEDWINDOW
#define WS_EX_DLGMODALFRAME 0x00000001L
#define WS_EX_NOPARENTNOTIFY 0x00000004L
#define WS_EX_TOPMOST 0x00000008L
#define WS_EX_ACCEPTFILES 0x00000010L
#define WS_EX_TRANSPARENT 0x00000020L
#define CW_USEDEFAULT ((int)0x8000)

#define GWL_WNDPROC (-4)
#define GWW_HINSTANCE (-6)
#define GWW_HWNDPARENT (-8)
#define GWW_ID (-12)
#define GWL_STYLE (-16)
#define GWL_EXSTYLE (-20)

#define SW_HIDE 0
#define SW_SHOWNORMAL 1
#define SW_NORMAL 1
#define SW_SHOWMINIMIZED 2
#define SW_SHOWMAXIMIZED 3
#define SW_MAXIMIZE 3
#define SW_SHOWNOACTIVATE 4
#define SW_SHOW 5
#define SW_MINIMIZE 6
#define SW_SHOWMINNOACTIVE 7
#define SW_SHOWNA 8
#define SW_RESTORE 9
#define HIDE_WINDOW 0
#define SHOW_OPENWINDOW 1
#define SHOW_ICONWINDOW 2
#define SHOW_FULLSCREEN 3
#define SHOW_OPENNOACTIVATE 4

#define SWP_NOSIZE 0x0001
#define SWP_NOMOVE 0x0002
#define SWP_NOZORDER 0x0004
#define SWP_NOREDRAW 0x0008
#define SWP_NOACTIVATE 0x0010
#define SWP_FRAMECHANGED 0x0020
#define SWP_DRAWFRAME SWP_FRAMECHANGED
#define SWP_SHOWWINDOW 0x0040
#define SWP_HIDEWINDOW 0x0080
#define SWP_NOCOPYBITS 0x0100
#define SWP_NOOWNERZORDER 0x0200
#define SWP_NOREPOSITION SWP_NOOWNERZORDER
#define HWND_DESKTOP ((HWND)0)
#define HWND_TOP ((HWND)0)
#define HWND_BOTTOM ((HWND)1)
#define HWND_TOPMOST ((HWND)-1)
#define HWND_NOTOPMOST ((HWND)-2)

#define GW_HWNDFIRST 0
#define GW_HWNDLAST 1
#define GW_HWNDNEXT 2
#define GW_HWNDPREV 3
#define GW_OWNER 4
#define GW_CHILD 5

#define WPF_SETMINPOSITION 0x0001
#define WPF_RESTORETOMAXIMIZED 0x0002

#define RDW_INVALIDATE 0x0001
#define RDW_INTERNALPAINT 0x0002
#define RDW_ERASE 0x0004
#define RDW_VALIDATE 0x0008
#define RDW_NOINTERNALPAINT 0x0010
#define RDW_NOERASE 0x0020
#define RDW_NOCHILDREN 0x0040
#define RDW_ALLCHILDREN 0x0080
#define RDW_UPDATENOW 0x0100
#define RDW_ERASENOW 0x0200
#define RDW_FRAME 0x0400
#define RDW_NOFRAME 0x0800

#define DCX_WINDOW 0x00000001L
#define DCX_CACHE 0x00000002L
#define DCX_CLIPCHILDREN 0x00000008L
#define DCX_CLIPSIBLINGS 0x00000010L
#define DCX_PARENTCLIP 0x00000020L
#define DCX_EXCLUDERGN 0x00000040L
#define DCX_INTERSECTRGN 0x00000080L
#define DCX_LOCKWINDOWUPDATE 0x00000400L
#define DCX_USESTYLE 0x00010000L

#define SW_SCROLLCHILDREN 0x0001
#define SW_INVALIDATE 0x0002
#define SW_ERASE 0x0004

#ifndef RC_INVOKED
typedef struct tagCREATESTRUCT {
  void FAR *lpCreateParams;
  HINSTANCE hInstance;
  HMENU hMenu;
  HWND hwndParent;
  int cy;
  int cx;
  int y;
  int x;
  LONG style;
  LPCSTR lpszName;
  LPCSTR lpszClass;
  DWORD dwExStyle;
} CREATESTRUCT;
typedef CREATESTRUCT FAR *LPCREATESTRUCT;

typedef struct tagWINDOWPOS {
  HWND hwnd;
  HWND hwndInsertAfter;
  int x;
  int y;
  int cx;
  int cy;
  UINT flags;
} WINDOWPOS;
typedef WINDOWPOS FAR *LPWINDOWPOS;

typedef struct tagNCCALCSIZE_PARAMS {
  RECT rgrc[3];
  WINDOWPOS FAR *lppos;
} NCCALCSIZE_PARAMS;
typedef NCCALCSIZE_PARAMS FAR *LPNCCALCSIZE_PARAMS;
#define WVR_ALIGNTOP 0x0010
#define WVR_ALIGNLEFT 0x0020
#define WVR_ALIGNBOTTOM 0x0040
#define WVR_ALIGNRIGHT 0x0080
#define WVR_HREDRAW 0x0100
#define WVR_VREDRAW 0x0200
#define WVR_REDRAW (WVR_HREDRAW | WVR_VREDRAW)
#define WVR_VALIDRECTS 0x0400

typedef struct tagMINMAXINFO {
  POINT ptReserved;
  POINT ptMaxSize;
  POINT ptMaxPosition;
  POINT ptMinTrackSize;
  POINT ptMaxTrackSize;
} MINMAXINFO;

typedef struct tagWINDOWPLACEMENT {
  UINT length;
  UINT flags;
  UINT showCmd;
  POINT ptMinPosition;
  POINT ptMaxPosition;
  RECT rcNormalPosition;
} WINDOWPLACEMENT;
typedef WINDOWPLACEMENT FAR *LPWINDOWPLACEMENT;

typedef struct tagPAINTSTRUCT {
  HDC hdc;
  BOOL fErase;
  RECT rcPaint;
  BOOL fRestore;
  BOOL fIncUpdate;
  BYTE rgbReserved[16];
} PAINTSTRUCT;
typedef PAINTSTRUCT NEAR *PPAINTSTRUCT;
typedef PAINTSTRUCT NEAR *NPPAINTSTRUCT;
typedef PAINTSTRUCT FAR *LPPAINTSTRUCT;

/* Windows. */
HWND WINAPI CreateWindow(LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND,
                         HMENU, HINSTANCE, void FAR *);
#if WINVER >= 0x0300
HWND WINAPI CreateWindowEx(DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int,
                           HWND, HMENU, HINSTANCE, void FAR *);
#endif
BOOL WINAPI DestroyWindow(HWND);
BOOL WINAPI IsWindow(HWND);
BOOL WINAPI ShowWindow(HWND, int);
void WINAPI CloseWindow(HWND);
BOOL WINAPI OpenIcon(HWND);
void WINAPI MoveWindow(HWND, int, int, int, int, BOOL);
#if WINVER >= 0x030A
BOOL WINAPI SetWindowPos(HWND, HWND, int, int, int, int, UINT);
#elif WINVER >= 0x0200
void WINAPI SetWindowPos(HWND, HWND, int, int, int, int, UINT);
#endif
#if WINVER >= 0x0200
HDWP WINAPI BeginDeferWindowPos(int);
HDWP WINAPI DeferWindowPos(HDWP, HWND, HWND, int, int, int, int, UINT);
void WINAPI EndDeferWindowPos(HDWP);
#endif
#if WINVER >= 0x030A
BOOL WINAPI GetWindowPlacement(HWND, WINDOWPLACEMENT FAR *);
BOOL WINAPI SetWindowPlacement(HWND, const WINDOWPLACEMENT FAR *);
#endif
BOOL WINAPI IsWindowVisible(HWND);
BOOL WINAPI IsIconic(HWND);
#if WINVER >= 0x0200
BOOL WINAPI IsZoomed(HWND);
#endif
BOOL WINAPI AnyPopup(void);
void WINAPI BringWindowToTop(HWND);
BOOL WINAPI IsChild(HWND, HWND);
BOOL WINAPI EnableWindow(HWND, BOOL);
BOOL WINAPI IsWindowEnabled(HWND);
HWND WINAPI GetParent(HWND);
#if WINVER >= 0x0200
HWND WINAPI SetParent(HWND, HWND);
#endif
HWND WINAPI FindWindow(LPCSTR, LPCSTR);
BOOL WINAPI EnumWindows(WNDENUMPROC, LPARAM);
BOOL WINAPI EnumChildWindows(HWND, WNDENUMPROC, LPARAM);
#if WINVER >= 0x0200
BOOL WINAPI EnumTaskWindows(HTASK, WNDENUMPROC, LPARAM);
HWND WINAPI GetWindow(HWND, UINT);
HWND WINAPI GetNextWindow(HWND, UINT);
HWND WINAPI GetTopWindow(HWND);
HTASK WINAPI GetWindowTask(HWND);
#endif
#if WINVER >= 0x0300
HWND WINAPI GetLastActivePopup(HWND);
HWND WINAPI GetDesktopWindow(void);
#endif
HWND WINAPI GetActiveWindow(void);
HWND WINAPI SetActiveWindow(HWND);
HWND WINAPI GetFocus(void);
HWND WINAPI SetFocus(HWND);
#if WINVER >= 0x0200
HWND WINAPI GetCapture(void);
#endif
HWND WINAPI SetCapture(HWND);
void WINAPI ReleaseCapture(void);
HWND WINAPI GetSysModalWindow(void);
HWND WINAPI SetSysModalWindow(HWND);
HWND WINAPI WindowFromPoint(POINT);
HWND WINAPI ChildWindowFromPoint(HWND, POINT);
WORD WINAPI GetWindowWord(HWND, int);
WORD WINAPI SetWindowWord(HWND, int, WORD);
LONG WINAPI GetWindowLong(HWND, int);
LONG WINAPI SetWindowLong(HWND, int, LONG);
int WINAPI GetWindowText(HWND, LPSTR, int);
void WINAPI SetWindowText(HWND, LPCSTR);
int WINAPI GetWindowTextLength(HWND);
void WINAPI GetClientRect(HWND, RECT FAR *);
void WINAPI GetWindowRect(HWND, RECT FAR *);
void WINAPI AdjustWindowRect(RECT FAR *, DWORD, BOOL);
#if WINVER >= 0x0300
void WINAPI AdjustWindowRectEx(RECT FAR *, DWORD, BOOL, DWORD);
#endif
void WINAPI ClientToScreen(HWND, POINT FAR *);
void WINAPI ScreenToClient(HWND, POINT FAR *);
#if WINVER >= 0x030A
void WINAPI MapWindowPoints(HWND, HWND, POINT FAR *, UINT);
#endif
BOOL WINAPI FlashWindow(HWND, BOOL);
#if WINVER >= 0x0200
void WINAPI ShowOwnedPopups(HWND, BOOL);
#endif
#if WINVER >= 0x0300
UINT WINAPI ArrangeIconicWindows(HWND);
#endif
BOOL WINAPI SetProp(HWND, LPCSTR, HANDLE);
HANDLE WINAPI GetProp(HWND, LPCSTR);
HANDLE WINAPI RemoveProp(HWND, LPCSTR);
int WINAPI EnumProps(HWND, PROPENUMPROC);

LRESULT WINAPI DefWindowProc(HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI CallWindowProc(WNDPROC, HWND, UINT, WPARAM, LPARAM);

/* Painting. */
HDC WINAPI BeginPaint(HWND, PAINTSTRUCT FAR *);
void WINAPI EndPaint(HWND, const PAINTSTRUCT FAR *);
HDC WINAPI GetDC(HWND);
HDC WINAPI GetWindowDC(HWND);
int WINAPI ReleaseDC(HWND, HDC);
#if WINVER >= 0x030A
HDC WINAPI GetDCEx(HWND, HRGN, DWORD);
BOOL WINAPI RedrawWindow(HWND, const RECT FAR *, HRGN, UINT);
BOOL WINAPI LockWindowUpdate(HWND);
int WINAPI ScrollWindowEx(HWND, int, int, const RECT FAR *, const RECT FAR *,
                          HRGN, RECT FAR *, UINT);
#endif
void WINAPI UpdateWindow(HWND);
BOOL WINAPI GetUpdateRect(HWND, RECT FAR *, BOOL);
#if WINVER >= 0x0200
int WINAPI GetUpdateRgn(HWND, HRGN, BOOL);
int WINAPI ExcludeUpdateRgn(HDC, HWND);
#endif
void WINAPI InvalidateRect(HWND, const RECT FAR *, BOOL);
void WINAPI ValidateRect(HWND, const RECT FAR *);
void WINAPI InvalidateRgn(HWND, HRGN, BOOL);
void WINAPI ValidateRgn(HWND, HRGN);
void WINAPI ScrollWindow(HWND, int, int, const RECT FAR *, const RECT FAR *);
#if WINVER >= 0x0200
BOOL WINAPI ScrollDC(HDC, int, int, const RECT FAR *, const RECT FAR *, HRGN,
                     RECT FAR *);
#endif
BOOL WINAPI DrawIcon(HDC, int, int, HICON);
int WINAPI DrawText(HDC, LPCSTR, int, RECT FAR *, UINT);
BOOL WINAPI GrayString(HDC, HBRUSH, GRAYSTRINGPROC, LPARAM, int, int, int, int,
                       int);
#if WINVER >= 0x0300
LONG WINAPI TabbedTextOut(HDC, int, int, LPCSTR, int, int, int FAR *, int);
DWORD WINAPI GetTabbedTextExtent(HDC, LPCSTR, int, int, int FAR *);
#endif
int WINAPI FillRect(HDC, const RECT FAR *, HBRUSH);
int WINAPI FrameRect(HDC, const RECT FAR *, HBRUSH);
void WINAPI InvertRect(HDC, const RECT FAR *);
#if WINVER >= 0x0300
void WINAPI DrawFocusRect(HDC, const RECT FAR *);
#endif
#endif /* RC_INVOKED */

#define DT_TOP 0x0000
#define DT_LEFT 0x0000
#define DT_CENTER 0x0001
#define DT_RIGHT 0x0002
#define DT_VCENTER 0x0004
#define DT_BOTTOM 0x0008
#define DT_WORDBREAK 0x0010
#define DT_SINGLELINE 0x0020
#define DT_EXPANDTABS 0x0040
#define DT_TABSTOP 0x0080
#define DT_NOCLIP 0x0100
#define DT_EXTERNALLEADING 0x0200
#define DT_CALCRECT 0x0400
#define DT_NOPREFIX 0x0800
#define DT_INTERNAL 0x1000

#ifndef RC_INVOKED
/* Rectangles. */
void WINAPI SetRect(RECT FAR *, int, int, int, int);
void WINAPI SetRectEmpty(RECT FAR *);
void WINAPI CopyRect(RECT FAR *, const RECT FAR *);
void WINAPI InflateRect(RECT FAR *, int, int);
BOOL WINAPI IntersectRect(RECT FAR *, const RECT FAR *, const RECT FAR *);
BOOL WINAPI UnionRect(RECT FAR *, const RECT FAR *, const RECT FAR *);
#if WINVER >= 0x030A
BOOL WINAPI SubtractRect(RECT FAR *, const RECT FAR *, const RECT FAR *);
#endif
void WINAPI OffsetRect(RECT FAR *, int, int);
BOOL WINAPI IsRectEmpty(const RECT FAR *);
#if WINVER >= 0x0200
BOOL WINAPI EqualRect(const RECT FAR *, const RECT FAR *);
#endif
BOOL WINAPI PtInRect(const RECT FAR *, POINT);

/* Timers. */
UINT WINAPI SetTimer(HWND, UINT, UINT, TIMERPROC);
BOOL WINAPI KillTimer(HWND, UINT);
DWORD WINAPI GetTimerResolution(void);
#endif /* RC_INVOKED */

/* Dialogs and controls. */
#define DS_ABSALIGN 0x01L
#define DS_SYSMODAL 0x02L
#define DS_LOCALEDIT 0x20L
#define DS_SETFONT 0x40L
#define DS_MODALFRAME 0x80L
#define DS_NOIDLEMSG 0x100L
#define DM_GETDEFID (WM_USER + 0)
#define DM_SETDEFID (WM_USER + 1)
#define DC_HASDEFID 0x534B
#define DWL_MSGRESULT 0
#define DWL_DLGPROC 4
#define DWL_USER 8
#define DLGWINDOWEXTRA 30

#define DLGC_WANTARROWS 0x0001
#define DLGC_WANTTAB 0x0002
#define DLGC_WANTALLKEYS 0x0004
#define DLGC_WANTMESSAGE 0x0004
#define DLGC_HASSETSEL 0x0008
#define DLGC_DEFPUSHBUTTON 0x0010
#define DLGC_UNDEFPUSHBUTTON 0x0020
#define DLGC_RADIOBUTTON 0x0040
#define DLGC_WANTCHARS 0x0080
#define DLGC_STATIC 0x0100
#define DLGC_BUTTON 0x2000

#define BS_PUSHBUTTON 0x00L
#define BS_DEFPUSHBUTTON 0x01L
#define BS_CHECKBOX 0x02L
#define BS_AUTOCHECKBOX 0x03L
#define BS_RADIOBUTTON 0x04L
#define BS_3STATE 0x05L
#define BS_AUTO3STATE 0x06L
#define BS_GROUPBOX 0x07L
#define BS_USERBUTTON 0x08L
#define BS_AUTORADIOBUTTON 0x09L
#define BS_OWNERDRAW 0x0BL
#define BS_LEFTTEXT 0x20L
#define BN_CLICKED 0
#define BN_PAINT 1
#define BN_HILITE 2
#define BN_UNHILITE 3
#define BN_DISABLE 4
#define BN_DOUBLECLICKED 5
#define BM_GETCHECK (WM_USER + 0)
#define BM_SETCHECK (WM_USER + 1)
#define BM_GETSTATE (WM_USER + 2)
#define BM_SETSTATE (WM_USER + 3)
#define BM_SETSTYLE (WM_USER + 4)
#define BST_UNCHECKED 0
#define BST_CHECKED 1
#define BST_INDETERMINATE 2

#define ES_LEFT 0x0000L
#define ES_CENTER 0x0001L
#define ES_RIGHT 0x0002L
#define ES_MULTILINE 0x0004L
#define ES_UPPERCASE 0x0008L
#define ES_LOWERCASE 0x0010L
#define ES_PASSWORD 0x0020L
#define ES_AUTOVSCROLL 0x0040L
#define ES_AUTOHSCROLL 0x0080L
#define ES_NOHIDESEL 0x0100L
#define ES_OEMCONVERT 0x0400L
#define ES_READONLY 0x0800L
#define ES_WANTRETURN 0x1000L
#define EN_SETFOCUS 0x0100
#define EN_KILLFOCUS 0x0200
#define EN_CHANGE 0x0300
#define EN_UPDATE 0x0400
#define EN_ERRSPACE 0x0500
#define EN_MAXTEXT 0x0501
#define EN_HSCROLL 0x0601
#define EN_VSCROLL 0x0602
#define EM_GETSEL (WM_USER + 0)
#define EM_SETSEL (WM_USER + 1)
#define EM_GETRECT (WM_USER + 2)
#define EM_SETRECT (WM_USER + 3)
#define EM_SETRECTNP (WM_USER + 4)
#define EM_LINESCROLL (WM_USER + 6)
#define EM_GETMODIFY (WM_USER + 8)
#define EM_SETMODIFY (WM_USER + 9)
#define EM_GETLINECOUNT (WM_USER + 10)
#define EM_LINEINDEX (WM_USER + 11)
#define EM_SETHANDLE (WM_USER + 12)
#define EM_GETHANDLE (WM_USER + 13)
#define EM_GETTHUMB (WM_USER + 14)
#define EM_LINELENGTH (WM_USER + 17)
#define EM_REPLACESEL (WM_USER + 18)
#define EM_GETLINE (WM_USER + 20)
#define EM_LIMITTEXT (WM_USER + 21)
#define EM_CANUNDO (WM_USER + 22)
#define EM_UNDO (WM_USER + 23)
#define EM_FMTLINES (WM_USER + 24)
#define EM_LINEFROMCHAR (WM_USER + 25)
#define EM_SETTABSTOPS (WM_USER + 27)
#define EM_SETPASSWORDCHAR (WM_USER + 28)
#define EM_EMPTYUNDOBUFFER (WM_USER + 29)
#define EM_GETFIRSTVISIBLELINE (WM_USER + 30)
#define EM_SETREADONLY (WM_USER + 31)
#define EM_SETWORDBREAKPROC (WM_USER + 32)
#define EM_GETWORDBREAKPROC (WM_USER + 33)
#define EM_GETPASSWORDCHAR (WM_USER + 34)
#define WB_LEFT 0
#define WB_RIGHT 1
#define WB_ISDELIMITER 2

#define SS_LEFT 0x00L
#define SS_CENTER 0x01L
#define SS_RIGHT 0x02L
#define SS_ICON 0x03L
#define SS_BLACKRECT 0x04L
#define SS_GRAYRECT 0x05L
#define SS_WHITERECT 0x06L
#define SS_BLACKFRAME 0x07L
#define SS_GRAYFRAME 0x08L
#define SS_WHITEFRAME 0x09L
#define SS_USERITEM 0x0AL
#define SS_SIMPLE 0x0BL
#define SS_LEFTNOWORDWRAP 0x0CL
#define SS_NOPREFIX 0x80L
#define STM_SETICON (WM_USER + 0)
#define STM_GETICON (WM_USER + 1)

#define LBS_NOTIFY 0x0001L
#define LBS_SORT 0x0002L
#define LBS_NOREDRAW 0x0004L
#define LBS_MULTIPLESEL 0x0008L
#define LBS_OWNERDRAWFIXED 0x0010L
#define LBS_OWNERDRAWVARIABLE 0x0020L
#define LBS_HASSTRINGS 0x0040L
#define LBS_USETABSTOPS 0x0080L
#define LBS_NOINTEGRALHEIGHT 0x0100L
#define LBS_MULTICOLUMN 0x0200L
#define LBS_WANTKEYBOARDINPUT 0x0400L
#define LBS_EXTENDEDSEL 0x0800L
#define LBS_DISABLENOSCROLL 0x1000L
#define LBS_STANDARD (LBS_NOTIFY | LBS_SORT | WS_VSCROLL | WS_BORDER)
#define LB_OKAY 0
#define LB_ERR (-1)
#define LB_ERRSPACE (-2)
#define LBN_ERRSPACE (-2)
#define LBN_SELCHANGE 1
#define LBN_DBLCLK 2
#define LBN_SELCANCEL 3
#define LBN_SETFOCUS 4
#define LBN_KILLFOCUS 5
#define LB_ADDSTRING (WM_USER + 1)
#define LB_INSERTSTRING (WM_USER + 2)
#define LB_DELETESTRING (WM_USER + 3)
#define LB_RESETCONTENT (WM_USER + 5)
#define LB_SETSEL (WM_USER + 6)
#define LB_SETCURSEL (WM_USER + 7)
#define LB_GETSEL (WM_USER + 8)
#define LB_GETCURSEL (WM_USER + 9)
#define LB_GETTEXT (WM_USER + 10)
#define LB_GETTEXTLEN (WM_USER + 11)
#define LB_GETCOUNT (WM_USER + 12)
#define LB_SELECTSTRING (WM_USER + 13)
#define LB_DIR (WM_USER + 14)
#define LB_GETTOPINDEX (WM_USER + 15)
#define LB_FINDSTRING (WM_USER + 16)
#define LB_GETSELCOUNT (WM_USER + 17)
#define LB_GETSELITEMS (WM_USER + 18)
#define LB_SETTABSTOPS (WM_USER + 19)
#define LB_GETHORIZONTALEXTENT (WM_USER + 20)
#define LB_SETHORIZONTALEXTENT (WM_USER + 21)
#define LB_SETCOLUMNWIDTH (WM_USER + 22)
#define LB_SETTOPINDEX (WM_USER + 24)
#define LB_GETITEMRECT (WM_USER + 25)
#define LB_GETITEMDATA (WM_USER + 26)
#define LB_SETITEMDATA (WM_USER + 27)
#define LB_SELITEMRANGE (WM_USER + 28)
#define LB_SETCARETINDEX (WM_USER + 31)
#define LB_GETCARETINDEX (WM_USER + 32)
#define LB_SETITEMHEIGHT (WM_USER + 33)
#define LB_GETITEMHEIGHT (WM_USER + 34)
#define LB_FINDSTRINGEXACT (WM_USER + 35)

#define CBS_SIMPLE 0x0001L
#define CBS_DROPDOWN 0x0002L
#define CBS_DROPDOWNLIST 0x0003L
#define CBS_OWNERDRAWFIXED 0x0010L
#define CBS_OWNERDRAWVARIABLE 0x0020L
#define CBS_AUTOHSCROLL 0x0040L
#define CBS_OEMCONVERT 0x0080L
#define CBS_SORT 0x0100L
#define CBS_HASSTRINGS 0x0200L
#define CBS_NOINTEGRALHEIGHT 0x0400L
#define CBS_DISABLENOSCROLL 0x0800L
#define CB_OKAY 0
#define CB_ERR (-1)
#define CB_ERRSPACE (-2)
#define CBN_ERRSPACE (-1)
#define CBN_SELCHANGE 1
#define CBN_DBLCLK 2
#define CBN_SETFOCUS 3
#define CBN_KILLFOCUS 4
#define CBN_EDITCHANGE 5
#define CBN_EDITUPDATE 6
#define CBN_DROPDOWN 7
#define CBN_CLOSEUP 8
#define CBN_SELENDOK 9
#define CBN_SELENDCANCEL 10
#define CB_GETEDITSEL (WM_USER + 0)
#define CB_LIMITTEXT (WM_USER + 1)
#define CB_SETEDITSEL (WM_USER + 2)
#define CB_ADDSTRING (WM_USER + 3)
#define CB_DELETESTRING (WM_USER + 4)
#define CB_DIR (WM_USER + 5)
#define CB_GETCOUNT (WM_USER + 6)
#define CB_GETCURSEL (WM_USER + 7)
#define CB_GETLBTEXT (WM_USER + 8)
#define CB_GETLBTEXTLEN (WM_USER + 9)
#define CB_INSERTSTRING (WM_USER + 10)
#define CB_RESETCONTENT (WM_USER + 11)
#define CB_FINDSTRING (WM_USER + 12)
#define CB_SELECTSTRING (WM_USER + 13)
#define CB_SETCURSEL (WM_USER + 14)
#define CB_SHOWDROPDOWN (WM_USER + 15)
#define CB_GETITEMDATA (WM_USER + 16)
#define CB_SETITEMDATA (WM_USER + 17)
#define CB_GETDROPPEDCONTROLRECT (WM_USER + 18)
#define CB_SETITEMHEIGHT (WM_USER + 19)
#define CB_GETITEMHEIGHT (WM_USER + 20)
#define CB_SETEXTENDEDUI (WM_USER + 21)
#define CB_GETEXTENDEDUI (WM_USER + 22)
#define CB_GETDROPPEDSTATE (WM_USER + 23)
#define CB_FINDSTRINGEXACT (WM_USER + 24)

#define SBS_HORZ 0x0000L
#define SBS_VERT 0x0001L
#define SBS_TOPALIGN 0x0002L
#define SBS_LEFTALIGN 0x0002L
#define SBS_BOTTOMALIGN 0x0004L
#define SBS_RIGHTALIGN 0x0004L
#define SBS_SIZEBOXTOPLEFTALIGN 0x0002L
#define SBS_SIZEBOXBOTTOMRIGHTALIGN 0x0004L
#define SBS_SIZEBOX 0x0008L
#define SB_HORZ 0
#define SB_VERT 1
#define SB_CTL 2
#define SB_BOTH 3
#define SB_LINEUP 0
#define SB_LINELEFT 0
#define SB_LINEDOWN 1
#define SB_LINERIGHT 1
#define SB_PAGEUP 2
#define SB_PAGELEFT 2
#define SB_PAGEDOWN 3
#define SB_PAGERIGHT 3
#define SB_THUMBPOSITION 4
#define SB_THUMBTRACK 5
#define SB_TOP 6
#define SB_LEFT 6
#define SB_BOTTOM 7
#define SB_RIGHT 7
#define SB_ENDSCROLL 8
#define ESB_ENABLE_BOTH 0x0000
#define ESB_DISABLE_BOTH 0x0003
#define ESB_DISABLE_LEFT 0x0001
#define ESB_DISABLE_RIGHT 0x0002
#define ESB_DISABLE_UP 0x0001
#define ESB_DISABLE_DOWN 0x0002
#define ESB_DISABLE_LTUP ESB_DISABLE_LEFT
#define ESB_DISABLE_RTDN ESB_DISABLE_RIGHT

#define MDIS_ALLCHILDSTYLES 0x0001
#define MDITILE_VERTICAL 0x0000
#define MDITILE_HORIZONTAL 0x0001
#define MDITILE_SKIPDISABLED 0x0002

/* Owner-drawn controls. */
#define ODT_MENU 1
#define ODT_LISTBOX 2
#define ODT_COMBOBOX 3
#define ODT_BUTTON 4
#define ODA_DRAWENTIRE 0x0001
#define ODA_SELECT 0x0002
#define ODA_FOCUS 0x0004
#define ODS_SELECTED 0x0001
#define ODS_GRAYED 0x0002
#define ODS_DISABLED 0x0004
#define ODS_CHECKED 0x0008
#define ODS_FOCUS 0x0010

/* DlgDirList. */
#define DDL_READWRITE 0x0000
#define DDL_READONLY 0x0001
#define DDL_HIDDEN 0x0002
#define DDL_SYSTEM 0x0004
#define DDL_DIRECTORY 0x0010
#define DDL_ARCHIVE 0x0020
#define DDL_POSTMSGS 0x2000
#define DDL_DRIVES 0x4000
#define DDL_EXCLUSIVE 0x8000

#ifndef RC_INVOKED
typedef struct tagMEASUREITEMSTRUCT {
  UINT CtlType;
  UINT CtlID;
  UINT itemID;
  UINT itemWidth;
  UINT itemHeight;
  DWORD itemData;
} MEASUREITEMSTRUCT;
typedef MEASUREITEMSTRUCT FAR *LPMEASUREITEMSTRUCT;

typedef struct tagDRAWITEMSTRUCT {
  UINT CtlType;
  UINT CtlID;
  UINT itemID;
  UINT itemAction;
  UINT itemState;
  HWND hwndItem;
  HDC hDC;
  RECT rcItem;
  DWORD itemData;
} DRAWITEMSTRUCT;
typedef DRAWITEMSTRUCT FAR *LPDRAWITEMSTRUCT;

typedef struct tagDELETEITEMSTRUCT {
  UINT CtlType;
  UINT CtlID;
  UINT itemID;
  HWND hwndItem;
  DWORD itemData;
} DELETEITEMSTRUCT;
typedef DELETEITEMSTRUCT FAR *LPDELETEITEMSTRUCT;

typedef struct tagCOMPAREITEMSTRUCT {
  UINT CtlType;
  UINT CtlID;
  HWND hwndItem;
  UINT itemID1;
  DWORD itemData1;
  UINT itemID2;
  DWORD itemData2;
} COMPAREITEMSTRUCT;
typedef COMPAREITEMSTRUCT FAR *LPCOMPAREITEMSTRUCT;

typedef struct tagCLIENTCREATESTRUCT {
  HMENU hWindowMenu;
  UINT idFirstChild;
} CLIENTCREATESTRUCT;
typedef CLIENTCREATESTRUCT FAR *LPCLIENTCREATESTRUCT;

typedef struct tagMDICREATESTRUCT {
  LPCSTR szClass;
  LPCSTR szTitle;
  HINSTANCE hOwner;
  int x;
  int y;
  int cx;
  int cy;
  LONG style;
  LPARAM lParam;
} MDICREATESTRUCT;
typedef MDICREATESTRUCT FAR *LPMDICREATESTRUCT;

HWND WINAPI CreateDialog(HINSTANCE, LPCSTR, HWND, DLGPROC);
#if WINVER >= 0x0200
HWND WINAPI CreateDialogIndirect(HINSTANCE, const void FAR *, HWND, DLGPROC);
#endif
int WINAPI DialogBox(HINSTANCE, LPCSTR, HWND, DLGPROC);
#if WINVER >= 0x0200
int WINAPI DialogBoxIndirect(HINSTANCE, HGLOBAL, HWND, DLGPROC);
#endif
#if WINVER >= 0x0300
HWND WINAPI CreateDialogParam(HINSTANCE, LPCSTR, HWND, DLGPROC, LPARAM);
HWND WINAPI CreateDialogIndirectParam(HINSTANCE, const void FAR *, HWND,
                                      DLGPROC, LPARAM);
int WINAPI DialogBoxParam(HINSTANCE, LPCSTR, HWND, DLGPROC, LPARAM);
int WINAPI DialogBoxIndirectParam(HINSTANCE, HGLOBAL, HWND, DLGPROC, LPARAM);
#endif
void WINAPI EndDialog(HWND, int);
#if WINVER >= 0x0300
LRESULT WINAPI DefDlgProc(HWND, UINT, WPARAM, LPARAM);
#endif
BOOL WINAPI IsDialogMessage(HWND, MSG FAR *);
HWND WINAPI GetDlgItem(HWND, int);
void WINAPI SetDlgItemInt(HWND, int, UINT, BOOL);
UINT WINAPI GetDlgItemInt(HWND, int, BOOL FAR *, BOOL);
void WINAPI SetDlgItemText(HWND, int, LPCSTR);
int WINAPI GetDlgItemText(HWND, int, LPSTR, int);
void WINAPI CheckDlgButton(HWND, int, UINT);
void WINAPI CheckRadioButton(HWND, int, int, int);
UINT WINAPI IsDlgButtonChecked(HWND, int);
LRESULT WINAPI SendDlgItemMessage(HWND, int, UINT, WPARAM, LPARAM);
#if WINVER >= 0x0200
HWND WINAPI GetNextDlgGroupItem(HWND, HWND, BOOL);
HWND WINAPI GetNextDlgTabItem(HWND, HWND, BOOL);
#endif
#if WINVER >= 0x0300
int WINAPI GetDlgCtrlID(HWND);
LONG WINAPI GetDialogBaseUnits(void);
#endif
void WINAPI MapDialogRect(HWND, RECT FAR *);
int WINAPI DlgDirList(HWND, LPSTR, int, int, UINT);
BOOL WINAPI DlgDirSelect(HWND, LPSTR, int);
#if WINVER >= 0x0300
int WINAPI DlgDirListComboBox(HWND, LPSTR, int, int, UINT);
BOOL WINAPI DlgDirSelectComboBox(HWND, LPSTR, int);
#endif
#if WINVER >= 0x030A
BOOL WINAPI DlgDirSelectEx(HWND, LPSTR, int, int);
BOOL WINAPI DlgDirSelectComboBoxEx(HWND, LPSTR, int, int);
#endif

/* MDI. */
#if WINVER >= 0x0300
LRESULT WINAPI DefFrameProc(HWND, HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI DefMDIChildProc(HWND, UINT, WPARAM, LPARAM);
BOOL WINAPI TranslateMDISysAccel(HWND, MSG FAR *);
#endif

/* Scroll bars. */
int WINAPI SetScrollPos(HWND, int, int, BOOL);
int WINAPI GetScrollPos(HWND, int);
void WINAPI SetScrollRange(HWND, int, int, int, BOOL);
void WINAPI GetScrollRange(HWND, int, int FAR *, int FAR *);
#if WINVER >= 0x0200
void WINAPI ShowScrollBar(HWND, int, BOOL);
#endif
#if WINVER >= 0x030A
BOOL WINAPI EnableScrollBar(HWND, int, UINT);
#endif
#endif /* RC_INVOKED */

/* Menus. */
#define MF_INSERT 0x0000
#define MF_CHANGE 0x0080
#define MF_APPEND 0x0100
#define MF_DELETE 0x0200
#define MF_REMOVE 0x1000
#define MF_BYCOMMAND 0x0000
#define MF_BYPOSITION 0x0400
#define MF_SEPARATOR 0x0800
#define MF_ENABLED 0x0000
#define MF_GRAYED 0x0001
#define MF_DISABLED 0x0002
#define MF_UNCHECKED 0x0000
#define MF_CHECKED 0x0008
#define MF_USECHECKBITMAPS 0x0200
#define MF_STRING 0x0000
#define MF_BITMAP 0x0004
#define MF_OWNERDRAW 0x0100
#define MF_POPUP 0x0010
#define MF_MENUBARBREAK 0x0020
#define MF_MENUBREAK 0x0040
#define MF_UNHILITE 0x0000
#define MF_HILITE 0x0080
#define MF_SYSMENU 0x2000
#define MF_HELP 0x4000
#define MF_MOUSESELECT 0x8000
#define MF_END 0x0080
#define TPM_LEFTBUTTON 0x0000
#define TPM_RIGHTBUTTON 0x0002
#define TPM_LEFTALIGN 0x0000
#define TPM_CENTERALIGN 0x0004
#define TPM_RIGHTALIGN 0x0008

#ifndef RC_INVOKED
typedef struct {
  UINT versionNumber;
  UINT offset;
} MENUITEMTEMPLATEHEADER;
typedef struct {
  UINT mtOption;
  UINT mtID;
  char mtString[1];
} MENUITEMTEMPLATE;

HMENU WINAPI LoadMenu(HINSTANCE, LPCSTR);
#if WINVER >= 0x0200
HMENU WINAPI LoadMenuIndirect(const void FAR *);
#endif
HMENU WINAPI CreateMenu(void);
#if WINVER >= 0x0300
HMENU WINAPI CreatePopupMenu(void);
#endif
BOOL WINAPI DestroyMenu(HMENU);
HMENU WINAPI GetMenu(HWND);
BOOL WINAPI SetMenu(HWND, HMENU);
HMENU WINAPI GetSubMenu(HMENU, int);
HMENU WINAPI GetSystemMenu(HWND, BOOL);
void WINAPI DrawMenuBar(HWND);
BOOL WINAPI HiliteMenuItem(HWND, HMENU, UINT, UINT);
BOOL WINAPI ChangeMenu(HMENU, UINT, LPCSTR, UINT, UINT);
#if WINVER >= 0x0300
BOOL WINAPI AppendMenu(HMENU, UINT, UINT, LPCSTR);
BOOL WINAPI InsertMenu(HMENU, UINT, UINT, UINT, LPCSTR);
BOOL WINAPI ModifyMenu(HMENU, UINT, UINT, UINT, LPCSTR);
BOOL WINAPI RemoveMenu(HMENU, UINT, UINT);
BOOL WINAPI DeleteMenu(HMENU, UINT, UINT);
BOOL WINAPI TrackPopupMenu(HMENU, UINT, int, int, int, HWND, const RECT FAR *);
BOOL WINAPI SetMenuItemBitmaps(HMENU, UINT, UINT, HBITMAP, HBITMAP);
DWORD WINAPI GetMenuCheckMarkDimensions(void);
#endif
BOOL WINAPI CheckMenuItem(HMENU, UINT, UINT);
BOOL WINAPI EnableMenuItem(HMENU, UINT, UINT);
#if WINVER >= 0x0200
UINT WINAPI GetMenuState(HMENU, UINT, UINT);
#endif
int WINAPI GetMenuString(HMENU, UINT, LPSTR, int, UINT);
#if WINVER >= 0x0200
int WINAPI GetMenuItemCount(HMENU);
UINT WINAPI GetMenuItemID(HMENU, int);
#endif
#if WINVER >= 0x030A
BOOL WINAPI IsMenu(HMENU);
#endif

/* Accelerators. */
HACCEL WINAPI LoadAccelerators(HINSTANCE, LPCSTR);
int WINAPI TranslateAccelerator(HWND, HACCEL, MSG FAR *);

/* Strings, icons, cursors and bitmaps from resources. */
int WINAPI LoadString(HINSTANCE, UINT, LPSTR, int);
HICON WINAPI LoadIcon(HINSTANCE, LPCSTR);
HCURSOR WINAPI LoadCursor(HINSTANCE, LPCSTR);
HBITMAP WINAPI LoadBitmap(HINSTANCE, LPCSTR);
#if WINVER >= 0x0300
HICON WINAPI CreateIcon(HINSTANCE, int, int, BYTE, BYTE, const void FAR *,
                        const void FAR *);
HCURSOR WINAPI CreateCursor(HINSTANCE, int, int, int, int, const void FAR *,
                            const void FAR *);
BOOL WINAPI DestroyIcon(HICON);
BOOL WINAPI DestroyCursor(HCURSOR);
#endif
#if WINVER >= 0x030A
HICON WINAPI CopyIcon(HINSTANCE, HICON);
HCURSOR WINAPI CopyCursor(HINSTANCE, HCURSOR);
#endif
#endif /* RC_INVOKED */

#define IDC_ARROW MAKEINTRESOURCE(32512)
#define IDC_IBEAM MAKEINTRESOURCE(32513)
#define IDC_WAIT MAKEINTRESOURCE(32514)
#define IDC_CROSS MAKEINTRESOURCE(32515)
#define IDC_UPARROW MAKEINTRESOURCE(32516)
#define IDC_SIZE MAKEINTRESOURCE(32640)
#define IDC_ICON MAKEINTRESOURCE(32641)
#define IDC_SIZENWSE MAKEINTRESOURCE(32642)
#define IDC_SIZENESW MAKEINTRESOURCE(32643)
#define IDC_SIZEWE MAKEINTRESOURCE(32644)
#define IDC_SIZENS MAKEINTRESOURCE(32645)
#define IDI_APPLICATION MAKEINTRESOURCE(32512)
#define IDI_HAND MAKEINTRESOURCE(32513)
#define IDI_QUESTION MAKEINTRESOURCE(32514)
#define IDI_EXCLAMATION MAKEINTRESOURCE(32515)
#define IDI_ASTERISK MAKEINTRESOURCE(32516)

/* Message boxes. */
#define MB_OK 0x0000
#define MB_OKCANCEL 0x0001
#define MB_ABORTRETRYIGNORE 0x0002
#define MB_YESNOCANCEL 0x0003
#define MB_YESNO 0x0004
#define MB_RETRYCANCEL 0x0005
#define MB_TYPEMASK 0x000F
#define MB_ICONHAND 0x0010
#define MB_ICONQUESTION 0x0020
#define MB_ICONEXCLAMATION 0x0030
#define MB_ICONASTERISK 0x0040
#define MB_ICONMASK 0x00F0
#define MB_ICONINFORMATION MB_ICONASTERISK
#define MB_ICONSTOP MB_ICONHAND
#define MB_DEFBUTTON1 0x0000
#define MB_DEFBUTTON2 0x0100
#define MB_DEFBUTTON3 0x0200
#define MB_DEFMASK 0x0F00
#define MB_APPLMODAL 0x0000
#define MB_SYSTEMMODAL 0x1000
#define MB_TASKMODAL 0x2000
#define MB_NOFOCUS 0x8000
#define MB_MODEMASK 0x3000
#define MB_MISCMASK 0xC000
#define IDOK 1
#define IDCANCEL 2
#define IDABORT 3
#define IDRETRY 4
#define IDIGNORE 5
#define IDYES 6
#define IDNO 7

#ifndef RC_INVOKED
int WINAPI MessageBox(HWND, LPCSTR, LPCSTR, UINT);
void WINAPI MessageBeep(UINT);
#if WINVER >= 0x0300
int __far __cdecl wsprintf(LPSTR, LPCSTR, ...);
int WINAPI wvsprintf(LPSTR, LPCSTR, const void FAR *);
#endif

/* The clipboard. */
BOOL WINAPI OpenClipboard(HWND);
BOOL WINAPI CloseClipboard(void);
BOOL WINAPI EmptyClipboard(void);
HWND WINAPI GetClipboardOwner(void);
HANDLE WINAPI SetClipboardData(UINT, HANDLE);
HANDLE WINAPI GetClipboardData(UINT);
BOOL WINAPI IsClipboardFormatAvailable(UINT);
int WINAPI CountClipboardFormats(void);
UINT WINAPI EnumClipboardFormats(UINT);
UINT WINAPI RegisterClipboardFormat(LPCSTR);
int WINAPI GetClipboardFormatName(UINT, LPSTR, int);
HWND WINAPI SetClipboardViewer(HWND);
HWND WINAPI GetClipboardViewer(void);
BOOL WINAPI ChangeClipboardChain(HWND, HWND);
#if WINVER >= 0x0300
int WINAPI GetPriorityClipboardFormat(UINT FAR *, int);
#endif
#if WINVER >= 0x030A
HWND WINAPI GetOpenClipboardWindow(void);
#endif
#endif /* RC_INVOKED */
#define CF_TEXT 1
#define CF_BITMAP 2
#define CF_METAFILEPICT 3
#define CF_SYLK 4
#define CF_DIF 5
#define CF_TIFF 6
#define CF_OEMTEXT 7
#define CF_DIB 8
#define CF_PALETTE 9
#define CF_PENDATA 10
#define CF_RIFF 11
#define CF_WAVE 12
#define CF_OWNERDISPLAY 0x0080
#define CF_DSPTEXT 0x0081
#define CF_DSPBITMAP 0x0082
#define CF_DSPMETAFILEPICT 0x0083
#define CF_PRIVATEFIRST 0x0200
#define CF_PRIVATELAST 0x02FF
#define CF_GDIOBJFIRST 0x0300
#define CF_GDIOBJLAST 0x03FF

#ifndef RC_INVOKED
/* The caret, the cursor and the mouse. */
void WINAPI CreateCaret(HWND, HBITMAP, int, int);
void WINAPI DestroyCaret(void);
void WINAPI HideCaret(HWND);
void WINAPI ShowCaret(HWND);
void WINAPI SetCaretPos(int, int);
void WINAPI GetCaretPos(POINT FAR *);
void WINAPI SetCaretBlinkTime(UINT);
UINT WINAPI GetCaretBlinkTime(void);
HCURSOR WINAPI SetCursor(HCURSOR);
#if WINVER >= 0x030A
HCURSOR WINAPI GetCursor(void);
void WINAPI GetClipCursor(RECT FAR *);
#endif
int WINAPI ShowCursor(BOOL);
void WINAPI SetCursorPos(int, int);
void WINAPI GetCursorPos(POINT FAR *);
void WINAPI ClipCursor(const RECT FAR *);
UINT WINAPI GetDoubleClickTime(void);
void WINAPI SetDoubleClickTime(UINT);
BOOL WINAPI SwapMouseButton(BOOL);

/* The keyboard. */
int WINAPI GetKeyState(int);
#if WINVER >= 0x0200
int WINAPI GetAsyncKeyState(int);
void WINAPI GetKeyboardState(BYTE FAR *);
void WINAPI SetKeyboardState(BYTE FAR *);
BOOL WINAPI EnableHardwareInput(BOOL);
#endif
#if WINVER >= 0x0300
BOOL WINAPI IsCharAlpha(char);
BOOL WINAPI IsCharAlphaNumeric(char);
BOOL WINAPI IsCharUpper(char);
BOOL WINAPI IsCharLower(char);
UINT WINAPI AnsiUpperBuff(LPSTR, UINT);
UINT WINAPI AnsiLowerBuff(LPSTR, UINT);
#endif
/* KEYBOARD. */
BOOL WINAPI AnsiToOem(LPCSTR, LPSTR);
BOOL WINAPI OemToAnsi(LPCSTR, LPSTR);
#if WINVER >= 0x0300
void WINAPI AnsiToOemBuff(LPCSTR, LPSTR, UINT);
void WINAPI OemToAnsiBuff(LPCSTR, LPSTR, UINT);
UINT WINAPI VkKeyScan(UINT);
UINT WINAPI MapVirtualKey(UINT, UINT);
int WINAPI GetKeyNameText(LONG, LPSTR, int);
int WINAPI GetKBCodePage(void);
int WINAPI GetKeyboardType(int);
#endif
#if WINVER >= 0x0200
int WINAPI ToAscii(UINT, UINT, BYTE FAR *, DWORD FAR *, UINT);
DWORD WINAPI OemKeyScan(UINT);
#endif
#endif /* RC_INVOKED */

#define VK_LBUTTON 0x01
#define VK_RBUTTON 0x02
#define VK_CANCEL 0x03
#define VK_MBUTTON 0x04
#define VK_BACK 0x08
#define VK_TAB 0x09
#define VK_CLEAR 0x0C
#define VK_RETURN 0x0D
#define VK_SHIFT 0x10
#define VK_CONTROL 0x11
#define VK_MENU 0x12
#define VK_PAUSE 0x13
#define VK_CAPITAL 0x14
#define VK_ESCAPE 0x1B
#define VK_SPACE 0x20
#define VK_PRIOR 0x21
#define VK_NEXT 0x22
#define VK_END 0x23
#define VK_HOME 0x24
#define VK_LEFT 0x25
#define VK_UP 0x26
#define VK_RIGHT 0x27
#define VK_DOWN 0x28
#define VK_SELECT 0x29
#define VK_PRINT 0x2A
#define VK_EXECUTE 0x2B
#define VK_SNAPSHOT 0x2C
#define VK_INSERT 0x2D
#define VK_DELETE 0x2E
#define VK_HELP 0x2F
#define VK_NUMPAD0 0x60
#define VK_NUMPAD1 0x61
#define VK_NUMPAD2 0x62
#define VK_NUMPAD3 0x63
#define VK_NUMPAD4 0x64
#define VK_NUMPAD5 0x65
#define VK_NUMPAD6 0x66
#define VK_NUMPAD7 0x67
#define VK_NUMPAD8 0x68
#define VK_NUMPAD9 0x69
#define VK_MULTIPLY 0x6A
#define VK_ADD 0x6B
#define VK_SEPARATOR 0x6C
#define VK_SUBTRACT 0x6D
#define VK_DECIMAL 0x6E
#define VK_DIVIDE 0x6F
#define VK_F1 0x70
#define VK_F2 0x71
#define VK_F3 0x72
#define VK_F4 0x73
#define VK_F5 0x74
#define VK_F6 0x75
#define VK_F7 0x76
#define VK_F8 0x77
#define VK_F9 0x78
#define VK_F10 0x79
#define VK_F11 0x7A
#define VK_F12 0x7B
#define VK_F13 0x7C
#define VK_F14 0x7D
#define VK_F15 0x7E
#define VK_F16 0x7F
#define VK_F17 0x80
#define VK_F18 0x81
#define VK_F19 0x82
#define VK_F20 0x83
#define VK_F21 0x84
#define VK_F22 0x85
#define VK_F23 0x86
#define VK_F24 0x87
#define VK_NUMLOCK 0x90
#define VK_SCROLL 0x91

/* Hooks. */
#define WH_MSGFILTER (-1)
#define WH_JOURNALRECORD 0
#define WH_JOURNALPLAYBACK 1
#define WH_KEYBOARD 2
#define WH_GETMESSAGE 3
#define WH_CALLWNDPROC 4
#define WH_CBT 5
#define WH_SYSMSGFILTER 6
#define WH_MOUSE 7
#define WH_HARDWARE 8
#define WH_DEBUG 9
#define WH_SHELL 10
#define HC_ACTION 0
#define HC_GETNEXT 1
#define HC_SKIP 2
#define HC_NOREM 3
#define HC_NOREMOVE 3
#define HC_SYSMODALON 4
#define HC_SYSMODALOFF 5
#define HCBT_MOVESIZE 0
#define HCBT_MINMAX 1
#define HCBT_QS 2
#define HCBT_CREATEWND 3
#define HCBT_DESTROYWND 4
#define HCBT_ACTIVATE 5
#define HCBT_CLICKSKIPPED 6
#define HCBT_KEYSKIPPED 7
#define HCBT_SYSCOMMAND 8
#define HCBT_SETFOCUS 9
#define MSGF_DIALOGBOX 0
#define MSGF_MESSAGEBOX 1
#define MSGF_MENU 2
#define MSGF_MOVE 3
#define MSGF_SIZE 4
#define MSGF_SCROLLBAR 5
#define MSGF_NEXTWINDOW 6
#define MSGF_MAINLOOP 8
#define MSGF_USER 4096
#define HSHELL_WINDOWCREATED 1
#define HSHELL_WINDOWDESTROYED 2
#define HSHELL_ACTIVATESHELLWINDOW 3

#ifndef RC_INVOKED
typedef struct tagEVENTMSG {
  UINT message;
  UINT paramL;
  UINT paramH;
  DWORD time;
} EVENTMSG;
typedef EVENTMSG FAR *LPEVENTMSG;
typedef struct tagCWPSTRUCT {
  LPARAM lParam;
  WPARAM wParam;
  UINT message;
  HWND hwnd;
} CWPSTRUCT;
typedef struct tagDEBUGHOOKINFO {
  HMODULE hModuleHook;
  LPARAM reserved;
  LPARAM lParam;
  WPARAM wParam;
  int code;
} DEBUGHOOKINFO;
typedef DEBUGHOOKINFO FAR *LPDEBUGHOOKINFO;
typedef struct tagMOUSEHOOKSTRUCT {
  POINT pt;
  HWND hwnd;
  UINT wHitTestCode;
  DWORD dwExtraInfo;
} MOUSEHOOKSTRUCT;
typedef MOUSEHOOKSTRUCT FAR *LPMOUSEHOOKSTRUCT;
typedef struct tagCBT_CREATEWND {
  CREATESTRUCT FAR *lpcs;
  HWND hwndInsertAfter;
} CBT_CREATEWND;
typedef CBT_CREATEWND FAR *LPCBT_CREATEWND;
typedef struct tagCBTACTIVATESTRUCT {
  BOOL fMouse;
  HWND hWndActive;
} CBTACTIVATESTRUCT;
typedef struct tagHARDWAREHOOKSTRUCT {
  HWND hWnd;
  UINT wMessage;
  WPARAM wParam;
  LPARAM lParam;
} HARDWAREHOOKSTRUCT;

#ifndef NOWH
HOOKPROC WINAPI SetWindowsHook(int, HOOKPROC);
#if WINVER >= 0x0200
BOOL WINAPI UnhookWindowsHook(int, HOOKPROC);
LRESULT WINAPI DefHookProc(int, WPARAM, LPARAM, HOOKPROC FAR *);
#endif
#if WINVER >= 0x030A
HHOOK WINAPI SetWindowsHookEx(int, HOOKPROC, HINSTANCE, HTASK);
BOOL WINAPI UnhookWindowsHookEx(HHOOK);
LRESULT WINAPI CallNextHookEx(HHOOK, int, WPARAM, LPARAM);
#endif
#endif

/* System information and settings. */
int WINAPI GetSystemMetrics(int);
COLORREF WINAPI GetSysColor(int);
void WINAPI SetSysColors(int, const int FAR *, const COLORREF FAR *);
#if WINVER >= 0x030A
BOOL WINAPI SystemParametersInfo(UINT, UINT, void FAR *, UINT);
#endif
BOOL WINAPI ExitWindows(DWORD, UINT);
#if WINVER >= 0x030A
BOOL WINAPI ExitWindowsExec(LPCSTR, LPCSTR);
#endif
#if WINVER >= 0x0300
BOOL WINAPI WinHelp(HWND, LPCSTR, UINT, DWORD);
#endif
#endif /* RC_INVOKED */

#define EW_RESTARTWINDOWS 0x42
#define EW_REBOOTSYSTEM 0x43
#define EW_EXITANDEXECAPP 0x44

#define HELP_CONTEXT 0x0001
#define HELP_QUIT 0x0002
#define HELP_INDEX 0x0003
#define HELP_CONTENTS 0x0003
#define HELP_HELPONHELP 0x0004
#define HELP_SETINDEX 0x0005
#define HELP_SETCONTENTS 0x0005
#define HELP_CONTEXTPOPUP 0x0008
#define HELP_FORCEFILE 0x0009
#define HELP_KEY 0x0101
#define HELP_COMMAND 0x0102
#define HELP_PARTIALKEY 0x0105
#define HELP_MULTIKEY 0x0201
#define HELP_SETWINPOS 0x0203

#define SM_CXSCREEN 0
#define SM_CYSCREEN 1
#define SM_CXVSCROLL 2
#define SM_CYHSCROLL 3
#define SM_CYCAPTION 4
#define SM_CXBORDER 5
#define SM_CYBORDER 6
#define SM_CXDLGFRAME 7
#define SM_CYDLGFRAME 8
#define SM_CYVTHUMB 9
#define SM_CXHTHUMB 10
#define SM_CXICON 11
#define SM_CYICON 12
#define SM_CXCURSOR 13
#define SM_CYCURSOR 14
#define SM_CYMENU 15
#define SM_CXFULLSCREEN 16
#define SM_CYFULLSCREEN 17
#define SM_CYKANJIWINDOW 18
#define SM_MOUSEPRESENT 19
#define SM_CYVSCROLL 20
#define SM_CXHSCROLL 21
#define SM_DEBUG 22
#define SM_SWAPBUTTON 23
#define SM_RESERVED1 24
#define SM_RESERVED2 25
#define SM_RESERVED3 26
#define SM_RESERVED4 27
#define SM_CXMIN 28
#define SM_CYMIN 29
#define SM_CXSIZE 30
#define SM_CYSIZE 31
#define SM_CXFRAME 32
#define SM_CYFRAME 33
#define SM_CXMINTRACK 34
#define SM_CYMINTRACK 35
#define SM_CXDOUBLECLK 36
#define SM_CYDOUBLECLK 37
#define SM_CXICONSPACING 38
#define SM_CYICONSPACING 39
#define SM_MENUDROPALIGNMENT 40
#define SM_PENWINDOWS 41
#define SM_DBCSENABLED 42
#define SM_CMETRICS 43

#define COLOR_SCROLLBAR 0
#define COLOR_BACKGROUND 1
#define COLOR_ACTIVECAPTION 2
#define COLOR_INACTIVECAPTION 3
#define COLOR_MENU 4
#define COLOR_WINDOW 5
#define COLOR_WINDOWFRAME 6
#define COLOR_MENUTEXT 7
#define COLOR_WINDOWTEXT 8
#define COLOR_CAPTIONTEXT 9
#define COLOR_ACTIVEBORDER 10
#define COLOR_INACTIVEBORDER 11
#define COLOR_APPWORKSPACE 12
#define COLOR_HIGHLIGHT 13
#define COLOR_HIGHLIGHTTEXT 14
#define COLOR_BTNFACE 15
#define COLOR_BTNSHADOW 16
#define COLOR_GRAYTEXT 17
#define COLOR_BTNTEXT 18
#define COLOR_INACTIVECAPTIONTEXT 19
#define COLOR_BTNHIGHLIGHT 20

#define SPI_GETBEEP 1
#define SPI_SETBEEP 2
#define SPI_GETMOUSE 3
#define SPI_SETMOUSE 4
#define SPI_GETBORDER 5
#define SPI_SETBORDER 6
#define SPI_GETKEYBOARDSPEED 10
#define SPI_SETKEYBOARDSPEED 11
#define SPI_LANGDRIVER 12
#define SPI_ICONHORIZONTALSPACING 13
#define SPI_GETSCREENSAVETIMEOUT 14
#define SPI_SETSCREENSAVETIMEOUT 15
#define SPI_GETSCREENSAVEACTIVE 16
#define SPI_SETSCREENSAVEACTIVE 17
#define SPI_GETGRIDGRANULARITY 18
#define SPI_SETGRIDGRANULARITY 19
#define SPI_SETDESKWALLPAPER 20
#define SPI_SETDESKPATTERN 21
#define SPI_GETKEYBOARDDELAY 22
#define SPI_SETKEYBOARDDELAY 23
#define SPI_ICONVERTICALSPACING 24
#define SPI_GETICONTITLEWRAP 25
#define SPI_SETICONTITLEWRAP 26
#define SPI_GETMENUDROPALIGNMENT 27
#define SPI_SETMENUDROPALIGNMENT 28
#define SPI_SETDOUBLECLKWIDTH 29
#define SPI_SETDOUBLECLKHEIGHT 30
#define SPI_GETICONTITLELOGFONT 31
#define SPI_SETDOUBLECLICKTIME 32
#define SPI_SETMOUSEBUTTONSWAP 33
#define SPI_SETICONTITLELOGFONT 34
#define SPI_GETFASTTASKSWITCH 35
#define SPI_SETFASTTASKSWITCH 36
#define SPIF_UPDATEINIFILE 0x0001
#define SPIF_SENDWININICHANGE 0x0002

/* Communications ports. */
#define NOPARITY 0
#define ODDPARITY 1
#define EVENPARITY 2
#define MARKPARITY 3
#define SPACEPARITY 4
#define ONESTOPBIT 0
#define ONE5STOPBITS 1
#define TWOSTOPBITS 2
#define IGNORE 0
#define INFINITE 0xFFFF
#define CBR_110 0xFF10
#define CBR_300 0xFF11
#define CBR_600 0xFF12
#define CBR_1200 0xFF13
#define CBR_2400 0xFF14
#define CBR_4800 0xFF15
#define CBR_9600 0xFF16
#define CBR_14400 0xFF17
#define CBR_19200 0xFF18
#define CBR_38400 0xFF1B
#define CBR_56000 0xFF1F
#define CBR_128000 0xFF23
#define CBR_256000 0xFF27
#define CE_RXOVER 0x0001
#define CE_OVERRUN 0x0002
#define CE_RXPARITY 0x0004
#define CE_FRAME 0x0008
#define CE_BREAK 0x0010
#define CE_CTSTO 0x0020
#define CE_DSRTO 0x0040
#define CE_RLSDTO 0x0080
#define CE_TXFULL 0x0100
#define CE_PTO 0x0200
#define CE_IOE 0x0400
#define CE_DNS 0x0800
#define CE_OOP 0x1000
#define CE_MODE 0x8000
#define IE_BADID (-1)
#define IE_OPEN (-2)
#define IE_NOPEN (-3)
#define IE_MEMORY (-4)
#define IE_DEFAULT (-5)
#define IE_HARDWARE (-10)
#define IE_BYTESIZE (-11)
#define IE_BAUDRATE (-12)
#define EV_RXCHAR 0x0001
#define EV_RXFLAG 0x0002
#define EV_TXEMPTY 0x0004
#define EV_CTS 0x0008
#define EV_DSR 0x0010
#define EV_RLSD 0x0020
#define EV_BREAK 0x0040
#define EV_ERR 0x0080
#define EV_RING 0x0100
#define EV_PERR 0x0200
#define EV_CTSS 0x0400
#define EV_DSRS 0x0800
#define EV_RLSDS 0x1000
#define EV_RingTe 0x2000
#define SETXOFF 1
#define SETXON 2
#define SETRTS 3
#define CLRRTS 4
#define SETDTR 5
#define CLRDTR 6
#define RESETDEV 7
#define GETMAXLPT 8
#define GETMAXCOM 9
#define GETBASEIRQ 10
#define LPTx 0x80
#define CSTF_CTSHOLD 0x01
#define CSTF_DSRHOLD 0x02
#define CSTF_RLSDHOLD 0x04
#define CSTF_XOFFHOLD 0x08
#define CSTF_XOFFSENT 0x10
#define CSTF_EOF 0x20
#define CSTF_TXIM 0x40

#if !defined(RC_INVOKED) && !defined(NOCOMM)
typedef struct tagDCB {
  BYTE Id;
  UINT BaudRate;
  BYTE ByteSize;
  BYTE Parity;
  BYTE StopBits;
  UINT RlsTimeout;
  UINT CtsTimeout;
  UINT DsrTimeout;
  UINT fBinary : 1;
  UINT fRtsDisable : 1;
  UINT fParity : 1;
  UINT fOutxCtsFlow : 1;
  UINT fOutxDsrFlow : 1;
  UINT fDummy : 2;
  UINT fDtrDisable : 1;
  UINT fOutX : 1;
  UINT fInX : 1;
  UINT fPeChar : 1;
  UINT fNull : 1;
  UINT fChEvt : 1;
  UINT fDtrflow : 1;
  UINT fRtsflow : 1;
  UINT fDummy2 : 1;
  char XonChar;
  char XoffChar;
  UINT XonLim;
  UINT XoffLim;
  char PeChar;
  char EofChar;
  char EvtChar;
  UINT TxDelay;
} DCB;
typedef DCB FAR *LPDCB;

typedef struct tagCOMSTAT {
  BYTE status;
  UINT cbInQue;
  UINT cbOutQue;
} COMSTAT;

int WINAPI OpenComm(LPCSTR, UINT, UINT);
int WINAPI CloseComm(int);
int WINAPI ReadComm(int, void FAR *, int);
int WINAPI WriteComm(int, const void FAR *, int);
int WINAPI UngetCommChar(int, char);
int WINAPI TransmitCommChar(int, char);
int WINAPI GetCommState(int, DCB FAR *);
int WINAPI SetCommState(const DCB FAR *);
int WINAPI BuildCommDCB(LPCSTR, DCB FAR *);
int WINAPI GetCommError(int, COMSTAT FAR *);
int WINAPI FlushComm(int, int);
UINT FAR *WINAPI SetCommEventMask(int, UINT);
UINT WINAPI GetCommEventMask(int, int);
int WINAPI SetCommBreak(int);
int WINAPI ClearCommBreak(int);
LONG WINAPI EscapeCommFunction(int, int);
#if WINVER >= 0x030A
BOOL WINAPI EnableCommNotification(int, HWND, int, int);
#endif
#endif

/* SOUND. */
#define S_QUEUEEMPTY 0
#define S_THRESHOLD 1
#define S_ALLTHRESHOLD 2
#define S_NORMAL 0
#define S_LEGATO 1
#define S_STACCATO 2
#define S_PERIOD512 0
#define S_PERIOD1024 1
#define S_PERIOD2048 2
#define S_PERIODVOICE 3
#define S_WHITE512 4
#define S_WHITE1024 5
#define S_WHITE2048 6
#define S_WHITEVOICE 7
#define S_SERDVNA (-1)
#define S_SEROFM (-2)
#define S_SERMACT (-3)
#define S_SERQFUL (-4)
#define S_SERBDNT (-5)
#define S_SERDLN (-6)
#define S_SERDCC (-7)
#define S_SERDTP (-8)
#define S_SERDVL (-9)
#define S_SERDMD (-10)
#define S_SERDSH (-11)
#define S_SERDPT (-12)
#define S_SERDFQ (-13)
#define S_SERDDR (-14)
#define S_SERDSR (-15)
#define S_SERDST (-16)
#if !defined(RC_INVOKED) && !defined(NOSOUND)
int WINAPI OpenSound(void);
void WINAPI CloseSound(void);
int WINAPI SetVoiceQueueSize(int, int);
int WINAPI SetVoiceNote(int, int, int, int);
int WINAPI SetVoiceAccent(int, int, int, int, int);
int WINAPI SetVoiceEnvelope(int, int, int);
int WINAPI SetSoundNoise(int, int);
int WINAPI SetVoiceSound(int, DWORD, int);
int WINAPI StartSound(void);
int WINAPI StopSound(void);
int WINAPI WaitSoundState(int);
int WINAPI SyncAllVoices(void);
int WINAPI CountVoiceNotes(int);
int FAR *WINAPI GetThresholdEvent(void);
int WINAPI GetThresholdStatus(void);
int WINAPI SetVoiceThreshold(int, int);
#endif

#ifndef NODRIVERS
/* Installable drivers (Windows 3.1). */
#define DRV_LOAD 0x0001
#define DRV_ENABLE 0x0002
#define DRV_OPEN 0x0003
#define DRV_CLOSE 0x0004
#define DRV_DISABLE 0x0005
#define DRV_FREE 0x0006
#define DRV_CONFIGURE 0x0007
#define DRV_QUERYCONFIGURE 0x0008
#define DRV_INSTALL 0x0009
#define DRV_REMOVE 0x000A
#define DRV_EXITSESSION 0x000B
#define DRV_EXITAPPLICATION 0x000C
#define DRV_POWER 0x000F
#define DRV_RESERVED 0x0800
#define DRV_USER 0x4000

#define DRVCNF_CANCEL 0x0000
#define DRVCNF_OK 0x0001
#define DRVCNF_RESTART 0x0002

#define DRVEA_NORMALEXIT 0x0001
#define DRVEA_ABNORMALEXIT 0x0002

#define GND_FIRSTINSTANCEONLY 0x00000001
#define GND_FORWARD 0x00000000
#define GND_REVERSE 0x00000002

typedef struct tagDRVCONFIGINFO {
  DWORD dwDCISize;
  LPCSTR lpszDCISectionName;
  LPCSTR lpszDCIAliasName;
} DRVCONFIGINFO;
typedef DRVCONFIGINFO FAR *LPDRVCONFIGINFO;

typedef struct tagDRIVERINFOSTRUCT {
  UINT length;
  HDRVR hDriver;
  HINSTANCE hModule;
  char szAliasName[128];
} DRIVERINFOSTRUCT;
typedef DRIVERINFOSTRUCT FAR *LPDRIVERINFOSTRUCT;

typedef LRESULT(CALLBACK *DRIVERPROC)(DWORD, HDRVR, UINT, LPARAM, LPARAM);

#if WINVER >= 0x030A
HDRVR WINAPI OpenDriver(LPCSTR, LPCSTR, LPARAM);
LRESULT WINAPI CloseDriver(HDRVR, LPARAM, LPARAM);
LRESULT WINAPI SendDriverMessage(HDRVR, UINT, LPARAM, LPARAM);
LRESULT WINAPI DefDriverProc(DWORD, HDRVR, UINT, LPARAM, LPARAM);
HINSTANCE WINAPI GetDriverModuleHandle(HDRVR);
BOOL WINAPI GetDriverInfo(HDRVR, DRIVERINFOSTRUCT FAR *);
HDRVR WINAPI GetNextDriver(HDRVR, DWORD);
#endif
#endif /* NODRIVERS */

/****************************************************************************
 * GDI
 ****************************************************************************/

/* GetDeviceCaps. */
#define DRIVERVERSION 0
#define TECHNOLOGY 2
#define HORZSIZE 4
#define VERTSIZE 6
#define HORZRES 8
#define VERTRES 10
#define BITSPIXEL 12
#define PLANES 14
#define NUMBRUSHES 16
#define NUMPENS 18
#define NUMMARKERS 20
#define NUMFONTS 22
#define NUMCOLORS 24
#define PDEVICESIZE 26
#define CURVECAPS 28
#define LINECAPS 30
#define POLYGONALCAPS 32
#define TEXTCAPS 34
#define CLIPCAPS 36
#define RASTERCAPS 38
#define ASPECTX 40
#define ASPECTY 42
#define ASPECTXY 44
#define LOGPIXELSX 88
#define LOGPIXELSY 90
#define SIZEPALETTE 104
#define NUMRESERVED 106
#define COLORRES 108
#define DT_PLOTTER 0
#define DT_RASDISPLAY 1
#define DT_RASPRINTER 2
#define DT_RASCAMERA 3
#define DT_CHARSTREAM 4
#define DT_METAFILE 5
#define DT_DISPFILE 6
#ifndef NOGDICAPMASKS
#define CC_NONE 0x0000
#define CC_CIRCLES 0x0001
#define CC_PIE 0x0002
#define CC_CHORD 0x0004
#define CC_ELLIPSES 0x0008
#define CC_WIDE 0x0010
#define CC_STYLED 0x0020
#define CC_WIDESTYLED 0x0040
#define CC_INTERIORS 0x0080
#define LC_NONE 0x0000
#define LC_POLYLINE 0x0002
#define LC_MARKER 0x0004
#define LC_POLYMARKER 0x0008
#define LC_WIDE 0x0010
#define LC_STYLED 0x0020
#define LC_WIDESTYLED 0x0040
#define LC_INTERIORS 0x0080
#define PC_NONE 0x0000
#define PC_POLYGON 0x0001
#define PC_RECTANGLE 0x0002
#define PC_WINDPOLYGON 0x0004
#define PC_SCANLINE 0x0008
#define PC_WIDE 0x0010
#define PC_STYLED 0x0020
#define PC_WIDESTYLED 0x0040
#define PC_INTERIORS 0x0080
#define CP_NONE 0x0000
#define CP_RECTANGLE 0x0001
#define CP_REGION 0x0002
#define TC_OP_CHARACTER 0x0001
#define TC_OP_STROKE 0x0002
#define TC_CP_STROKE 0x0004
#define TC_CR_90 0x0008
#define TC_CR_ANY 0x0010
#define TC_SF_X_YINDEP 0x0020
#define TC_SA_DOUBLE 0x0040
#define TC_SA_INTEGER 0x0080
#define TC_SA_CONTIN 0x0100
#define TC_EA_DOUBLE 0x0200
#define TC_IA_ABLE 0x0400
#define TC_UA_ABLE 0x0800
#define TC_SO_ABLE 0x1000
#define TC_RA_ABLE 0x2000
#define TC_VA_ABLE 0x4000
#define TC_RESERVED 0x8000
#define RC_NONE
#define RC_BITBLT 0x0001
#define RC_BANDING 0x0002
#define RC_SCALING 0x0004
#define RC_BITMAP64 0x0008
#define RC_GDI20_OUTPUT 0x0010
#define RC_DI_BITMAP 0x0080
#define RC_PALETTE 0x0100
#define RC_DIBTODEV 0x0200
#define RC_BIGFONT 0x0400
#define RC_STRETCHBLT 0x0800
#define RC_FLOODFILL 0x1000
#define RC_STRETCHDIB 0x2000
#endif /* NOGDICAPMASKS */

/* Mapping modes, drawing modes and raster operations. */
#define MM_TEXT 1
#define MM_LOMETRIC 2
#define MM_HIMETRIC 3
#define MM_LOENGLISH 4
#define MM_HIENGLISH 5
#define MM_TWIPS 6
#define MM_ISOTROPIC 7
#define MM_ANISOTROPIC 8
#define ABSOLUTE 1
#define RELATIVE 2
#define TRANSPARENT 1
#define OPAQUE 2
#define ALTERNATE 1
#define WINDING 2
#define BLACKONWHITE 1
#define WHITEONBLACK 2
#define COLORONCOLOR 3
#define STRETCH_ANDSCANS 1
#define STRETCH_ORSCANS 2
#define STRETCH_DELETESCANS 3
#define FLOODFILLBORDER 0
#define FLOODFILLSURFACE 1
#ifndef NORASTEROPS
#define R2_BLACK 1
#define R2_NOTMERGEPEN 2
#define R2_MASKNOTPEN 3
#define R2_NOTCOPYPEN 4
#define R2_MASKPENNOT 5
#define R2_NOT 6
#define R2_XORPEN 7
#define R2_NOTMASKPEN 8
#define R2_MASKPEN 9
#define R2_NOTXORPEN 10
#define R2_NOP 11
#define R2_MERGENOTPEN 12
#define R2_COPYPEN 13
#define R2_MERGEPENNOT 14
#define R2_MERGEPEN 15
#define R2_WHITE 16
#define SRCCOPY 0x00CC0020L
#define SRCPAINT 0x00EE0086L
#define SRCAND 0x008800C6L
#define SRCINVERT 0x00660046L
#define SRCERASE 0x00440328L
#define NOTSRCCOPY 0x00330008L
#define NOTSRCERASE 0x001100A6L
#define MERGECOPY 0x00C000CAL
#define MERGEPAINT 0x00BB0226L
#define PATCOPY 0x00F00021L
#define PATPAINT 0x00FB0A09L
#define PATINVERT 0x005A0049L
#define DSTINVERT 0x00550009L
#define BLACKNESS 0x00000042L
#define WHITENESS 0x00FF0062L
#endif
#define TA_NOUPDATECP 0x0000
#define TA_UPDATECP 0x0001
#define TA_LEFT 0x0000
#define TA_RIGHT 0x0002
#define TA_CENTER 0x0006
#define TA_TOP 0x0000
#define TA_BOTTOM 0x0008
#define TA_BASELINE 0x0018
#define ETO_GRAYED 0x0001
#define ETO_OPAQUE 0x0002
#define ETO_CLIPPED 0x0004
#define DCB_RESET 0x0001
#define DCB_ACCUMULATE 0x0002
#define DCB_DIRTY DCB_ACCUMULATE
#define DCB_SET (DCB_RESET | DCB_ACCUMULATE)
#define DCB_ENABLE 0x0004
#define DCB_DISABLE 0x0008

/* Objects. */
#define WHITE_BRUSH 0
#define LTGRAY_BRUSH 1
#define GRAY_BRUSH 2
#define DKGRAY_BRUSH 3
#define BLACK_BRUSH 4
#define NULL_BRUSH 5
#define HOLLOW_BRUSH NULL_BRUSH
#define WHITE_PEN 6
#define BLACK_PEN 7
#define NULL_PEN 8
#define OEM_FIXED_FONT 10
#define ANSI_FIXED_FONT 11
#define ANSI_VAR_FONT 12
#define SYSTEM_FONT 13
#define DEVICE_DEFAULT_FONT 14
#define DEFAULT_PALETTE 15
#define SYSTEM_FIXED_FONT 16
#define OBJ_PEN 1
#define OBJ_BRUSH 2
#define BS_SOLID 0
#define BS_NULL 1
#define BS_HOLLOW BS_NULL
#define BS_HATCHED 2
#define BS_PATTERN 3
#define BS_INDEXED 4
#define BS_DIBPATTERN 5
#define HS_HORIZONTAL 0
#define HS_VERTICAL 1
#define HS_FDIAGONAL 2
#define HS_BDIAGONAL 3
#define HS_CROSS 4
#define HS_DIAGCROSS 5
#define PS_SOLID 0
#define PS_DASH 1
#define PS_DOT 2
#define PS_DASHDOT 3
#define PS_DASHDOTDOT 4
#define PS_NULL 5
#define PS_INSIDEFRAME 6
#define RGN_AND 1
#define RGN_OR 2
#define RGN_XOR 3
#define RGN_DIFF 4
#define RGN_COPY 5
#define ERROR 0
#define NULLREGION 1
#define SIMPLEREGION 2
#define COMPLEXREGION 3
#define PC_RESERVED 0x01
#define PC_EXPLICIT 0x02
#define PC_NOCOLLAPSE 0x04
#define SYSPAL_STATIC 1
#define SYSPAL_NOSTATIC 2

/* Bitmaps. */
#define DIB_RGB_COLORS 0
#define DIB_PAL_COLORS 1
#define CBM_INIT 0x00000004L
#define BI_RGB 0L
#define BI_RLE8 1L
#define BI_RLE4 2L

/* Fonts. */
#define LF_FACESIZE 32
#define LF_FULLFACESIZE 64
#define OUT_DEFAULT_PRECIS 0
#define OUT_STRING_PRECIS 1
#define OUT_CHARACTER_PRECIS 2
#define OUT_STROKE_PRECIS 3
#define OUT_TT_PRECIS 4
#define OUT_DEVICE_PRECIS 5
#define OUT_RASTER_PRECIS 6
#define OUT_TT_ONLY_PRECIS 7
#define CLIP_DEFAULT_PRECIS 0x00
#define CLIP_CHARACTER_PRECIS 0x01
#define CLIP_STROKE_PRECIS 0x02
#define CLIP_MASK 0x0F
#define CLIP_LH_ANGLES 0x10
#define CLIP_TT_ALWAYS 0x20
#define CLIP_EMBEDDED 0x80
#define DEFAULT_QUALITY 0
#define DRAFT_QUALITY 1
#define PROOF_QUALITY 2
#define DEFAULT_PITCH 0x00
#define FIXED_PITCH 0x01
#define VARIABLE_PITCH 0x02
#define ANSI_CHARSET 0
#define DEFAULT_CHARSET 1
#define SYMBOL_CHARSET 2
#define SHIFTJIS_CHARSET 128
#define HANGEUL_CHARSET 129
#define CHINESEBIG5_CHARSET 136
#define OEM_CHARSET 255
#define FF_DONTCARE 0x00
#define FF_ROMAN 0x10
#define FF_SWISS 0x20
#define FF_MODERN 0x30
#define FF_SCRIPT 0x40
#define FF_DECORATIVE 0x50
#define FW_DONTCARE 0
#define FW_THIN 100
#define FW_EXTRALIGHT 200
#define FW_LIGHT 300
#define FW_NORMAL 400
#define FW_MEDIUM 500
#define FW_SEMIBOLD 600
#define FW_BOLD 700
#define FW_EXTRABOLD 800
#define FW_HEAVY 900
#define FW_ULTRALIGHT FW_EXTRALIGHT
#define FW_REGULAR FW_NORMAL
#define FW_DEMIBOLD FW_SEMIBOLD
#define FW_ULTRABOLD FW_EXTRABOLD
#define FW_BLACK FW_HEAVY
#define TMPF_FIXED_PITCH 0x01
#define TMPF_VECTOR 0x02
#define TMPF_TRUETYPE 0x04
#define TMPF_DEVICE 0x08
#define RASTER_FONTTYPE 0x0001
#define DEVICE_FONTTYPE 0x0002
#define TRUETYPE_FONTTYPE 0x0004
#define NTM_ITALIC 0x00000001L
#define NTM_BOLD 0x00000020L
#define NTM_REGULAR 0x00000040L
#define ASPECT_FILTERING 0x00000001L
#define GGO_METRICS 0
#define GGO_BITMAP 1
#define GGO_NATIVE 2
#define TT_POLYGON_TYPE 24
#define TT_PRIM_LINE 1
#define TT_PRIM_QSPLINE 2
#define TT_AVAILABLE 0x0001
#define TT_ENABLED 0x0002

#ifndef RC_INVOKED
typedef struct tagLOGPEN {
  UINT lopnStyle;
  POINT lopnWidth;
  COLORREF lopnColor;
} LOGPEN;
typedef LOGPEN NEAR *PLOGPEN;
typedef LOGPEN FAR *LPLOGPEN;

typedef struct tagLOGBRUSH {
  UINT lbStyle;
  COLORREF lbColor;
  int lbHatch;
} LOGBRUSH;
typedef LOGBRUSH NEAR *PLOGBRUSH;
typedef LOGBRUSH FAR *LPLOGBRUSH;
typedef LOGBRUSH PATTERN;
typedef PATTERN FAR *LPPATTERN;

typedef struct tagLOGFONT {
  int lfHeight;
  int lfWidth;
  int lfEscapement;
  int lfOrientation;
  int lfWeight;
  BYTE lfItalic;
  BYTE lfUnderline;
  BYTE lfStrikeOut;
  BYTE lfCharSet;
  BYTE lfOutPrecision;
  BYTE lfClipPrecision;
  BYTE lfQuality;
  BYTE lfPitchAndFamily;
  char lfFaceName[LF_FACESIZE];
} LOGFONT;
typedef LOGFONT NEAR *PLOGFONT;
typedef LOGFONT FAR *LPLOGFONT;

typedef struct tagENUMLOGFONT {
  LOGFONT elfLogFont;
  char elfFullName[LF_FULLFACESIZE];
  char elfStyle[LF_FACESIZE];
} ENUMLOGFONT;
typedef ENUMLOGFONT FAR *LPENUMLOGFONT;

typedef struct tagTEXTMETRIC {
  int tmHeight;
  int tmAscent;
  int tmDescent;
  int tmInternalLeading;
  int tmExternalLeading;
  int tmAveCharWidth;
  int tmMaxCharWidth;
  int tmWeight;
  BYTE tmItalic;
  BYTE tmUnderlined;
  BYTE tmStruckOut;
  BYTE tmFirstChar;
  BYTE tmLastChar;
  BYTE tmDefaultChar;
  BYTE tmBreakChar;
  BYTE tmPitchAndFamily;
  BYTE tmCharSet;
  int tmOverhang;
  int tmDigitizedAspectX;
  int tmDigitizedAspectY;
} TEXTMETRIC;
typedef TEXTMETRIC NEAR *PTEXTMETRIC;
typedef TEXTMETRIC FAR *LPTEXTMETRIC;

typedef struct tagNEWTEXTMETRIC {
  int tmHeight;
  int tmAscent;
  int tmDescent;
  int tmInternalLeading;
  int tmExternalLeading;
  int tmAveCharWidth;
  int tmMaxCharWidth;
  int tmWeight;
  BYTE tmItalic;
  BYTE tmUnderlined;
  BYTE tmStruckOut;
  BYTE tmFirstChar;
  BYTE tmLastChar;
  BYTE tmDefaultChar;
  BYTE tmBreakChar;
  BYTE tmPitchAndFamily;
  BYTE tmCharSet;
  int tmOverhang;
  int tmDigitizedAspectX;
  int tmDigitizedAspectY;
  DWORD ntmFlags;
  UINT ntmSizeEM;
  UINT ntmCellHeight;
  UINT ntmAvgWidth;
} NEWTEXTMETRIC;
typedef NEWTEXTMETRIC FAR *LPNEWTEXTMETRIC;

typedef struct tagPANOSE {
  BYTE bFamilyType;
  BYTE bSerifStyle;
  BYTE bWeight;
  BYTE bProportion;
  BYTE bContrast;
  BYTE bStrokeVariation;
  BYTE bArmStyle;
  BYTE bLetterform;
  BYTE bMidline;
  BYTE bXHeight;
} PANOSE;

typedef struct tagOUTLINETEXTMETRIC {
  UINT otmSize;
  TEXTMETRIC otmTextMetrics;
  BYTE otmFiller;
  PANOSE otmPanoseNumber;
  UINT otmfsSelection;
  UINT otmfsType;
  int otmsCharSlopeRise;
  int otmsCharSlopeRun;
  int otmItalicAngle;
  UINT otmEMSquare;
  int otmAscent;
  int otmDescent;
  UINT otmLineGap;
  UINT otmsCapEmHeight;
  UINT otmsXHeight;
  RECT otmrcFontBox;
  int otmMacAscent;
  int otmMacDescent;
  UINT otmMacLineGap;
  UINT otmusMinimumPPEM;
  POINT otmptSubscriptSize;
  POINT otmptSubscriptOffset;
  POINT otmptSuperscriptSize;
  POINT otmptSuperscriptOffset;
  UINT otmsStrikeoutSize;
  int otmsStrikeoutPosition;
  int otmsUnderscoreSize;
  int otmsUnderscorePosition;
  PSTR otmpFamilyName; /* offsets from the start of the structure */
  PSTR otmpFaceName;
  PSTR otmpStyleName;
  PSTR otmpFullName;
} OUTLINETEXTMETRIC;
typedef OUTLINETEXTMETRIC FAR *LPOUTLINETEXTMETRIC;

typedef struct tagABC {
  int abcA;
  UINT abcB;
  int abcC;
} ABC;
typedef ABC FAR *LPABC;

typedef struct tagKERNINGPAIR {
  WORD wFirst;
  WORD wSecond;
  int iKernAmount;
} KERNINGPAIR;
typedef KERNINGPAIR FAR *LPKERNINGPAIR;

typedef struct tagRASTERIZER_STATUS {
  int nSize;
  int wFlags;
  int nLanguageID;
} RASTERIZER_STATUS;
typedef RASTERIZER_STATUS FAR *LPRASTERIZER_STATUS;

typedef struct tagFIXED {
  UINT fract;
  int value;
} FIXED;
typedef struct tagMAT2 {
  FIXED eM11;
  FIXED eM12;
  FIXED eM21;
  FIXED eM22;
} MAT2;
typedef MAT2 FAR *LPMAT2;
typedef struct tagPOINTFX {
  FIXED x;
  FIXED y;
} POINTFX;
typedef POINTFX FAR *LPPOINTFX;
typedef struct tagGLYPHMETRICS {
  UINT gmBlackBoxX;
  UINT gmBlackBoxY;
  POINT gmptGlyphOrigin;
  int gmCellIncX;
  int gmCellIncY;
} GLYPHMETRICS;
typedef GLYPHMETRICS FAR *LPGLYPHMETRICS;
typedef struct tagTTPOLYCURVE {
  UINT wType;
  UINT cpfx;
  POINTFX apfx[1];
} TTPOLYCURVE;
typedef TTPOLYCURVE FAR *LPTTPOLYCURVE;
typedef struct tagTTPOLYGONHEADER {
  DWORD cb;
  DWORD dwType;
  POINTFX pfxStart;
} TTPOLYGONHEADER;
typedef TTPOLYGONHEADER FAR *LPTTPOLYGONHEADER;

typedef struct tagBITMAP {
  int bmType;
  int bmWidth;
  int bmHeight;
  int bmWidthBytes;
  BYTE bmPlanes;
  BYTE bmBitsPixel;
  void FAR *bmBits;
} BITMAP;
typedef BITMAP NEAR *PBITMAP;
typedef BITMAP FAR *LPBITMAP;

typedef struct tagRGBTRIPLE {
  BYTE rgbtBlue;
  BYTE rgbtGreen;
  BYTE rgbtRed;
} RGBTRIPLE;
typedef struct tagRGBQUAD {
  BYTE rgbBlue;
  BYTE rgbGreen;
  BYTE rgbRed;
  BYTE rgbReserved;
} RGBQUAD;
typedef RGBQUAD FAR *LPRGBQUAD;

typedef struct tagBITMAPCOREHEADER {
  DWORD bcSize;
  short bcWidth;
  short bcHeight;
  WORD bcPlanes;
  WORD bcBitCount;
} BITMAPCOREHEADER;
typedef BITMAPCOREHEADER FAR *LPBITMAPCOREHEADER;
typedef struct tagBITMAPCOREINFO {
  BITMAPCOREHEADER bmciHeader;
  RGBTRIPLE bmciColors[1];
} BITMAPCOREINFO;
typedef BITMAPCOREINFO FAR *LPBITMAPCOREINFO;

typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG biWidth;
  LONG biHeight;
  WORD biPlanes;
  WORD biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG biXPelsPerMeter;
  LONG biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER;
typedef BITMAPINFOHEADER FAR *LPBITMAPINFOHEADER;
typedef struct tagBITMAPINFO {
  BITMAPINFOHEADER bmiHeader;
  RGBQUAD bmiColors[1];
} BITMAPINFO;
typedef BITMAPINFO FAR *LPBITMAPINFO;

typedef struct tagBITMAPFILEHEADER {
  UINT bfType;
  DWORD bfSize;
  UINT bfReserved1;
  UINT bfReserved2;
  DWORD bfOffBits;
} BITMAPFILEHEADER;
typedef BITMAPFILEHEADER FAR *LPBITMAPFILEHEADER;

typedef struct tagPALETTEENTRY {
  BYTE peRed;
  BYTE peGreen;
  BYTE peBlue;
  BYTE peFlags;
} PALETTEENTRY;
typedef PALETTEENTRY FAR *LPPALETTEENTRY;
typedef struct tagLOGPALETTE {
  WORD palVersion;
  WORD palNumEntries;
  PALETTEENTRY palPalEntry[1];
} LOGPALETTE;
typedef LOGPALETTE NEAR *PLOGPALETTE;
typedef LOGPALETTE FAR *LPLOGPALETTE;

typedef struct tagHANDLETABLE {
  HGDIOBJ objectHandle[1];
} HANDLETABLE;
typedef HANDLETABLE FAR *LPHANDLETABLE;
typedef struct tagMETARECORD {
  DWORD rdSize;
  UINT rdFunction;
  UINT rdParm[1];
} METARECORD;
typedef METARECORD FAR *LPMETARECORD;
typedef struct tagMETAFILEPICT {
  int mm;
  int xExt;
  int yExt;
  HMETAFILE hMF;
} METAFILEPICT;
typedef METAFILEPICT FAR *LPMETAFILEPICT;
typedef struct tagMETAHEADER {
  UINT mtType;
  UINT mtHeaderSize;
  UINT mtVersion;
  DWORD mtSize;
  UINT mtNoObjects;
  DWORD mtMaxRecord;
  UINT mtNoParameters;
} METAHEADER;

/* DEVMODE, for CreateDC and the printer drivers (print.h has the rest). */
#define CCHDEVICENAME 32
typedef struct tagDEVMODE {
  char dmDeviceName[CCHDEVICENAME];
  UINT dmSpecVersion;
  UINT dmDriverVersion;
  UINT dmSize;
  UINT dmDriverExtra;
  DWORD dmFields;
  int dmOrientation;
  int dmPaperSize;
  int dmPaperLength;
  int dmPaperWidth;
  int dmScale;
  int dmCopies;
  int dmDefaultSource;
  int dmPrintQuality;
  int dmColor;
  int dmDuplex;
  int dmYResolution;
  int dmTTOption;
} DEVMODE;
typedef DEVMODE FAR *LPDEVMODE;

typedef struct tagDOCINFO {
  int cbSize;
  LPCSTR lpszDocName;
  LPCSTR lpszOutput;
} DOCINFO;
typedef DOCINFO FAR *LPDOCINFO;

#ifdef STRICT
typedef int(CALLBACK *GOBJENUMPROC)(void FAR *, LPARAM);
typedef void(CALLBACK *LINEDDAPROC)(int, int, LPARAM);
typedef int(CALLBACK *OLDFONTENUMPROC)(const LOGFONT FAR *,
                                       const TEXTMETRIC FAR *, int, LPARAM);
typedef int(CALLBACK *FONTENUMPROC)(const ENUMLOGFONT FAR *,
                                    const NEWTEXTMETRIC FAR *, int, LPARAM);
typedef int(CALLBACK *MFENUMPROC)(HDC, HANDLETABLE FAR *, METARECORD FAR *,
                                  int, LPARAM);
typedef BOOL(CALLBACK *ABORTPROC)(HDC, int);
#else
typedef FARPROC GOBJENUMPROC;
typedef FARPROC LINEDDAPROC;
typedef FARPROC OLDFONTENUMPROC;
typedef FARPROC FONTENUMPROC;
typedef FARPROC MFENUMPROC;
typedef FARPROC ABORTPROC;
#endif

#ifndef NOGDI
/* Device contexts. */
HDC WINAPI CreateDC(LPCSTR, LPCSTR, LPCSTR, const void FAR *);
HDC WINAPI CreateIC(LPCSTR, LPCSTR, LPCSTR, const void FAR *);
HDC WINAPI CreateCompatibleDC(HDC);
BOOL WINAPI DeleteDC(HDC);
#if WINVER >= 0x030A
HDC WINAPI ResetDC(HDC, const DEVMODE FAR *);
#endif
int WINAPI SaveDC(HDC);
BOOL WINAPI RestoreDC(HDC, int);
int WINAPI GetDeviceCaps(HDC, int);
DWORD WINAPI GetDCOrg(HDC);
#if WINVER >= 0x030A
UINT WINAPI SetBoundsRect(HDC, const RECT FAR *, UINT);
UINT WINAPI GetBoundsRect(HDC, RECT FAR *, UINT);
#endif

/* Coordinates. */
int WINAPI SetMapMode(HDC, int);
int WINAPI GetMapMode(HDC);
DWORD WINAPI SetWindowOrg(HDC, int, int);
DWORD WINAPI GetWindowOrg(HDC);
DWORD WINAPI SetWindowExt(HDC, int, int);
DWORD WINAPI GetWindowExt(HDC);
DWORD WINAPI OffsetWindowOrg(HDC, int, int);
DWORD WINAPI ScaleWindowExt(HDC, int, int, int, int);
DWORD WINAPI SetViewportOrg(HDC, int, int);
DWORD WINAPI GetViewportOrg(HDC);
DWORD WINAPI SetViewportExt(HDC, int, int);
DWORD WINAPI GetViewportExt(HDC);
DWORD WINAPI OffsetViewportOrg(HDC, int, int);
DWORD WINAPI ScaleViewportExt(HDC, int, int, int, int);
#if WINVER >= 0x030A
BOOL WINAPI SetWindowOrgEx(HDC, int, int, POINT FAR *);
BOOL WINAPI GetWindowOrgEx(HDC, POINT FAR *);
BOOL WINAPI SetWindowExtEx(HDC, int, int, SIZE FAR *);
BOOL WINAPI GetWindowExtEx(HDC, SIZE FAR *);
BOOL WINAPI OffsetWindowOrgEx(HDC, int, int, POINT FAR *);
BOOL WINAPI ScaleWindowExtEx(HDC, int, int, int, int, SIZE FAR *);
BOOL WINAPI SetViewportOrgEx(HDC, int, int, POINT FAR *);
BOOL WINAPI GetViewportOrgEx(HDC, POINT FAR *);
BOOL WINAPI SetViewportExtEx(HDC, int, int, SIZE FAR *);
BOOL WINAPI GetViewportExtEx(HDC, SIZE FAR *);
BOOL WINAPI OffsetViewportOrgEx(HDC, int, int, POINT FAR *);
BOOL WINAPI ScaleViewportExtEx(HDC, int, int, int, int, SIZE FAR *);
#endif
BOOL WINAPI DPtoLP(HDC, POINT FAR *, int);
BOOL WINAPI LPtoDP(HDC, POINT FAR *, int);

/* Drawing attributes. */
COLORREF WINAPI SetBkColor(HDC, COLORREF);
COLORREF WINAPI GetBkColor(HDC);
int WINAPI SetBkMode(HDC, int);
int WINAPI GetBkMode(HDC);
COLORREF WINAPI SetTextColor(HDC, COLORREF);
COLORREF WINAPI GetTextColor(HDC);
int WINAPI SetROP2(HDC, int);
int WINAPI GetROP2(HDC);
int WINAPI SetPolyFillMode(HDC, int);
int WINAPI GetPolyFillMode(HDC);
int WINAPI SetStretchBltMode(HDC, int);
int WINAPI GetStretchBltMode(HDC);
int WINAPI SetRelAbs(HDC, int);
int WINAPI GetRelAbs(HDC);
COLORREF WINAPI GetNearestColor(HDC, COLORREF);

/* Lines and shapes. */
DWORD WINAPI MoveTo(HDC, int, int);
DWORD WINAPI GetCurrentPosition(HDC);
#if WINVER >= 0x030A
BOOL WINAPI MoveToEx(HDC, int, int, POINT FAR *);
BOOL WINAPI GetCurrentPositionEx(HDC, POINT FAR *);
#endif
BOOL WINAPI LineTo(HDC, int, int);
BOOL WINAPI Polyline(HDC, const POINT FAR *, int);
BOOL WINAPI Polygon(HDC, const POINT FAR *, int);
#if WINVER >= 0x0300
BOOL WINAPI PolyPolygon(HDC, const POINT FAR *, const int FAR *, int);
#endif
BOOL WINAPI Rectangle(HDC, int, int, int, int);
BOOL WINAPI RoundRect(HDC, int, int, int, int, int, int);
BOOL WINAPI Ellipse(HDC, int, int, int, int);
BOOL WINAPI Arc(HDC, int, int, int, int, int, int, int, int);
#if WINVER >= 0x0200
BOOL WINAPI Chord(HDC, int, int, int, int, int, int, int, int);
#endif
BOOL WINAPI Pie(HDC, int, int, int, int, int, int, int, int);
void WINAPI LineDDA(int, int, int, int, LINEDDAPROC, LPARAM);
COLORREF WINAPI SetPixel(HDC, int, int, COLORREF);
COLORREF WINAPI GetPixel(HDC, int, int);
BOOL WINAPI FloodFill(HDC, int, int, COLORREF);
#if WINVER >= 0x0300
BOOL WINAPI ExtFloodFill(HDC, int, int, COLORREF, UINT);
#endif
BOOL WINAPI PatBlt(HDC, int, int, int, int, DWORD);
BOOL WINAPI BitBlt(HDC, int, int, int, int, HDC, int, int, DWORD);
BOOL WINAPI StretchBlt(HDC, int, int, int, int, HDC, int, int, int, int,
                       DWORD);

/* Pens, brushes and other objects. */
HPEN WINAPI CreatePen(int, int, COLORREF);
HPEN WINAPI CreatePenIndirect(const LOGPEN FAR *);
HBRUSH WINAPI CreateSolidBrush(COLORREF);
HBRUSH WINAPI CreateHatchBrush(int, COLORREF);
HBRUSH WINAPI CreatePatternBrush(HBITMAP);
HBRUSH WINAPI CreateBrushIndirect(const LOGBRUSH FAR *);
#if WINVER >= 0x0300
HBRUSH WINAPI CreateDIBPatternBrush(HGLOBAL, UINT);
#endif
HGDIOBJ WINAPI GetStockObject(int);
HGDIOBJ WINAPI SelectObject(HDC, HGDIOBJ);
BOOL WINAPI DeleteObject(HGDIOBJ);
int WINAPI GetObject(HGDIOBJ, int, void FAR *);
BOOL WINAPI UnrealizeObject(HGDIOBJ);
int WINAPI EnumObjects(HDC, int, GOBJENUMPROC, LPARAM);
DWORD WINAPI SetBrushOrg(HDC, int, int);
DWORD WINAPI GetBrushOrg(HDC);
#if WINVER >= 0x030A
BOOL WINAPI GetBrushOrgEx(HDC, POINT FAR *);
BOOL WINAPI IsGDIObject(HGDIOBJ);
#endif

/* Bitmaps. */
HBITMAP WINAPI CreateBitmap(int, int, UINT, UINT, const void FAR *);
HBITMAP WINAPI CreateBitmapIndirect(BITMAP FAR *);
HBITMAP WINAPI CreateCompatibleBitmap(HDC, int, int);
HBITMAP WINAPI CreateDiscardableBitmap(HDC, int, int);
LONG WINAPI SetBitmapBits(HBITMAP, DWORD, const void FAR *);
LONG WINAPI GetBitmapBits(HBITMAP, LONG, void FAR *);
DWORD WINAPI SetBitmapDimension(HBITMAP, int, int);
DWORD WINAPI GetBitmapDimension(HBITMAP);
#if WINVER >= 0x030A
BOOL WINAPI SetBitmapDimensionEx(HBITMAP, int, int, SIZE FAR *);
BOOL WINAPI GetBitmapDimensionEx(HBITMAP, SIZE FAR *);
#endif
#if WINVER >= 0x0300
HBITMAP WINAPI CreateDIBitmap(HDC, BITMAPINFOHEADER FAR *, DWORD,
                              const void FAR *, BITMAPINFO FAR *, UINT);
int WINAPI SetDIBits(HDC, HBITMAP, UINT, UINT, const void FAR *,
                     BITMAPINFO FAR *, UINT);
int WINAPI GetDIBits(HDC, HBITMAP, UINT, UINT, void FAR *, BITMAPINFO FAR *,
                     UINT);
int WINAPI SetDIBitsToDevice(HDC, int, int, int, int, int, int, UINT, UINT,
                             void FAR *, BITMAPINFO FAR *, UINT);
int WINAPI StretchDIBits(HDC, int, int, int, int, int, int, int, int,
                         const void FAR *, BITMAPINFO FAR *, UINT, DWORD);
#endif

/* Regions and clipping. */
HRGN WINAPI CreateRectRgn(int, int, int, int);
HRGN WINAPI CreateRectRgnIndirect(const RECT FAR *);
HRGN WINAPI CreateEllipticRgn(int, int, int, int);
HRGN WINAPI CreateEllipticRgnIndirect(const RECT FAR *);
HRGN WINAPI CreatePolygonRgn(const POINT FAR *, int, int);
#if WINVER >= 0x0300
HRGN WINAPI CreatePolyPolygonRgn(const POINT FAR *, const int FAR *, int, int);
HRGN WINAPI CreateRoundRectRgn(int, int, int, int, int, int);
#endif
int WINAPI CombineRgn(HRGN, HRGN, HRGN, int);
BOOL WINAPI EqualRgn(HRGN, HRGN);
int WINAPI OffsetRgn(HRGN, int, int);
int WINAPI GetRgnBox(HRGN, RECT FAR *);
#if WINVER >= 0x0200
void WINAPI SetRectRgn(HRGN, int, int, int, int);
#endif
BOOL WINAPI PtInRegion(HRGN, int, int);
#if WINVER >= 0x0200
BOOL WINAPI RectInRegion(HRGN, const RECT FAR *);
#endif
BOOL WINAPI FillRgn(HDC, HRGN, HBRUSH);
BOOL WINAPI FrameRgn(HDC, HRGN, HBRUSH, int, int);
BOOL WINAPI InvertRgn(HDC, HRGN);
BOOL WINAPI PaintRgn(HDC, HRGN);
int WINAPI SelectClipRgn(HDC, HRGN);
int WINAPI ExcludeClipRect(HDC, int, int, int, int);
int WINAPI IntersectClipRect(HDC, int, int, int, int);
int WINAPI OffsetClipRgn(HDC, int, int);
int WINAPI GetClipBox(HDC, RECT FAR *);
BOOL WINAPI PtVisible(HDC, int, int);
BOOL WINAPI RectVisible(HDC, const RECT FAR *);

/* Text and fonts. */
BOOL WINAPI TextOut(HDC, int, int, LPCSTR, int);
#if WINVER >= 0x0200
BOOL WINAPI ExtTextOut(HDC, int, int, UINT, const RECT FAR *, LPCSTR, UINT,
                       int FAR *);
#endif
DWORD WINAPI GetTextExtent(HDC, LPCSTR, int);
#if WINVER >= 0x030A
BOOL WINAPI GetTextExtentPoint(HDC, LPCSTR, int, SIZE FAR *);
#endif
int WINAPI GetTextFace(HDC, int, LPSTR);
BOOL WINAPI GetTextMetrics(HDC, TEXTMETRIC FAR *);
#if WINVER >= 0x0200
UINT WINAPI SetTextAlign(HDC, UINT);
#endif
#if WINVER >= 0x0300
UINT WINAPI GetTextAlign(HDC);
#endif
int WINAPI SetTextCharacterExtra(HDC, int);
int WINAPI GetTextCharacterExtra(HDC);
int WINAPI SetTextJustification(HDC, int, int);
#if WINVER >= 0x0200
BOOL WINAPI GetCharWidth(HDC, UINT, UINT, int FAR *);
DWORD WINAPI SetMapperFlags(HDC, DWORD);
DWORD WINAPI GetAspectRatioFilter(HDC);
#endif
#if WINVER >= 0x030A
BOOL WINAPI GetAspectRatioFilterEx(HDC, SIZE FAR *);
#endif
HFONT WINAPI CreateFont(int, int, int, int, int, BYTE, BYTE, BYTE, BYTE, BYTE,
                        BYTE, BYTE, BYTE, LPCSTR);
HFONT WINAPI CreateFontIndirect(const LOGFONT FAR *);
int WINAPI EnumFonts(HDC, LPCSTR, OLDFONTENUMPROC, LPARAM);
int WINAPI AddFontResource(LPCSTR);
BOOL WINAPI RemoveFontResource(LPCSTR);
#if WINVER >= 0x030A
int WINAPI EnumFontFamilies(HDC, LPCSTR, FONTENUMPROC, LPARAM);
BOOL WINAPI GetCharABCWidths(HDC, UINT, UINT, ABC FAR *);
WORD WINAPI GetOutlineTextMetrics(HDC, UINT, OUTLINETEXTMETRIC FAR *);
DWORD WINAPI GetGlyphOutline(HDC, UINT, UINT, GLYPHMETRICS FAR *, DWORD,
                             void FAR *, const MAT2 FAR *);
BOOL WINAPI CreateScalableFontResource(UINT, LPCSTR, LPCSTR, LPCSTR);
DWORD WINAPI GetFontData(HDC, DWORD, DWORD, void FAR *, DWORD);
BOOL WINAPI GetRasterizerCaps(RASTERIZER_STATUS FAR *, int);
int WINAPI GetKerningPairs(HDC, int, KERNINGPAIR FAR *);
#endif

/* Palettes. */
#if WINVER >= 0x0300
HPALETTE WINAPI CreatePalette(const LOGPALETTE FAR *);
HPALETTE WINAPI SelectPalette(HDC, HPALETTE, BOOL);
UINT WINAPI RealizePalette(HDC);
int WINAPI UpdateColors(HDC);
void WINAPI AnimatePalette(HPALETTE, UINT, UINT, const PALETTEENTRY FAR *);
UINT WINAPI SetPaletteEntries(HPALETTE, UINT, UINT,
                              const PALETTEENTRY FAR *);
UINT WINAPI GetPaletteEntries(HPALETTE, UINT, UINT, PALETTEENTRY FAR *);
UINT WINAPI GetNearestPaletteIndex(HPALETTE, COLORREF);
BOOL WINAPI ResizePalette(HPALETTE, UINT);
UINT WINAPI GetSystemPaletteEntries(HDC, UINT, UINT, PALETTEENTRY FAR *);
UINT WINAPI GetSystemPaletteUse(HDC);
UINT WINAPI SetSystemPaletteUse(HDC, UINT);
#endif

/* Metafiles. */
#ifndef NOMETAFILE
HDC WINAPI CreateMetaFile(LPCSTR);
HMETAFILE WINAPI CloseMetaFile(HDC);
HMETAFILE WINAPI GetMetaFile(LPCSTR);
HMETAFILE WINAPI CopyMetaFile(HMETAFILE, LPCSTR);
BOOL WINAPI DeleteMetaFile(HMETAFILE);
BOOL WINAPI PlayMetaFile(HDC, HMETAFILE);
HGLOBAL WINAPI GetMetaFileBits(HMETAFILE);
HMETAFILE WINAPI SetMetaFileBits(HGLOBAL);
#if WINVER >= 0x0200
void WINAPI PlayMetaFileRecord(HDC, HANDLETABLE FAR *, METARECORD FAR *,
                               UINT);
BOOL WINAPI EnumMetaFile(HDC, HMETAFILE, MFENUMPROC, LPARAM);
#endif
#if WINVER >= 0x030A
HMETAFILE WINAPI SetMetaFileBitsBetter(HGLOBAL);
#endif
#endif

/* Printing. */
int WINAPI Escape(HDC, int, int, LPCSTR, void FAR *);
#if WINVER >= 0x030A
int WINAPI StartDoc(HDC, DOCINFO FAR *);
int WINAPI EndDoc(HDC);
int WINAPI StartPage(HDC);
int WINAPI EndPage(HDC);
int WINAPI AbortDoc(HDC);
int WINAPI SetAbortProc(HDC, ABORTPROC);
#endif
BOOL WINAPI QueryAbort(HDC, int);
int WINAPI GetEnvironment(LPCSTR, void FAR *, UINT);
int WINAPI SetEnvironment(LPCSTR, const void FAR *, UINT);
#endif /* NOGDI */
#endif /* RC_INVOKED */

/* Printer escapes. */
#define NEWFRAME 1
#define ABORTDOC 2
#define NEXTBAND 3
#define SETCOLORTABLE 4
#define GETCOLORTABLE 5
#define FLUSHOUTPUT 6
#define DRAFTMODE 7
#define QUERYESCSUPPORT 8
#define SETABORTPROC 9
#define STARTDOC 10
#define ENDDOC 11
#define GETPHYSPAGESIZE 12
#define GETPRINTINGOFFSET 13
#define GETSCALINGFACTOR 14
#define MFCOMMENT 15
#define GETPENWIDTH 16
#define SETCOPYCOUNT 17
#define SELECTPAPERSOURCE 18
#define DEVICEDATA 19
#define PASSTHROUGH 19
#define GETTECHNOLGY 20
#define GETTECHNOLOGY 20
#define SETLINECAP 21
#define SETLINEJOIN 22
#define SETMITERLIMIT 23
#define BANDINFO 24
#define DRAWPATTERNRECT 25
#define GETVECTORPENSIZE 26
#define GETVECTORBRUSHSIZE 27
#define ENABLEDUPLEX 28
#define GETSETPAPERBINS 29
#define GETSETPRINTORIENT 30
#define ENUMPAPERBINS 31
#define SETDIBSCALING 32
#define EPSPRINTING 33
#define ENUMPAPERMETRICS 34
#define GETSETPAPERMETRICS 35
#define POSTSCRIPT_DATA 37
#define POSTSCRIPT_IGNORE 38
#define GETEXTENDEDTEXTMETRICS 256
#define GETEXTENTTABLE 257
#define GETPAIRKERNTABLE 258
#define GETTRACKKERNTABLE 259
#define EXTTEXTOUT 512
#define ENABLERELATIVEWIDTHS 768
#define ENABLEPAIRKERNING 769
#define SETKERNTRACK 770
#define SETALLJUSTVALUES 771
#define SETCHARSET 772
#define STRETCHBLT 2048
#define BEGIN_PATH 4096
#define CLIP_TO_PATH 4097
#define END_PATH 4098
#define EXT_DEVICE_CAPS 4099
#define RESTORE_CTM 4100
#define SAVE_CTM 4101
#define SET_ARC_DIRECTION 4102
#define SET_BACKGROUND_COLOR 4103
#define SET_POLY_MODE 4104
#define SET_SCREEN_ANGLE 4105
#define SET_SPREAD 4106
#define TRANSFORM_CTM 4107
#define SET_CLIP_BOX 4108
#define SET_BOUNDS 4109
#define SP_NOTREPORTED 0x4000
#define SP_ERROR (-1)
#define SP_APPABORT (-2)
#define SP_USERABORT (-3)
#define SP_OUTOFDISK (-4)
#define SP_OUTOFMEMORY (-5)
#define PR_JOBSTATUS 0x0000

/* Metafile records. */
#define META_SETBKCOLOR 0x0201
#define META_SETBKMODE 0x0102
#define META_SETMAPMODE 0x0103
#define META_SETROP2 0x0104
#define META_SETRELABS 0x0105
#define META_SETPOLYFILLMODE 0x0106
#define META_SETSTRETCHBLTMODE 0x0107
#define META_SETTEXTCHAREXTRA 0x0108
#define META_SETTEXTCOLOR 0x0209
#define META_SETTEXTJUSTIFICATION 0x020A
#define META_SETWINDOWORG 0x020B
#define META_SETWINDOWEXT 0x020C
#define META_SETVIEWPORTORG 0x020D
#define META_SETVIEWPORTEXT 0x020E
#define META_OFFSETWINDOWORG 0x020F
#define META_SCALEWINDOWEXT 0x0410
#define META_OFFSETVIEWPORTORG 0x0211
#define META_SCALEVIEWPORTEXT 0x0412
#define META_LINETO 0x0213
#define META_MOVETO 0x0214
#define META_EXCLUDECLIPRECT 0x0415
#define META_INTERSECTCLIPRECT 0x0416
#define META_ARC 0x0817
#define META_ELLIPSE 0x0418
#define META_FLOODFILL 0x0419
#define META_PIE 0x081A
#define META_RECTANGLE 0x041B
#define META_ROUNDRECT 0x061C
#define META_PATBLT 0x061D
#define META_SAVEDC 0x001E
#define META_SETPIXEL 0x041F
#define META_OFFSETCLIPRGN 0x0220
#define META_TEXTOUT 0x0521
#define META_BITBLT 0x0922
#define META_STRETCHBLT 0x0B23
#define META_POLYGON 0x0324
#define META_POLYLINE 0x0325
#define META_ESCAPE 0x0626
#define META_RESTOREDC 0x0127
#define META_FILLREGION 0x0228
#define META_FRAMEREGION 0x0429
#define META_INVERTREGION 0x012A
#define META_PAINTREGION 0x012B
#define META_SELECTCLIPREGION 0x012C
#define META_SELECTOBJECT 0x012D
#define META_SETTEXTALIGN 0x012E
#define META_DRAWTEXT 0x062F
#define META_CHORD 0x0830
#define META_SETMAPPERFLAGS 0x0231
#define META_EXTTEXTOUT 0x0A32
#define META_SETDIBTODEV 0x0D33
#define META_SELECTPALETTE 0x0234
#define META_REALIZEPALETTE 0x0035
#define META_ANIMATEPALETTE 0x0436
#define META_SETPALENTRIES 0x0037
#define META_POLYPOLYGON 0x0538
#define META_RESIZEPALETTE 0x0139
#define META_DIBBITBLT 0x0940
#define META_DIBSTRETCHBLT 0x0B41
#define META_DIBCREATEPATTERNBRUSH 0x0142
#define META_STRETCHDIB 0x0F43
#define META_DELETEOBJECT 0x01F0
#define META_CREATEPALETTE 0x00F7
#define META_CREATEBRUSH 0x00F8
#define META_CREATEPATTERNBRUSH 0x01F9
#define META_CREATEPENINDIRECT 0x02FA
#define META_CREATEFONTINDIRECT 0x02FB
#define META_CREATEBRUSHINDIRECT 0x02FC
#define META_CREATEBITMAPINDIRECT 0x02FD
#define META_CREATEBITMAP 0x06FE
#define META_CREATEREGION 0x06FF

/****************************************************************************/

#ifndef RC_INVOKED
/* The program's entry point, which the C library's start-up code calls when
 * the program has no main(). */
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
#endif

#ifdef __cplusplus
}
#endif

#ifndef RC_INVOKED
#pragma pack(pop)
#endif

#endif /* _WINDOWS_H */
