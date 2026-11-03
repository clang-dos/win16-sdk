/* shellapi.h: the shell (SHELL.DLL, Windows 3.1): the registration
 * database, drag and drop, and running programs by their documents.
 * Written for clang-dos from the published API; BSD 3-Clause, see the
 * win16-sdk LICENSE. */
#ifndef _SHELLAPI_H
#define _SHELLAPI_H
#define _INC_SHELLAPI

#include <windows.h>
#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

/* The registration database. Its keys are 32 bits. */
typedef DWORD HKEY;
typedef HKEY FAR *PHKEY;
#define HKEY_CLASSES_ROOT ((HKEY)1)
#define REG_SZ 1
#define ERROR_SUCCESS 0L
#define ERROR_BADDB 1L
#define ERROR_BADKEY 2L
#define ERROR_CANTOPEN 3L
#define ERROR_CANTREAD 4L
#define ERROR_CANTWRITE 5L
#define ERROR_OUTOFMEMORY 6L
#define ERROR_INVALID_PARAMETER 7L
#define ERROR_ACCESS_DENIED 8L

DECLARE_HANDLE(HDROP);

/* ShellExecute and FindExecutable errors (results up to 32). */
#define SE_ERR_FNF 2
#define SE_ERR_PNF 3
#define SE_ERR_OOM 8
#define SE_ERR_SHARE 26
#define SE_ERR_ASSOCINCOMPLETE 27
#define SE_ERR_DDETIMEOUT 28
#define SE_ERR_DDEFAIL 29
#define SE_ERR_DDEBUSY 30
#define SE_ERR_NOASSOC 31

#if WINVER >= 0x030A
LONG WINAPI RegOpenKey(HKEY, LPCSTR, HKEY FAR *);
LONG WINAPI RegCreateKey(HKEY, LPCSTR, HKEY FAR *);
LONG WINAPI RegCloseKey(HKEY);
LONG WINAPI RegDeleteKey(HKEY, LPCSTR);
LONG WINAPI RegSetValue(HKEY, LPCSTR, DWORD, LPCSTR, DWORD);
LONG WINAPI RegQueryValue(HKEY, LPCSTR, LPSTR, LONG FAR *);
LONG WINAPI RegEnumKey(HKEY, DWORD, LPSTR, DWORD);

void WINAPI DragAcceptFiles(HWND, BOOL);
UINT WINAPI DragQueryFile(HDROP, UINT, LPSTR, UINT);
BOOL WINAPI DragQueryPoint(HDROP, POINT FAR *);
void WINAPI DragFinish(HDROP);

HINSTANCE WINAPI ShellExecute(HWND, LPCSTR, LPCSTR, LPCSTR, LPCSTR, int);
HINSTANCE WINAPI FindExecutable(LPCSTR, LPCSTR, LPSTR);
int WINAPI ShellAbout(HWND, LPCSTR, LPCSTR, HICON);
HICON WINAPI ExtractIcon(HINSTANCE, LPCSTR, UINT);
HICON WINAPI ExtractAssociatedIcon(HINSTANCE, LPSTR, UINT FAR *);
DWORD WINAPI DoEnvironmentSubst(LPSTR, UINT);
#endif

#ifdef __cplusplus
}
#endif

#pragma pack(pop)
#endif /* _SHELLAPI_H */
