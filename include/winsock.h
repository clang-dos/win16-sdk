/* winsock.h: Windows Sockets 1.1 for 16-bit Windows (WINSOCK.DLL, which
 * comes with the network software, and with Windows for Workgroups 3.11).
 * Written for clang-dos from the published Windows Sockets 1.1
 * specification; AGPL-3.0-only, see the win16-sdk LICENSE.
 *
 * The functions are PASCAL FAR, as the specification requires for 16-bit
 * Windows; a SOCKET is 16 bits. */
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#define _INC_WINSOCK

#include <windows.h>
#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;

typedef u_int SOCKET;

/* select() sets. */
#ifndef FD_SETSIZE
#define FD_SETSIZE 64
#endif

typedef struct fd_set {
  u_short fd_count;
  SOCKET fd_array[FD_SETSIZE];
} fd_set;

#if WINVER >= 0x030A
int PASCAL FAR __WSAFDIsSet(SOCKET, fd_set FAR *);
#endif

#define FD_CLR(fd, set)                                                        \
  do {                                                                         \
    u_int __i;                                                                 \
    for (__i = 0; __i < ((fd_set FAR *)(set))->fd_count; __i++) {             \
      if (((fd_set FAR *)(set))->fd_array[__i] == (fd)) {                     \
        while (__i < ((fd_set FAR *)(set))->fd_count - 1) {                   \
          ((fd_set FAR *)(set))->fd_array[__i] =                              \
              ((fd_set FAR *)(set))->fd_array[__i + 1];                       \
          __i++;                                                               \
        }                                                                      \
        ((fd_set FAR *)(set))->fd_count--;                                    \
        break;                                                                 \
      }                                                                        \
    }                                                                          \
  } while (0)

#define FD_SET(fd, set)                                                        \
  do {                                                                         \
    if (((fd_set FAR *)(set))->fd_count < FD_SETSIZE)                         \
      ((fd_set FAR *)(set))->fd_array[((fd_set FAR *)(set))->fd_count++] =    \
          (fd);                                                                \
  } while (0)

#define FD_ZERO(set) (((fd_set FAR *)(set))->fd_count = 0)

#define FD_ISSET(fd, set) __WSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))

struct timeval {
  long tv_sec;
  long tv_usec;
};

#define timerisset(tvp) ((tvp)->tv_sec || (tvp)->tv_usec)
#define timercmp(tvp, uvp, cmp)                                                \
  ((tvp)->tv_sec cmp(uvp)->tv_sec ||                                           \
   (tvp)->tv_sec == (uvp)->tv_sec && (tvp)->tv_usec cmp(uvp)->tv_usec)
#define timerclear(tvp) ((tvp)->tv_sec = (tvp)->tv_usec = 0)

/* ioctlsocket() commands. */
#define IOCPARM_MASK 0x7f
#define IOC_VOID 0x20000000
#define IOC_OUT 0x40000000
#define IOC_IN 0x80000000
#define IOC_INOUT (IOC_IN | IOC_OUT)

#define _IO(x, y) (IOC_VOID | ((long)(x) << 8) | (y))
#define _IOR(x, y, t)                                                          \
  (IOC_OUT | (((long)sizeof(t) & IOCPARM_MASK) << 16) | ((long)(x) << 8) |     \
   (y))
#define _IOW(x, y, t)                                                          \
  (IOC_IN | (((long)sizeof(t) & IOCPARM_MASK) << 16) | ((long)(x) << 8) | (y))

#define FIONREAD _IOR('f', 127, u_long)
#define FIONBIO _IOW('f', 126, u_long)
#define FIOASYNC _IOW('f', 125, u_long)

#define SIOCSHIWAT _IOW('s', 0, u_long)
#define SIOCGHIWAT _IOR('s', 1, u_long)
#define SIOCSLOWAT _IOW('s', 2, u_long)
#define SIOCGLOWAT _IOR('s', 3, u_long)
#define SIOCATMARK _IOR('s', 7, u_long)

/* Database entries. */
struct hostent {
  char FAR *h_name;
  char FAR *FAR *h_aliases;
  short h_addrtype;
  short h_length;
  char FAR *FAR *h_addr_list;
#define h_addr h_addr_list[0]
};

struct netent {
  char FAR *n_name;
  char FAR *FAR *n_aliases;
  short n_addrtype;
  u_long n_net;
};

struct servent {
  char FAR *s_name;
  char FAR *FAR *s_aliases;
  short s_port;
  char FAR *s_proto;
};

struct protoent {
  char FAR *p_name;
  char FAR *FAR *p_aliases;
  short p_proto;
};

/* Protocols and ports. */
#define IPPROTO_IP 0
#define IPPROTO_ICMP 1
#define IPPROTO_GGP 2 /* as in Windows Sockets 1.1 */
#define IPPROTO_TCP 6
#define IPPROTO_PUP 12
#define IPPROTO_UDP 17
#define IPPROTO_IDP 22
#define IPPROTO_ND 77
#define IPPROTO_RAW 255
#define IPPROTO_MAX 256

#define IPPORT_ECHO 7
#define IPPORT_DISCARD 9
#define IPPORT_SYSTAT 11
#define IPPORT_DAYTIME 13
#define IPPORT_NETSTAT 15
#define IPPORT_FTP 21
#define IPPORT_TELNET 23
#define IPPORT_SMTP 25
#define IPPORT_TIMESERVER 37
#define IPPORT_NAMESERVER 42
#define IPPORT_WHOIS 43
#define IPPORT_MTP 57
#define IPPORT_TFTP 69
#define IPPORT_RJE 77
#define IPPORT_FINGER 79
#define IPPORT_TTYLINK 87
#define IPPORT_SUPDUP 95
#define IPPORT_EXECSERVER 512
#define IPPORT_LOGINSERVER 513
#define IPPORT_CMDSERVER 514
#define IPPORT_EFSSERVER 520
#define IPPORT_BIFFUDP 512
#define IPPORT_WHOSERVER 513
#define IPPORT_ROUTESERVER 520
#define IPPORT_RESERVED 1024

#define IMPLINK_IP 155
#define IMPLINK_LOWEXPER 156
#define IMPLINK_HIGHEXPER 158

/* Internet addresses. */
struct in_addr {
  union {
    struct {
      u_char s_b1, s_b2, s_b3, s_b4;
    } S_un_b;
    struct {
      u_short s_w1, s_w2;
    } S_un_w;
    u_long S_addr;
  } S_un;
#define s_addr S_un.S_addr
#define s_host S_un.S_un_b.s_b2
#define s_net S_un.S_un_b.s_b1
#define s_imp S_un.S_un_w.s_w2
#define s_impno S_un.S_un_b.s_b4
#define s_lh S_un.S_un_b.s_b3
};

#define IN_CLASSA(i) (((long)(i)&0x80000000) == 0)
#define IN_CLASSA_NET 0xff000000
#define IN_CLASSA_NSHIFT 24
#define IN_CLASSA_HOST 0x00ffffff
#define IN_CLASSA_MAX 128
#define IN_CLASSB(i) (((long)(i)&0xc0000000) == 0x80000000)
#define IN_CLASSB_NET 0xffff0000
#define IN_CLASSB_NSHIFT 16
#define IN_CLASSB_HOST 0x0000ffff
#define IN_CLASSB_MAX 65536
#define IN_CLASSC(i) (((long)(i)&0xe0000000) == 0xc0000000)
#define IN_CLASSC_NET 0xffffff00
#define IN_CLASSC_NSHIFT 8
#define IN_CLASSC_HOST 0x000000ff

#define INADDR_ANY (u_long)0x00000000
#define INADDR_LOOPBACK 0x7f000001
#define INADDR_BROADCAST (u_long)0xffffffff
#define INADDR_NONE 0xffffffff

struct sockaddr_in {
  short sin_family;
  u_short sin_port;
  struct in_addr sin_addr;
  char sin_zero[8];
};

#define WSADESCRIPTION_LEN 256
#define WSASYS_STATUS_LEN 128

typedef struct WSAData {
  WORD wVersion;
  WORD wHighVersion;
  char szDescription[WSADESCRIPTION_LEN + 1];
  char szSystemStatus[WSASYS_STATUS_LEN + 1];
  unsigned short iMaxSockets;
  unsigned short iMaxUdpDg;
  char FAR *lpVendorInfo;
} WSADATA;
typedef WSADATA FAR *LPWSADATA;

#define IP_OPTIONS 1

#define INVALID_SOCKET (SOCKET)(~0)
#define SOCKET_ERROR (-1)

/* Socket types. */
#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define SOCK_RAW 3
#define SOCK_RDM 4
#define SOCK_SEQPACKET 5

/* Socket options. */
#define SO_DEBUG 0x0001
#define SO_ACCEPTCONN 0x0002
#define SO_REUSEADDR 0x0004
#define SO_KEEPALIVE 0x0008
#define SO_DONTROUTE 0x0010
#define SO_BROADCAST 0x0020
#define SO_USELOOPBACK 0x0040
#define SO_LINGER 0x0080
#define SO_OOBINLINE 0x0100

#define SO_DONTLINGER (u_int)(~SO_LINGER)

#define SO_SNDBUF 0x1001
#define SO_RCVBUF 0x1002
#define SO_SNDLOWAT 0x1003
#define SO_RCVLOWAT 0x1004
#define SO_SNDTIMEO 0x1005
#define SO_RCVTIMEO 0x1006
#define SO_ERROR 0x1007
#define SO_TYPE 0x1008

#define TCP_NODELAY 0x0001

/* Address families. */
#define AF_UNSPEC 0
#define AF_UNIX 1
#define AF_INET 2
#define AF_IMPLINK 3
#define AF_PUP 4
#define AF_CHAOS 5
#define AF_IPX 6
#define AF_NS 6
#define AF_ISO 7
#define AF_OSI AF_ISO
#define AF_ECMA 8
#define AF_DATAKIT 9
#define AF_CCITT 10
#define AF_SNA 11
#define AF_DECnet 12
#define AF_DLI 13
#define AF_LAT 14
#define AF_HYLINK 15
#define AF_APPLETALK 16
#define AF_NETBIOS 17
#define AF_MAX 18

struct sockaddr {
  u_short sa_family;
  char sa_data[14];
};

struct sockproto {
  u_short sp_family;
  u_short sp_protocol;
};

#define PF_UNSPEC AF_UNSPEC
#define PF_UNIX AF_UNIX
#define PF_INET AF_INET
#define PF_IMPLINK AF_IMPLINK
#define PF_PUP AF_PUP
#define PF_CHAOS AF_CHAOS
#define PF_NS AF_NS
#define PF_IPX AF_IPX
#define PF_ISO AF_ISO
#define PF_OSI AF_OSI
#define PF_ECMA AF_ECMA
#define PF_DATAKIT AF_DATAKIT
#define PF_CCITT AF_CCITT
#define PF_SNA AF_SNA
#define PF_DECnet AF_DECnet
#define PF_DLI AF_DLI
#define PF_LAT AF_LAT
#define PF_HYLINK AF_HYLINK
#define PF_APPLETALK AF_APPLETALK
#define PF_MAX AF_MAX

struct linger {
  u_short l_onoff;
  u_short l_linger;
};

#define SOL_SOCKET 0xffff
#define SOMAXCONN 5

#define MSG_OOB 0x1
#define MSG_PEEK 0x2
#define MSG_DONTROUTE 0x4
#define MSG_MAXIOVLEN 16

#define MAXGETHOSTSTRUCT 1024

/* WSAAsyncSelect events. */
#define FD_READ 0x01
#define FD_WRITE 0x02
#define FD_OOB 0x04
#define FD_ACCEPT 0x08
#define FD_CONNECT 0x10
#define FD_CLOSE 0x20

/* Error codes, from WSAGetLastError. */
#define WSABASEERR 10000
#define WSAEINTR (WSABASEERR + 4)
#define WSAEBADF (WSABASEERR + 9)
#define WSAEACCES (WSABASEERR + 13)
#define WSAEFAULT (WSABASEERR + 14)
#define WSAEINVAL (WSABASEERR + 22)
#define WSAEMFILE (WSABASEERR + 24)
#define WSAEWOULDBLOCK (WSABASEERR + 35)
#define WSAEINPROGRESS (WSABASEERR + 36)
#define WSAEALREADY (WSABASEERR + 37)
#define WSAENOTSOCK (WSABASEERR + 38)
#define WSAEDESTADDRREQ (WSABASEERR + 39)
#define WSAEMSGSIZE (WSABASEERR + 40)
#define WSAEPROTOTYPE (WSABASEERR + 41)
#define WSAENOPROTOOPT (WSABASEERR + 42)
#define WSAEPROTONOSUPPORT (WSABASEERR + 43)
#define WSAESOCKTNOSUPPORT (WSABASEERR + 44)
#define WSAEOPNOTSUPP (WSABASEERR + 45)
#define WSAEPFNOSUPPORT (WSABASEERR + 46)
#define WSAEAFNOSUPPORT (WSABASEERR + 47)
#define WSAEADDRINUSE (WSABASEERR + 48)
#define WSAEADDRNOTAVAIL (WSABASEERR + 49)
#define WSAENETDOWN (WSABASEERR + 50)
#define WSAENETUNREACH (WSABASEERR + 51)
#define WSAENETRESET (WSABASEERR + 52)
#define WSAECONNABORTED (WSABASEERR + 53)
#define WSAECONNRESET (WSABASEERR + 54)
#define WSAENOBUFS (WSABASEERR + 55)
#define WSAEISCONN (WSABASEERR + 56)
#define WSAENOTCONN (WSABASEERR + 57)
#define WSAESHUTDOWN (WSABASEERR + 58)
#define WSAETOOMANYREFS (WSABASEERR + 59)
#define WSAETIMEDOUT (WSABASEERR + 60)
#define WSAECONNREFUSED (WSABASEERR + 61)
#define WSAELOOP (WSABASEERR + 62)
#define WSAENAMETOOLONG (WSABASEERR + 63)
#define WSAEHOSTDOWN (WSABASEERR + 64)
#define WSAEHOSTUNREACH (WSABASEERR + 65)
#define WSAENOTEMPTY (WSABASEERR + 66)
#define WSAEPROCLIM (WSABASEERR + 67)
#define WSAEUSERS (WSABASEERR + 68)
#define WSAEDQUOT (WSABASEERR + 69)
#define WSAESTALE (WSABASEERR + 70)
#define WSAEREMOTE (WSABASEERR + 71)
#define WSASYSNOTREADY (WSABASEERR + 91)
#define WSAVERNOTSUPPORTED (WSABASEERR + 92)
#define WSANOTINITIALISED (WSABASEERR + 93)
#define WSAHOST_NOT_FOUND (WSABASEERR + 1001)
#define WSATRY_AGAIN (WSABASEERR + 1002)
#define WSANO_RECOVERY (WSABASEERR + 1003)
#define WSANO_DATA (WSABASEERR + 1004)
#define WSANO_ADDRESS WSANO_DATA

/* The resolver's error names. */
#define h_errno WSAGetLastError()
#define HOST_NOT_FOUND WSAHOST_NOT_FOUND
#define TRY_AGAIN WSATRY_AGAIN
#define NO_RECOVERY WSANO_RECOVERY
#define NO_DATA WSANO_DATA
#define NO_ADDRESS WSANO_ADDRESS

/* Berkeley names for the socket errors; define _WINSOCK_NO_ERRNO to keep
 * them out, if the C library's errno.h has its own. */
#ifndef _WINSOCK_NO_ERRNO
#ifndef EWOULDBLOCK
#define EWOULDBLOCK WSAEWOULDBLOCK
#endif
#ifndef EINPROGRESS
#define EINPROGRESS WSAEINPROGRESS
#endif
#ifndef EALREADY
#define EALREADY WSAEALREADY
#endif
#ifndef ENOTSOCK
#define ENOTSOCK WSAENOTSOCK
#endif
#ifndef EDESTADDRREQ
#define EDESTADDRREQ WSAEDESTADDRREQ
#endif
#ifndef EMSGSIZE
#define EMSGSIZE WSAEMSGSIZE
#endif
#ifndef EPROTOTYPE
#define EPROTOTYPE WSAEPROTOTYPE
#endif
#ifndef ENOPROTOOPT
#define ENOPROTOOPT WSAENOPROTOOPT
#endif
#ifndef EPROTONOSUPPORT
#define EPROTONOSUPPORT WSAEPROTONOSUPPORT
#endif
#ifndef ESOCKTNOSUPPORT
#define ESOCKTNOSUPPORT WSAESOCKTNOSUPPORT
#endif
#ifndef EOPNOTSUPP
#define EOPNOTSUPP WSAEOPNOTSUPP
#endif
#ifndef EPFNOSUPPORT
#define EPFNOSUPPORT WSAEPFNOSUPPORT
#endif
#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT WSAEAFNOSUPPORT
#endif
#ifndef EADDRINUSE
#define EADDRINUSE WSAEADDRINUSE
#endif
#ifndef EADDRNOTAVAIL
#define EADDRNOTAVAIL WSAEADDRNOTAVAIL
#endif
#ifndef ENETDOWN
#define ENETDOWN WSAENETDOWN
#endif
#ifndef ENETUNREACH
#define ENETUNREACH WSAENETUNREACH
#endif
#ifndef ENETRESET
#define ENETRESET WSAENETRESET
#endif
#ifndef ECONNABORTED
#define ECONNABORTED WSAECONNABORTED
#endif
#ifndef ECONNRESET
#define ECONNRESET WSAECONNRESET
#endif
#ifndef ENOBUFS
#define ENOBUFS WSAENOBUFS
#endif
#ifndef EISCONN
#define EISCONN WSAEISCONN
#endif
#ifndef ENOTCONN
#define ENOTCONN WSAENOTCONN
#endif
#ifndef ESHUTDOWN
#define ESHUTDOWN WSAESHUTDOWN
#endif
#ifndef ETOOMANYREFS
#define ETOOMANYREFS WSAETOOMANYREFS
#endif
#ifndef ETIMEDOUT
#define ETIMEDOUT WSAETIMEDOUT
#endif
#ifndef ECONNREFUSED
#define ECONNREFUSED WSAECONNREFUSED
#endif
#ifndef ELOOP
#define ELOOP WSAELOOP
#endif
#ifndef EHOSTDOWN
#define EHOSTDOWN WSAEHOSTDOWN
#endif
#ifndef EHOSTUNREACH
#define EHOSTUNREACH WSAEHOSTUNREACH
#endif
#ifndef EPROCLIM
#define EPROCLIM WSAEPROCLIM
#endif
#ifndef EUSERS
#define EUSERS WSAEUSERS
#endif
#ifndef EDQUOT
#define EDQUOT WSAEDQUOT
#endif
#ifndef ESTALE
#define ESTALE WSAESTALE
#endif
#ifndef EREMOTE
#define EREMOTE WSAEREMOTE
#endif
#endif /* _WINSOCK_NO_ERRNO */

#if WINVER >= 0x030A
/* Berkeley sockets. */
SOCKET PASCAL FAR accept(SOCKET s, struct sockaddr FAR *addr,
                         int FAR *addrlen);
int PASCAL FAR bind(SOCKET s, const struct sockaddr FAR *addr, int namelen);
int PASCAL FAR closesocket(SOCKET s);
int PASCAL FAR connect(SOCKET s, const struct sockaddr FAR *name,
                       int namelen);
int PASCAL FAR ioctlsocket(SOCKET s, long cmd, u_long FAR *argp);
int PASCAL FAR getpeername(SOCKET s, struct sockaddr FAR *name,
                           int FAR *namelen);
int PASCAL FAR getsockname(SOCKET s, struct sockaddr FAR *name,
                           int FAR *namelen);
int PASCAL FAR getsockopt(SOCKET s, int level, int optname,
                          char FAR *optval, int FAR *optlen);
u_long PASCAL FAR htonl(u_long hostlong);
u_short PASCAL FAR htons(u_short hostshort);
unsigned long PASCAL FAR inet_addr(const char FAR *cp);
char FAR *PASCAL FAR inet_ntoa(struct in_addr in);
int PASCAL FAR listen(SOCKET s, int backlog);
u_long PASCAL FAR ntohl(u_long netlong);
u_short PASCAL FAR ntohs(u_short netshort);
int PASCAL FAR recv(SOCKET s, char FAR *buf, int len, int flags);
int PASCAL FAR recvfrom(SOCKET s, char FAR *buf, int len, int flags,
                        struct sockaddr FAR *from, int FAR *fromlen);
int PASCAL FAR select(int nfds, fd_set FAR *readfds, fd_set FAR *writefds,
                      fd_set FAR *exceptfds, const struct timeval FAR *timeout);
int PASCAL FAR send(SOCKET s, const char FAR *buf, int len, int flags);
int PASCAL FAR sendto(SOCKET s, const char FAR *buf, int len, int flags,
                      const struct sockaddr FAR *to, int tolen);
int PASCAL FAR setsockopt(SOCKET s, int level, int optname,
                          const char FAR *optval, int optlen);
int PASCAL FAR shutdown(SOCKET s, int how);
SOCKET PASCAL FAR socket(int af, int type, int protocol);

/* Databases. */
struct hostent FAR *PASCAL FAR gethostbyaddr(const char FAR *addr, int len,
                                             int type);
struct hostent FAR *PASCAL FAR gethostbyname(const char FAR *name);
int PASCAL FAR gethostname(char FAR *name, int namelen);
struct servent FAR *PASCAL FAR getservbyport(int port,
                                             const char FAR *proto);
struct servent FAR *PASCAL FAR getservbyname(const char FAR *name,
                                             const char FAR *proto);
struct protoent FAR *PASCAL FAR getprotobynumber(int proto);
struct protoent FAR *PASCAL FAR getprotobyname(const char FAR *name);

/* Windows extensions. */
int PASCAL FAR WSAStartup(WORD wVersionRequired, LPWSADATA lpWSAData);
int PASCAL FAR WSACleanup(void);
void PASCAL FAR WSASetLastError(int iError);
int PASCAL FAR WSAGetLastError(void);
BOOL PASCAL FAR WSAIsBlocking(void);
int PASCAL FAR WSAUnhookBlockingHook(void);
FARPROC PASCAL FAR WSASetBlockingHook(FARPROC lpBlockFunc);
int PASCAL FAR WSACancelBlockingCall(void);

HANDLE PASCAL FAR WSAAsyncGetServByName(HWND hWnd, u_int wMsg,
                                        const char FAR *name,
                                        const char FAR *proto, char FAR *buf,
                                        int buflen);
HANDLE PASCAL FAR WSAAsyncGetServByPort(HWND hWnd, u_int wMsg, int port,
                                        const char FAR *proto, char FAR *buf,
                                        int buflen);
HANDLE PASCAL FAR WSAAsyncGetProtoByName(HWND hWnd, u_int wMsg,
                                         const char FAR *name, char FAR *buf,
                                         int buflen);
HANDLE PASCAL FAR WSAAsyncGetProtoByNumber(HWND hWnd, u_int wMsg, int number,
                                           char FAR *buf, int buflen);
HANDLE PASCAL FAR WSAAsyncGetHostByName(HWND hWnd, u_int wMsg,
                                        const char FAR *name, char FAR *buf,
                                        int buflen);
HANDLE PASCAL FAR WSAAsyncGetHostByAddr(HWND hWnd, u_int wMsg,
                                        const char FAR *addr, int len,
                                        int type, char FAR *buf, int buflen);
int PASCAL FAR WSACancelAsyncRequest(HANDLE hAsyncTaskHandle);
int PASCAL FAR WSAAsyncSelect(SOCKET s, HWND hWnd, u_int wMsg, long lEvent);
#endif /* WINVER >= 0x030A */

/* Pieces of the WSAAsync* reply message. */
#define WSAMAKEASYNCREPLY(buflen, error) MAKELONG(buflen, error)
#define WSAMAKESELECTREPLY(event, error) MAKELONG(event, error)
#define WSAGETASYNCBUFLEN(lParam) LOWORD(lParam)
#define WSAGETASYNCERROR(lParam) HIWORD(lParam)
#define WSAGETSELECTEVENT(lParam) LOWORD(lParam)
#define WSAGETSELECTERROR(lParam) HIWORD(lParam)

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr *PSOCKADDR;
typedef struct sockaddr FAR *LPSOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in *PSOCKADDR_IN;
typedef struct sockaddr_in FAR *LPSOCKADDR_IN;
typedef struct linger LINGER;
typedef struct linger *PLINGER;
typedef struct linger FAR *LPLINGER;
typedef struct in_addr IN_ADDR;
typedef struct in_addr *PIN_ADDR;
typedef struct in_addr FAR *LPIN_ADDR;
typedef struct fd_set FD_SET;
typedef struct fd_set *PFD_SET;
typedef struct fd_set FAR *LPFD_SET;
typedef struct hostent HOSTENT;
typedef struct hostent *PHOSTENT;
typedef struct hostent FAR *LPHOSTENT;
typedef struct servent SERVENT;
typedef struct servent *PSERVENT;
typedef struct servent FAR *LPSERVENT;
typedef struct protoent PROTOENT;
typedef struct protoent *PPROTOENT;
typedef struct protoent FAR *LPPROTOENT;
typedef struct timeval TIMEVAL;
typedef struct timeval *PTIMEVAL;
typedef struct timeval FAR *LPTIMEVAL;

#ifdef __cplusplus
}
#endif

#pragma pack(pop)
#endif /* _WINSOCKAPI_ */
