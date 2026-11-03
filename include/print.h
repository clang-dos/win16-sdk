/* print.h: printer driver settings (the DEVMODE fields, ExtDeviceMode and
 * DeviceCapabilities) and the GDI print spooler. DEVMODE itself is in
 * windows.h. Written for clang-dos from the published API; BSD 3-Clause,
 * see the win16-sdk LICENSE. */
#ifndef _PRINT_H
#define _PRINT_H
#define _INC_PRINT

#include <windows.h>
#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

/* DEVMODE.dmSpecVersion for Windows 3.1 drivers. */
#define DM_SPECVERSION 0x030A

/* DEVMODE.dmFields */
#define DM_ORIENTATION 0x0000001L
#define DM_PAPERSIZE 0x0000002L
#define DM_PAPERLENGTH 0x0000004L
#define DM_PAPERWIDTH 0x0000008L
#define DM_SCALE 0x0000010L
#define DM_COPIES 0x0000100L
#define DM_DEFAULTSOURCE 0x0000200L
#define DM_PRINTQUALITY 0x0000400L
#define DM_COLOR 0x0000800L
#define DM_DUPLEX 0x0001000L
#define DM_YRESOLUTION 0x0002000L
#define DM_TTOPTION 0x0004000L

#define DMORIENT_PORTRAIT 1
#define DMORIENT_LANDSCAPE 2

#define DMPAPER_FIRST DMPAPER_LETTER
#define DMPAPER_LETTER 1
#define DMPAPER_LETTERSMALL 2
#define DMPAPER_TABLOID 3
#define DMPAPER_LEDGER 4
#define DMPAPER_LEGAL 5
#define DMPAPER_STATEMENT 6
#define DMPAPER_EXECUTIVE 7
#define DMPAPER_A3 8
#define DMPAPER_A4 9
#define DMPAPER_A4SMALL 10
#define DMPAPER_A5 11
#define DMPAPER_B4 12
#define DMPAPER_B5 13
#define DMPAPER_FOLIO 14
#define DMPAPER_QUARTO 15
#define DMPAPER_10X14 16
#define DMPAPER_11X17 17
#define DMPAPER_NOTE 18
#define DMPAPER_ENV_9 19
#define DMPAPER_ENV_10 20
#define DMPAPER_ENV_11 21
#define DMPAPER_ENV_12 22
#define DMPAPER_ENV_14 23
#define DMPAPER_CSHEET 24
#define DMPAPER_DSHEET 25
#define DMPAPER_ESHEET 26
#define DMPAPER_ENV_DL 27
#define DMPAPER_ENV_C5 28
#define DMPAPER_ENV_C3 29
#define DMPAPER_ENV_C4 30
#define DMPAPER_ENV_C6 31
#define DMPAPER_ENV_C65 32
#define DMPAPER_ENV_B4 33
#define DMPAPER_ENV_B5 34
#define DMPAPER_ENV_B6 35
#define DMPAPER_ENV_ITALY 36
#define DMPAPER_ENV_MONARCH 37
#define DMPAPER_ENV_PERSONAL 38
#define DMPAPER_FANFOLD_US 39
#define DMPAPER_FANFOLD_STD_GERMAN 40
#define DMPAPER_FANFOLD_LGL_GERMAN 41
#define DMPAPER_LAST DMPAPER_FANFOLD_LGL_GERMAN
#define DMPAPER_USER 256

#define DMBIN_FIRST DMBIN_UPPER
#define DMBIN_UPPER 1
#define DMBIN_ONLYONE 1
#define DMBIN_LOWER 2
#define DMBIN_MIDDLE 3
#define DMBIN_MANUAL 4
#define DMBIN_ENVELOPE 5
#define DMBIN_ENVMANUAL 6
#define DMBIN_AUTO 7
#define DMBIN_TRACTOR 8
#define DMBIN_SMALLFMT 9
#define DMBIN_LARGEFMT 10
#define DMBIN_LARGECAPACITY 11
#define DMBIN_CASSETTE 14
#define DMBIN_LAST DMBIN_CASSETTE
#define DMBIN_USER 256

#define DMRES_DRAFT (-1)
#define DMRES_LOW (-2)
#define DMRES_MEDIUM (-3)
#define DMRES_HIGH (-4)

#define DMCOLOR_MONOCHROME 1
#define DMCOLOR_COLOR 2

#define DMDUP_SIMPLEX 1
#define DMDUP_VERTICAL 2
#define DMDUP_HORIZONTAL 3

#define DMTT_BITMAP 1
#define DMTT_DOWNLOAD 2
#define DMTT_SUBDEV 3

/* ExtDeviceMode modes. */
#define DM_UPDATE 1
#define DM_COPY 2
#define DM_PROMPT 4
#define DM_MODIFY 8
#define DM_IN_BUFFER DM_MODIFY
#define DM_IN_PROMPT DM_PROMPT
#define DM_OUT_BUFFER DM_COPY
#define DM_OUT_DEFAULT DM_UPDATE

/* DeviceCapabilities indexes. */
#define DC_FIELDS 1
#define DC_PAPERS 2
#define DC_PAPERSIZE 3
#define DC_MINEXTENT 4
#define DC_MAXEXTENT 5
#define DC_BINS 6
#define DC_DUPLEX 7
#define DC_SIZE 8
#define DC_EXTRA 9
#define DC_VERSION 10
#define DC_DRIVER 11
#define DC_BINNAMES 12
#define DC_ENUMRESOLUTIONS 13
#define DC_FILEDEPENDENCIES 14
#define DC_TRUETYPE 15
#define DC_PAPERNAMES 16
#define DC_ORIENTATION 17
#define DC_COPIES 18

#define DCTT_BITMAP 0x0000001L
#define DCTT_DOWNLOAD 0x0000002L
#define DCTT_SUBDEV 0x0000004L

/* The printer driver's own entry points, found with GetProcAddress:
 * "ExtDeviceMode", "DeviceCapabilities", and for 3.0 drivers
 * "DeviceMode". */
typedef UINT(CALLBACK *LPFNDEVMODE)(HWND, HMODULE, LPDEVMODE, LPSTR, LPSTR,
                                    LPDEVMODE, LPSTR, UINT);
typedef DWORD(CALLBACK *LPFNDEVCAPS)(LPSTR, LPSTR, UINT, LPSTR, LPDEVMODE);
typedef void(CALLBACK *LPFNOLDDEVMODE)(HWND, HMODULE, LPSTR, LPSTR);

#define PROC_EXTDEVICEMODE MAKEINTRESOURCE(90)
#define PROC_DEVICECAPABILITIES MAKEINTRESOURCE(91)
#define PROC_OLDDEVICEMODE MAKEINTRESOURCE(13)

/* The spooler, used by printer drivers. */
typedef HANDLE HPJOB;

/* The SP_* error codes are in windows.h. */

HPJOB WINAPI OpenJob(LPSTR lpOutput, LPSTR lpTitle, HDC hDC);
int WINAPI StartSpoolPage(HPJOB hJob);
int WINAPI EndSpoolPage(HPJOB hJob);
int WINAPI WriteSpool(HPJOB hJob, LPSTR lpData, int cch);
int WINAPI CloseJob(HPJOB hJob);
int WINAPI DeleteJob(HPJOB hJob, int nDummy);
int WINAPI WriteDialog(HPJOB hJob, LPSTR lpMsg, int nFlags);
DWORD WINAPI GetSpoolJob(int nOption, LPSTR lpData);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)
#endif /* _PRINT_H */
