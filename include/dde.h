/* dde.h: the messages and data structures of dynamic data exchange.
 * Written for clang-dos from the published API; AGPL-3.0-only, see the
 * win16-sdk LICENSE. */
#ifndef _DDE_H
#define _DDE_H
#define _INC_DDE

#include <windows.h>
#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

#define WM_DDE_FIRST 0x03E0
#define WM_DDE_INITIATE (WM_DDE_FIRST)
#define WM_DDE_TERMINATE (WM_DDE_FIRST + 1)
#define WM_DDE_ADVISE (WM_DDE_FIRST + 2)
#define WM_DDE_UNADVISE (WM_DDE_FIRST + 3)
#define WM_DDE_ACK (WM_DDE_FIRST + 4)
#define WM_DDE_DATA (WM_DDE_FIRST + 5)
#define WM_DDE_REQUEST (WM_DDE_FIRST + 6)
#define WM_DDE_POKE (WM_DDE_FIRST + 7)
#define WM_DDE_EXECUTE (WM_DDE_FIRST + 8)
#define WM_DDE_LAST (WM_DDE_FIRST + 8)

typedef struct tagDDEACK {
  WORD bAppReturnCode : 8;
  WORD reserved : 6;
  WORD fBusy : 1;
  WORD fAck : 1;
} DDEACK;

typedef struct tagDDEADVISE {
  WORD reserved : 14;
  WORD fDeferUpd : 1;
  WORD fAckReq : 1;
  short cfFormat;
} DDEADVISE;

typedef struct tagDDEDATA {
  WORD unused : 12;
  WORD fResponse : 1;
  WORD fRelease : 1;
  WORD reserved : 1;
  WORD fAckReq : 1;
  short cfFormat;
  BYTE Value[1];
} DDEDATA;

typedef struct tagDDEPOKE {
  WORD unused : 13;
  WORD fRelease : 1;
  WORD fReserved : 2;
  short cfFormat;
  BYTE Value[1];
} DDEPOKE;

#ifdef __cplusplus
}
#endif

#pragma pack(pop)
#endif /* _DDE_H */
