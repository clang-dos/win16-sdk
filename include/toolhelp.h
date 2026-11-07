/* toolhelp.h: walking the system's heaps, modules, tasks and stacks, and
 * system notifications (TOOLHELP.DLL, Windows 3.1; it can be shipped with
 * programs for 3.0). Written for clang-dos from the published API; AGPL-3.0-only, see
 * the win16-sdk LICENSE. */
#ifndef _TOOLHELP_H
#define _TOOLHELP_H
#define _INC_TOOLHELP

#include <windows.h>
#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_DATA 11
#define MAX_PATH 255
#define MAX_MODULE_NAME 9
#define MAX_FILENAME 255
#define MAX_CLASSNAME 255

/* The global heap. */
typedef struct tagGLOBALINFO {
  DWORD dwSize;
  WORD wcItems;
  WORD wcItemsFree;
  WORD wcItemsLRU;
} GLOBALINFO;

typedef struct tagGLOBALENTRY {
  DWORD dwSize;
  DWORD dwAddress;
  DWORD dwBlockSize;
  HGLOBAL hBlock;
  WORD wcLock;
  WORD wcPageLock;
  WORD wFlags;
  BOOL wHeapPresent;
  HGLOBAL hOwner;
  WORD wType;
  WORD wData;
  DWORD dwNext;
  DWORD dwNextAlt;
} GLOBALENTRY;

#define GLOBAL_ALL 0
#define GLOBAL_LRU 1
#define GLOBAL_FREE 2
#define GT_UNKNOWN 0
#define GT_DGROUP 1
#define GT_DATA 2
#define GT_CODE 3
#define GT_TASK 4
#define GT_RESOURCE 5
#define GT_MODULE 6
#define GT_FREE 7
#define GT_INTERNAL 8
#define GT_SENTINEL 9
#define GT_BURGERMASTER 10
#define GD_USERDEFINED 0
#define GD_CURSORCOMPONENT 1
#define GD_BITMAP 2
#define GD_ICONCOMPONENT 3
#define GD_MENU 4
#define GD_DIALOG 5
#define GD_STRING 6
#define GD_FONTDIR 7
#define GD_FONT 8
#define GD_ACCELERATORS 9
#define GD_RCDATA 10
#define GD_ERRTABLE 11
#define GD_CURSOR 12
#define GD_ICON 14
#define GD_NAMETABLE 15
#define GD_MAX_RESOURCE 15
#define GF_PDB_OWNER 0x0100

/* Local heaps. */
typedef struct tagLOCALINFO {
  DWORD dwSize;
  WORD wcItems;
} LOCALINFO;

typedef struct tagLOCALENTRY {
  DWORD dwSize;
  HLOCAL hHandle;
  WORD wAddress;
  WORD wSize;
  WORD wFlags;
  WORD wcLock;
  WORD wType;
  WORD hHeap;
  WORD wHeapType;
  WORD wNext;
} LOCALENTRY;

#define NORMAL_HEAP 0
#define USER_HEAP 1
#define GDI_HEAP 2
#define LF_FIXED 1
#define LF_FREE 2
#define LF_MOVEABLE 4
#define LT_NORMAL 0
#define LT_FREE 0xFF
#define LT_GDI_PEN 1
#define LT_GDI_BRUSH 2
#define LT_GDI_FONT 3
#define LT_GDI_PALETTE 4
#define LT_GDI_BITMAP 5
#define LT_GDI_RGN 6
#define LT_GDI_DC 7
#define LT_GDI_DISABLED_DC 8
#define LT_GDI_METADC 9
#define LT_GDI_METAFILE 10
#define LT_GDI_MAX LT_GDI_METAFILE
#define LT_USER_CLASS 1
#define LT_USER_WND 2
#define LT_USER_STRING 3
#define LT_USER_MENU 4
#define LT_USER_CLIP 5
#define LT_USER_CBOX 6
#define LT_USER_PALETTE 7
#define LT_USER_ED 8
#define LT_USER_BWL 9
#define LT_USER_OWNERDRAW 10
#define LT_USER_SPB 11
#define LT_USER_CHECKPOINT 12
#define LT_USER_DCE 13
#define LT_USER_MWP 14
#define LT_USER_PROP 15
#define LT_USER_LBIV 16
#define LT_USER_MISC 17
#define LT_USER_ATOMS 18
#define LT_USER_LOCKINPUTSTATE 19
#define LT_USER_HOOKLIST 20
#define LT_USER_USERSEEUSERDOALLOC 21
#define LT_USER_HOTKEYLIST 22
#define LT_USER_POPUPMENU 23
#define LT_USER_HANDLETABLE 32
#define LT_USER_MAX LT_USER_HANDLETABLE

/* Stacks, modules, tasks and classes. */
typedef struct tagSTACKTRACEENTRY {
  DWORD dwSize;
  HTASK hTask;
  WORD wSS;
  WORD wBP;
  WORD wCS;
  WORD wIP;
  HMODULE hModule;
  WORD wSegment;
  WORD wFlags;
} STACKTRACEENTRY;
#define FRAME_FAR 0
#define FRAME_NEAR 1

typedef struct tagMODULEENTRY {
  DWORD dwSize;
  char szModule[MAX_MODULE_NAME + 1];
  HMODULE hModule;
  WORD wcUsage;
  char szExePath[MAX_PATH + 1];
  WORD wNext;
} MODULEENTRY;
typedef MODULEENTRY FAR *LPMODULEENTRY;

typedef struct tagTASKENTRY {
  DWORD dwSize;
  HTASK hTask;
  HTASK hTaskParent;
  HINSTANCE hInst;
  HMODULE hModule;
  WORD wSS;
  WORD wSP;
  WORD wStackTop;
  WORD wStackMinimum;
  WORD wStackBottom;
  WORD wcEvents;
  HGLOBAL hQueue;
  char szModule[MAX_MODULE_NAME + 1];
  WORD wPSPOffset;
  HANDLE hNext;
} TASKENTRY;
typedef TASKENTRY FAR *LPTASKENTRY;

typedef struct tagCLASSENTRY {
  DWORD dwSize;
  HMODULE hInst;
  char szClassName[MAX_CLASSNAME + 1];
  WORD wNext;
} CLASSENTRY;
typedef CLASSENTRY FAR *LPCLASSENTRY;

/* Memory and timers. */
typedef struct tagMEMMANINFO {
  DWORD dwSize;
  DWORD dwLargestFreeBlock;
  DWORD dwMaxPagesAvailable;
  DWORD dwMaxPagesLockable;
  DWORD dwTotalLinearSpace;
  DWORD dwTotalUnlockedPages;
  DWORD dwFreePages;
  DWORD dwTotalPages;
  DWORD dwFreeLinearSpace;
  DWORD dwSwapFilePages;
  WORD wPageSize;
} MEMMANINFO;
typedef MEMMANINFO FAR *LPMEMMANINFO;

typedef struct tagSYSHEAPINFO {
  DWORD dwSize;
  WORD wUserFreePercent;
  WORD wGDIFreePercent;
  HGLOBAL hUserSegment;
  HGLOBAL hGDISegment;
} SYSHEAPINFO;

typedef struct tagTIMERINFO {
  DWORD dwSize;
  DWORD dwmsSinceStart;
  DWORD dwmsThisVM;
} TIMERINFO;

/* Notifications. */
typedef BOOL(CALLBACK *LPFNNOTIFYCALLBACK)(WORD, DWORD);
#define NF_NORMAL 0
#define NF_TASKSWITCH 1
#define NF_RIP 2
#define NFY_UNKNOWN 0
#define NFY_LOADSEG 1
#define NFY_FREESEG 2
#define NFY_STARTDLL 3
#define NFY_STARTTASK 4
#define NFY_EXITTASK 5
#define NFY_DELMODULE 6
#define NFY_RIP 7
#define NFY_TASKIN 8
#define NFY_TASKOUT 9
#define NFY_INCHAR 10
#define NFY_OUTSTR 11
#define NFY_LOGERROR 12
#define NFY_LOGPARAMERROR 13

typedef struct tagNFYLOADSEG {
  DWORD dwSize;
  WORD wSelector;
  WORD wSegNum;
  WORD wType;
  WORD wcInstance;
  LPCSTR lpstrModuleName;
} NFYLOADSEG;
typedef struct tagNFYSTARTDLL {
  DWORD dwSize;
  HMODULE hModule;
  WORD wCS;
  WORD wIP;
} NFYSTARTDLL;
typedef struct tagNFYRIP {
  DWORD dwSize;
  WORD wIP;
  WORD wCS;
  WORD wSS;
  WORD wBP;
  WORD wExitCode;
} NFYRIP;
typedef struct tagNFYLOGERROR {
  DWORD dwSize;
  UINT wErrCode;
  void FAR *lpInfo;
} NFYLOGERROR;
typedef struct tagNFYLOGPARAMERROR {
  DWORD dwSize;
  UINT wErrCode;
  FARPROC lpfnErrorAddr;
  void FAR *FAR *lpBadParam;
} NFYLOGPARAMERROR;

#define INT_DIV0 0
#define INT_1 1
#define INT_3 3
#define INT_UDINSTR 6
#define INT_STKFAULT 12
#define INT_GPFAULT 13
#define INT_BADPAGEFAULT 14
#define INT_CTLALTSYSRQ 256
#define NO_UAE_BOX 0x0001
#define UAE_BOX 0x0000

#if WINVER >= 0x030A
BOOL WINAPI TimerCount(TIMERINFO FAR *);
BOOL WINAPI SystemHeapInfo(SYSHEAPINFO FAR *);
BOOL WINAPI MemManInfo(MEMMANINFO FAR *);
BOOL WINAPI GlobalInfo(GLOBALINFO FAR *);
BOOL WINAPI GlobalFirst(GLOBALENTRY FAR *, WORD);
BOOL WINAPI GlobalNext(GLOBALENTRY FAR *, WORD);
BOOL WINAPI GlobalEntryHandle(GLOBALENTRY FAR *, HGLOBAL);
BOOL WINAPI GlobalEntryModule(GLOBALENTRY FAR *, HMODULE, WORD);
WORD WINAPI GlobalHandleToSel(HGLOBAL);
BOOL WINAPI LocalInfo(LOCALINFO FAR *, HGLOBAL);
BOOL WINAPI LocalFirst(LOCALENTRY FAR *, HGLOBAL);
BOOL WINAPI LocalNext(LOCALENTRY FAR *);
BOOL WINAPI StackTraceFirst(STACKTRACEENTRY FAR *, HTASK);
BOOL WINAPI StackTraceCSIPFirst(STACKTRACEENTRY FAR *, WORD, WORD, WORD, WORD);
BOOL WINAPI StackTraceNext(STACKTRACEENTRY FAR *);
BOOL WINAPI ModuleFirst(MODULEENTRY FAR *);
BOOL WINAPI ModuleNext(MODULEENTRY FAR *);
HMODULE WINAPI ModuleFindName(MODULEENTRY FAR *, LPCSTR);
HMODULE WINAPI ModuleFindHandle(MODULEENTRY FAR *, HMODULE);
BOOL WINAPI TaskFirst(TASKENTRY FAR *);
BOOL WINAPI TaskNext(TASKENTRY FAR *);
BOOL WINAPI TaskFindHandle(TASKENTRY FAR *, HTASK);
DWORD WINAPI TaskSetCSIP(HTASK, WORD, WORD);
DWORD WINAPI TaskGetCSIP(HTASK);
BOOL WINAPI TaskSwitch(HTASK, DWORD);
BOOL WINAPI ClassFirst(CLASSENTRY FAR *);
BOOL WINAPI ClassNext(CLASSENTRY FAR *);
BOOL WINAPI NotifyRegister(HTASK, LPFNNOTIFYCALLBACK, WORD);
BOOL WINAPI NotifyUnRegister(HTASK);
BOOL WINAPI InterruptRegister(HTASK, FARPROC);
BOOL WINAPI InterruptUnRegister(HTASK);
void WINAPI TerminateApp(HTASK, WORD);
DWORD WINAPI MemoryRead(WORD, DWORD, void FAR *, DWORD);
DWORD WINAPI MemoryWrite(WORD, DWORD, void FAR *, DWORD);
#endif

#ifdef __cplusplus
}
#endif

#pragma pack(pop)
#endif /* _TOOLHELP_H */
