/* windowsx.h: macro APIs, message crackers and control messages for
 * Windows 3.1 (all macros; it needs no DLL). Written for clang-dos from the
 * published API; BSD 3-Clause, see the win16-sdk LICENSE.
 *
 * A message cracker splits a message's wParam and lParam into the
 * arguments of a handler function, and a forwarder packs them again:
 *
 *   void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
 *   ...
 *   switch (msg) {
 *     HANDLE_MSG(hwnd, WM_COMMAND, Cls_OnCommand);
 *   }
 *
 * Each HANDLE_WM_xxx macro below is preceded by the prototype of its
 * handler. */
#ifndef _WINDOWSX_H
#define _WINDOWSX_H
#define _INC_WINDOWSX

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 * KERNEL
 ****************************************************************************/
#define GetInstanceModule(hInstance)                                           \
  GetModuleHandle((LPCSTR)MAKELP(0, (hInstance)))

#define GlobalPtrHandle(lp) ((HGLOBAL)LOWORD(GlobalHandle(SELECTOROF(lp))))
#define GlobalLockPtr(lp) ((BOOL)SELECTOROF(GlobalLock(GlobalPtrHandle(lp))))
#define GlobalUnlockPtr(lp) GlobalUnlock(GlobalPtrHandle(lp))
#define GlobalAllocPtr(flags, cb) (GlobalLock(GlobalAlloc((flags), (cb))))
#define GlobalReAllocPtr(lp, cbNew, flags)                                     \
  (GlobalUnlockPtr(lp),                                                        \
   GlobalLock(GlobalReAlloc(GlobalPtrHandle(lp), (cbNew), (flags))))
#define GlobalFreePtr(lp)                                                      \
  (GlobalUnlockPtr(lp), (BOOL)GlobalFree(GlobalPtrHandle(lp)))

/****************************************************************************
 * GDI
 ****************************************************************************/
#define DeletePen(hpen) DeleteObject((HGDIOBJ)(HPEN)(hpen))
#define SelectPen(hdc, hpen)                                                   \
  ((HPEN)SelectObject((hdc), (HGDIOBJ)(HPEN)(hpen)))
#define GetStockPen(i) ((HPEN)GetStockObject(i))

#define DeleteBrush(hbr) DeleteObject((HGDIOBJ)(HBRUSH)(hbr))
#define SelectBrush(hdc, hbr)                                                  \
  ((HBRUSH)SelectObject((hdc), (HGDIOBJ)(HBRUSH)(hbr)))
#define GetStockBrush(i) ((HBRUSH)GetStockObject(i))

#define DeleteRgn(hrgn) DeleteObject((HGDIOBJ)(HRGN)(hrgn))
#define CopyRgn(hrgnDst, hrgnSrc) CombineRgn(hrgnDst, hrgnSrc, 0, RGN_COPY)
#define IntersectRgn(hrgnResult, hrgnA, hrgnB)                                 \
  CombineRgn(hrgnResult, hrgnA, hrgnB, RGN_AND)
#define SubtractRgn(hrgnResult, hrgnA, hrgnB)                                  \
  CombineRgn(hrgnResult, hrgnA, hrgnB, RGN_DIFF)
#define UnionRgn(hrgnResult, hrgnA, hrgnB)                                     \
  CombineRgn(hrgnResult, hrgnA, hrgnB, RGN_OR)
#define XorRgn(hrgnResult, hrgnA, hrgnB)                                       \
  CombineRgn(hrgnResult, hrgnA, hrgnB, RGN_XOR)

#define DeletePalette(hpal) DeleteObject((HGDIOBJ)(HPALETTE)(hpal))

#define DeleteFont(hfont) DeleteObject((HGDIOBJ)(HFONT)(hfont))
#define SelectFont(hdc, hfont)                                                 \
  ((HFONT)SelectObject((hdc), (HGDIOBJ)(HFONT)(hfont)))
#define GetStockFont(i) ((HFONT)GetStockObject(i))

#define DeleteBitmap(hbm) DeleteObject((HGDIOBJ)(HBITMAP)(hbm))
#define SelectBitmap(hdc, hbm)                                                 \
  ((HBITMAP)SelectObject((hdc), (HGDIOBJ)(HBITMAP)(hbm)))

#define InsetRect(lprc, dx, dy) InflateRect((lprc), -(dx), -(dy))

/****************************************************************************
 * USER
 ****************************************************************************/
#define GetWindowInstance(hwnd)                                                \
  ((HINSTANCE)GetWindowWord((hwnd), GWW_HINSTANCE))
#define GetWindowStyle(hwnd) ((DWORD)GetWindowLong((hwnd), GWL_STYLE))
#define GetWindowExStyle(hwnd) ((DWORD)GetWindowLong((hwnd), GWL_EXSTYLE))
#define GetWindowOwner(hwnd) GetWindow((hwnd), GW_OWNER)
#define GetFirstChild(hwnd) GetTopWindow(hwnd)
#define GetFirstSibling(hwnd) GetWindow((hwnd), GW_HWNDFIRST)
#define GetLastSibling(hwnd) GetWindow((hwnd), GW_HWNDLAST)
#define GetNextSibling(hwnd) GetWindow((hwnd), GW_HWNDNEXT)
#define GetPrevSibling(hwnd) GetWindow((hwnd), GW_HWNDPREV)
#define GetWindowID(hwnd) GetDlgCtrlID(hwnd)

#define SetWindowRedraw(hwnd, fRedraw)                                         \
  ((void)SendMessage((hwnd), WM_SETREDRAW, (WPARAM)(BOOL)(fRedraw), 0L))
#define SubclassWindow(hwnd, lpfn)                                             \
  ((WNDPROC)SetWindowLong((hwnd), GWL_WNDPROC, (LPARAM)(WNDPROC)(lpfn)))

#define IsMinimized(hwnd) IsIconic(hwnd)
#define IsMaximized(hwnd) IsZoomed(hwnd)
#define IsRestored(hwnd)                                                       \
  ((GetWindowStyle(hwnd) & (WS_MINIMIZE | WS_MAXIMIZE)) == 0L)

#define SetWindowFont(hwnd, hfont, fRedraw)                                    \
  FORWARD_WM_SETFONT((hwnd), (hfont), (fRedraw), SendMessage)
#define GetWindowFont(hwnd) FORWARD_WM_GETFONT((hwnd), SendMessage)

#if WINVER >= 0x030A
#define MapWindowRect(hwndFrom, hwndTo, lprc)                                  \
  MapWindowPoints((hwndFrom), (hwndTo), (POINT FAR *)(lprc), 2)
#endif

#define IsLButtonDown() (GetKeyState(VK_LBUTTON) < 0)
#define IsRButtonDown() (GetKeyState(VK_RBUTTON) < 0)
#define IsMButtonDown() (GetKeyState(VK_MBUTTON) < 0)

#define SubclassDialog(hwndDlg, lpfn)                                          \
  ((DLGPROC)SetWindowLong(hwndDlg, DWL_DLGPROC, (LPARAM)(DLGPROC)(lpfn)))

/* A dialog procedure returns most results through DWL_MSGRESULT, but a
 * few messages take the procedure's own return value. */
#define SetDlgMsgResult(hwnd, msg, result)                                     \
  (((msg) == WM_CTLCOLOR || (msg) == WM_COMPAREITEM ||                         \
    (msg) == WM_VKEYTOITEM || (msg) == WM_CHARTOITEM ||                        \
    (msg) == WM_QUERYDRAGICON || (msg) == WM_INITDIALOG)                       \
       ? (BOOL)(result)                                                        \
       : (SetWindowLong((hwnd), DWL_MSGRESULT, (LPARAM)(LRESULT)(result)),     \
          TRUE))

/* For a dialog class whose window procedure uses message crackers. */
#define DefDlgProcEx(hwnd, msg, wParam, lParam, pfRecursion)                   \
  (*(pfRecursion) = TRUE, DefDlgProc(hwnd, msg, wParam, lParam))
#define CheckDefDlgRecursion(pfRecursion)                                      \
  if (*(pfRecursion)) {                                                        \
    *(pfRecursion) = FALSE;                                                    \
    return FALSE;                                                              \
  }

/****************************************************************************
 * Message crackers
 ****************************************************************************/
#define HANDLE_MSG(hwnd, message, fn)                                          \
  case (message):                                                              \
    return HANDLE_##message((hwnd), (wParam), (lParam), (fn))

/* void Cls_OnCompacting(HWND hwnd, UINT compactRatio) */
#define HANDLE_WM_COMPACTING(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam)), 0L)
#define FORWARD_WM_COMPACTING(hwnd, compactRatio, fn) \
  (void)(fn)((hwnd), WM_COMPACTING, (WPARAM)(UINT)(compactRatio), 0L)

/* void Cls_OnWinIniChange(HWND hwnd, LPCSTR lpszSectionName) */
#define HANDLE_WM_WININICHANGE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (LPCSTR)(lParam)), 0L)
#define FORWARD_WM_WININICHANGE(hwnd, lpszSectionName, fn) \
  (void)(fn)((hwnd), WM_WININICHANGE, 0, (LPARAM)(LPCSTR)(lpszSectionName))

/* void Cls_OnSysColorChange(HWND hwnd) */
#define HANDLE_WM_SYSCOLORCHANGE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_SYSCOLORCHANGE(hwnd, fn) \
  (void)(fn)((hwnd), WM_SYSCOLORCHANGE, 0, 0L)

/* BOOL Cls_OnQueryNewPalette(HWND hwnd) */
#define HANDLE_WM_QUERYNEWPALETTE(hwnd, wParam, lParam, fn) \
  MAKELRESULT((BOOL)(fn)((hwnd)), 0L)
#define FORWARD_WM_QUERYNEWPALETTE(hwnd, fn) \
  (BOOL)(DWORD)(fn)((hwnd), WM_QUERYNEWPALETTE, 0, 0L)

/* void Cls_OnPaletteIsChanging(HWND hwnd, HWND hwndPaletteChange) */
#define HANDLE_WM_PALETTEISCHANGING(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HWND)(wParam)), 0L)
#define FORWARD_WM_PALETTEISCHANGING(hwnd, hwndPaletteChange, fn) \
  (void)(fn)((hwnd), WM_PALETTEISCHANGING, (WPARAM)(HWND)(hwndPaletteChange), 0L)

/* void Cls_OnPaletteChanged(HWND hwnd, HWND hwndPaletteChange) */
#define HANDLE_WM_PALETTECHANGED(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HWND)(wParam)), 0L)
#define FORWARD_WM_PALETTECHANGED(hwnd, hwndPaletteChange, fn) \
  (void)(fn)((hwnd), WM_PALETTECHANGED, (WPARAM)(HWND)(hwndPaletteChange), 0L)

/* void Cls_OnFontChange(HWND hwnd) */
#define HANDLE_WM_FONTCHANGE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_FONTCHANGE(hwnd, fn) \
  (void)(fn)((hwnd), WM_FONTCHANGE, 0, 0L)

/* void Cls_OnSpoolerStatus(HWND hwnd, UINT status, int cJobInQueue) */
#define HANDLE_WM_SPOOLERSTATUS(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam), (int)LOWORD(lParam)), 0L)
#define FORWARD_WM_SPOOLERSTATUS(hwnd, status, cJobInQueue, fn) \
  (void)(fn)((hwnd), WM_SPOOLERSTATUS, (WPARAM)(status), MAKELPARAM((cJobInQueue), 0))

/* void Cls_OnDevModeChange(HWND hwnd, LPCSTR lpszDeviceName) */
#define HANDLE_WM_DEVMODECHANGE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (LPCSTR)(lParam)), 0L)
#define FORWARD_WM_DEVMODECHANGE(hwnd, lpszDeviceName, fn) \
  (void)(fn)((hwnd), WM_DEVMODECHANGE, 0, (LPARAM)(LPCSTR)(lpszDeviceName))

/* void Cls_OnTimeChange(HWND hwnd) */
#define HANDLE_WM_TIMECHANGE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_TIMECHANGE(hwnd, fn) \
  (void)(fn)((hwnd), WM_TIMECHANGE, 0, 0L)

/* void Cls_OnPower(HWND hwnd, int code) */
#define HANDLE_WM_POWER(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (int)(wParam)), 0L)
#define FORWARD_WM_POWER(hwnd, code, fn) \
  (void)(fn)((hwnd), WM_POWER, (WPARAM)(int)(code), 0L)

/* BOOL Cls_OnQueryEndSession(HWND hwnd) */
#define HANDLE_WM_QUERYENDSESSION(hwnd, wParam, lParam, fn) \
  MAKELRESULT((BOOL)(fn)((hwnd)), 0L)
#define FORWARD_WM_QUERYENDSESSION(hwnd, fn) \
  (BOOL)(DWORD)(fn)((hwnd), WM_QUERYENDSESSION, 0, 0L)

/* void Cls_OnEndSession(HWND hwnd, BOOL fEnding) */
#define HANDLE_WM_ENDSESSION(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (BOOL)(wParam)), 0L)
#define FORWARD_WM_ENDSESSION(hwnd, fEnding, fn) \
  (void)(fn)((hwnd), WM_ENDSESSION, (WPARAM)(BOOL)(fEnding), 0L)

/* void Cls_OnQuit(HWND hwnd, int exitCode) */
#define HANDLE_WM_QUIT(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (int)(wParam)), 0L)
#define FORWARD_WM_QUIT(hwnd, exitCode, fn) \
  (void)(fn)((hwnd), WM_QUIT, (WPARAM)(exitCode), 0L)

/* void Cls_OnSystemError(HWND hwnd, int errCode) */
#define HANDLE_WM_SYSTEMERROR(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (int)(wParam)), 0L)
#define FORWARD_WM_SYSTEMERROR(hwnd, errCode, fn) \
  (void)(fn)((hwnd), WM_SYSTEMERROR, (WPARAM)(errCode), 0L)

/* BOOL Cls_OnCreate(HWND hwnd, CREATESTRUCT FAR *lpCreateStruct) */
#define HANDLE_WM_CREATE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (CREATESTRUCT FAR *)(lParam)) ? 0L : (LRESULT)-1L)
#define FORWARD_WM_CREATE(hwnd, lpCreateStruct, fn) \
  (BOOL)(DWORD)(fn)((hwnd), WM_CREATE, 0, (LPARAM)(CREATESTRUCT FAR *)(lpCreateStruct))

/* BOOL Cls_OnNCCreate(HWND hwnd, CREATESTRUCT FAR *lpCreateStruct) */
#define HANDLE_WM_NCCREATE(hwnd, wParam, lParam, fn) \
  MAKELRESULT((BOOL)(fn)((hwnd), (CREATESTRUCT FAR *)(lParam)), 0L)
#define FORWARD_WM_NCCREATE(hwnd, lpCreateStruct, fn) \
  (BOOL)(DWORD)(fn)((hwnd), WM_NCCREATE, 0, (LPARAM)(CREATESTRUCT FAR *)(lpCreateStruct))

/* void Cls_OnDestroy(HWND hwnd) */
#define HANDLE_WM_DESTROY(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_DESTROY(hwnd, fn) \
  (void)(fn)((hwnd), WM_DESTROY, 0, 0L)

/* void Cls_OnNCDestroy(HWND hwnd) */
#define HANDLE_WM_NCDESTROY(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_NCDESTROY(hwnd, fn) \
  (void)(fn)((hwnd), WM_NCDESTROY, 0, 0L)

/* void Cls_OnShowWindow(HWND hwnd, BOOL fShow, UINT status) */
#define HANDLE_WM_SHOWWINDOW(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (BOOL)(wParam), (UINT)LOWORD(lParam)), 0L)
#define FORWARD_WM_SHOWWINDOW(hwnd, fShow, status, fn) \
  (void)(fn)((hwnd), WM_SHOWWINDOW, (WPARAM)(BOOL)(fShow), MAKELPARAM((status), 0))

/* void Cls_OnSetRedraw(HWND hwnd, BOOL fRedraw) */
#define HANDLE_WM_SETREDRAW(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (BOOL)(wParam)), 0L)
#define FORWARD_WM_SETREDRAW(hwnd, fRedraw, fn) \
  (void)(fn)((hwnd), WM_SETREDRAW, (WPARAM)(fRedraw), 0L)

/* void Cls_OnEnable(HWND hwnd, BOOL fEnable) */
#define HANDLE_WM_ENABLE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (BOOL)(wParam)), 0L)
#define FORWARD_WM_ENABLE(hwnd, fEnable, fn) \
  (void)(fn)((hwnd), WM_ENABLE, (WPARAM)(BOOL)(fEnable), 0L)

/* void Cls_OnSetText(HWND hwnd, LPCSTR lpszText) */
#define HANDLE_WM_SETTEXT(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (LPCSTR)(lParam)), 0L)
#define FORWARD_WM_SETTEXT(hwnd, lpszText, fn) \
  (void)(fn)((hwnd), WM_SETTEXT, 0, (LPARAM)(LPCSTR)(lpszText))

/* int Cls_OnGetText(HWND hwnd, int cchTextMax, LPSTR lpszText) */
#define HANDLE_WM_GETTEXT(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(int)(fn)((hwnd), (int)(wParam), (LPSTR)(lParam))
#define FORWARD_WM_GETTEXT(hwnd, cchTextMax, lpszText, fn) \
  (int)(DWORD)(fn)((hwnd), WM_GETTEXT, (WPARAM)(int)(cchTextMax), (LPARAM)(LPSTR)(lpszText))

/* int Cls_OnGetTextLength(HWND hwnd) */
#define HANDLE_WM_GETTEXTLENGTH(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(int)(fn)((hwnd))
#define FORWARD_WM_GETTEXTLENGTH(hwnd, fn) \
  (int)(DWORD)(fn)((hwnd), WM_GETTEXTLENGTH, 0, 0L)

/* BOOL Cls_OnWindowPosChanging(HWND hwnd, WINDOWPOS FAR *lpwpos) */
#define HANDLE_WM_WINDOWPOSCHANGING(hwnd, wParam, lParam, fn) \
  MAKELRESULT((BOOL)(fn)((hwnd), (WINDOWPOS FAR *)(lParam)), 0L)
#define FORWARD_WM_WINDOWPOSCHANGING(hwnd, lpwpos, fn) \
  (BOOL)(DWORD)(fn)((hwnd), WM_WINDOWPOSCHANGING, 0, (LPARAM)(WINDOWPOS FAR *)(lpwpos))

/* void Cls_OnWindowPosChanged(HWND hwnd, const WINDOWPOS FAR *lpwpos) */
#define HANDLE_WM_WINDOWPOSCHANGED(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (const WINDOWPOS FAR *)(lParam)), 0L)
#define FORWARD_WM_WINDOWPOSCHANGED(hwnd, lpwpos, fn) \
  (void)(fn)((hwnd), WM_WINDOWPOSCHANGED, 0, (LPARAM)(const WINDOWPOS FAR *)(lpwpos))

/* void Cls_OnMove(HWND hwnd, int x, int y) */
#define HANDLE_WM_MOVE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam)), 0L)
#define FORWARD_WM_MOVE(hwnd, x, y, fn) \
  (void)(fn)((hwnd), WM_MOVE, 0, MAKELPARAM((x), (y)))

/* void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy) */
#define HANDLE_WM_SIZE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam)), 0L)
#define FORWARD_WM_SIZE(hwnd, state, cx, cy, fn) \
  (void)(fn)((hwnd), WM_SIZE, (WPARAM)(UINT)(state), MAKELPARAM((cx), (cy)))

/* void Cls_OnClose(HWND hwnd) */
#define HANDLE_WM_CLOSE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_CLOSE(hwnd, fn) \
  (void)(fn)((hwnd), WM_CLOSE, 0, 0L)

/* BOOL Cls_OnQueryOpen(HWND hwnd) */
#define HANDLE_WM_QUERYOPEN(hwnd, wParam, lParam, fn) \
  MAKELRESULT((BOOL)(fn)((hwnd)), 0L)
#define FORWARD_WM_QUERYOPEN(hwnd, fn) \
  (BOOL)(DWORD)(fn)((hwnd), WM_QUERYOPEN, 0, 0L)

/* void Cls_OnGetMinMaxInfo(HWND hwnd, MINMAXINFO FAR *lpMinMaxInfo) */
#define HANDLE_WM_GETMINMAXINFO(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (MINMAXINFO FAR *)(lParam)), 0L)
#define FORWARD_WM_GETMINMAXINFO(hwnd, lpMinMaxInfo, fn) \
  (void)(fn)((hwnd), WM_GETMINMAXINFO, 0, (LPARAM)(MINMAXINFO FAR *)(lpMinMaxInfo))

/* void Cls_OnPaint(HWND hwnd) */
#define HANDLE_WM_PAINT(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_PAINT(hwnd, fn) \
  (void)(fn)((hwnd), WM_PAINT, 0, 0L)

/* BOOL Cls_OnEraseBkgnd(HWND hwnd, HDC hdc) */
#define HANDLE_WM_ERASEBKGND(hwnd, wParam, lParam, fn) \
  MAKELRESULT((BOOL)(fn)((hwnd), (HDC)(wParam)), 0L)
#define FORWARD_WM_ERASEBKGND(hwnd, hdc, fn) \
  (BOOL)(DWORD)(fn)((hwnd), WM_ERASEBKGND, (WPARAM)(HDC)(hdc), 0L)

/* BOOL Cls_OnIconEraseBkgnd(HWND hwnd, HDC hdc) */
#define HANDLE_WM_ICONERASEBKGND(hwnd, wParam, lParam, fn) \
  MAKELRESULT((BOOL)(fn)((hwnd), (HDC)(wParam)), 0L)
#define FORWARD_WM_ICONERASEBKGND(hwnd, hdc, fn) \
  (BOOL)(DWORD)(fn)((hwnd), WM_ICONERASEBKGND, (WPARAM)(HDC)(hdc), 0L)

/* void Cls_OnNCPaint(HWND hwnd, HRGN hrgn) */
#define HANDLE_WM_NCPAINT(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HRGN)(wParam)), 0L)
#define FORWARD_WM_NCPAINT(hwnd, hrgn, fn) \
  (void)(fn)((hwnd), WM_NCPAINT, (WPARAM)(HRGN)(hrgn), 0L)

/* UINT Cls_OnNCCalcSize(HWND hwnd, BOOL fCalcValidRects, NCCALCSIZE_PARAMS FAR *lpcsp) */
#define HANDLE_WM_NCCALCSIZE(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(UINT)(fn)((hwnd), (BOOL)(wParam), (NCCALCSIZE_PARAMS FAR *)(lParam))
#define FORWARD_WM_NCCALCSIZE(hwnd, fCalcValidRects, lpcsp, fn) \
  (UINT)(DWORD)(fn)((hwnd), WM_NCCALCSIZE, (WPARAM)(fCalcValidRects), (LPARAM)(NCCALCSIZE_PARAMS FAR *)(lpcsp))

/* UINT Cls_OnNCHitTest(HWND hwnd, int x, int y) */
#define HANDLE_WM_NCHITTEST(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(UINT)(fn)((hwnd), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam))
#define FORWARD_WM_NCHITTEST(hwnd, x, y, fn) \
  (UINT)(DWORD)(fn)((hwnd), WM_NCHITTEST, 0, MAKELPARAM((x), (y)))

/* HICON Cls_OnQueryDragIcon(HWND hwnd) */
#define HANDLE_WM_QUERYDRAGICON(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(UINT)(HICON)(fn)((hwnd))
#define FORWARD_WM_QUERYDRAGICON(hwnd, fn) \
  (HICON)(UINT)(DWORD)(fn)((hwnd), WM_QUERYDRAGICON, 0, 0L)

/* void Cls_OnActivate(HWND hwnd, UINT state, HWND hwndActDeact, BOOL fMinimized) */
#define HANDLE_WM_ACTIVATE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam), (HWND)LOWORD(lParam), (BOOL)HIWORD(lParam)), 0L)
#define FORWARD_WM_ACTIVATE(hwnd, state, hwndActDeact, fMinimized, fn) \
  (void)(fn)((hwnd), WM_ACTIVATE, (WPARAM)(UINT)(state), MAKELPARAM((UINT)(HWND)(hwndActDeact), (BOOL)(fMinimized)))

/* void Cls_OnActivateApp(HWND hwnd, BOOL fActivate, HTASK htaskActDeact) */
#define HANDLE_WM_ACTIVATEAPP(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (BOOL)(wParam), (HTASK)LOWORD(lParam)), 0L)
#define FORWARD_WM_ACTIVATEAPP(hwnd, fActivate, htaskActDeact, fn) \
  (void)(fn)((hwnd), WM_ACTIVATEAPP, (WPARAM)(BOOL)(fActivate), MAKELPARAM((UINT)(HTASK)(htaskActDeact), 0))

/* BOOL Cls_OnNCActivate(HWND hwnd, BOOL fActive, HWND hwndActDeact, BOOL fMinimized) */
#define HANDLE_WM_NCACTIVATE(hwnd, wParam, lParam, fn) \
  MAKELRESULT((BOOL)(fn)((hwnd), (BOOL)(wParam), (HWND)LOWORD(lParam), (BOOL)HIWORD(lParam)), 0L)
#define FORWARD_WM_NCACTIVATE(hwnd, fActive, hwndActDeact, fMinimized, fn) \
  (BOOL)(DWORD)(fn)((hwnd), WM_NCACTIVATE, (WPARAM)(BOOL)(fActive), MAKELPARAM((UINT)(HWND)(hwndActDeact), (BOOL)(fMinimized)))

/* void Cls_OnSetFocus(HWND hwnd, HWND hwndOldFocus) */
#define HANDLE_WM_SETFOCUS(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HWND)(wParam)), 0L)
#define FORWARD_WM_SETFOCUS(hwnd, hwndOldFocus, fn) \
  (void)(fn)((hwnd), WM_SETFOCUS, (WPARAM)(HWND)(hwndOldFocus), 0L)

/* void Cls_OnKillFocus(HWND hwnd, HWND hwndNewFocus) */
#define HANDLE_WM_KILLFOCUS(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HWND)(wParam)), 0L)
#define FORWARD_WM_KILLFOCUS(hwnd, hwndNewFocus, fn) \
  (void)(fn)((hwnd), WM_KILLFOCUS, (WPARAM)(HWND)(hwndNewFocus), 0L)

/* void Cls_OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags) */
#define HANDLE_WM_KEYDOWN(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam), TRUE, (int)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L)
#define FORWARD_WM_KEYDOWN(hwnd, vk, cRepeat, flags, fn) \
  (void)(fn)((hwnd), WM_KEYDOWN, (WPARAM)(UINT)(vk), MAKELPARAM((cRepeat), (flags)))

/* void Cls_OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags) */
#define HANDLE_WM_KEYUP(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam), FALSE, (int)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L)
#define FORWARD_WM_KEYUP(hwnd, vk, cRepeat, flags, fn) \
  (void)(fn)((hwnd), WM_KEYUP, (WPARAM)(UINT)(vk), MAKELPARAM((cRepeat), (flags)))

/* void Cls_OnSysKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags) */
#define HANDLE_WM_SYSKEYDOWN(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam), TRUE, (int)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L)
#define FORWARD_WM_SYSKEYDOWN(hwnd, vk, cRepeat, flags, fn) \
  (void)(fn)((hwnd), WM_SYSKEYDOWN, (WPARAM)(UINT)(vk), MAKELPARAM((cRepeat), (flags)))

/* void Cls_OnSysKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags) */
#define HANDLE_WM_SYSKEYUP(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam), FALSE, (int)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L)
#define FORWARD_WM_SYSKEYUP(hwnd, vk, cRepeat, flags, fn) \
  (void)(fn)((hwnd), WM_SYSKEYUP, (WPARAM)(UINT)(vk), MAKELPARAM((cRepeat), (flags)))

/* void Cls_OnChar(HWND hwnd, UINT ch, int cRepeat) */
#define HANDLE_WM_CHAR(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam), (int)LOWORD(lParam)), 0L)
#define FORWARD_WM_CHAR(hwnd, ch, cRepeat, fn) \
  (void)(fn)((hwnd), WM_CHAR, (WPARAM)(UINT)(ch), MAKELPARAM((cRepeat), 0))

/* void Cls_OnDeadChar(HWND hwnd, UINT ch, int cRepeat) */
#define HANDLE_WM_DEADCHAR(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam), (int)LOWORD(lParam)), 0L)
#define FORWARD_WM_DEADCHAR(hwnd, ch, cRepeat, fn) \
  (void)(fn)((hwnd), WM_DEADCHAR, (WPARAM)(UINT)(ch), MAKELPARAM((cRepeat), 0))

/* void Cls_OnSysChar(HWND hwnd, UINT ch, int cRepeat) */
#define HANDLE_WM_SYSCHAR(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam), (int)LOWORD(lParam)), 0L)
#define FORWARD_WM_SYSCHAR(hwnd, ch, cRepeat, fn) \
  (void)(fn)((hwnd), WM_SYSCHAR, (WPARAM)(UINT)(ch), MAKELPARAM((cRepeat), 0))

/* void Cls_OnSysDeadChar(HWND hwnd, UINT ch, int cRepeat) */
#define HANDLE_WM_SYSDEADCHAR(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam), (int)LOWORD(lParam)), 0L)
#define FORWARD_WM_SYSDEADCHAR(hwnd, ch, cRepeat, fn) \
  (void)(fn)((hwnd), WM_SYSDEADCHAR, (WPARAM)(UINT)(ch), MAKELPARAM((cRepeat), 0))

/* void Cls_OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags) */
#define HANDLE_WM_MOUSEMOVE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_MOUSEMOVE(hwnd, x, y, keyFlags, fn) \
  (void)(fn)((hwnd), WM_MOUSEMOVE, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls_OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define HANDLE_WM_LBUTTONDOWN(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_LBUTTONDOWN(hwnd, fDoubleClick, x, y, keyFlags, fn) \
  (void)(fn)((hwnd), (fDoubleClick) ? WM_LBUTTONDBLCLK : WM_LBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls_OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define HANDLE_WM_LBUTTONDBLCLK(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_LBUTTONDBLCLK(hwnd, fDoubleClick, x, y, keyFlags, fn) \
  (void)(fn)((hwnd), (fDoubleClick) ? WM_LBUTTONDBLCLK : WM_LBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls_OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags) */
#define HANDLE_WM_LBUTTONUP(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_LBUTTONUP(hwnd, x, y, keyFlags, fn) \
  (void)(fn)((hwnd), WM_LBUTTONUP, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls_OnRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define HANDLE_WM_RBUTTONDOWN(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_RBUTTONDOWN(hwnd, fDoubleClick, x, y, keyFlags, fn) \
  (void)(fn)((hwnd), (fDoubleClick) ? WM_RBUTTONDBLCLK : WM_RBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls_OnRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define HANDLE_WM_RBUTTONDBLCLK(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_RBUTTONDBLCLK(hwnd, fDoubleClick, x, y, keyFlags, fn) \
  (void)(fn)((hwnd), (fDoubleClick) ? WM_RBUTTONDBLCLK : WM_RBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls_OnRButtonUp(HWND hwnd, int x, int y, UINT keyFlags) */
#define HANDLE_WM_RBUTTONUP(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_RBUTTONUP(hwnd, x, y, keyFlags, fn) \
  (void)(fn)((hwnd), WM_RBUTTONUP, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls_OnMButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define HANDLE_WM_MBUTTONDOWN(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_MBUTTONDOWN(hwnd, fDoubleClick, x, y, keyFlags, fn) \
  (void)(fn)((hwnd), (fDoubleClick) ? WM_MBUTTONDBLCLK : WM_MBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls_OnMButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define HANDLE_WM_MBUTTONDBLCLK(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_MBUTTONDBLCLK(hwnd, fDoubleClick, x, y, keyFlags, fn) \
  (void)(fn)((hwnd), (fDoubleClick) ? WM_MBUTTONDBLCLK : WM_MBUTTONDOWN, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls_OnMButtonUp(HWND hwnd, int x, int y, UINT keyFlags) */
#define HANDLE_WM_MBUTTONUP(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_MBUTTONUP(hwnd, x, y, keyFlags, fn) \
  (void)(fn)((hwnd), WM_MBUTTONUP, (WPARAM)(UINT)(keyFlags), MAKELPARAM((x), (y)))

/* void Cls_OnNCMouseMove(HWND hwnd, int x, int y, UINT codeHitTest) */
#define HANDLE_WM_NCMOUSEMOVE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_NCMOUSEMOVE(hwnd, x, y, codeHitTest, fn) \
  (void)(fn)((hwnd), WM_NCMOUSEMOVE, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)))

/* void Cls_OnNCLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest) */
#define HANDLE_WM_NCLBUTTONDOWN(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_NCLBUTTONDOWN(hwnd, fDoubleClick, x, y, codeHitTest, fn) \
  (void)(fn)((hwnd), (fDoubleClick) ? WM_NCLBUTTONDBLCLK : WM_NCLBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)))

/* void Cls_OnNCLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest) */
#define HANDLE_WM_NCLBUTTONDBLCLK(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_NCLBUTTONDBLCLK(hwnd, fDoubleClick, x, y, codeHitTest, fn) \
  (void)(fn)((hwnd), (fDoubleClick) ? WM_NCLBUTTONDBLCLK : WM_NCLBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)))

/* void Cls_OnNCLButtonUp(HWND hwnd, int x, int y, UINT codeHitTest) */
#define HANDLE_WM_NCLBUTTONUP(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_NCLBUTTONUP(hwnd, x, y, codeHitTest, fn) \
  (void)(fn)((hwnd), WM_NCLBUTTONUP, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)))

/* void Cls_OnNCRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest) */
#define HANDLE_WM_NCRBUTTONDOWN(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_NCRBUTTONDOWN(hwnd, fDoubleClick, x, y, codeHitTest, fn) \
  (void)(fn)((hwnd), (fDoubleClick) ? WM_NCRBUTTONDBLCLK : WM_NCRBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)))

/* void Cls_OnNCRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest) */
#define HANDLE_WM_NCRBUTTONDBLCLK(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_NCRBUTTONDBLCLK(hwnd, fDoubleClick, x, y, codeHitTest, fn) \
  (void)(fn)((hwnd), (fDoubleClick) ? WM_NCRBUTTONDBLCLK : WM_NCRBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)))

/* void Cls_OnNCRButtonUp(HWND hwnd, int x, int y, UINT codeHitTest) */
#define HANDLE_WM_NCRBUTTONUP(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_NCRBUTTONUP(hwnd, x, y, codeHitTest, fn) \
  (void)(fn)((hwnd), WM_NCRBUTTONUP, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)))

/* void Cls_OnNCMButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest) */
#define HANDLE_WM_NCMBUTTONDOWN(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_NCMBUTTONDOWN(hwnd, fDoubleClick, x, y, codeHitTest, fn) \
  (void)(fn)((hwnd), (fDoubleClick) ? WM_NCMBUTTONDBLCLK : WM_NCMBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)))

/* void Cls_OnNCMButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest) */
#define HANDLE_WM_NCMBUTTONDBLCLK(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_NCMBUTTONDBLCLK(hwnd, fDoubleClick, x, y, codeHitTest, fn) \
  (void)(fn)((hwnd), (fDoubleClick) ? WM_NCMBUTTONDBLCLK : WM_NCMBUTTONDOWN, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)))

/* void Cls_OnNCMButtonUp(HWND hwnd, int x, int y, UINT codeHitTest) */
#define HANDLE_WM_NCMBUTTONUP(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)
#define FORWARD_WM_NCMBUTTONUP(hwnd, x, y, codeHitTest, fn) \
  (void)(fn)((hwnd), WM_NCMBUTTONUP, (WPARAM)(UINT)(codeHitTest), MAKELPARAM((x), (y)))

/* int Cls_OnMouseActivate(HWND hwnd, HWND hwndTopLevel, UINT codeHitTest, UINT msg) */
#define HANDLE_WM_MOUSEACTIVATE(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(int)(fn)((hwnd), (HWND)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam))
#define FORWARD_WM_MOUSEACTIVATE(hwnd, hwndTopLevel, codeHitTest, msg, fn) \
  (int)(DWORD)(fn)((hwnd), WM_MOUSEACTIVATE, (WPARAM)(HWND)(hwndTopLevel), MAKELPARAM((codeHitTest), (msg)))

/* void Cls_OnCancelMode(HWND hwnd) */
#define HANDLE_WM_CANCELMODE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_CANCELMODE(hwnd, fn) \
  (void)(fn)((hwnd), WM_CANCELMODE, 0, 0L)

/* void Cls_OnTimer(HWND hwnd, UINT id) */
#define HANDLE_WM_TIMER(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam)), 0L)
#define FORWARD_WM_TIMER(hwnd, id, fn) \
  (void)(fn)((hwnd), WM_TIMER, (WPARAM)(UINT)(id), 0L)

/* void Cls_OnInitMenu(HWND hwnd, HMENU hMenu) */
#define HANDLE_WM_INITMENU(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HMENU)(wParam)), 0L)
#define FORWARD_WM_INITMENU(hwnd, hMenu, fn) \
  (void)(fn)((hwnd), WM_INITMENU, (WPARAM)(HMENU)(hMenu), 0L)

/* void Cls_OnInitMenuPopup(HWND hwnd, HMENU hMenu, int item, BOOL fSystemMenu) */
#define HANDLE_WM_INITMENUPOPUP(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HMENU)(wParam), (int)LOWORD(lParam), (BOOL)HIWORD(lParam)), 0L)
#define FORWARD_WM_INITMENUPOPUP(hwnd, hMenu, item, fSystemMenu, fn) \
  (void)(fn)((hwnd), WM_INITMENUPOPUP, (WPARAM)(HMENU)(hMenu), MAKELPARAM((item), (fSystemMenu)))

/* void Cls_OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags) */
#define HANDLE_WM_MENUSELECT(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HMENU)HIWORD(lParam), (LOWORD(lParam) & MF_POPUP) ? 0 : (int)(wParam), (LOWORD(lParam) & MF_POPUP) ? (HMENU)(wParam) : 0, (UINT)LOWORD(lParam)), 0L)
#define FORWARD_WM_MENUSELECT(hwnd, hmenu, item, hmenuPopup, flags, fn) \
  (void)(fn)((hwnd), WM_MENUSELECT, ((flags) & MF_POPUP) ? (WPARAM)(HMENU)(hmenuPopup) : (WPARAM)(int)(item), MAKELPARAM((flags), (UINT)(HMENU)(hmenu)))

/* DWORD Cls_OnMenuChar(HWND hwnd, UINT ch, UINT flags, HMENU hmenu) */
#define HANDLE_WM_MENUCHAR(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(fn)((hwnd), (UINT)(wParam), (UINT)LOWORD(lParam), (HMENU)HIWORD(lParam))
#define FORWARD_WM_MENUCHAR(hwnd, ch, flags, hmenu, fn) \
  (DWORD)(fn)((hwnd), WM_MENUCHAR, (WPARAM)(UINT)(ch), MAKELPARAM((flags), (UINT)(HMENU)(hmenu)))

/* void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) */
#define HANDLE_WM_COMMAND(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (int)(wParam), (HWND)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L)
#define FORWARD_WM_COMMAND(hwnd, id, hwndCtl, codeNotify, fn) \
  (void)(fn)((hwnd), WM_COMMAND, (WPARAM)(int)(id), MAKELPARAM((UINT)(HWND)(hwndCtl), (codeNotify)))

/* void Cls_OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos) */
#define HANDLE_WM_HSCROLL(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HWND)HIWORD(lParam), (UINT)(wParam), (int)LOWORD(lParam)), 0L)
#define FORWARD_WM_HSCROLL(hwnd, hwndCtl, code, pos, fn) \
  (void)(fn)((hwnd), WM_HSCROLL, (WPARAM)(UINT)(code), MAKELPARAM((pos), (UINT)(HWND)(hwndCtl)))

/* void Cls_OnVScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos) */
#define HANDLE_WM_VSCROLL(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HWND)HIWORD(lParam), (UINT)(wParam), (int)LOWORD(lParam)), 0L)
#define FORWARD_WM_VSCROLL(hwnd, hwndCtl, code, pos, fn) \
  (void)(fn)((hwnd), WM_VSCROLL, (WPARAM)(UINT)(code), MAKELPARAM((pos), (UINT)(HWND)(hwndCtl)))

/* void Cls_OnCut(HWND hwnd) */
#define HANDLE_WM_CUT(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_CUT(hwnd, fn) \
  (void)(fn)((hwnd), WM_CUT, 0, 0L)

/* void Cls_OnCopy(HWND hwnd) */
#define HANDLE_WM_COPY(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_COPY(hwnd, fn) \
  (void)(fn)((hwnd), WM_COPY, 0, 0L)

/* void Cls_OnPaste(HWND hwnd) */
#define HANDLE_WM_PASTE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_PASTE(hwnd, fn) \
  (void)(fn)((hwnd), WM_PASTE, 0, 0L)

/* void Cls_OnClear(HWND hwnd) */
#define HANDLE_WM_CLEAR(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_CLEAR(hwnd, fn) \
  (void)(fn)((hwnd), WM_CLEAR, 0, 0L)

/* void Cls_OnUndo(HWND hwnd) */
#define HANDLE_WM_UNDO(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_UNDO(hwnd, fn) \
  (void)(fn)((hwnd), WM_UNDO, 0, 0L)

/* void Cls_OnRenderAllFormats(HWND hwnd) */
#define HANDLE_WM_RENDERALLFORMATS(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_RENDERALLFORMATS(hwnd, fn) \
  (void)(fn)((hwnd), WM_RENDERALLFORMATS, 0, 0L)

/* void Cls_OnDestroyClipboard(HWND hwnd) */
#define HANDLE_WM_DESTROYCLIPBOARD(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_DESTROYCLIPBOARD(hwnd, fn) \
  (void)(fn)((hwnd), WM_DESTROYCLIPBOARD, 0, 0L)

/* void Cls_OnDrawClipboard(HWND hwnd) */
#define HANDLE_WM_DRAWCLIPBOARD(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_DRAWCLIPBOARD(hwnd, fn) \
  (void)(fn)((hwnd), WM_DRAWCLIPBOARD, 0, 0L)

/* HANDLE Cls_OnRenderFormat(HWND hwnd, UINT fmt) */
#define HANDLE_WM_RENDERFORMAT(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(UINT)(HANDLE)(fn)((hwnd), (UINT)(wParam))
#define FORWARD_WM_RENDERFORMAT(hwnd, fmt, fn) \
  (HANDLE)(UINT)(DWORD)(fn)((hwnd), WM_RENDERFORMAT, (WPARAM)(UINT)(fmt), 0L)

/* void Cls_OnAskCBFormatName(HWND hwnd, int cchMax, LPSTR rgchName) */
#define HANDLE_WM_ASKCBFORMATNAME(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (int)(wParam), (LPSTR)(lParam)), 0L)
#define FORWARD_WM_ASKCBFORMATNAME(hwnd, cchMax, rgchName, fn) \
  (void)(fn)((hwnd), WM_ASKCBFORMATNAME, (WPARAM)(int)(cchMax), (LPARAM)(rgchName))

/* void Cls_OnChangeCBChain(HWND hwnd, HWND hwndRemove, HWND hwndNext) */
#define HANDLE_WM_CHANGECBCHAIN(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HWND)(wParam), (HWND)LOWORD(lParam)), 0L)
#define FORWARD_WM_CHANGECBCHAIN(hwnd, hwndRemove, hwndNext, fn) \
  (void)(fn)((hwnd), WM_CHANGECBCHAIN, (WPARAM)(HWND)(hwndRemove), MAKELPARAM((UINT)(HWND)(hwndNext), 0))

/* void Cls_OnHScrollClipboard(HWND hwnd, HWND hwndCBViewer, UINT code, int pos) */
#define HANDLE_WM_HSCROLLCLIPBOARD(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HWND)(wParam), (UINT)LOWORD(lParam), (int)HIWORD(lParam)), 0L)
#define FORWARD_WM_HSCROLLCLIPBOARD(hwnd, hwndCBViewer, code, pos, fn) \
  (void)(fn)((hwnd), WM_HSCROLLCLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), MAKELPARAM((code), (pos)))

/* void Cls_OnVScrollClipboard(HWND hwnd, HWND hwndCBViewer, UINT code, int pos) */
#define HANDLE_WM_VSCROLLCLIPBOARD(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HWND)(wParam), (UINT)LOWORD(lParam), (int)HIWORD(lParam)), 0L)
#define FORWARD_WM_VSCROLLCLIPBOARD(hwnd, hwndCBViewer, code, pos, fn) \
  (void)(fn)((hwnd), WM_VSCROLLCLIPBOARD, (WPARAM)(HWND)(hwndCBViewer), MAKELPARAM((code), (pos)))

/* BOOL Cls_OnSetCursor(HWND hwnd, HWND hwndCursor, UINT codeHitTest, UINT msg) */
#define HANDLE_WM_SETCURSOR(hwnd, wParam, lParam, fn) \
  MAKELRESULT((BOOL)(fn)((hwnd), (HWND)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L)
#define FORWARD_WM_SETCURSOR(hwnd, hwndCursor, codeHitTest, msg, fn) \
  (BOOL)(DWORD)(fn)((hwnd), WM_SETCURSOR, (WPARAM)(HWND)(hwndCursor), MAKELPARAM((codeHitTest), (msg)))

/* void Cls_OnSysCommand(HWND hwnd, UINT cmd, int x, int y) */
#define HANDLE_WM_SYSCOMMAND(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam)), 0L)
#define FORWARD_WM_SYSCOMMAND(hwnd, cmd, x, y, fn) \
  (void)(fn)((hwnd), WM_SYSCOMMAND, (WPARAM)(UINT)(cmd), MAKELPARAM((x), (y)))

/* HWND Cls_OnMDICreate(HWND hwnd, const MDICREATESTRUCT FAR *lpmcs) */
#define HANDLE_WM_MDICREATE(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(UINT)(HWND)(fn)((hwnd), (const MDICREATESTRUCT FAR *)(lParam))
#define FORWARD_WM_MDICREATE(hwnd, lpmcs, fn) \
  (HWND)(UINT)(DWORD)(fn)((hwnd), WM_MDICREATE, 0, (LPARAM)(const MDICREATESTRUCT FAR *)(lpmcs))

/* void Cls_OnMDIDestroy(HWND hwnd, HWND hwndDestroy) */
#define HANDLE_WM_MDIDESTROY(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HWND)(wParam)), 0L)
#define FORWARD_WM_MDIDESTROY(hwnd, hwndDestroy, fn) \
  (void)(fn)((hwnd), WM_MDIDESTROY, (WPARAM)(HWND)(hwndDestroy), 0L)

/* void Cls_OnMDIActivate(HWND hwnd, BOOL fActive, HWND hwndActivate, HWND hwndDeactivate) */
#define HANDLE_WM_MDIACTIVATE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (BOOL)(wParam), (HWND)LOWORD(lParam), (HWND)HIWORD(lParam)), 0L)
#define FORWARD_WM_MDIACTIVATE(hwnd, fActive, hwndActivate, hwndDeactivate, fn) \
  (void)(fn)((hwnd), WM_MDIACTIVATE, (WPARAM)(BOOL)(fActive), MAKELPARAM((UINT)(HWND)(hwndActivate), (UINT)(HWND)(hwndDeactivate)))

/* void Cls_OnMDIRestore(HWND hwnd, HWND hwndRestore) */
#define HANDLE_WM_MDIRESTORE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HWND)(wParam)), 0L)
#define FORWARD_WM_MDIRESTORE(hwnd, hwndRestore, fn) \
  (void)(fn)((hwnd), WM_MDIRESTORE, (WPARAM)(HWND)(hwndRestore), 0L)

/* HWND Cls_OnMDINext(HWND hwnd, HWND hwndCur, BOOL fPrev) */
#define HANDLE_WM_MDINEXT(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(UINT)(HWND)(fn)((hwnd), (HWND)(wParam), (BOOL)LOWORD(lParam))
#define FORWARD_WM_MDINEXT(hwnd, hwndCur, fPrev, fn) \
  (HWND)(UINT)(DWORD)(fn)((hwnd), WM_MDINEXT, (WPARAM)(HWND)(hwndCur), MAKELPARAM((fPrev), 0))

/* void Cls_OnMDIMaximize(HWND hwnd, HWND hwndMaximize) */
#define HANDLE_WM_MDIMAXIMIZE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HWND)(wParam)), 0L)
#define FORWARD_WM_MDIMAXIMIZE(hwnd, hwndMaximize, fn) \
  (void)(fn)((hwnd), WM_MDIMAXIMIZE, (WPARAM)(HWND)(hwndMaximize), 0L)

/* BOOL Cls_OnMDITile(HWND hwnd, UINT cmd) */
#define HANDLE_WM_MDITILE(hwnd, wParam, lParam, fn) \
  MAKELRESULT((BOOL)(fn)((hwnd), (UINT)(wParam)), 0L)
#define FORWARD_WM_MDITILE(hwnd, cmd, fn) \
  (BOOL)(DWORD)(fn)((hwnd), WM_MDITILE, (WPARAM)(cmd), 0L)

/* BOOL Cls_OnMDICascade(HWND hwnd, UINT cmd) */
#define HANDLE_WM_MDICASCADE(hwnd, wParam, lParam, fn) \
  MAKELRESULT((BOOL)(fn)((hwnd), (UINT)(wParam)), 0L)
#define FORWARD_WM_MDICASCADE(hwnd, cmd, fn) \
  (BOOL)(DWORD)(fn)((hwnd), WM_MDICASCADE, (WPARAM)(cmd), 0L)

/* void Cls_OnMDIIconArrange(HWND hwnd) */
#define HANDLE_WM_MDIICONARRANGE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_MDIICONARRANGE(hwnd, fn) \
  (void)(fn)((hwnd), WM_MDIICONARRANGE, 0, 0L)

/* HWND Cls_OnMDIGetActive(HWND hwnd) */
#define HANDLE_WM_MDIGETACTIVE(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(UINT)(HWND)(fn)((hwnd))
#define FORWARD_WM_MDIGETACTIVE(hwnd, fn) \
  (HWND)(UINT)(DWORD)(fn)((hwnd), WM_MDIGETACTIVE, 0, 0L)

/* HMENU Cls_OnMDISetMenu(HWND hwnd, BOOL fRefresh, HMENU hmenuFrame, HMENU hmenuWindow) */
#define HANDLE_WM_MDISETMENU(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(UINT)(HMENU)(fn)((hwnd), (BOOL)(wParam), (HMENU)LOWORD(lParam), (HMENU)HIWORD(lParam))
#define FORWARD_WM_MDISETMENU(hwnd, fRefresh, hmenuFrame, hmenuWindow, fn) \
  (HMENU)(UINT)(DWORD)(fn)((hwnd), WM_MDISETMENU, (WPARAM)(BOOL)(fRefresh), MAKELPARAM((UINT)(HMENU)(hmenuFrame), (UINT)(HMENU)(hmenuWindow)))

/* void Cls_OnChildActivate(HWND hwnd) */
#define HANDLE_WM_CHILDACTIVATE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_CHILDACTIVATE(hwnd, fn) \
  (void)(fn)((hwnd), WM_CHILDACTIVATE, 0, 0L)

/* BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) */
#define HANDLE_WM_INITDIALOG(hwnd, wParam, lParam, fn) \
  MAKELRESULT((BOOL)(fn)((hwnd), (HWND)(wParam), lParam), 0L)
#define FORWARD_WM_INITDIALOG(hwnd, hwndFocus, lParam, fn) \
  (BOOL)(DWORD)(fn)((hwnd), WM_INITDIALOG, (WPARAM)(HWND)(hwndFocus), (lParam))

/* HWND Cls_OnNextDlgCtl(HWND hwnd, HWND hwndSetFocus, BOOL fNext) */
#define HANDLE_WM_NEXTDLGCTL(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(UINT)(HWND)(fn)((hwnd), (HWND)(wParam), (BOOL)LOWORD(lParam))
#define FORWARD_WM_NEXTDLGCTL(hwnd, hwndSetFocus, fNext, fn) \
  (HWND)(UINT)(DWORD)(fn)((hwnd), WM_NEXTDLGCTL, (WPARAM)(HWND)(hwndSetFocus), MAKELPARAM((fNext), 0))

/* void Cls_OnParentNotify(HWND hwnd, UINT msg, HWND hwndChild, int idChild) */
#define HANDLE_WM_PARENTNOTIFY(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam), (HWND)LOWORD(lParam), (int)HIWORD(lParam)), 0L)
#define FORWARD_WM_PARENTNOTIFY(hwnd, msg, hwndChild, idChild, fn) \
  (void)(fn)((hwnd), WM_PARENTNOTIFY, (WPARAM)(UINT)(msg), MAKELPARAM((UINT)(HWND)(hwndChild), (UINT)(idChild)))

/* void Cls_OnEnterIdle(HWND hwnd, UINT source, HWND hwndSource) */
#define HANDLE_WM_ENTERIDLE(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam), (HWND)LOWORD(lParam)), 0L)
#define FORWARD_WM_ENTERIDLE(hwnd, source, hwndSource, fn) \
  (void)(fn)((hwnd), WM_ENTERIDLE, (WPARAM)(UINT)(source), MAKELPARAM((UINT)(HWND)(hwndSource), 0))

/* UINT Cls_OnGetDlgCode(HWND hwnd, MSG FAR *lpmsg) */
#define HANDLE_WM_GETDLGCODE(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(UINT)(fn)((hwnd), (MSG FAR *)(lParam))
#define FORWARD_WM_GETDLGCODE(hwnd, lpmsg, fn) \
  (UINT)(DWORD)(fn)((hwnd), WM_GETDLGCODE, 0, (LPARAM)(MSG FAR *)(lpmsg))

/* HBRUSH Cls_OnCtlColor(HWND hwnd, HDC hdc, HWND hwndChild, int type) */
#define HANDLE_WM_CTLCOLOR(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(UINT)(HBRUSH)(fn)((hwnd), (HDC)(wParam), (HWND)LOWORD(lParam), (int)HIWORD(lParam))
#define FORWARD_WM_CTLCOLOR(hwnd, hdc, hwndChild, type, fn) \
  (HBRUSH)(UINT)(DWORD)(fn)((hwnd), WM_CTLCOLOR, (WPARAM)(HDC)(hdc), MAKELPARAM((UINT)(HWND)(hwndChild), (UINT)(int)(type)))

/* void Cls_OnSetFont(HWND hwnd, HFONT hfont, BOOL fRedraw) */
#define HANDLE_WM_SETFONT(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HFONT)(wParam), (BOOL)LOWORD(lParam)), 0L)
#define FORWARD_WM_SETFONT(hwnd, hfont, fRedraw, fn) \
  (void)(fn)((hwnd), WM_SETFONT, (WPARAM)(HFONT)(hfont), MAKELPARAM((fRedraw), 0))

/* HFONT Cls_OnGetFont(HWND hwnd) */
#define HANDLE_WM_GETFONT(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(UINT)(HFONT)(fn)((hwnd))
#define FORWARD_WM_GETFONT(hwnd, fn) \
  (HFONT)(UINT)(DWORD)(fn)((hwnd), WM_GETFONT, 0, 0L)

/* void Cls_OnDrawItem(HWND hwnd, const DRAWITEMSTRUCT FAR *lpDrawItem) */
#define HANDLE_WM_DRAWITEM(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (const DRAWITEMSTRUCT FAR *)(lParam)), 0L)
#define FORWARD_WM_DRAWITEM(hwnd, lpDrawItem, fn) \
  (void)(fn)((hwnd), WM_DRAWITEM, 0, (LPARAM)(const DRAWITEMSTRUCT FAR *)(lpDrawItem))

/* void Cls_OnMeasureItem(HWND hwnd, MEASUREITEMSTRUCT FAR *lpMeasureItem) */
#define HANDLE_WM_MEASUREITEM(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (MEASUREITEMSTRUCT FAR *)(lParam)), 0L)
#define FORWARD_WM_MEASUREITEM(hwnd, lpMeasureItem, fn) \
  (void)(fn)((hwnd), WM_MEASUREITEM, 0, (LPARAM)(MEASUREITEMSTRUCT FAR *)(lpMeasureItem))

/* void Cls_OnDeleteItem(HWND hwnd, const DELETEITEMSTRUCT FAR *lpDeleteItem) */
#define HANDLE_WM_DELETEITEM(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (const DELETEITEMSTRUCT FAR *)(lParam)), 0L)
#define FORWARD_WM_DELETEITEM(hwnd, lpDeleteItem, fn) \
  (void)(fn)((hwnd), WM_DELETEITEM, 0, (LPARAM)(const DELETEITEMSTRUCT FAR *)(lpDeleteItem))

/* int Cls_OnCompareItem(HWND hwnd, const COMPAREITEMSTRUCT FAR *lpCompareItem) */
#define HANDLE_WM_COMPAREITEM(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(int)(fn)((hwnd), (const COMPAREITEMSTRUCT FAR *)(lParam))
#define FORWARD_WM_COMPAREITEM(hwnd, lpCompareItem, fn) \
  (int)(DWORD)(fn)((hwnd), WM_COMPAREITEM, 0, (LPARAM)(const COMPAREITEMSTRUCT FAR *)(lpCompareItem))

/* int Cls_OnVkeyToItem(HWND hwnd, UINT vk, HWND hwndListbox, int iCaret) */
#define HANDLE_WM_VKEYTOITEM(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(int)(fn)((hwnd), (UINT)(wParam), (HWND)LOWORD(lParam), (int)HIWORD(lParam))
#define FORWARD_WM_VKEYTOITEM(hwnd, vk, hwndListbox, iCaret, fn) \
  (int)(DWORD)(fn)((hwnd), WM_VKEYTOITEM, (WPARAM)(UINT)(vk), MAKELPARAM((UINT)(HWND)(hwndListbox), (UINT)(iCaret)))

/* int Cls_OnCharToItem(HWND hwnd, UINT ch, HWND hwndListbox, int iCaret) */
#define HANDLE_WM_CHARTOITEM(hwnd, wParam, lParam, fn) \
  (LRESULT)(DWORD)(int)(fn)((hwnd), (UINT)(wParam), (HWND)LOWORD(lParam), (int)HIWORD(lParam))
#define FORWARD_WM_CHARTOITEM(hwnd, ch, hwndListbox, iCaret, fn) \
  (int)(DWORD)(fn)((hwnd), WM_CHARTOITEM, (WPARAM)(UINT)(ch), MAKELPARAM((UINT)(HWND)(hwndListbox), (UINT)(iCaret)))

/* void Cls_OnQueueSync(HWND hwnd) */
#define HANDLE_WM_QUEUESYNC(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd)), 0L)
#define FORWARD_WM_QUEUESYNC(hwnd, fn) \
  (void)(fn)((hwnd), WM_QUEUESYNC, 0, 0L)

/* void Cls_OnCommNotify(HWND hwnd, int cid, UINT flags) */
#define HANDLE_WM_COMMNOTIFY(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (int)(wParam), (UINT)LOWORD(lParam)), 0L)
#define FORWARD_WM_COMMNOTIFY(hwnd, cid, flags, fn) \
  (void)(fn)((hwnd), WM_COMMNOTIFY, (WPARAM)(cid), MAKELPARAM((flags), 0))


/* void Cls_OnDropFiles(HWND hwnd, HDROP hdrop) (HDROP is in shellapi.h) */
#define HANDLE_WM_DROPFILES(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (HDROP)(wParam)), 0L)
#define FORWARD_WM_DROPFILES(hwnd, hdrop, fn) \
  (void)(fn)((hwnd), WM_DROPFILES, (WPARAM)(HDROP)(hdrop), 0L)

/****************************************************************************
 * Controls
 ****************************************************************************/

/* Static controls. */
#define Static_Enable(hwnd, fEnable) EnableWindow((hwnd), (fEnable))
#define Static_GetText(hwnd, lpch, cchMax)                                     \
  GetWindowText((hwnd), (lpch), (cchMax))
#define Static_GetTextLength(hwnd) GetWindowTextLength(hwnd)
#define Static_SetText(hwnd, lpsz) SetWindowText((hwnd), (lpsz))
#define Static_SetIcon(hwnd, hIcon)                                            \
  ((HICON)(UINT)(DWORD)SendMessage((hwnd), STM_SETICON,                        \
                                   (WPARAM)(HICON)(hIcon), 0L))
#define Static_GetIcon(hwnd, hIcon)                                            \
  ((HICON)(UINT)(DWORD)SendMessage((hwnd), STM_GETICON, 0, 0L))

/* Buttons. */
#define Button_Enable(hwnd, fEnable) EnableWindow((hwnd), (fEnable))
#define Button_GetText(hwnd, lpch, cchMax)                                     \
  GetWindowText((hwnd), (lpch), (cchMax))
#define Button_GetTextLength(hwnd) GetWindowTextLength(hwnd)
#define Button_SetText(hwnd, lpsz) SetWindowText((hwnd), (lpsz))
#define Button_GetCheck(hwnd)                                                  \
  ((int)(DWORD)SendMessage((hwnd), BM_GETCHECK, 0, 0L))
#define Button_SetCheck(hwnd, check)                                           \
  ((void)SendMessage((hwnd), BM_SETCHECK, (WPARAM)(int)(check), 0L))
#define Button_GetState(hwnd)                                                  \
  ((int)(DWORD)SendMessage((hwnd), BM_GETSTATE, 0, 0L))
#define Button_SetState(hwnd, state)                                           \
  ((UINT)(DWORD)SendMessage((hwnd), BM_SETSTATE, (WPARAM)(int)(state), 0L))
#define Button_SetStyle(hwnd, style, fRedraw)                                  \
  ((void)SendMessage((hwnd), BM_SETSTYLE, (WPARAM)LOWORD(style),               \
                     MAKELPARAM(((fRedraw) ? TRUE : FALSE), 0)))

/* Edit controls. */
#define Edit_Enable(hwnd, fEnable) EnableWindow((hwnd), (fEnable))
#define Edit_GetText(hwnd, lpch, cchMax) GetWindowText((hwnd), (lpch), (cchMax))
#define Edit_GetTextLength(hwnd) GetWindowTextLength(hwnd)
#define Edit_SetText(hwnd, lpsz) SetWindowText((hwnd), (lpsz))
#define Edit_LimitText(hwnd, cchMax)                                           \
  ((void)SendMessage((hwnd), EM_LIMITTEXT, (WPARAM)(cchMax), 0L))
#define Edit_GetLineCount(hwnd)                                                \
  ((int)(DWORD)SendMessage((hwnd), EM_GETLINECOUNT, 0, 0L))
#define Edit_GetLine(hwnd, line, lpch, cchMax)                                 \
  ((*((int FAR *)(lpch)) = (cchMax)),                                          \
   ((int)(DWORD)SendMessage((hwnd), EM_GETLINE, (WPARAM)(int)(line),          \
                            (LPARAM)(LPSTR)(lpch))))
#define Edit_GetRect(hwnd, lprc)                                               \
  ((void)SendMessage((hwnd), EM_GETRECT, 0, (LPARAM)(RECT FAR *)(lprc)))
#define Edit_SetRect(hwnd, lprc)                                               \
  ((void)SendMessage((hwnd), EM_SETRECT, 0, (LPARAM)(const RECT FAR *)(lprc)))
#define Edit_SetRectNoPaint(hwnd, lprc)                                        \
  ((void)SendMessage((hwnd), EM_SETRECTNP, 0,                                  \
                     (LPARAM)(const RECT FAR *)(lprc)))
#define Edit_GetSel(hwnd) ((DWORD)SendMessage((hwnd), EM_GETSEL, 0, 0L))
#define Edit_SetSel(hwnd, ichStart, ichEnd)                                    \
  ((void)SendMessage((hwnd), EM_SETSEL, 0, MAKELPARAM((ichStart), (ichEnd))))
#define Edit_ReplaceSel(hwnd, lpszReplace)                                     \
  ((void)SendMessage((hwnd), EM_REPLACESEL, 0, (LPARAM)(LPCSTR)(lpszReplace)))
#define Edit_GetModify(hwnd)                                                   \
  ((BOOL)(DWORD)SendMessage((hwnd), EM_GETMODIFY, 0, 0L))
#define Edit_SetModify(hwnd, fModified)                                        \
  ((void)SendMessage((hwnd), EM_SETMODIFY, (WPARAM)(UINT)(fModified), 0L))
#define Edit_LineFromChar(hwnd, ich)                                           \
  ((int)(DWORD)SendMessage((hwnd), EM_LINEFROMCHAR, (WPARAM)(int)(ich), 0L))
#define Edit_LineIndex(hwnd, line)                                             \
  ((int)(DWORD)SendMessage((hwnd), EM_LINEINDEX, (WPARAM)(int)(line), 0L))
#define Edit_LineLength(hwnd, line)                                            \
  ((int)(DWORD)SendMessage((hwnd), EM_LINELENGTH, (WPARAM)(int)(line), 0L))
#define Edit_Scroll(hwnd, dv, dh)                                              \
  ((void)SendMessage((hwnd), EM_LINESCROLL, 0, MAKELPARAM((dv), (dh))))
#define Edit_CanUndo(hwnd)                                                     \
  ((BOOL)(DWORD)SendMessage((hwnd), EM_CANUNDO, 0, 0L))
#define Edit_Undo(hwnd) ((BOOL)(DWORD)SendMessage((hwnd), EM_UNDO, 0, 0L))
#define Edit_EmptyUndoBuffer(hwnd)                                             \
  ((void)SendMessage((hwnd), EM_EMPTYUNDOBUFFER, 0, 0L))
#define Edit_SetPasswordChar(hwnd, ch)                                         \
  ((void)SendMessage((hwnd), EM_SETPASSWORDCHAR, (WPARAM)(UINT)(ch), 0L))
#define Edit_SetTabStops(hwnd, cTabs, lpTabs)                                  \
  ((void)SendMessage((hwnd), EM_SETTABSTOPS, (WPARAM)(int)(cTabs),            \
                     (LPARAM)(const int FAR *)(lpTabs)))
#define Edit_FmtLines(hwnd, fAddEOL)                                           \
  ((BOOL)(DWORD)SendMessage((hwnd), EM_FMTLINES, (WPARAM)(BOOL)(fAddEOL), 0L))
#define Edit_GetHandle(hwnd)                                                   \
  ((HLOCAL)(UINT)(DWORD)SendMessage((hwnd), EM_GETHANDLE, 0, 0L))
#define Edit_SetHandle(hwnd, h)                                                \
  ((void)SendMessage((hwnd), EM_SETHANDLE, (WPARAM)(UINT)(HLOCAL)(h), 0L))
#if WINVER >= 0x030A
#define Edit_GetFirstVisibleLine(hwnd)                                         \
  ((int)(DWORD)SendMessage((hwnd), EM_GETFIRSTVISIBLELINE, 0, 0L))
#define Edit_SetReadOnly(hwnd, fReadOnly)                                      \
  ((BOOL)(DWORD)SendMessage((hwnd), EM_SETREADONLY, (WPARAM)(BOOL)(fReadOnly), \
                            0L))
#define Edit_GetPasswordChar(hwnd)                                             \
  ((char)(DWORD)SendMessage((hwnd), EM_GETPASSWORDCHAR, 0, 0L))
#define Edit_SetWordBreakProc(hwnd, lpfnWordBreak)                             \
  ((void)SendMessage((hwnd), EM_SETWORDBREAKPROC, 0,                           \
                     (LPARAM)(EDITWORDBREAKPROC)(lpfnWordBreak)))
#define Edit_GetWordBreakProc(hwnd)                                            \
  ((EDITWORDBREAKPROC)SendMessage((hwnd), EM_GETWORDBREAKPROC, 0, 0L))
#endif

/* Scroll bars. */
#if WINVER >= 0x030A
#define ScrollBar_Enable(hwnd, flags) EnableScrollBar((hwnd), SB_CTL, (flags))
#endif
#define ScrollBar_Show(hwnd, fShow)                                            \
  ShowWindow((hwnd), (fShow) ? SW_SHOWNORMAL : SW_HIDE)
#define ScrollBar_SetPos(hwnd, pos, fRedraw)                                   \
  SetScrollPos((hwnd), SB_CTL, (pos), (fRedraw))
#define ScrollBar_GetPos(hwnd) GetScrollPos((hwnd), SB_CTL)
#define ScrollBar_SetRange(hwnd, posMin, posMax, fRedraw)                      \
  SetScrollRange((hwnd), SB_CTL, (posMin), (posMax), (fRedraw))
#define ScrollBar_GetRange(hwnd, lpposMin, lpposMax)                           \
  GetScrollRange((hwnd), SB_CTL, (lpposMin), (lpposMax))

/* List boxes. */
#define ListBox_Enable(hwnd, fEnable) EnableWindow((hwnd), (fEnable))
#define ListBox_GetCount(hwnd)                                                 \
  ((int)(DWORD)SendMessage((hwnd), LB_GETCOUNT, 0, 0L))
#define ListBox_ResetContent(hwnd)                                             \
  ((BOOL)(DWORD)SendMessage((hwnd), LB_RESETCONTENT, 0, 0L))
#define ListBox_AddString(hwnd, lpsz)                                          \
  ((int)(DWORD)SendMessage((hwnd), LB_ADDSTRING, 0, (LPARAM)(LPCSTR)(lpsz)))
#define ListBox_InsertString(hwnd, index, lpsz)                                \
  ((int)(DWORD)SendMessage((hwnd), LB_INSERTSTRING, (WPARAM)(int)(index),     \
                           (LPARAM)(LPCSTR)(lpsz)))
#define ListBox_AddItemData(hwnd, data)                                        \
  ((int)(DWORD)SendMessage((hwnd), LB_ADDSTRING, 0, (LPARAM)(data)))
#define ListBox_InsertItemData(hwnd, index, data)                              \
  ((int)(DWORD)SendMessage((hwnd), LB_INSERTSTRING, (WPARAM)(int)(index),     \
                           (LPARAM)(data)))
#define ListBox_DeleteString(hwnd, index)                                      \
  ((int)(DWORD)SendMessage((hwnd), LB_DELETESTRING, (WPARAM)(int)(index), 0L))
#define ListBox_GetTextLen(hwnd, index)                                        \
  ((int)(DWORD)SendMessage((hwnd), LB_GETTEXTLEN, (WPARAM)(int)(index), 0L))
#define ListBox_GetText(hwnd, index, lpszBuffer)                               \
  ((int)(DWORD)SendMessage((hwnd), LB_GETTEXT, (WPARAM)(int)(index),          \
                           (LPARAM)(LPSTR)(lpszBuffer)))
#define ListBox_GetItemData(hwnd, index)                                       \
  ((LRESULT)(DWORD)SendMessage((hwnd), LB_GETITEMDATA, (WPARAM)(int)(index),  \
                               0L))
#define ListBox_SetItemData(hwnd, index, data)                                 \
  ((int)(DWORD)SendMessage((hwnd), LB_SETITEMDATA, (WPARAM)(int)(index),      \
                           (LPARAM)(data)))
#define ListBox_FindString(hwnd, indexStart, lpszFind)                         \
  ((int)(DWORD)SendMessage((hwnd), LB_FINDSTRING, (WPARAM)(int)(indexStart),  \
                           (LPARAM)(LPCSTR)(lpszFind)))
#define ListBox_FindItemData(hwnd, indexStart, data)                           \
  ((int)(DWORD)SendMessage((hwnd), LB_FINDSTRING, (WPARAM)(int)(indexStart),  \
                           (LPARAM)(data)))
#define ListBox_SetSel(hwnd, fSelect, index)                                   \
  ((int)(DWORD)SendMessage((hwnd), LB_SETSEL, (WPARAM)(BOOL)(fSelect),        \
                           MAKELPARAM((index), 0)))
#define ListBox_SelItemRange(hwnd, fSelect, first, last)                       \
  ((int)(DWORD)SendMessage((hwnd), LB_SELITEMRANGE, (WPARAM)(BOOL)(fSelect),  \
                           MAKELPARAM((first), (last))))
#define ListBox_GetCurSel(hwnd)                                                \
  ((int)(DWORD)SendMessage((hwnd), LB_GETCURSEL, 0, 0L))
#define ListBox_SetCurSel(hwnd, index)                                         \
  ((int)(DWORD)SendMessage((hwnd), LB_SETCURSEL, (WPARAM)(int)(index), 0L))
#define ListBox_SelectString(hwnd, indexStart, lpszFind)                       \
  ((int)(DWORD)SendMessage((hwnd), LB_SELECTSTRING, (WPARAM)(int)(indexStart),\
                           (LPARAM)(LPCSTR)(lpszFind)))
#define ListBox_SelectItemData(hwnd, indexStart, data)                         \
  ((int)(DWORD)SendMessage((hwnd), LB_SELECTSTRING, (WPARAM)(int)(indexStart),\
                           (LPARAM)(data)))
#define ListBox_GetSel(hwnd, index)                                            \
  ((int)(DWORD)SendMessage((hwnd), LB_GETSEL, (WPARAM)(int)(index), 0L))
#define ListBox_GetSelCount(hwnd)                                              \
  ((int)(DWORD)SendMessage((hwnd), LB_GETSELCOUNT, 0, 0L))
#define ListBox_GetTopIndex(hwnd)                                              \
  ((int)(DWORD)SendMessage((hwnd), LB_GETTOPINDEX, 0, 0L))
#define ListBox_GetSelItems(hwnd, cItems, lpItems)                             \
  ((int)(DWORD)SendMessage((hwnd), LB_GETSELITEMS, (WPARAM)(int)(cItems),     \
                           (LPARAM)(int FAR *)(lpItems)))
#define ListBox_SetTopIndex(hwnd, indexTop)                                    \
  ((int)(DWORD)SendMessage((hwnd), LB_SETTOPINDEX, (WPARAM)(int)(indexTop),   \
                           0L))
#define ListBox_SetColumnWidth(hwnd, cxColumn)                                 \
  ((void)SendMessage((hwnd), LB_SETCOLUMNWIDTH, (WPARAM)(int)(cxColumn), 0L))
#define ListBox_GetHorizontalExtent(hwnd)                                      \
  ((int)(DWORD)SendMessage((hwnd), LB_GETHORIZONTALEXTENT, 0, 0L))
#define ListBox_SetHorizontalExtent(hwnd, cxExtent)                            \
  ((void)SendMessage((hwnd), LB_SETHORIZONTALEXTENT, (WPARAM)(int)(cxExtent), \
                     0L))
#define ListBox_SetTabStops(hwnd, cTabs, lpTabs)                               \
  ((BOOL)(DWORD)SendMessage((hwnd), LB_SETTABSTOPS, (WPARAM)(int)(cTabs),     \
                            (LPARAM)(const int FAR *)(lpTabs)))
#define ListBox_GetItemRect(hwnd, index, lprc)                                 \
  ((int)(DWORD)SendMessage((hwnd), LB_GETITEMRECT, (WPARAM)(int)(index),      \
                           (LPARAM)(RECT FAR *)(lprc)))
#define ListBox_SetCaretIndex(hwnd, index)                                     \
  ((int)(DWORD)SendMessage((hwnd), LB_SETCARETINDEX, (WPARAM)(int)(index), 0L))
#define ListBox_GetCaretIndex(hwnd)                                            \
  ((int)(DWORD)SendMessage((hwnd), LB_GETCARETINDEX, 0, 0L))
#define ListBox_Dir(hwnd, attrs, lpszFileSpec)                                 \
  ((int)(DWORD)SendMessage((hwnd), LB_DIR, (WPARAM)(UINT)(attrs),             \
                           (LPARAM)(LPCSTR)(lpszFileSpec)))
#if WINVER >= 0x030A
#define ListBox_FindStringExact(hwnd, indexStart, lpszFind)                    \
  ((int)(DWORD)SendMessage((hwnd), LB_FINDSTRINGEXACT,                         \
                           (WPARAM)(int)(indexStart),                          \
                           (LPARAM)(LPCSTR)(lpszFind)))
#define ListBox_SetItemHeight(hwnd, index, cy)                                 \
  ((int)(DWORD)SendMessage((hwnd), LB_SETITEMHEIGHT, (WPARAM)(int)(index),    \
                           MAKELPARAM((cy), 0)))
#define ListBox_GetItemHeight(hwnd, index)                                     \
  ((int)(DWORD)SendMessage((hwnd), LB_GETITEMHEIGHT, (WPARAM)(int)(index), 0L))
#endif

/* Combo boxes. */
#define ComboBox_Enable(hwnd, fEnable) EnableWindow((hwnd), (fEnable))
#define ComboBox_GetText(hwnd, lpch, cchMax)                                   \
  GetWindowText((hwnd), (lpch), (cchMax))
#define ComboBox_GetTextLength(hwnd) GetWindowTextLength(hwnd)
#define ComboBox_SetText(hwnd, lpsz) SetWindowText((hwnd), (lpsz))
#define ComboBox_LimitText(hwnd, cchLimit)                                     \
  ((int)(DWORD)SendMessage((hwnd), CB_LIMITTEXT, (WPARAM)(int)(cchLimit), 0L))
#define ComboBox_GetEditSel(hwnd)                                              \
  ((DWORD)SendMessage((hwnd), CB_GETEDITSEL, 0, 0L))
#define ComboBox_SetEditSel(hwnd, ichStart, ichEnd)                            \
  ((int)(DWORD)SendMessage((hwnd), CB_SETEDITSEL, 0,                           \
                           MAKELPARAM((ichStart), (ichEnd))))
#define ComboBox_GetCount(hwnd)                                                \
  ((int)(DWORD)SendMessage((hwnd), CB_GETCOUNT, 0, 0L))
#define ComboBox_ResetContent(hwnd)                                            \
  ((int)(DWORD)SendMessage((hwnd), CB_RESETCONTENT, 0, 0L))
#define ComboBox_AddString(hwnd, lpsz)                                         \
  ((int)(DWORD)SendMessage((hwnd), CB_ADDSTRING, 0, (LPARAM)(LPCSTR)(lpsz)))
#define ComboBox_InsertString(hwnd, index, lpsz)                               \
  ((int)(DWORD)SendMessage((hwnd), CB_INSERTSTRING, (WPARAM)(int)(index),     \
                           (LPARAM)(LPCSTR)(lpsz)))
#define ComboBox_AddItemData(hwnd, data)                                       \
  ((int)(DWORD)SendMessage((hwnd), CB_ADDSTRING, 0, (LPARAM)(data)))
#define ComboBox_InsertItemData(hwnd, index, data)                             \
  ((int)(DWORD)SendMessage((hwnd), CB_INSERTSTRING, (WPARAM)(int)(index),     \
                           (LPARAM)(data)))
#define ComboBox_DeleteString(hwnd, index)                                     \
  ((int)(DWORD)SendMessage((hwnd), CB_DELETESTRING, (WPARAM)(int)(index), 0L))
#define ComboBox_GetLBTextLen(hwnd, index)                                     \
  ((int)(DWORD)SendMessage((hwnd), CB_GETLBTEXTLEN, (WPARAM)(int)(index), 0L))
#define ComboBox_GetLBText(hwnd, index, lpszBuffer)                            \
  ((int)(DWORD)SendMessage((hwnd), CB_GETLBTEXT, (WPARAM)(int)(index),        \
                           (LPARAM)(LPSTR)(lpszBuffer)))
#define ComboBox_GetItemData(hwnd, index)                                      \
  ((LRESULT)(DWORD)SendMessage((hwnd), CB_GETITEMDATA, (WPARAM)(int)(index),  \
                               0L))
#define ComboBox_SetItemData(hwnd, index, data)                                \
  ((int)(DWORD)SendMessage((hwnd), CB_SETITEMDATA, (WPARAM)(int)(index),      \
                           (LPARAM)(data)))
#define ComboBox_FindString(hwnd, indexStart, lpszFind)                        \
  ((int)(DWORD)SendMessage((hwnd), CB_FINDSTRING, (WPARAM)(int)(indexStart),  \
                           (LPARAM)(LPCSTR)(lpszFind)))
#define ComboBox_FindItemData(hwnd, indexStart, data)                          \
  ((int)(DWORD)SendMessage((hwnd), CB_FINDSTRING, (WPARAM)(int)(indexStart),  \
                           (LPARAM)(data)))
#define ComboBox_GetCurSel(hwnd)                                               \
  ((int)(DWORD)SendMessage((hwnd), CB_GETCURSEL, 0, 0L))
#define ComboBox_SetCurSel(hwnd, index)                                        \
  ((int)(DWORD)SendMessage((hwnd), CB_SETCURSEL, (WPARAM)(int)(index), 0L))
#define ComboBox_SelectString(hwnd, indexStart, lpszSelect)                    \
  ((int)(DWORD)SendMessage((hwnd), CB_SELECTSTRING, (WPARAM)(int)(indexStart),\
                           (LPARAM)(LPCSTR)(lpszSelect)))
#define ComboBox_SelectItemData(hwnd, indexStart, data)                        \
  ((int)(DWORD)SendMessage((hwnd), CB_SELECTSTRING, (WPARAM)(int)(indexStart),\
                           (LPARAM)(data)))
#define ComboBox_Dir(hwnd, attrs, lpszFileSpec)                                \
  ((int)(DWORD)SendMessage((hwnd), CB_DIR, (WPARAM)(UINT)(attrs),             \
                           (LPARAM)(LPCSTR)(lpszFileSpec)))
#define ComboBox_ShowDropdown(hwnd, fShow)                                     \
  ((BOOL)(DWORD)SendMessage((hwnd), CB_SHOWDROPDOWN, (WPARAM)(BOOL)(fShow), 0L))
#if WINVER >= 0x030A
#define ComboBox_FindStringExact(hwnd, indexStart, lpszFind)                   \
  ((int)(DWORD)SendMessage((hwnd), CB_FINDSTRINGEXACT,                         \
                           (WPARAM)(int)(indexStart),                          \
                           (LPARAM)(LPCSTR)(lpszFind)))
#define ComboBox_GetDroppedState(hwnd)                                         \
  ((BOOL)(DWORD)SendMessage((hwnd), CB_GETDROPPEDSTATE, 0, 0L))
#define ComboBox_GetDroppedControlRect(hwnd, lprc)                             \
  ((void)SendMessage((hwnd), CB_GETDROPPEDCONTROLRECT, 0,                      \
                     (LPARAM)(RECT FAR *)(lprc)))
#define ComboBox_GetItemHeight(hwnd)                                           \
  ((int)(DWORD)SendMessage((hwnd), CB_GETITEMHEIGHT, 0, 0L))
#define ComboBox_SetItemHeight(hwnd, cyItem)                                   \
  ((int)(DWORD)SendMessage((hwnd), CB_SETITEMHEIGHT, 0, (LPARAM)(int)(cyItem)))
#define ComboBox_GetExtendedUI(hwnd)                                           \
  ((UINT)(DWORD)SendMessage((hwnd), CB_GETEXTENDEDUI, 0, 0L))
#define ComboBox_SetExtendedUI(hwnd, flags)                                    \
  ((int)(DWORD)SendMessage((hwnd), CB_SETEXTENDEDUI, (WPARAM)(UINT)(flags), 0L))
#endif

#ifdef __cplusplus
}
#endif

#endif /* _WINDOWSX_H */
