/* ddeml.h: the DDE Management Library (DDEML.DLL, Windows 3.1; it can be
 * shipped with programs for 3.0). Written for clang-dos from the published
 * API; BSD 3-Clause, see the win16-sdk LICENSE. */
#ifndef _DDEML_H
#define _DDEML_H
#define _INC_DDEML

#include <windows.h>
#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

/* DDEML handles are 32 bits. */
DECLARE_HANDLE32(HCONVLIST);
DECLARE_HANDLE32(HCONV);
DECLARE_HANDLE32(HSZ);
DECLARE_HANDLE32(HDDEDATA);

typedef struct tagHSZPAIR {
  HSZ hszSvc;
  HSZ hszTopic;
} HSZPAIR;
typedef HSZPAIR FAR *PHSZPAIR;

typedef struct tagCONVCONTEXT {
  UINT cb;
  UINT wFlags;
  UINT wCountryID;
  int iCodePage;
  DWORD dwLangID;
  DWORD dwSecurity;
} CONVCONTEXT;
typedef CONVCONTEXT FAR *PCONVCONTEXT;

typedef struct tagCONVINFO {
  DWORD cb;
  DWORD hUser;
  HCONV hConvPartner;
  HSZ hszSvcPartner;
  HSZ hszServiceReq;
  HSZ hszTopic;
  HSZ hszItem;
  UINT wFmt;
  UINT wType;
  UINT wStatus;
  UINT wConvst;
  UINT wLastError;
  HCONVLIST hConvList;
  CONVCONTEXT ConvCtxt;
} CONVINFO;
typedef CONVINFO FAR *PCONVINFO;

/* Conversation states (wConvst). */
#define XST_NULL 0
#define XST_INCOMPLETE 1
#define XST_CONNECTED 2
#define XST_INIT1 3
#define XST_INIT2 4
#define XST_REQSENT 5
#define XST_DATARCVD 6
#define XST_POKESENT 7
#define XST_POKEACKRCVD 8
#define XST_EXECSENT 9
#define XST_EXECACKRCVD 10
#define XST_ADVSENT 11
#define XST_UNADVSENT 12
#define XST_ADVACKRCVD 13
#define XST_UNADVACKRCVD 14
#define XST_ADVDATASENT 15
#define XST_ADVDATAACKRCVD 16

#define CADV_LATEACK 0xFFFF

/* Conversation status bits (wStatus). */
#define ST_CONNECTED 0x0001
#define ST_ADVISE 0x0002
#define ST_ISLOCAL 0x0004
#define ST_BLOCKED 0x0008
#define ST_CLIENT 0x0010
#define ST_TERMINATED 0x0020
#define ST_INLIST 0x0040
#define ST_BLOCKNEXT 0x0080
#define ST_ISSELF 0x0100

#define DDE_FACK 0x8000
#define DDE_FBUSY 0x4000
#define DDE_FDEFERUPD 0x4000
#define DDE_FACKREQ 0x8000
#define DDE_FRELEASE 0x2000
#define DDE_FREQUESTED 0x1000
#define DDE_FAPPSTATUS 0x00FF
#define DDE_FNOTPROCESSED 0x0000

#define CF_FIRST 1

/* Transaction classes and flags. */
#define XCLASS_MASK 0xFC00
#define XCLASS_BOOL 0x1000
#define XCLASS_DATA 0x2000
#define XCLASS_FLAGS 0x4000
#define XCLASS_NOTIFICATION 0x8000

#define XTYPF_NOBLOCK 0x0002
#define XTYPF_NODATA 0x0004
#define XTYPF_ACKREQ 0x0008

#define XTYP_ERROR (0x0000 | XCLASS_NOTIFICATION | XTYPF_NOBLOCK)
#define XTYP_ADVDATA (0x0010 | XCLASS_FLAGS)
#define XTYP_ADVREQ (0x0020 | XCLASS_DATA | XTYPF_NOBLOCK)
#define XTYP_ADVSTART (0x0030 | XCLASS_BOOL)
#define XTYP_ADVSTOP (0x0040 | XCLASS_NOTIFICATION)
#define XTYP_EXECUTE (0x0050 | XCLASS_FLAGS)
#define XTYP_CONNECT (0x0060 | XCLASS_BOOL | XTYPF_NOBLOCK)
#define XTYP_CONNECT_CONFIRM (0x0070 | XCLASS_NOTIFICATION | XTYPF_NOBLOCK)
#define XTYP_XACT_COMPLETE (0x0080 | XCLASS_NOTIFICATION)
#define XTYP_POKE (0x0090 | XCLASS_FLAGS)
#define XTYP_REGISTER (0x00A0 | XCLASS_NOTIFICATION | XTYPF_NOBLOCK)
#define XTYP_REQUEST (0x00B0 | XCLASS_DATA)
#define XTYP_DISCONNECT (0x00C0 | XCLASS_NOTIFICATION | XTYPF_NOBLOCK)
#define XTYP_UNREGISTER (0x00D0 | XCLASS_NOTIFICATION | XTYPF_NOBLOCK)
#define XTYP_WILDCONNECT (0x00E0 | XCLASS_DATA | XTYPF_NOBLOCK)
#define XTYP_MONITOR (0x00F0 | XCLASS_NOTIFICATION | XTYPF_NOBLOCK)

#define XTYP_MASK 0x00F0
#define XTYP_SHIFT 4

#define TIMEOUT_ASYNC 0xFFFFFFFFL
#define QID_SYNC 0xFFFFFFFFL

/* Standard topic and item strings. */
#define SZDDESYS_TOPIC "System"
#define SZDDESYS_ITEM_TOPICS "Topics"
#define SZDDESYS_ITEM_SYSITEMS "SysItems"
#define SZDDESYS_ITEM_RTNMSG "ReturnMessage"
#define SZDDESYS_ITEM_STATUS "Status"
#define SZDDESYS_ITEM_FORMATS "Formats"
#define SZDDESYS_ITEM_HELP "Help"
#define SZDDE_ITEM_ITEMLIST "TopicItemList"

typedef HDDEDATA CALLBACK FNCALLBACK(UINT wType, UINT wFmt, HCONV hConv,
                                     HSZ hsz1, HSZ hsz2, HDDEDATA hData,
                                     DWORD dwData1, DWORD dwData2);
typedef FNCALLBACK *PFNCALLBACK;

#define CBR_BLOCK 0xFFFFFFFFL

/* DdeInitialize flags. */
#define CBF_FAIL_SELFCONNECTIONS 0x00001000L
#define CBF_FAIL_CONNECTIONS 0x00002000L
#define CBF_FAIL_ADVISES 0x00004000L
#define CBF_FAIL_EXECUTES 0x00008000L
#define CBF_FAIL_POKES 0x00010000L
#define CBF_FAIL_REQUESTS 0x00020000L
#define CBF_FAIL_ALLSVRXACTIONS 0x0003F000L
#define CBF_SKIP_CONNECT_CONFIRMS 0x00040000L
#define CBF_SKIP_REGISTRATIONS 0x00080000L
#define CBF_SKIP_UNREGISTRATIONS 0x00100000L
#define CBF_SKIP_DISCONNECTS 0x00200000L
#define CBF_SKIP_ALLNOTIFICATIONS 0x003C0000L

#define APPCMD_CLIENTONLY 0x00000010L
#define APPCMD_FILTERINITS 0x00000020L
#define APPCMD_MASK 0x00000FF0L

#define APPCLASS_STANDARD 0x00000000L
#define APPCLASS_MONITOR 0x00000001L
#define APPCLASS_MASK 0x0000000FL

#define MF_HSZ_INFO 0x01000000L
#define MF_SENDMSGS 0x02000000L
#define MF_POSTMSGS 0x04000000L
#define MF_CALLBACKS 0x08000000L
#define MF_ERRORS 0x10000000L
#define MF_LINKS 0x20000000L
#define MF_CONV 0x40000000L
#define MF_MASK 0xFF000000L

/* DdeEnableCallback commands. */
#define EC_ENABLEALL 0
#define EC_ENABLEONE ST_BLOCKNEXT
#define EC_DISABLE ST_BLOCKED
#define EC_QUERYWAITING 2

/* DdeNameService flags. */
#define DNS_REGISTER 0x0001
#define DNS_UNREGISTER 0x0002
#define DNS_FILTERON 0x0004
#define DNS_FILTEROFF 0x0008

#define HDATA_APPOWNED 0x0001

/* DdeGetLastError codes. */
#define DMLERR_NO_ERROR 0
#define DMLERR_FIRST 0x4000
#define DMLERR_ADVACKTIMEOUT 0x4000
#define DMLERR_BUSY 0x4001
#define DMLERR_DATAACKTIMEOUT 0x4002
#define DMLERR_DLL_NOT_INITIALIZED 0x4003
#define DMLERR_DLL_USAGE 0x4004
#define DMLERR_EXECACKTIMEOUT 0x4005
#define DMLERR_INVALIDPARAMETER 0x4006
#define DMLERR_LOW_MEMORY 0x4007
#define DMLERR_MEMORY_ERROR 0x4008
#define DMLERR_NOTPROCESSED 0x4009
#define DMLERR_NO_CONV_ESTABLISHED 0x400A
#define DMLERR_POKEACKTIMEOUT 0x400B
#define DMLERR_POSTMSG_FAILED 0x400C
#define DMLERR_REENTRANCY 0x400D
#define DMLERR_SERVER_DIED 0x400E
#define DMLERR_SYS_ERROR 0x400F
#define DMLERR_UNADVACKTIMEOUT 0x4010
#define DMLERR_UNFOUND_QUEUE_ID 0x4011
#define DMLERR_LAST 0x4011

#define CP_WINANSI 1004

#define MH_CREATE 1
#define MH_KEEP 2
#define MH_DELETE 3
#define MH_CLEANUP 4

#define MSGF_DDEMGR 0x8001

/* Monitor structures, passed to an APPCLASS_MONITOR callback. */
typedef struct tagDDEML_MSG_HOOK_DATA {
  UINT uiLo;
  UINT uiHi;
  DWORD cbData;
  DWORD Data[8];
} DDEML_MSG_HOOK_DATA;

typedef struct tagMONMSGSTRUCT {
  UINT cb;
  HWND hwndTo;
  DWORD dwTime;
  HANDLE hTask;
  UINT wMsg;
  WPARAM wParam;
  LPARAM lParam;
  DDEML_MSG_HOOK_DATA dmhd;
} MONMSGSTRUCT;

typedef struct tagMONCBSTRUCT {
  UINT cb;
  WORD wReserved;
  DWORD dwTime;
  HANDLE hTask;
  DWORD dwRet;
  UINT wType;
  UINT wFmt;
  HCONV hConv;
  HSZ hsz1;
  HSZ hsz2;
  HDDEDATA hData;
  DWORD dwData1;
  DWORD dwData2;
} MONCBSTRUCT;

typedef struct tagMONHSZSTRUCT {
  UINT cb;
  BOOL fsAction;
  DWORD dwTime;
  HSZ hsz;
  HANDLE hTask;
  WORD wReserved;
  char str[1];
} MONHSZSTRUCT;

typedef struct tagMONERRSTRUCT {
  UINT cb;
  UINT wLastError;
  DWORD dwTime;
  HANDLE hTask;
} MONERRSTRUCT;

typedef struct tagMONLINKSTRUCT {
  UINT cb;
  DWORD dwTime;
  HANDLE hTask;
  BOOL fEstablished;
  BOOL fNoData;
  HSZ hszSvc;
  HSZ hszTopic;
  HSZ hszItem;
  UINT wFmt;
  BOOL fServer;
  HCONV hConvServer;
  HCONV hConvClient;
} MONLINKSTRUCT;

typedef struct tagMONCONVSTRUCT {
  UINT cb;
  BOOL fConnect;
  DWORD dwTime;
  HANDLE hTask;
  HSZ hszSvc;
  HSZ hszTopic;
  HCONV hConvClient;
  HCONV hConvServer;
} MONCONVSTRUCT;

#if WINVER >= 0x030A
UINT WINAPI DdeInitialize(DWORD FAR *pidInst, PFNCALLBACK pfnCallback,
                          DWORD afCmd, DWORD ulRes);
BOOL WINAPI DdeUninitialize(DWORD idInst);

HCONVLIST WINAPI DdeConnectList(DWORD idInst, HSZ hszService, HSZ hszTopic,
                                HCONVLIST hConvList, CONVCONTEXT FAR *pCC);
HCONV WINAPI DdeQueryNextServer(HCONVLIST hConvList, HCONV hConvPrev);
BOOL WINAPI DdeDisconnectList(HCONVLIST hConvList);

HCONV WINAPI DdeConnect(DWORD idInst, HSZ hszService, HSZ hszTopic,
                        CONVCONTEXT FAR *pCC);
BOOL WINAPI DdeDisconnect(HCONV hConv);
HCONV WINAPI DdeReconnect(HCONV hConv);
UINT WINAPI DdeQueryConvInfo(HCONV hConv, DWORD idTransaction,
                             CONVINFO FAR *pConvInfo);
BOOL WINAPI DdeSetUserHandle(HCONV hConv, DWORD id, DWORD hUser);
BOOL WINAPI DdeAbandonTransaction(DWORD idInst, HCONV hConv,
                                  DWORD idTransaction);

BOOL WINAPI DdePostAdvise(DWORD idInst, HSZ hszTopic, HSZ hszItem);
BOOL WINAPI DdeEnableCallback(DWORD idInst, HCONV hConv, UINT wCmd);
HDDEDATA WINAPI DdeNameService(DWORD idInst, HSZ hsz1, HSZ hszRes,
                               UINT afCmd);

HDDEDATA WINAPI DdeClientTransaction(void FAR *pData, DWORD cbData,
                                     HCONV hConv, HSZ hszItem, UINT wFmt,
                                     UINT wType, DWORD dwTimeout,
                                     DWORD FAR *pdwResult);

HDDEDATA WINAPI DdeCreateDataHandle(DWORD idInst, void FAR *pSrc, DWORD cb,
                                    DWORD cbOff, HSZ hszItem, UINT wFmt,
                                    UINT afCmd);
HDDEDATA WINAPI DdeAddData(HDDEDATA hData, void FAR *pSrc, DWORD cb,
                           DWORD cbOff);
DWORD WINAPI DdeGetData(HDDEDATA hData, void FAR *pDst, DWORD cbMax,
                        DWORD cbOff);
BYTE FAR *WINAPI DdeAccessData(HDDEDATA hData, DWORD FAR *pcbDataSize);
BOOL WINAPI DdeUnaccessData(HDDEDATA hData);
BOOL WINAPI DdeFreeDataHandle(HDDEDATA hData);

UINT WINAPI DdeGetLastError(DWORD idInst);

HSZ WINAPI DdeCreateStringHandle(DWORD idInst, LPCSTR psz, int iCodePage);
DWORD WINAPI DdeQueryString(DWORD idInst, HSZ hsz, LPSTR psz, DWORD cchMax,
                            int iCodePage);
BOOL WINAPI DdeFreeStringHandle(DWORD idInst, HSZ hsz);
BOOL WINAPI DdeKeepStringHandle(DWORD idInst, HSZ hsz);
int WINAPI DdeCmpStringHandles(HSZ hsz1, HSZ hsz2);
#endif /* WINVER >= 0x030A */

#ifdef __cplusplus
}
#endif

#pragma pack(pop)
#endif /* _DDEML_H */
