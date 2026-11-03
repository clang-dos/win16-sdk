/* windowsx.h: every message cracker splits a message and its forwarder
 * packs it again the same way, and the control macros compile. Built with
 * and without STRICT. Generated with the cracker table in windowsx.h. */
#include <stdio.h>
#include <windows.h>
#include <shellapi.h>
#include <windowsx.h>

static int failures;
#define CHECK(c)                                                               \
  do {                                                                         \
    if (!(c)) {                                                                \
      printf("FAIL line %d: %s\n", __LINE__, #c);                              \
      failures++;                                                              \
    }                                                                          \
  } while (0)

/* The last message forwarded. */
static UINT lastMsg;
static WPARAM lastW;
static LPARAM lastL;

static LRESULT CALLBACK Record(HWND hwnd, UINT msg, WPARAM wParam,
                               LPARAM lParam) {
  (void)hwnd;
  lastMsg = msg;
  lastW = wParam;
  lastL = lParam;
  return 0;
}

static void Cls_OnCompacting(HWND hwnd, UINT compactRatio) {
  FORWARD_WM_COMPACTING(hwnd, compactRatio, Record);
}

static void Cls_OnWinIniChange(HWND hwnd, LPCSTR lpszSectionName) {
  FORWARD_WM_WININICHANGE(hwnd, lpszSectionName, Record);
}

static void Cls_OnSysColorChange(HWND hwnd) {
  FORWARD_WM_SYSCOLORCHANGE(hwnd, Record);
}

static BOOL Cls_OnQueryNewPalette(HWND hwnd) {
  return FORWARD_WM_QUERYNEWPALETTE(hwnd, Record);
}

static void Cls_OnPaletteIsChanging(HWND hwnd, HWND hwndPaletteChange) {
  FORWARD_WM_PALETTEISCHANGING(hwnd, hwndPaletteChange, Record);
}

static void Cls_OnPaletteChanged(HWND hwnd, HWND hwndPaletteChange) {
  FORWARD_WM_PALETTECHANGED(hwnd, hwndPaletteChange, Record);
}

static void Cls_OnFontChange(HWND hwnd) {
  FORWARD_WM_FONTCHANGE(hwnd, Record);
}

static void Cls_OnSpoolerStatus(HWND hwnd, UINT status, int cJobInQueue) {
  FORWARD_WM_SPOOLERSTATUS(hwnd, status, cJobInQueue, Record);
}

static void Cls_OnDevModeChange(HWND hwnd, LPCSTR lpszDeviceName) {
  FORWARD_WM_DEVMODECHANGE(hwnd, lpszDeviceName, Record);
}

static void Cls_OnTimeChange(HWND hwnd) {
  FORWARD_WM_TIMECHANGE(hwnd, Record);
}

static void Cls_OnPower(HWND hwnd, int code) {
  FORWARD_WM_POWER(hwnd, code, Record);
}

static BOOL Cls_OnQueryEndSession(HWND hwnd) {
  return FORWARD_WM_QUERYENDSESSION(hwnd, Record);
}

static void Cls_OnEndSession(HWND hwnd, BOOL fEnding) {
  FORWARD_WM_ENDSESSION(hwnd, fEnding, Record);
}

static void Cls_OnQuit(HWND hwnd, int exitCode) {
  FORWARD_WM_QUIT(hwnd, exitCode, Record);
}

static void Cls_OnSystemError(HWND hwnd, int errCode) {
  FORWARD_WM_SYSTEMERROR(hwnd, errCode, Record);
}

static BOOL Cls_OnCreate(HWND hwnd, CREATESTRUCT FAR *lpCreateStruct) {
  FORWARD_WM_CREATE(hwnd, lpCreateStruct, Record);
  return lpCreateStruct != 0; /* -1 from the window procedure if not */
}

static BOOL Cls_OnNCCreate(HWND hwnd, CREATESTRUCT FAR *lpCreateStruct) {
  return FORWARD_WM_NCCREATE(hwnd, lpCreateStruct, Record);
}

static void Cls_OnDestroy(HWND hwnd) {
  FORWARD_WM_DESTROY(hwnd, Record);
}

static void Cls_OnNCDestroy(HWND hwnd) {
  FORWARD_WM_NCDESTROY(hwnd, Record);
}

static void Cls_OnShowWindow(HWND hwnd, BOOL fShow, UINT status) {
  FORWARD_WM_SHOWWINDOW(hwnd, fShow, status, Record);
}

static void Cls_OnSetRedraw(HWND hwnd, BOOL fRedraw) {
  FORWARD_WM_SETREDRAW(hwnd, fRedraw, Record);
}

static void Cls_OnEnable(HWND hwnd, BOOL fEnable) {
  FORWARD_WM_ENABLE(hwnd, fEnable, Record);
}

static void Cls_OnSetText(HWND hwnd, LPCSTR lpszText) {
  FORWARD_WM_SETTEXT(hwnd, lpszText, Record);
}

static int Cls_OnGetText(HWND hwnd, int cchTextMax, LPSTR lpszText) {
  return FORWARD_WM_GETTEXT(hwnd, cchTextMax, lpszText, Record);
}

static int Cls_OnGetTextLength(HWND hwnd) {
  return FORWARD_WM_GETTEXTLENGTH(hwnd, Record);
}

static BOOL Cls_OnWindowPosChanging(HWND hwnd, WINDOWPOS FAR *lpwpos) {
  return FORWARD_WM_WINDOWPOSCHANGING(hwnd, lpwpos, Record);
}

static void Cls_OnWindowPosChanged(HWND hwnd, const WINDOWPOS FAR *lpwpos) {
  FORWARD_WM_WINDOWPOSCHANGED(hwnd, lpwpos, Record);
}

static void Cls_OnMove(HWND hwnd, int x, int y) {
  FORWARD_WM_MOVE(hwnd, x, y, Record);
}

static void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy) {
  FORWARD_WM_SIZE(hwnd, state, cx, cy, Record);
}

static void Cls_OnClose(HWND hwnd) {
  FORWARD_WM_CLOSE(hwnd, Record);
}

static BOOL Cls_OnQueryOpen(HWND hwnd) {
  return FORWARD_WM_QUERYOPEN(hwnd, Record);
}

static void Cls_OnGetMinMaxInfo(HWND hwnd, MINMAXINFO FAR *lpMinMaxInfo) {
  FORWARD_WM_GETMINMAXINFO(hwnd, lpMinMaxInfo, Record);
}

static void Cls_OnPaint(HWND hwnd) {
  FORWARD_WM_PAINT(hwnd, Record);
}

static BOOL Cls_OnEraseBkgnd(HWND hwnd, HDC hdc) {
  return FORWARD_WM_ERASEBKGND(hwnd, hdc, Record);
}

static BOOL Cls_OnIconEraseBkgnd(HWND hwnd, HDC hdc) {
  return FORWARD_WM_ICONERASEBKGND(hwnd, hdc, Record);
}

static void Cls_OnNCPaint(HWND hwnd, HRGN hrgn) {
  FORWARD_WM_NCPAINT(hwnd, hrgn, Record);
}

static UINT Cls_OnNCCalcSize(HWND hwnd, BOOL fCalcValidRects, NCCALCSIZE_PARAMS FAR *lpcsp) {
  return FORWARD_WM_NCCALCSIZE(hwnd, fCalcValidRects, lpcsp, Record);
}

static UINT Cls_OnNCHitTest(HWND hwnd, int x, int y) {
  return FORWARD_WM_NCHITTEST(hwnd, x, y, Record);
}

static HICON Cls_OnQueryDragIcon(HWND hwnd) {
  return FORWARD_WM_QUERYDRAGICON(hwnd, Record);
}

static void Cls_OnActivate(HWND hwnd, UINT state, HWND hwndActDeact, BOOL fMinimized) {
  FORWARD_WM_ACTIVATE(hwnd, state, hwndActDeact, fMinimized, Record);
}

static void Cls_OnActivateApp(HWND hwnd, BOOL fActivate, HTASK htaskActDeact) {
  FORWARD_WM_ACTIVATEAPP(hwnd, fActivate, htaskActDeact, Record);
}

static BOOL Cls_OnNCActivate(HWND hwnd, BOOL fActive, HWND hwndActDeact, BOOL fMinimized) {
  return FORWARD_WM_NCACTIVATE(hwnd, fActive, hwndActDeact, fMinimized, Record);
}

static void Cls_OnSetFocus(HWND hwnd, HWND hwndOldFocus) {
  FORWARD_WM_SETFOCUS(hwnd, hwndOldFocus, Record);
}

static void Cls_OnKillFocus(HWND hwnd, HWND hwndNewFocus) {
  FORWARD_WM_KILLFOCUS(hwnd, hwndNewFocus, Record);
}

static void Cls_OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags) {
  if (fDown)
    FORWARD_WM_KEYDOWN(hwnd, vk, cRepeat, flags, Record);
  else
    FORWARD_WM_KEYUP(hwnd, vk, cRepeat, flags, Record);
}

static void Cls_OnSysKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags) {
  if (fDown)
    FORWARD_WM_SYSKEYDOWN(hwnd, vk, cRepeat, flags, Record);
  else
    FORWARD_WM_SYSKEYUP(hwnd, vk, cRepeat, flags, Record);
}

static void Cls_OnChar(HWND hwnd, UINT ch, int cRepeat) {
  FORWARD_WM_CHAR(hwnd, ch, cRepeat, Record);
}

static void Cls_OnDeadChar(HWND hwnd, UINT ch, int cRepeat) {
  FORWARD_WM_DEADCHAR(hwnd, ch, cRepeat, Record);
}

static void Cls_OnSysChar(HWND hwnd, UINT ch, int cRepeat) {
  FORWARD_WM_SYSCHAR(hwnd, ch, cRepeat, Record);
}

static void Cls_OnSysDeadChar(HWND hwnd, UINT ch, int cRepeat) {
  FORWARD_WM_SYSDEADCHAR(hwnd, ch, cRepeat, Record);
}

static void Cls_OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags) {
  FORWARD_WM_MOUSEMOVE(hwnd, x, y, keyFlags, Record);
}

static void Cls_OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) {
  FORWARD_WM_LBUTTONDOWN(hwnd, fDoubleClick, x, y, keyFlags, Record);
}

static void Cls_OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags) {
  FORWARD_WM_LBUTTONUP(hwnd, x, y, keyFlags, Record);
}

static void Cls_OnRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) {
  FORWARD_WM_RBUTTONDOWN(hwnd, fDoubleClick, x, y, keyFlags, Record);
}

static void Cls_OnRButtonUp(HWND hwnd, int x, int y, UINT keyFlags) {
  FORWARD_WM_RBUTTONUP(hwnd, x, y, keyFlags, Record);
}

static void Cls_OnMButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) {
  FORWARD_WM_MBUTTONDOWN(hwnd, fDoubleClick, x, y, keyFlags, Record);
}

static void Cls_OnMButtonUp(HWND hwnd, int x, int y, UINT keyFlags) {
  FORWARD_WM_MBUTTONUP(hwnd, x, y, keyFlags, Record);
}

static void Cls_OnNCMouseMove(HWND hwnd, int x, int y, UINT codeHitTest) {
  FORWARD_WM_NCMOUSEMOVE(hwnd, x, y, codeHitTest, Record);
}

static void Cls_OnNCLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest) {
  FORWARD_WM_NCLBUTTONDOWN(hwnd, fDoubleClick, x, y, codeHitTest, Record);
}

static void Cls_OnNCLButtonUp(HWND hwnd, int x, int y, UINT codeHitTest) {
  FORWARD_WM_NCLBUTTONUP(hwnd, x, y, codeHitTest, Record);
}

static void Cls_OnNCRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest) {
  FORWARD_WM_NCRBUTTONDOWN(hwnd, fDoubleClick, x, y, codeHitTest, Record);
}

static void Cls_OnNCRButtonUp(HWND hwnd, int x, int y, UINT codeHitTest) {
  FORWARD_WM_NCRBUTTONUP(hwnd, x, y, codeHitTest, Record);
}

static void Cls_OnNCMButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest) {
  FORWARD_WM_NCMBUTTONDOWN(hwnd, fDoubleClick, x, y, codeHitTest, Record);
}

static void Cls_OnNCMButtonUp(HWND hwnd, int x, int y, UINT codeHitTest) {
  FORWARD_WM_NCMBUTTONUP(hwnd, x, y, codeHitTest, Record);
}

static int Cls_OnMouseActivate(HWND hwnd, HWND hwndTopLevel, UINT codeHitTest, UINT msg) {
  return FORWARD_WM_MOUSEACTIVATE(hwnd, hwndTopLevel, codeHitTest, msg, Record);
}

static void Cls_OnCancelMode(HWND hwnd) {
  FORWARD_WM_CANCELMODE(hwnd, Record);
}

static void Cls_OnTimer(HWND hwnd, UINT id) {
  FORWARD_WM_TIMER(hwnd, id, Record);
}

static void Cls_OnInitMenu(HWND hwnd, HMENU hMenu) {
  FORWARD_WM_INITMENU(hwnd, hMenu, Record);
}

static void Cls_OnInitMenuPopup(HWND hwnd, HMENU hMenu, int item, BOOL fSystemMenu) {
  FORWARD_WM_INITMENUPOPUP(hwnd, hMenu, item, fSystemMenu, Record);
}

static void Cls_OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags) {
  FORWARD_WM_MENUSELECT(hwnd, hmenu, item, hmenuPopup, flags, Record);
}

static DWORD Cls_OnMenuChar(HWND hwnd, UINT ch, UINT flags, HMENU hmenu) {
  return FORWARD_WM_MENUCHAR(hwnd, ch, flags, hmenu, Record);
}

static void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
  FORWARD_WM_COMMAND(hwnd, id, hwndCtl, codeNotify, Record);
}

static void Cls_OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos) {
  FORWARD_WM_HSCROLL(hwnd, hwndCtl, code, pos, Record);
}

static void Cls_OnVScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos) {
  FORWARD_WM_VSCROLL(hwnd, hwndCtl, code, pos, Record);
}

static void Cls_OnCut(HWND hwnd) {
  FORWARD_WM_CUT(hwnd, Record);
}

static void Cls_OnCopy(HWND hwnd) {
  FORWARD_WM_COPY(hwnd, Record);
}

static void Cls_OnPaste(HWND hwnd) {
  FORWARD_WM_PASTE(hwnd, Record);
}

static void Cls_OnClear(HWND hwnd) {
  FORWARD_WM_CLEAR(hwnd, Record);
}

static void Cls_OnUndo(HWND hwnd) {
  FORWARD_WM_UNDO(hwnd, Record);
}

static void Cls_OnRenderAllFormats(HWND hwnd) {
  FORWARD_WM_RENDERALLFORMATS(hwnd, Record);
}

static void Cls_OnDestroyClipboard(HWND hwnd) {
  FORWARD_WM_DESTROYCLIPBOARD(hwnd, Record);
}

static void Cls_OnDrawClipboard(HWND hwnd) {
  FORWARD_WM_DRAWCLIPBOARD(hwnd, Record);
}

static HANDLE Cls_OnRenderFormat(HWND hwnd, UINT fmt) {
  return FORWARD_WM_RENDERFORMAT(hwnd, fmt, Record);
}

static void Cls_OnAskCBFormatName(HWND hwnd, int cchMax, LPSTR rgchName) {
  FORWARD_WM_ASKCBFORMATNAME(hwnd, cchMax, rgchName, Record);
}

static void Cls_OnChangeCBChain(HWND hwnd, HWND hwndRemove, HWND hwndNext) {
  FORWARD_WM_CHANGECBCHAIN(hwnd, hwndRemove, hwndNext, Record);
}

static void Cls_OnHScrollClipboard(HWND hwnd, HWND hwndCBViewer, UINT code, int pos) {
  FORWARD_WM_HSCROLLCLIPBOARD(hwnd, hwndCBViewer, code, pos, Record);
}

static void Cls_OnVScrollClipboard(HWND hwnd, HWND hwndCBViewer, UINT code, int pos) {
  FORWARD_WM_VSCROLLCLIPBOARD(hwnd, hwndCBViewer, code, pos, Record);
}

static BOOL Cls_OnSetCursor(HWND hwnd, HWND hwndCursor, UINT codeHitTest, UINT msg) {
  return FORWARD_WM_SETCURSOR(hwnd, hwndCursor, codeHitTest, msg, Record);
}

static void Cls_OnSysCommand(HWND hwnd, UINT cmd, int x, int y) {
  FORWARD_WM_SYSCOMMAND(hwnd, cmd, x, y, Record);
}

static HWND Cls_OnMDICreate(HWND hwnd, const MDICREATESTRUCT FAR *lpmcs) {
  return FORWARD_WM_MDICREATE(hwnd, lpmcs, Record);
}

static void Cls_OnMDIDestroy(HWND hwnd, HWND hwndDestroy) {
  FORWARD_WM_MDIDESTROY(hwnd, hwndDestroy, Record);
}

static void Cls_OnMDIActivate(HWND hwnd, BOOL fActive, HWND hwndActivate, HWND hwndDeactivate) {
  FORWARD_WM_MDIACTIVATE(hwnd, fActive, hwndActivate, hwndDeactivate, Record);
}

static void Cls_OnMDIRestore(HWND hwnd, HWND hwndRestore) {
  FORWARD_WM_MDIRESTORE(hwnd, hwndRestore, Record);
}

static HWND Cls_OnMDINext(HWND hwnd, HWND hwndCur, BOOL fPrev) {
  return FORWARD_WM_MDINEXT(hwnd, hwndCur, fPrev, Record);
}

static void Cls_OnMDIMaximize(HWND hwnd, HWND hwndMaximize) {
  FORWARD_WM_MDIMAXIMIZE(hwnd, hwndMaximize, Record);
}

static BOOL Cls_OnMDITile(HWND hwnd, UINT cmd) {
  return FORWARD_WM_MDITILE(hwnd, cmd, Record);
}

static BOOL Cls_OnMDICascade(HWND hwnd, UINT cmd) {
  return FORWARD_WM_MDICASCADE(hwnd, cmd, Record);
}

static void Cls_OnMDIIconArrange(HWND hwnd) {
  FORWARD_WM_MDIICONARRANGE(hwnd, Record);
}

static HWND Cls_OnMDIGetActive(HWND hwnd) {
  return FORWARD_WM_MDIGETACTIVE(hwnd, Record);
}

static HMENU Cls_OnMDISetMenu(HWND hwnd, BOOL fRefresh, HMENU hmenuFrame, HMENU hmenuWindow) {
  return FORWARD_WM_MDISETMENU(hwnd, fRefresh, hmenuFrame, hmenuWindow, Record);
}

static void Cls_OnChildActivate(HWND hwnd) {
  FORWARD_WM_CHILDACTIVATE(hwnd, Record);
}

static BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
  return FORWARD_WM_INITDIALOG(hwnd, hwndFocus, lParam, Record);
}

static HWND Cls_OnNextDlgCtl(HWND hwnd, HWND hwndSetFocus, BOOL fNext) {
  return FORWARD_WM_NEXTDLGCTL(hwnd, hwndSetFocus, fNext, Record);
}

static void Cls_OnParentNotify(HWND hwnd, UINT msg, HWND hwndChild, int idChild) {
  FORWARD_WM_PARENTNOTIFY(hwnd, msg, hwndChild, idChild, Record);
}

static void Cls_OnEnterIdle(HWND hwnd, UINT source, HWND hwndSource) {
  FORWARD_WM_ENTERIDLE(hwnd, source, hwndSource, Record);
}

static UINT Cls_OnGetDlgCode(HWND hwnd, MSG FAR *lpmsg) {
  return FORWARD_WM_GETDLGCODE(hwnd, lpmsg, Record);
}

static HBRUSH Cls_OnCtlColor(HWND hwnd, HDC hdc, HWND hwndChild, int type) {
  return FORWARD_WM_CTLCOLOR(hwnd, hdc, hwndChild, type, Record);
}

static void Cls_OnSetFont(HWND hwnd, HFONT hfont, BOOL fRedraw) {
  FORWARD_WM_SETFONT(hwnd, hfont, fRedraw, Record);
}

static HFONT Cls_OnGetFont(HWND hwnd) {
  return FORWARD_WM_GETFONT(hwnd, Record);
}

static void Cls_OnDrawItem(HWND hwnd, const DRAWITEMSTRUCT FAR *lpDrawItem) {
  FORWARD_WM_DRAWITEM(hwnd, lpDrawItem, Record);
}

static void Cls_OnMeasureItem(HWND hwnd, MEASUREITEMSTRUCT FAR *lpMeasureItem) {
  FORWARD_WM_MEASUREITEM(hwnd, lpMeasureItem, Record);
}

static void Cls_OnDeleteItem(HWND hwnd, const DELETEITEMSTRUCT FAR *lpDeleteItem) {
  FORWARD_WM_DELETEITEM(hwnd, lpDeleteItem, Record);
}

static int Cls_OnCompareItem(HWND hwnd, const COMPAREITEMSTRUCT FAR *lpCompareItem) {
  return FORWARD_WM_COMPAREITEM(hwnd, lpCompareItem, Record);
}

static int Cls_OnVkeyToItem(HWND hwnd, UINT vk, HWND hwndListbox, int iCaret) {
  return FORWARD_WM_VKEYTOITEM(hwnd, vk, hwndListbox, iCaret, Record);
}

static int Cls_OnCharToItem(HWND hwnd, UINT ch, HWND hwndListbox, int iCaret) {
  return FORWARD_WM_CHARTOITEM(hwnd, ch, hwndListbox, iCaret, Record);
}

static void Cls_OnQueueSync(HWND hwnd) {
  FORWARD_WM_QUEUESYNC(hwnd, Record);
}

static void Cls_OnCommNotify(HWND hwnd, int cid, UINT flags) {
  FORWARD_WM_COMMNOTIFY(hwnd, cid, flags, Record);
}

static void Cls_OnDropFiles(HWND hwnd, HDROP hdrop) {
  FORWARD_WM_DROPFILES(hwnd, hdrop, Record);
}

static LRESULT CALLBACK TestWndProc(HWND hwnd, UINT msg, WPARAM wParam,
                                    LPARAM lParam) {
  switch (msg) {
    HANDLE_MSG(hwnd, WM_COMPACTING, Cls_OnCompacting);
    HANDLE_MSG(hwnd, WM_WININICHANGE, Cls_OnWinIniChange);
    HANDLE_MSG(hwnd, WM_SYSCOLORCHANGE, Cls_OnSysColorChange);
    HANDLE_MSG(hwnd, WM_QUERYNEWPALETTE, Cls_OnQueryNewPalette);
    HANDLE_MSG(hwnd, WM_PALETTEISCHANGING, Cls_OnPaletteIsChanging);
    HANDLE_MSG(hwnd, WM_PALETTECHANGED, Cls_OnPaletteChanged);
    HANDLE_MSG(hwnd, WM_FONTCHANGE, Cls_OnFontChange);
    HANDLE_MSG(hwnd, WM_SPOOLERSTATUS, Cls_OnSpoolerStatus);
    HANDLE_MSG(hwnd, WM_DEVMODECHANGE, Cls_OnDevModeChange);
    HANDLE_MSG(hwnd, WM_TIMECHANGE, Cls_OnTimeChange);
    HANDLE_MSG(hwnd, WM_POWER, Cls_OnPower);
    HANDLE_MSG(hwnd, WM_QUERYENDSESSION, Cls_OnQueryEndSession);
    HANDLE_MSG(hwnd, WM_ENDSESSION, Cls_OnEndSession);
    HANDLE_MSG(hwnd, WM_QUIT, Cls_OnQuit);
    HANDLE_MSG(hwnd, WM_SYSTEMERROR, Cls_OnSystemError);
    HANDLE_MSG(hwnd, WM_CREATE, Cls_OnCreate);
    HANDLE_MSG(hwnd, WM_NCCREATE, Cls_OnNCCreate);
    HANDLE_MSG(hwnd, WM_DESTROY, Cls_OnDestroy);
    HANDLE_MSG(hwnd, WM_NCDESTROY, Cls_OnNCDestroy);
    HANDLE_MSG(hwnd, WM_SHOWWINDOW, Cls_OnShowWindow);
    HANDLE_MSG(hwnd, WM_SETREDRAW, Cls_OnSetRedraw);
    HANDLE_MSG(hwnd, WM_ENABLE, Cls_OnEnable);
    HANDLE_MSG(hwnd, WM_SETTEXT, Cls_OnSetText);
    HANDLE_MSG(hwnd, WM_GETTEXT, Cls_OnGetText);
    HANDLE_MSG(hwnd, WM_GETTEXTLENGTH, Cls_OnGetTextLength);
    HANDLE_MSG(hwnd, WM_WINDOWPOSCHANGING, Cls_OnWindowPosChanging);
    HANDLE_MSG(hwnd, WM_WINDOWPOSCHANGED, Cls_OnWindowPosChanged);
    HANDLE_MSG(hwnd, WM_MOVE, Cls_OnMove);
    HANDLE_MSG(hwnd, WM_SIZE, Cls_OnSize);
    HANDLE_MSG(hwnd, WM_CLOSE, Cls_OnClose);
    HANDLE_MSG(hwnd, WM_QUERYOPEN, Cls_OnQueryOpen);
    HANDLE_MSG(hwnd, WM_GETMINMAXINFO, Cls_OnGetMinMaxInfo);
    HANDLE_MSG(hwnd, WM_PAINT, Cls_OnPaint);
    HANDLE_MSG(hwnd, WM_ERASEBKGND, Cls_OnEraseBkgnd);
    HANDLE_MSG(hwnd, WM_ICONERASEBKGND, Cls_OnIconEraseBkgnd);
    HANDLE_MSG(hwnd, WM_NCPAINT, Cls_OnNCPaint);
    HANDLE_MSG(hwnd, WM_NCCALCSIZE, Cls_OnNCCalcSize);
    HANDLE_MSG(hwnd, WM_NCHITTEST, Cls_OnNCHitTest);
    HANDLE_MSG(hwnd, WM_QUERYDRAGICON, Cls_OnQueryDragIcon);
    HANDLE_MSG(hwnd, WM_ACTIVATE, Cls_OnActivate);
    HANDLE_MSG(hwnd, WM_ACTIVATEAPP, Cls_OnActivateApp);
    HANDLE_MSG(hwnd, WM_NCACTIVATE, Cls_OnNCActivate);
    HANDLE_MSG(hwnd, WM_SETFOCUS, Cls_OnSetFocus);
    HANDLE_MSG(hwnd, WM_KILLFOCUS, Cls_OnKillFocus);
    HANDLE_MSG(hwnd, WM_KEYDOWN, Cls_OnKey);
    HANDLE_MSG(hwnd, WM_KEYUP, Cls_OnKey);
    HANDLE_MSG(hwnd, WM_SYSKEYDOWN, Cls_OnSysKey);
    HANDLE_MSG(hwnd, WM_SYSKEYUP, Cls_OnSysKey);
    HANDLE_MSG(hwnd, WM_CHAR, Cls_OnChar);
    HANDLE_MSG(hwnd, WM_DEADCHAR, Cls_OnDeadChar);
    HANDLE_MSG(hwnd, WM_SYSCHAR, Cls_OnSysChar);
    HANDLE_MSG(hwnd, WM_SYSDEADCHAR, Cls_OnSysDeadChar);
    HANDLE_MSG(hwnd, WM_MOUSEMOVE, Cls_OnMouseMove);
    HANDLE_MSG(hwnd, WM_LBUTTONDOWN, Cls_OnLButtonDown);
    HANDLE_MSG(hwnd, WM_LBUTTONDBLCLK, Cls_OnLButtonDown);
    HANDLE_MSG(hwnd, WM_LBUTTONUP, Cls_OnLButtonUp);
    HANDLE_MSG(hwnd, WM_RBUTTONDOWN, Cls_OnRButtonDown);
    HANDLE_MSG(hwnd, WM_RBUTTONDBLCLK, Cls_OnRButtonDown);
    HANDLE_MSG(hwnd, WM_RBUTTONUP, Cls_OnRButtonUp);
    HANDLE_MSG(hwnd, WM_MBUTTONDOWN, Cls_OnMButtonDown);
    HANDLE_MSG(hwnd, WM_MBUTTONDBLCLK, Cls_OnMButtonDown);
    HANDLE_MSG(hwnd, WM_MBUTTONUP, Cls_OnMButtonUp);
    HANDLE_MSG(hwnd, WM_NCMOUSEMOVE, Cls_OnNCMouseMove);
    HANDLE_MSG(hwnd, WM_NCLBUTTONDOWN, Cls_OnNCLButtonDown);
    HANDLE_MSG(hwnd, WM_NCLBUTTONDBLCLK, Cls_OnNCLButtonDown);
    HANDLE_MSG(hwnd, WM_NCLBUTTONUP, Cls_OnNCLButtonUp);
    HANDLE_MSG(hwnd, WM_NCRBUTTONDOWN, Cls_OnNCRButtonDown);
    HANDLE_MSG(hwnd, WM_NCRBUTTONDBLCLK, Cls_OnNCRButtonDown);
    HANDLE_MSG(hwnd, WM_NCRBUTTONUP, Cls_OnNCRButtonUp);
    HANDLE_MSG(hwnd, WM_NCMBUTTONDOWN, Cls_OnNCMButtonDown);
    HANDLE_MSG(hwnd, WM_NCMBUTTONDBLCLK, Cls_OnNCMButtonDown);
    HANDLE_MSG(hwnd, WM_NCMBUTTONUP, Cls_OnNCMButtonUp);
    HANDLE_MSG(hwnd, WM_MOUSEACTIVATE, Cls_OnMouseActivate);
    HANDLE_MSG(hwnd, WM_CANCELMODE, Cls_OnCancelMode);
    HANDLE_MSG(hwnd, WM_TIMER, Cls_OnTimer);
    HANDLE_MSG(hwnd, WM_INITMENU, Cls_OnInitMenu);
    HANDLE_MSG(hwnd, WM_INITMENUPOPUP, Cls_OnInitMenuPopup);
    HANDLE_MSG(hwnd, WM_MENUSELECT, Cls_OnMenuSelect);
    HANDLE_MSG(hwnd, WM_MENUCHAR, Cls_OnMenuChar);
    HANDLE_MSG(hwnd, WM_COMMAND, Cls_OnCommand);
    HANDLE_MSG(hwnd, WM_HSCROLL, Cls_OnHScroll);
    HANDLE_MSG(hwnd, WM_VSCROLL, Cls_OnVScroll);
    HANDLE_MSG(hwnd, WM_CUT, Cls_OnCut);
    HANDLE_MSG(hwnd, WM_COPY, Cls_OnCopy);
    HANDLE_MSG(hwnd, WM_PASTE, Cls_OnPaste);
    HANDLE_MSG(hwnd, WM_CLEAR, Cls_OnClear);
    HANDLE_MSG(hwnd, WM_UNDO, Cls_OnUndo);
    HANDLE_MSG(hwnd, WM_RENDERALLFORMATS, Cls_OnRenderAllFormats);
    HANDLE_MSG(hwnd, WM_DESTROYCLIPBOARD, Cls_OnDestroyClipboard);
    HANDLE_MSG(hwnd, WM_DRAWCLIPBOARD, Cls_OnDrawClipboard);
    HANDLE_MSG(hwnd, WM_RENDERFORMAT, Cls_OnRenderFormat);
    HANDLE_MSG(hwnd, WM_ASKCBFORMATNAME, Cls_OnAskCBFormatName);
    HANDLE_MSG(hwnd, WM_CHANGECBCHAIN, Cls_OnChangeCBChain);
    HANDLE_MSG(hwnd, WM_HSCROLLCLIPBOARD, Cls_OnHScrollClipboard);
    HANDLE_MSG(hwnd, WM_VSCROLLCLIPBOARD, Cls_OnVScrollClipboard);
    HANDLE_MSG(hwnd, WM_SETCURSOR, Cls_OnSetCursor);
    HANDLE_MSG(hwnd, WM_SYSCOMMAND, Cls_OnSysCommand);
    HANDLE_MSG(hwnd, WM_MDICREATE, Cls_OnMDICreate);
    HANDLE_MSG(hwnd, WM_MDIDESTROY, Cls_OnMDIDestroy);
    HANDLE_MSG(hwnd, WM_MDIACTIVATE, Cls_OnMDIActivate);
    HANDLE_MSG(hwnd, WM_MDIRESTORE, Cls_OnMDIRestore);
    HANDLE_MSG(hwnd, WM_MDINEXT, Cls_OnMDINext);
    HANDLE_MSG(hwnd, WM_MDIMAXIMIZE, Cls_OnMDIMaximize);
    HANDLE_MSG(hwnd, WM_MDITILE, Cls_OnMDITile);
    HANDLE_MSG(hwnd, WM_MDICASCADE, Cls_OnMDICascade);
    HANDLE_MSG(hwnd, WM_MDIICONARRANGE, Cls_OnMDIIconArrange);
    HANDLE_MSG(hwnd, WM_MDIGETACTIVE, Cls_OnMDIGetActive);
    HANDLE_MSG(hwnd, WM_MDISETMENU, Cls_OnMDISetMenu);
    HANDLE_MSG(hwnd, WM_CHILDACTIVATE, Cls_OnChildActivate);
    HANDLE_MSG(hwnd, WM_INITDIALOG, Cls_OnInitDialog);
    HANDLE_MSG(hwnd, WM_NEXTDLGCTL, Cls_OnNextDlgCtl);
    HANDLE_MSG(hwnd, WM_PARENTNOTIFY, Cls_OnParentNotify);
    HANDLE_MSG(hwnd, WM_ENTERIDLE, Cls_OnEnterIdle);
    HANDLE_MSG(hwnd, WM_GETDLGCODE, Cls_OnGetDlgCode);
    HANDLE_MSG(hwnd, WM_CTLCOLOR, Cls_OnCtlColor);
    HANDLE_MSG(hwnd, WM_SETFONT, Cls_OnSetFont);
    HANDLE_MSG(hwnd, WM_GETFONT, Cls_OnGetFont);
    HANDLE_MSG(hwnd, WM_DRAWITEM, Cls_OnDrawItem);
    HANDLE_MSG(hwnd, WM_MEASUREITEM, Cls_OnMeasureItem);
    HANDLE_MSG(hwnd, WM_DELETEITEM, Cls_OnDeleteItem);
    HANDLE_MSG(hwnd, WM_COMPAREITEM, Cls_OnCompareItem);
    HANDLE_MSG(hwnd, WM_VKEYTOITEM, Cls_OnVkeyToItem);
    HANDLE_MSG(hwnd, WM_CHARTOITEM, Cls_OnCharToItem);
    HANDLE_MSG(hwnd, WM_QUEUESYNC, Cls_OnQueueSync);
    HANDLE_MSG(hwnd, WM_COMMNOTIFY, Cls_OnCommNotify);
    HANDLE_MSG(hwnd, WM_DROPFILES, Cls_OnDropFiles);
  }
  return 0;
}

static const UINT messages[] = {
    WM_COMPACTING,
    WM_WININICHANGE,
    WM_SYSCOLORCHANGE,
    WM_QUERYNEWPALETTE,
    WM_PALETTEISCHANGING,
    WM_PALETTECHANGED,
    WM_FONTCHANGE,
    WM_SPOOLERSTATUS,
    WM_DEVMODECHANGE,
    WM_TIMECHANGE,
    WM_POWER,
    WM_QUERYENDSESSION,
    WM_ENDSESSION,
    WM_QUIT,
    WM_SYSTEMERROR,
    WM_CREATE,
    WM_NCCREATE,
    WM_DESTROY,
    WM_NCDESTROY,
    WM_SHOWWINDOW,
    WM_SETREDRAW,
    WM_ENABLE,
    WM_SETTEXT,
    WM_GETTEXT,
    WM_GETTEXTLENGTH,
    WM_WINDOWPOSCHANGING,
    WM_WINDOWPOSCHANGED,
    WM_MOVE,
    WM_SIZE,
    WM_CLOSE,
    WM_QUERYOPEN,
    WM_GETMINMAXINFO,
    WM_PAINT,
    WM_ERASEBKGND,
    WM_ICONERASEBKGND,
    WM_NCPAINT,
    WM_NCCALCSIZE,
    WM_NCHITTEST,
    WM_QUERYDRAGICON,
    WM_ACTIVATE,
    WM_ACTIVATEAPP,
    WM_NCACTIVATE,
    WM_SETFOCUS,
    WM_KILLFOCUS,
    WM_KEYDOWN,
    WM_KEYUP,
    WM_SYSKEYDOWN,
    WM_SYSKEYUP,
    WM_CHAR,
    WM_DEADCHAR,
    WM_SYSCHAR,
    WM_SYSDEADCHAR,
    WM_MOUSEMOVE,
    WM_LBUTTONDOWN,
    WM_LBUTTONDBLCLK,
    WM_LBUTTONUP,
    WM_RBUTTONDOWN,
    WM_RBUTTONDBLCLK,
    WM_RBUTTONUP,
    WM_MBUTTONDOWN,
    WM_MBUTTONDBLCLK,
    WM_MBUTTONUP,
    WM_NCMOUSEMOVE,
    WM_NCLBUTTONDOWN,
    WM_NCLBUTTONDBLCLK,
    WM_NCLBUTTONUP,
    WM_NCRBUTTONDOWN,
    WM_NCRBUTTONDBLCLK,
    WM_NCRBUTTONUP,
    WM_NCMBUTTONDOWN,
    WM_NCMBUTTONDBLCLK,
    WM_NCMBUTTONUP,
    WM_MOUSEACTIVATE,
    WM_CANCELMODE,
    WM_TIMER,
    WM_INITMENU,
    WM_INITMENUPOPUP,
    WM_MENUSELECT,
    WM_MENUCHAR,
    WM_COMMAND,
    WM_HSCROLL,
    WM_VSCROLL,
    WM_CUT,
    WM_COPY,
    WM_PASTE,
    WM_CLEAR,
    WM_UNDO,
    WM_RENDERALLFORMATS,
    WM_DESTROYCLIPBOARD,
    WM_DRAWCLIPBOARD,
    WM_RENDERFORMAT,
    WM_ASKCBFORMATNAME,
    WM_CHANGECBCHAIN,
    WM_HSCROLLCLIPBOARD,
    WM_VSCROLLCLIPBOARD,
    WM_SETCURSOR,
    WM_SYSCOMMAND,
    WM_MDICREATE,
    WM_MDIDESTROY,
    WM_MDIACTIVATE,
    WM_MDIRESTORE,
    WM_MDINEXT,
    WM_MDIMAXIMIZE,
    WM_MDITILE,
    WM_MDICASCADE,
    WM_MDIICONARRANGE,
    WM_MDIGETACTIVE,
    WM_MDISETMENU,
    WM_CHILDACTIVATE,
    WM_INITDIALOG,
    WM_NEXTDLGCTL,
    WM_PARENTNOTIFY,
    WM_ENTERIDLE,
    WM_GETDLGCODE,
    WM_CTLCOLOR,
    WM_SETFONT,
    WM_GETFONT,
    WM_DRAWITEM,
    WM_MEASUREITEM,
    WM_DELETEITEM,
    WM_COMPAREITEM,
    WM_VKEYTOITEM,
    WM_CHARTOITEM,
    WM_QUEUESYNC,
    WM_COMMNOTIFY,
    WM_DROPFILES,
};

static const UINT lossless[] = {
    WM_ACTIVATE,
    WM_CHARTOITEM,
    WM_COMMAND,
    WM_CTLCOLOR,
    WM_HSCROLL,
    WM_INITMENUPOPUP,
    WM_KEYDOWN,
    WM_LBUTTONDBLCLK,
    WM_LBUTTONDOWN,
    WM_MDIACTIVATE,
    WM_MDISETMENU,
    WM_MENUCHAR,
    WM_MENUSELECT,
    WM_MOUSEMOVE,
    WM_NCLBUTTONDBLCLK,
    WM_PARENTNOTIFY,
    WM_SETCURSOR,
    WM_SIZE,
    WM_SYSCOMMAND,
    WM_VKEYTOITEM,
    WM_VSCROLL,
};

/* Every control macro, compiled but not run. */
static void controls(HWND h) {
  char buf[16];
  int tabs[2] = {8, 16};
  int pmin, pmax;
  RECT rc;
  Static_Enable(h, TRUE);
  Static_GetText(h, buf, sizeof buf);
  Static_GetTextLength(h);
  Static_SetText(h, "x");
  Static_SetIcon(h, 0);
  Static_GetIcon(h, 0);
  Button_Enable(h, TRUE);
  Button_GetText(h, buf, sizeof buf);
  Button_GetTextLength(h);
  Button_SetText(h, "x");
  Button_GetCheck(h);
  Button_SetCheck(h, 1);
  Button_GetState(h);
  Button_SetState(h, 1);
  Button_SetStyle(h, BS_CHECKBOX, TRUE);
  Edit_Enable(h, TRUE);
  Edit_GetText(h, buf, sizeof buf);
  Edit_GetTextLength(h);
  Edit_SetText(h, "x");
  Edit_LimitText(h, 10);
  Edit_GetLineCount(h);
  Edit_GetLine(h, 0, buf, sizeof buf);
  Edit_GetRect(h, &rc);
  Edit_SetRect(h, &rc);
  Edit_SetRectNoPaint(h, &rc);
  Edit_GetSel(h);
  Edit_SetSel(h, 0, 1);
  Edit_ReplaceSel(h, "x");
  Edit_GetModify(h);
  Edit_SetModify(h, FALSE);
  Edit_LineFromChar(h, 0);
  Edit_LineIndex(h, 0);
  Edit_LineLength(h, 0);
  Edit_Scroll(h, 1, 0);
  Edit_CanUndo(h);
  Edit_Undo(h);
  Edit_EmptyUndoBuffer(h);
  Edit_SetPasswordChar(h, '*');
  Edit_SetTabStops(h, 2, tabs);
  Edit_FmtLines(h, TRUE);
  Edit_SetHandle(h, Edit_GetHandle(h));
#if WINVER >= 0x030A
  Edit_GetFirstVisibleLine(h);
  Edit_SetReadOnly(h, TRUE);
  Edit_GetPasswordChar(h);
  Edit_SetWordBreakProc(h, Edit_GetWordBreakProc(h));
  ScrollBar_Enable(h, ESB_ENABLE_BOTH);
#endif
  ScrollBar_Show(h, TRUE);
  ScrollBar_SetPos(h, 1, TRUE);
  ScrollBar_GetPos(h);
  ScrollBar_SetRange(h, 0, 10, TRUE);
  ScrollBar_GetRange(h, &pmin, &pmax);
  ListBox_Enable(h, TRUE);
  ListBox_GetCount(h);
  ListBox_ResetContent(h);
  ListBox_AddString(h, "x");
  ListBox_InsertString(h, 0, "x");
  ListBox_AddItemData(h, 1);
  ListBox_InsertItemData(h, 0, 1);
  ListBox_DeleteString(h, 0);
  ListBox_GetTextLen(h, 0);
  ListBox_GetText(h, 0, buf);
  ListBox_GetItemData(h, 0);
  ListBox_SetItemData(h, 0, 1);
  ListBox_FindString(h, -1, "x");
  ListBox_FindItemData(h, -1, 1);
  ListBox_SetSel(h, TRUE, 0);
  ListBox_SelItemRange(h, TRUE, 0, 1);
  ListBox_GetCurSel(h);
  ListBox_SetCurSel(h, 0);
  ListBox_SelectString(h, -1, "x");
  ListBox_SelectItemData(h, -1, 1);
  ListBox_GetSel(h, 0);
  ListBox_GetSelCount(h);
  ListBox_GetTopIndex(h);
  ListBox_GetSelItems(h, 2, tabs);
  ListBox_SetTopIndex(h, 0);
  ListBox_SetColumnWidth(h, 10);
  ListBox_GetHorizontalExtent(h);
  ListBox_SetHorizontalExtent(h, 10);
  ListBox_SetTabStops(h, 2, tabs);
  ListBox_GetItemRect(h, 0, &rc);
  ListBox_SetCaretIndex(h, 0);
  ListBox_GetCaretIndex(h);
  ListBox_Dir(h, 0, "*.*");
#if WINVER >= 0x030A
  ListBox_FindStringExact(h, -1, "x");
  ListBox_SetItemHeight(h, 0, 10);
  ListBox_GetItemHeight(h, 0);
#endif
  ComboBox_Enable(h, TRUE);
  ComboBox_GetText(h, buf, sizeof buf);
  ComboBox_GetTextLength(h);
  ComboBox_SetText(h, "x");
  ComboBox_LimitText(h, 10);
  ComboBox_GetEditSel(h);
  ComboBox_SetEditSel(h, 0, 1);
  ComboBox_GetCount(h);
  ComboBox_ResetContent(h);
  ComboBox_AddString(h, "x");
  ComboBox_InsertString(h, 0, "x");
  ComboBox_AddItemData(h, 1);
  ComboBox_InsertItemData(h, 0, 1);
  ComboBox_DeleteString(h, 0);
  ComboBox_GetLBTextLen(h, 0);
  ComboBox_GetLBText(h, 0, buf);
  ComboBox_GetItemData(h, 0);
  ComboBox_SetItemData(h, 0, 1);
  ComboBox_FindString(h, -1, "x");
  ComboBox_FindItemData(h, -1, 1);
  ComboBox_GetCurSel(h);
  ComboBox_SetCurSel(h, 0);
  ComboBox_SelectString(h, -1, "x");
  ComboBox_SelectItemData(h, -1, 1);
  ComboBox_Dir(h, 0, "*.*");
  ComboBox_ShowDropdown(h, TRUE);
#if WINVER >= 0x030A
  ComboBox_FindStringExact(h, -1, "x");
  ComboBox_GetDroppedState(h);
  ComboBox_GetDroppedControlRect(h, &rc);
  ComboBox_GetItemHeight(h);
  ComboBox_SetItemHeight(h, 10);
  ComboBox_GetExtendedUI(h);
  ComboBox_SetExtendedUI(h, TRUE);
#endif
  SetWindowFont(h, GetWindowFont(h), TRUE);
  SetWindowRedraw(h, TRUE);
  SubclassWindow(h, Record);
#if WINVER >= 0x030A
  MapWindowRect(h, 0, &rc);
#endif
  InsetRect(&rc, 1, 1);
  DeleteFont(SelectFont(0, GetStockFont(SYSTEM_FONT)));
  DeletePen(SelectPen(0, GetStockPen(BLACK_PEN)));
  DeleteBrush(SelectBrush(0, GetStockBrush(WHITE_BRUSH)));
  (void)GetWindowInstance(h);
  (void)GetWindowStyle(h);
#if WINVER >= 0x0200
  (void)GetFirstChild(h);
  (void)GetNextSibling(h);
#endif
  (void)IsRestored(h);
  (void)IsLButtonDown();
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show) {
  unsigned i, j;
  (void)inst;
  (void)prev;
  (void)show;
  if (cmd[0] == '!')
    controls(0);
  for (i = 0; i < sizeof messages / sizeof messages[0]; i++) {
    UINT msg = messages[i];
    WPARAM w;
    LPARAM l;
    lastMsg = 0;
    TestWndProc(0, msg, 0x1234, 0x56789ABCL);
    CHECK(lastMsg == msg);
    if (lastMsg != msg)
      printf("  message 0x%04X\n", msg);
    /* Cracking what was forwarded gives it back. */
    w = lastW;
    l = lastL;
    TestWndProc(0, msg, w, l);
    CHECK(lastW == w && lastL == l);
    if (lastW != w || lastL != l)
      printf("  message 0x%04X\n", msg);
    for (j = 0; j < sizeof lossless / sizeof lossless[0]; j++) {
      if (lossless[j] == msg) {
        CHECK(w == 0x1234 && l == 0x56789ABCL);
        if (w != 0x1234 || l != 0x56789ABCL)
          printf("  message 0x%04X: %04X %08lX\n", msg, w, (unsigned long)l);
      }
    }
  }
  /* A few by hand. */
  CHECK(TestWndProc(0, WM_CREATE, 0, 0) == -1);
  TestWndProc(0, WM_LBUTTONDBLCLK, MK_LBUTTON, MAKELPARAM(-3, 5));
  CHECK(lastMsg == WM_LBUTTONDBLCLK && lastL == MAKELPARAM(-3, 5));
  TestWndProc(0, WM_MENUSELECT, 42, MAKELPARAM(MF_STRING, 0x1111));
  CHECK(lastW == 42 && LOWORD(lastL) == MF_STRING && HIWORD(lastL) == 0x1111);
  if (failures == 0)
    printf("ALL PASSED\n");
  return failures;
}
