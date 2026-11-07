/* mmsystem.h: the multimedia API (MMSYSTEM.DLL, Windows 3.1 and the
 * Multimedia Extensions for 3.0): sound, waveform audio, MIDI, auxiliary
 * audio, timers, joysticks, RIFF file I/O and the Media Control Interface.
 * Written for clang-dos from the published API; AGPL-3.0-only, see the
 * win16-sdk LICENSE.
 *
 * Define MMNOSOUND, MMNOWAVE, MMNOMIDI, MMNOAUX, MMNOTIMER, MMNOJOY,
 * MMNOMMIO or MMNOMCI to leave a part out. */
#ifndef _MMSYSTEM_H
#define _MMSYSTEM_H
#define _INC_MMSYSTEM

#include <windows.h>
#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

/* General types. */
#define MAXPNAMELEN 32
#define MAXERRORLENGTH 128

typedef WORD VERSION;
typedef UINT MMRESULT;
typedef UINT FAR *LPUINT;

typedef struct mmtime_tag {
  UINT wType;
  union {
    DWORD ms;
    DWORD sample;
    DWORD cb;
    struct {
      BYTE hour;
      BYTE min;
      BYTE sec;
      BYTE frame;
      BYTE fps;
      BYTE dummy;
    } smpte;
    struct {
      DWORD songptrpos;
    } midi;
  } u;
} MMTIME;
typedef MMTIME *PMMTIME;
typedef MMTIME NEAR *NPMMTIME;
typedef MMTIME FAR *LPMMTIME;

#define TIME_MS 0x0001
#define TIME_SAMPLES 0x0002
#define TIME_BYTES 0x0004
#define TIME_SMPTE 0x0008
#define TIME_MIDI 0x0010

/* Window messages sent by the multimedia system. */
#define MM_JOY1MOVE 0x3A0
#define MM_JOY2MOVE 0x3A1
#define MM_JOY1ZMOVE 0x3A2
#define MM_JOY2ZMOVE 0x3A3
#define MM_JOY1BUTTONDOWN 0x3B5
#define MM_JOY2BUTTONDOWN 0x3B6
#define MM_JOY1BUTTONUP 0x3B7
#define MM_JOY2BUTTONUP 0x3B8
#define MM_MCINOTIFY 0x3B9
#define MM_WOM_OPEN 0x3BB
#define MM_WOM_CLOSE 0x3BC
#define MM_WOM_DONE 0x3BD
#define MM_WIM_OPEN 0x3BE
#define MM_WIM_CLOSE 0x3BF
#define MM_WIM_DATA 0x3C0
#define MM_MIM_OPEN 0x3C1
#define MM_MIM_CLOSE 0x3C2
#define MM_MIM_DATA 0x3C3
#define MM_MIM_LONGDATA 0x3C4
#define MM_MIM_ERROR 0x3C5
#define MM_MIM_LONGERROR 0x3C6
#define MM_MOM_OPEN 0x3C7
#define MM_MOM_CLOSE 0x3C8
#define MM_MOM_DONE 0x3C9

/* Error codes. */
#define MMSYSERR_BASE 0
#define WAVERR_BASE 32
#define MIDIERR_BASE 64
#define TIMERR_BASE 96
#define JOYERR_BASE 160
#define MCIERR_BASE 256

#define MCI_STRING_OFFSET 512
#define MCI_VD_OFFSET 1024
#define MCI_CD_OFFSET 1088
#define MCI_WAVE_OFFSET 1152
#define MCI_SEQ_OFFSET 1216

#define MMSYSERR_NOERROR 0
#define MMSYSERR_ERROR (MMSYSERR_BASE + 1)
#define MMSYSERR_BADDEVICEID (MMSYSERR_BASE + 2)
#define MMSYSERR_NOTENABLED (MMSYSERR_BASE + 3)
#define MMSYSERR_ALLOCATED (MMSYSERR_BASE + 4)
#define MMSYSERR_INVALHANDLE (MMSYSERR_BASE + 5)
#define MMSYSERR_NODRIVER (MMSYSERR_BASE + 6)
#define MMSYSERR_NOMEM (MMSYSERR_BASE + 7)
#define MMSYSERR_NOTSUPPORTED (MMSYSERR_BASE + 8)
#define MMSYSERR_BADERRNUM (MMSYSERR_BASE + 9)
#define MMSYSERR_INVALFLAG (MMSYSERR_BASE + 10)
#define MMSYSERR_INVALPARAM (MMSYSERR_BASE + 11)
#define MMSYSERR_LASTERROR (MMSYSERR_BASE + 11)

#ifndef MMNODRV
#define CALLBACK_TYPEMASK 0x00070000L
#define CALLBACK_NULL 0x00000000L
#define CALLBACK_WINDOW 0x00010000L
#define CALLBACK_TASK 0x00020000L
#define CALLBACK_FUNCTION 0x00030000L

typedef void(CALLBACK DRVCALLBACK)(HDRVR h, UINT uMessage, DWORD dwUser,
                                   DWORD dw1, DWORD dw2);
typedef DRVCALLBACK FAR *LPDRVCALLBACK;
#endif

/* Manufacturer and product IDs. */
#define MM_MICROSOFT 1
#define MM_MIDI_MAPPER 1
#define MM_WAVE_MAPPER 2
#define MM_SNDBLST_MIDIOUT 3
#define MM_SNDBLST_MIDIIN 4
#define MM_SNDBLST_SYNTH 5
#define MM_SNDBLST_WAVEOUT 6
#define MM_SNDBLST_WAVEIN 7
#define MM_ADLIB 9
#define MM_MPU401_MIDIOUT 10
#define MM_MPU401_MIDIIN 11
#define MM_PC_JOYSTICK 12

#if WINVER >= 0x030A
UINT WINAPI mmsystemGetVersion(void);
void WINAPI OutputDebugStr(LPCSTR);
#endif

/****************************************************************************
 * Sound
 ****************************************************************************/
#ifndef MMNOSOUND
#define SND_SYNC 0x0000
#define SND_ASYNC 0x0001
#define SND_NODEFAULT 0x0002
#define SND_MEMORY 0x0004
#define SND_LOOP 0x0008
#define SND_NOSTOP 0x0010

#if WINVER >= 0x030A
BOOL WINAPI sndPlaySound(LPCSTR lpszSoundName, UINT uFlags);
#endif
#endif /* MMNOSOUND */

/****************************************************************************
 * Waveform audio
 ****************************************************************************/
#ifndef MMNOWAVE
#define WAVERR_BADFORMAT (WAVERR_BASE + 0)
#define WAVERR_STILLPLAYING (WAVERR_BASE + 1)
#define WAVERR_UNPREPARED (WAVERR_BASE + 2)
#define WAVERR_SYNC (WAVERR_BASE + 3)
#define WAVERR_LASTERROR (WAVERR_BASE + 3)

DECLARE_HANDLE(HWAVE);
DECLARE_HANDLE(HWAVEIN);
DECLARE_HANDLE(HWAVEOUT);
typedef HWAVEIN FAR *LPHWAVEIN;
typedef HWAVEOUT FAR *LPHWAVEOUT;
typedef DRVCALLBACK WAVECALLBACK;
typedef WAVECALLBACK FAR *LPWAVECALLBACK;

#define WOM_OPEN MM_WOM_OPEN
#define WOM_CLOSE MM_WOM_CLOSE
#define WOM_DONE MM_WOM_DONE
#define WIM_OPEN MM_WIM_OPEN
#define WIM_CLOSE MM_WIM_CLOSE
#define WIM_DATA MM_WIM_DATA

#define WAVE_MAPPER (-1)
#define WAVE_FORMAT_QUERY 0x0001
#define WAVE_ALLOWSYNC 0x0002

typedef struct wavehdr_tag {
  LPSTR lpData;
  DWORD dwBufferLength;
  DWORD dwBytesRecorded;
  DWORD dwUser;
  DWORD dwFlags;
  DWORD dwLoops;
  struct wavehdr_tag FAR *lpNext;
  DWORD reserved;
} WAVEHDR;
typedef WAVEHDR *PWAVEHDR;
typedef WAVEHDR NEAR *NPWAVEHDR;
typedef WAVEHDR FAR *LPWAVEHDR;

#define WHDR_DONE 0x00000001
#define WHDR_PREPARED 0x00000002
#define WHDR_BEGINLOOP 0x00000004
#define WHDR_ENDLOOP 0x00000008
#define WHDR_INQUEUE 0x00000010

typedef struct waveoutcaps_tag {
  UINT wMid;
  UINT wPid;
  VERSION vDriverVersion;
  char szPname[MAXPNAMELEN];
  DWORD dwFormats;
  UINT wChannels;
  DWORD dwSupport;
} WAVEOUTCAPS;
typedef WAVEOUTCAPS *PWAVEOUTCAPS;
typedef WAVEOUTCAPS NEAR *NPWAVEOUTCAPS;
typedef WAVEOUTCAPS FAR *LPWAVEOUTCAPS;

#define WAVECAPS_PITCH 0x0001
#define WAVECAPS_PLAYBACKRATE 0x0002
#define WAVECAPS_VOLUME 0x0004
#define WAVECAPS_LRVOLUME 0x0008
#define WAVECAPS_SYNC 0x0010

typedef struct waveincaps_tag {
  UINT wMid;
  UINT wPid;
  VERSION vDriverVersion;
  char szPname[MAXPNAMELEN];
  DWORD dwFormats;
  UINT wChannels;
} WAVEINCAPS;
typedef WAVEINCAPS *PWAVEINCAPS;
typedef WAVEINCAPS NEAR *NPWAVEINCAPS;
typedef WAVEINCAPS FAR *LPWAVEINCAPS;

#define WAVE_INVALIDFORMAT 0x00000000
#define WAVE_FORMAT_1M08 0x00000001
#define WAVE_FORMAT_1S08 0x00000002
#define WAVE_FORMAT_1M16 0x00000004
#define WAVE_FORMAT_1S16 0x00000008
#define WAVE_FORMAT_2M08 0x00000010
#define WAVE_FORMAT_2S08 0x00000020
#define WAVE_FORMAT_2M16 0x00000040
#define WAVE_FORMAT_2S16 0x00000080
#define WAVE_FORMAT_4M08 0x00000100
#define WAVE_FORMAT_4S08 0x00000200
#define WAVE_FORMAT_4M16 0x00000400
#define WAVE_FORMAT_4S16 0x00000800

typedef struct waveformat_tag {
  WORD wFormatTag;
  WORD nChannels;
  DWORD nSamplesPerSec;
  DWORD nAvgBytesPerSec;
  WORD nBlockAlign;
} WAVEFORMAT;
typedef WAVEFORMAT *PWAVEFORMAT;
typedef WAVEFORMAT NEAR *NPWAVEFORMAT;
typedef WAVEFORMAT FAR *LPWAVEFORMAT;

#define WAVE_FORMAT_PCM 1

typedef struct pcmwaveformat_tag {
  WAVEFORMAT wf;
  WORD wBitsPerSample;
} PCMWAVEFORMAT;
typedef PCMWAVEFORMAT *PPCMWAVEFORMAT;
typedef PCMWAVEFORMAT NEAR *NPPCMWAVEFORMAT;
typedef PCMWAVEFORMAT FAR *LPPCMWAVEFORMAT;

#if WINVER >= 0x030A
UINT WINAPI waveOutGetNumDevs(void);
UINT WINAPI waveOutGetDevCaps(UINT uDeviceID, WAVEOUTCAPS FAR *lpCaps,
                              UINT uSize);
UINT WINAPI waveOutGetVolume(UINT uDeviceID, DWORD FAR *lpdwVolume);
UINT WINAPI waveOutSetVolume(UINT uDeviceID, DWORD dwVolume);
UINT WINAPI waveOutGetErrorText(UINT uError, LPSTR lpText, UINT uSize);
UINT WINAPI waveOutOpen(HWAVEOUT FAR *lphWaveOut, UINT uDeviceID,
                        const WAVEFORMAT FAR *lpFormat, DWORD dwCallback,
                        DWORD dwInstance, DWORD dwFlags);
UINT WINAPI waveOutClose(HWAVEOUT hWaveOut);
UINT WINAPI waveOutPrepareHeader(HWAVEOUT hWaveOut, WAVEHDR FAR *lpWaveOutHdr,
                                 UINT uSize);
UINT WINAPI waveOutUnprepareHeader(HWAVEOUT hWaveOut,
                                   WAVEHDR FAR *lpWaveOutHdr, UINT uSize);
UINT WINAPI waveOutWrite(HWAVEOUT hWaveOut, WAVEHDR FAR *lpWaveOutHdr,
                         UINT uSize);
UINT WINAPI waveOutPause(HWAVEOUT hWaveOut);
UINT WINAPI waveOutRestart(HWAVEOUT hWaveOut);
UINT WINAPI waveOutReset(HWAVEOUT hWaveOut);
UINT WINAPI waveOutBreakLoop(HWAVEOUT hWaveOut);
UINT WINAPI waveOutGetPosition(HWAVEOUT hWaveOut, MMTIME FAR *lpInfo,
                               UINT uSize);
UINT WINAPI waveOutGetPitch(HWAVEOUT hWaveOut, DWORD FAR *lpdwPitch);
UINT WINAPI waveOutSetPitch(HWAVEOUT hWaveOut, DWORD dwPitch);
UINT WINAPI waveOutGetPlaybackRate(HWAVEOUT hWaveOut, DWORD FAR *lpdwRate);
UINT WINAPI waveOutSetPlaybackRate(HWAVEOUT hWaveOut, DWORD dwRate);
UINT WINAPI waveOutGetID(HWAVEOUT hWaveOut, UINT FAR *lpuDeviceID);
DWORD WINAPI waveOutMessage(HWAVEOUT hWaveOut, UINT uMessage, DWORD dw1,
                            DWORD dw2);

UINT WINAPI waveInGetNumDevs(void);
UINT WINAPI waveInGetDevCaps(UINT uDeviceID, WAVEINCAPS FAR *lpCaps,
                             UINT uSize);
UINT WINAPI waveInGetErrorText(UINT uError, LPSTR lpText, UINT uSize);
UINT WINAPI waveInOpen(HWAVEIN FAR *lphWaveIn, UINT uDeviceID,
                       const WAVEFORMAT FAR *lpFormat, DWORD dwCallback,
                       DWORD dwInstance, DWORD dwFlags);
UINT WINAPI waveInClose(HWAVEIN hWaveIn);
UINT WINAPI waveInPrepareHeader(HWAVEIN hWaveIn, WAVEHDR FAR *lpWaveInHdr,
                                UINT uSize);
UINT WINAPI waveInUnprepareHeader(HWAVEIN hWaveIn, WAVEHDR FAR *lpWaveInHdr,
                                  UINT uSize);
UINT WINAPI waveInAddBuffer(HWAVEIN hWaveIn, WAVEHDR FAR *lpWaveInHdr,
                            UINT uSize);
UINT WINAPI waveInStart(HWAVEIN hWaveIn);
UINT WINAPI waveInStop(HWAVEIN hWaveIn);
UINT WINAPI waveInReset(HWAVEIN hWaveIn);
UINT WINAPI waveInGetPosition(HWAVEIN hWaveIn, MMTIME FAR *lpInfo,
                              UINT uSize);
UINT WINAPI waveInGetID(HWAVEIN hWaveIn, UINT FAR *lpuDeviceID);
DWORD WINAPI waveInMessage(HWAVEIN hWaveIn, UINT uMessage, DWORD dw1,
                           DWORD dw2);
#endif
#endif /* MMNOWAVE */

/****************************************************************************
 * MIDI
 ****************************************************************************/
#ifndef MMNOMIDI
#define MIDIERR_UNPREPARED (MIDIERR_BASE + 0)
#define MIDIERR_STILLPLAYING (MIDIERR_BASE + 1)
#define MIDIERR_NOMAP (MIDIERR_BASE + 2)
#define MIDIERR_NOTREADY (MIDIERR_BASE + 3)
#define MIDIERR_NODEVICE (MIDIERR_BASE + 4)
#define MIDIERR_INVALIDSETUP (MIDIERR_BASE + 5)
#define MIDIERR_LASTERROR (MIDIERR_BASE + 5)

DECLARE_HANDLE(HMIDI);
DECLARE_HANDLE(HMIDIIN);
DECLARE_HANDLE(HMIDIOUT);
typedef HMIDIIN FAR *LPHMIDIIN;
typedef HMIDIOUT FAR *LPHMIDIOUT;
typedef DRVCALLBACK MIDICALLBACK;
typedef MIDICALLBACK FAR *LPMIDICALLBACK;

#define MIDIPATCHSIZE 128
typedef WORD PATCHARRAY[MIDIPATCHSIZE];
typedef WORD FAR *LPPATCHARRAY;
typedef WORD KEYARRAY[MIDIPATCHSIZE];
typedef WORD FAR *LPKEYARRAY;

#define MIM_OPEN MM_MIM_OPEN
#define MIM_CLOSE MM_MIM_CLOSE
#define MIM_DATA MM_MIM_DATA
#define MIM_LONGDATA MM_MIM_LONGDATA
#define MIM_ERROR MM_MIM_ERROR
#define MIM_LONGERROR MM_MIM_LONGERROR
#define MOM_OPEN MM_MOM_OPEN
#define MOM_CLOSE MM_MOM_CLOSE
#define MOM_DONE MM_MOM_DONE

#define MIDIMAPPER (-1)
#define MIDI_MAPPER (-1)

#define MIDI_CACHE_ALL 1
#define MIDI_CACHE_BESTFIT 2
#define MIDI_CACHE_QUERY 3
#define MIDI_UNCACHE 4

typedef struct midioutcaps_tag {
  UINT wMid;
  UINT wPid;
  VERSION vDriverVersion;
  char szPname[MAXPNAMELEN];
  UINT wTechnology;
  UINT wVoices;
  UINT wNotes;
  UINT wChannelMask;
  DWORD dwSupport;
} MIDIOUTCAPS;
typedef MIDIOUTCAPS *PMIDIOUTCAPS;
typedef MIDIOUTCAPS NEAR *NPMIDIOUTCAPS;
typedef MIDIOUTCAPS FAR *LPMIDIOUTCAPS;

#define MOD_MIDIPORT 1
#define MOD_SYNTH 2
#define MOD_SQSYNTH 3
#define MOD_FMSYNTH 4
#define MOD_MAPPER 5

#define MIDICAPS_VOLUME 0x0001
#define MIDICAPS_LRVOLUME 0x0002
#define MIDICAPS_CACHE 0x0004

typedef struct midiincaps_tag {
  UINT wMid;
  UINT wPid;
  VERSION vDriverVersion;
  char szPname[MAXPNAMELEN];
} MIDIINCAPS;
typedef MIDIINCAPS *PMIDIINCAPS;
typedef MIDIINCAPS NEAR *NPMIDIINCAPS;
typedef MIDIINCAPS FAR *LPMIDIINCAPS;

typedef struct midihdr_tag {
  LPSTR lpData;
  DWORD dwBufferLength;
  DWORD dwBytesRecorded;
  DWORD dwUser;
  DWORD dwFlags;
  struct midihdr_tag FAR *lpNext;
  DWORD reserved;
} MIDIHDR;
typedef MIDIHDR *PMIDIHDR;
typedef MIDIHDR NEAR *NPMIDIHDR;
typedef MIDIHDR FAR *LPMIDIHDR;

#define MHDR_DONE 0x00000001
#define MHDR_PREPARED 0x00000002
#define MHDR_INQUEUE 0x00000004

#if WINVER >= 0x030A
UINT WINAPI midiOutGetNumDevs(void);
UINT WINAPI midiOutGetDevCaps(UINT uDeviceID, MIDIOUTCAPS FAR *lpCaps,
                              UINT uSize);
UINT WINAPI midiOutGetVolume(UINT uDeviceID, DWORD FAR *lpdwVolume);
UINT WINAPI midiOutSetVolume(UINT uDeviceID, DWORD dwVolume);
UINT WINAPI midiOutGetErrorText(UINT uError, LPSTR lpText, UINT uSize);
UINT WINAPI midiOutOpen(HMIDIOUT FAR *lphMidiOut, UINT uDeviceID,
                        DWORD dwCallback, DWORD dwInstance, DWORD dwFlags);
UINT WINAPI midiOutClose(HMIDIOUT hMidiOut);
UINT WINAPI midiOutPrepareHeader(HMIDIOUT hMidiOut, MIDIHDR FAR *lpMidiOutHdr,
                                 UINT uSize);
UINT WINAPI midiOutUnprepareHeader(HMIDIOUT hMidiOut,
                                   MIDIHDR FAR *lpMidiOutHdr, UINT uSize);
UINT WINAPI midiOutShortMsg(HMIDIOUT hMidiOut, DWORD dwMsg);
UINT WINAPI midiOutLongMsg(HMIDIOUT hMidiOut, MIDIHDR FAR *lpMidiOutHdr,
                           UINT uSize);
UINT WINAPI midiOutReset(HMIDIOUT hMidiOut);
UINT WINAPI midiOutCachePatches(HMIDIOUT hMidiOut, UINT uBank,
                                WORD FAR *lpwPatchArray, UINT uFlags);
UINT WINAPI midiOutCacheDrumPatches(HMIDIOUT hMidiOut, UINT uPatch,
                                    WORD FAR *lpwKeyArray, UINT uFlags);
UINT WINAPI midiOutGetID(HMIDIOUT hMidiOut, UINT FAR *lpuDeviceID);
DWORD WINAPI midiOutMessage(HMIDIOUT hMidiOut, UINT uMessage, DWORD dw1,
                            DWORD dw2);

UINT WINAPI midiInGetNumDevs(void);
UINT WINAPI midiInGetDevCaps(UINT uDeviceID, MIDIINCAPS FAR *lpCaps,
                             UINT uSize);
UINT WINAPI midiInGetErrorText(UINT uError, LPSTR lpText, UINT uSize);
UINT WINAPI midiInOpen(HMIDIIN FAR *lphMidiIn, UINT uDeviceID,
                       DWORD dwCallback, DWORD dwInstance, DWORD dwFlags);
UINT WINAPI midiInClose(HMIDIIN hMidiIn);
UINT WINAPI midiInPrepareHeader(HMIDIIN hMidiIn, MIDIHDR FAR *lpMidiInHdr,
                                UINT uSize);
UINT WINAPI midiInUnprepareHeader(HMIDIIN hMidiIn, MIDIHDR FAR *lpMidiInHdr,
                                  UINT uSize);
UINT WINAPI midiInAddBuffer(HMIDIIN hMidiIn, MIDIHDR FAR *lpMidiInHdr,
                            UINT uSize);
UINT WINAPI midiInStart(HMIDIIN hMidiIn);
UINT WINAPI midiInStop(HMIDIIN hMidiIn);
UINT WINAPI midiInReset(HMIDIIN hMidiIn);
UINT WINAPI midiInGetID(HMIDIIN hMidiIn, UINT FAR *lpuDeviceID);
DWORD WINAPI midiInMessage(HMIDIIN hMidiIn, UINT uMessage, DWORD dw1,
                           DWORD dw2);
#endif
#endif /* MMNOMIDI */

/****************************************************************************
 * Auxiliary audio
 ****************************************************************************/
#ifndef MMNOAUX
#define AUX_MAPPER (-1)

typedef struct auxcaps_tag {
  UINT wMid;
  UINT wPid;
  VERSION vDriverVersion;
  char szPname[MAXPNAMELEN];
  UINT wTechnology;
  DWORD dwSupport;
} AUXCAPS;
typedef AUXCAPS *PAUXCAPS;
typedef AUXCAPS NEAR *NPAUXCAPS;
typedef AUXCAPS FAR *LPAUXCAPS;

#define AUXCAPS_CDAUDIO 1
#define AUXCAPS_AUXIN 2

#define AUXCAPS_VOLUME 0x0001
#define AUXCAPS_LRVOLUME 0x0002

#if WINVER >= 0x030A
UINT WINAPI auxGetNumDevs(void);
UINT WINAPI auxGetDevCaps(UINT uDeviceID, AUXCAPS FAR *lpCaps, UINT uSize);
UINT WINAPI auxSetVolume(UINT uDeviceID, DWORD dwVolume);
UINT WINAPI auxGetVolume(UINT uDeviceID, DWORD FAR *lpdwVolume);
DWORD WINAPI auxOutMessage(UINT uDeviceID, UINT uMessage, DWORD dw1,
                           DWORD dw2);
#endif
#endif /* MMNOAUX */

/****************************************************************************
 * Timers
 ****************************************************************************/
#ifndef MMNOTIMER
#define TIMERR_NOERROR 0
#define TIMERR_NOCANDO (TIMERR_BASE + 1)
#define TIMERR_STRUCT (TIMERR_BASE + 33)

typedef void(CALLBACK TIMECALLBACK)(UINT uTimerID, UINT uMessage,
                                    DWORD dwUser, DWORD dw1, DWORD dw2);
typedef TIMECALLBACK FAR *LPTIMECALLBACK;

#define TIME_ONESHOT 0
#define TIME_PERIODIC 1

typedef struct timecaps_tag {
  UINT wPeriodMin;
  UINT wPeriodMax;
} TIMECAPS;
typedef TIMECAPS *PTIMECAPS;
typedef TIMECAPS NEAR *NPTIMECAPS;
typedef TIMECAPS FAR *LPTIMECAPS;

#if WINVER >= 0x030A
UINT WINAPI timeGetSystemTime(MMTIME FAR *lpTime, UINT uSize);
DWORD WINAPI timeGetTime(void);
UINT WINAPI timeSetEvent(UINT uDelay, UINT uResolution,
                         LPTIMECALLBACK lpFunction, DWORD dwUser,
                         UINT uFlags);
UINT WINAPI timeKillEvent(UINT uId);
UINT WINAPI timeGetDevCaps(TIMECAPS FAR *lpTimeCaps, UINT uSize);
UINT WINAPI timeBeginPeriod(UINT uPeriod);
UINT WINAPI timeEndPeriod(UINT uPeriod);
#endif
#endif /* MMNOTIMER */

/****************************************************************************
 * Joysticks
 ****************************************************************************/
#ifndef MMNOJOY
#define JOYERR_NOERROR 0
#define JOYERR_PARMS (JOYERR_BASE + 5)
#define JOYERR_NOCANDO (JOYERR_BASE + 6)
#define JOYERR_UNPLUGGED (JOYERR_BASE + 7)

#define JOY_BUTTON1 0x0001
#define JOY_BUTTON2 0x0002
#define JOY_BUTTON3 0x0004
#define JOY_BUTTON4 0x0008
#define JOY_BUTTON1CHG 0x0100
#define JOY_BUTTON2CHG 0x0200
#define JOY_BUTTON3CHG 0x0400
#define JOY_BUTTON4CHG 0x0800

#define JOYSTICKID1 0
#define JOYSTICKID2 1

typedef struct joycaps_tag {
  UINT wMid;
  UINT wPid;
  char szPname[MAXPNAMELEN];
  UINT wXmin;
  UINT wXmax;
  UINT wYmin;
  UINT wYmax;
  UINT wZmin;
  UINT wZmax;
  UINT wNumButtons;
  UINT wPeriodMin;
  UINT wPeriodMax;
} JOYCAPS;
typedef JOYCAPS *PJOYCAPS;
typedef JOYCAPS NEAR *NPJOYCAPS;
typedef JOYCAPS FAR *LPJOYCAPS;

typedef struct joyinfo_tag {
  UINT wXpos;
  UINT wYpos;
  UINT wZpos;
  UINT wButtons;
} JOYINFO;
typedef JOYINFO *PJOYINFO;
typedef JOYINFO NEAR *NPJOYINFO;
typedef JOYINFO FAR *LPJOYINFO;

#if WINVER >= 0x030A
UINT WINAPI joyGetDevCaps(UINT uJoyID, JOYCAPS FAR *lpCaps, UINT uSize);
UINT WINAPI joyGetNumDevs(void);
UINT WINAPI joyGetPos(UINT uJoyID, JOYINFO FAR *lpInfo);
UINT WINAPI joyGetThreshold(UINT uJoyID, UINT FAR *lpuThreshold);
UINT WINAPI joyReleaseCapture(UINT uJoyID);
UINT WINAPI joySetCapture(HWND hwnd, UINT uJoyID, UINT uPeriod,
                          BOOL bChanged);
UINT WINAPI joySetThreshold(UINT uJoyID, UINT uThreshold);
#endif
#endif /* MMNOJOY */

/****************************************************************************
 * RIFF file I/O
 ****************************************************************************/
#ifndef MMNOMMIO
#define MMIOERR_BASE 256
#define MMIOERR_FILENOTFOUND (MMIOERR_BASE + 1)
#define MMIOERR_OUTOFMEMORY (MMIOERR_BASE + 2)
#define MMIOERR_CANNOTOPEN (MMIOERR_BASE + 3)
#define MMIOERR_CANNOTCLOSE (MMIOERR_BASE + 4)
#define MMIOERR_CANNOTREAD (MMIOERR_BASE + 5)
#define MMIOERR_CANNOTWRITE (MMIOERR_BASE + 6)
#define MMIOERR_CANNOTSEEK (MMIOERR_BASE + 7)
#define MMIOERR_CANNOTEXPAND (MMIOERR_BASE + 8)
#define MMIOERR_CHUNKNOTFOUND (MMIOERR_BASE + 9)
#define MMIOERR_UNBUFFERED (MMIOERR_BASE + 10)

#define CFSEPCHAR '+'

typedef DWORD FOURCC;
DECLARE_HANDLE(HMMIO);
typedef LRESULT(CALLBACK MMIOPROC)(LPSTR lpmmioinfo, UINT uMessage,
                                   LPARAM lParam1, LPARAM lParam2);
typedef MMIOPROC FAR *LPMMIOPROC;

typedef struct _MMIOINFO {
  DWORD dwFlags;
  FOURCC fccIOProc;
  LPMMIOPROC pIOProc;
  UINT wErrorRet;
  HTASK htask;
  LONG cchBuffer;
  HPSTR pchBuffer;
  HPSTR pchNext;
  HPSTR pchEndRead;
  HPSTR pchEndWrite;
  LONG lBufOffset;
  LONG lDiskOffset;
  DWORD adwInfo[3];
  DWORD dwReserved1;
  DWORD dwReserved2;
  HMMIO hmmio;
} MMIOINFO;
typedef MMIOINFO *PMMIOINFO;
typedef MMIOINFO NEAR *NPMMIOINFO;
typedef MMIOINFO FAR *LPMMIOINFO;

typedef struct _MMCKINFO {
  FOURCC ckid;
  DWORD cksize;
  FOURCC fccType;
  DWORD dwDataOffset;
  DWORD dwFlags;
} MMCKINFO;
typedef MMCKINFO *PMMCKINFO;
typedef MMCKINFO NEAR *NPMMCKINFO;
typedef MMCKINFO FAR *LPMMCKINFO;

#define MMIO_RWMODE 0x00000003
#define MMIO_SHAREMODE 0x00000070
#define MMIO_CREATE 0x00001000
#define MMIO_PARSE 0x00000100
#define MMIO_DELETE 0x00000200
#define MMIO_EXIST 0x00004000
#define MMIO_ALLOCBUF 0x00010000
#define MMIO_GETTEMP 0x00020000
#define MMIO_DIRTY 0x10000000

#define MMIO_READ 0x00000000
#define MMIO_WRITE 0x00000001
#define MMIO_READWRITE 0x00000002

#define MMIO_COMPAT 0x00000000
#define MMIO_EXCLUSIVE 0x00000010
#define MMIO_DENYWRITE 0x00000020
#define MMIO_DENYREAD 0x00000030
#define MMIO_DENYNONE 0x00000040

#define MMIO_FHOPEN 0x0010
#define MMIO_EMPTYBUF 0x0010
#define MMIO_TOUPPER 0x0010
#define MMIO_INSTALLPROC 0x00010000
#define MMIO_PUBLICPROC 0x10000000
#define MMIO_UNICODEPROC 0x01000000
#define MMIO_REMOVEPROC 0x00020000
#define MMIO_FINDPROC 0x00040000
#define MMIO_FINDCHUNK 0x0010
#define MMIO_FINDRIFF 0x0020
#define MMIO_FINDLIST 0x0040
#define MMIO_CREATERIFF 0x0020
#define MMIO_CREATELIST 0x0040

#define MMIOM_READ MMIO_READ
#define MMIOM_WRITE MMIO_WRITE
#define MMIOM_SEEK 2
#define MMIOM_OPEN 3
#define MMIOM_CLOSE 4
#define MMIOM_WRITEFLUSH 5
#define MMIOM_RENAME 6
#define MMIOM_USER 0x8000

#define mmioFOURCC(ch0, ch1, ch2, ch3)                                         \
  ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |                            \
   ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24))

#define FOURCC_RIFF mmioFOURCC('R', 'I', 'F', 'F')
#define FOURCC_LIST mmioFOURCC('L', 'I', 'S', 'T')
#define FOURCC_DOS mmioFOURCC('D', 'O', 'S', ' ')
#define FOURCC_MEM mmioFOURCC('M', 'E', 'M', ' ')

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define MMIO_DEFAULTBUFFER 8192

#if WINVER >= 0x030A
FOURCC WINAPI mmioStringToFOURCC(LPCSTR sz, UINT uFlags);
LPMMIOPROC WINAPI mmioInstallIOProc(FOURCC fccIOProc, LPMMIOPROC pIOProc,
                                    DWORD dwFlags);
HMMIO WINAPI mmioOpen(LPSTR szFileName, MMIOINFO FAR *lpmmioinfo,
                      DWORD dwOpenFlags);
UINT WINAPI mmioClose(HMMIO hmmio, UINT uFlags);
LONG WINAPI mmioRead(HMMIO hmmio, HPSTR pch, LONG cch);
LONG WINAPI mmioWrite(HMMIO hmmio, const char __huge *pch, LONG cch);
LONG WINAPI mmioSeek(HMMIO hmmio, LONG lOffset, int iOrigin);
UINT WINAPI mmioGetInfo(HMMIO hmmio, MMIOINFO FAR *lpmmioinfo, UINT uFlags);
UINT WINAPI mmioSetInfo(HMMIO hmmio, const MMIOINFO FAR *lpmmioinfo,
                        UINT uFlags);
UINT WINAPI mmioSetBuffer(HMMIO hmmio, LPSTR pchBuffer, LONG cchBuffer,
                          UINT uFlags);
UINT WINAPI mmioFlush(HMMIO hmmio, UINT uFlags);
UINT WINAPI mmioAdvance(HMMIO hmmio, MMIOINFO FAR *lpmmioinfo, UINT uFlags);
LRESULT WINAPI mmioSendMessage(HMMIO hmmio, UINT uMessage, LPARAM lParam1,
                               LPARAM lParam2);
UINT WINAPI mmioDescend(HMMIO hmmio, MMCKINFO FAR *lpck,
                        const MMCKINFO FAR *lpckParent, UINT uFlags);
UINT WINAPI mmioAscend(HMMIO hmmio, MMCKINFO FAR *lpck, UINT uFlags);
UINT WINAPI mmioCreateChunk(HMMIO hmmio, MMCKINFO FAR *lpck, UINT uFlags);
#endif
#endif /* MMNOMMIO */

/****************************************************************************
 * Media Control Interface
 ****************************************************************************/
#ifndef MMNOMCI
typedef UINT(CALLBACK *YIELDPROC)(UINT uDeviceID, DWORD dwYieldData);

#if WINVER >= 0x030A
DWORD WINAPI mciSendCommand(UINT uDeviceID, UINT uMessage, DWORD dwParam1,
                            DWORD dwParam2);
DWORD WINAPI mciSendString(LPCSTR lpstrCommand, LPSTR lpstrReturnString,
                           UINT uReturnLength, HWND hwndCallback);
UINT WINAPI mciGetDeviceID(LPCSTR lpstrName);
UINT WINAPI mciGetDeviceIDFromElementID(DWORD dwElementID,
                                        LPCSTR lpstrType);
BOOL WINAPI mciGetErrorString(DWORD wError, LPSTR lpstrBuffer, UINT uLength);
BOOL WINAPI mciSetYieldProc(UINT uDeviceID, YIELDPROC fpYieldProc,
                            DWORD dwYieldData);
HTASK WINAPI mciGetCreatorTask(UINT uDeviceID);
YIELDPROC WINAPI mciGetYieldProc(UINT uDeviceID, DWORD FAR *lpdwYieldData);
BOOL WINAPI mciExecute(LPCSTR lpstrCommand);
#endif

#define MCIERR_INVALID_DEVICE_ID (MCIERR_BASE + 1)
#define MCIERR_UNRECOGNIZED_KEYWORD (MCIERR_BASE + 3)
#define MCIERR_UNRECOGNIZED_COMMAND (MCIERR_BASE + 5)
#define MCIERR_HARDWARE (MCIERR_BASE + 6)
#define MCIERR_INVALID_DEVICE_NAME (MCIERR_BASE + 7)
#define MCIERR_OUT_OF_MEMORY (MCIERR_BASE + 8)
#define MCIERR_DEVICE_OPEN (MCIERR_BASE + 9)
#define MCIERR_CANNOT_LOAD_DRIVER (MCIERR_BASE + 10)
#define MCIERR_MISSING_COMMAND_STRING (MCIERR_BASE + 11)
#define MCIERR_PARAM_OVERFLOW (MCIERR_BASE + 12)
#define MCIERR_MISSING_STRING_ARGUMENT (MCIERR_BASE + 13)
#define MCIERR_BAD_INTEGER (MCIERR_BASE + 14)
#define MCIERR_PARSER_INTERNAL (MCIERR_BASE + 15)
#define MCIERR_DRIVER_INTERNAL (MCIERR_BASE + 16)
#define MCIERR_MISSING_PARAMETER (MCIERR_BASE + 17)
#define MCIERR_UNSUPPORTED_FUNCTION (MCIERR_BASE + 18)
#define MCIERR_FILE_NOT_FOUND (MCIERR_BASE + 19)
#define MCIERR_DEVICE_NOT_READY (MCIERR_BASE + 20)
#define MCIERR_INTERNAL (MCIERR_BASE + 21)
#define MCIERR_DRIVER (MCIERR_BASE + 22)
#define MCIERR_CANNOT_USE_ALL (MCIERR_BASE + 23)
#define MCIERR_MULTIPLE (MCIERR_BASE + 24)
#define MCIERR_EXTENSION_NOT_FOUND (MCIERR_BASE + 25)
#define MCIERR_OUTOFRANGE (MCIERR_BASE + 26)
#define MCIERR_FLAGS_NOT_COMPATIBLE (MCIERR_BASE + 28)
#define MCIERR_FILE_NOT_SAVED (MCIERR_BASE + 30)
#define MCIERR_DEVICE_TYPE_REQUIRED (MCIERR_BASE + 31)
#define MCIERR_DEVICE_LOCKED (MCIERR_BASE + 32)
#define MCIERR_DUPLICATE_ALIAS (MCIERR_BASE + 33)
#define MCIERR_BAD_CONSTANT (MCIERR_BASE + 34)
#define MCIERR_MUST_USE_SHAREABLE (MCIERR_BASE + 35)
#define MCIERR_MISSING_DEVICE_NAME (MCIERR_BASE + 36)
#define MCIERR_BAD_TIME_FORMAT (MCIERR_BASE + 37)
#define MCIERR_NO_CLOSING_QUOTE (MCIERR_BASE + 38)
#define MCIERR_DUPLICATE_FLAGS (MCIERR_BASE + 39)
#define MCIERR_INVALID_FILE (MCIERR_BASE + 40)
#define MCIERR_NULL_PARAMETER_BLOCK (MCIERR_BASE + 41)
#define MCIERR_UNNAMED_RESOURCE (MCIERR_BASE + 42)
#define MCIERR_NEW_REQUIRES_ALIAS (MCIERR_BASE + 43)
#define MCIERR_NOTIFY_ON_AUTO_OPEN (MCIERR_BASE + 44)
#define MCIERR_NO_ELEMENT_ALLOWED (MCIERR_BASE + 45)
#define MCIERR_NONAPPLICABLE_FUNCTION (MCIERR_BASE + 46)
#define MCIERR_ILLEGAL_FOR_AUTO_OPEN (MCIERR_BASE + 47)
#define MCIERR_FILENAME_REQUIRED (MCIERR_BASE + 48)
#define MCIERR_EXTRA_CHARACTERS (MCIERR_BASE + 49)
#define MCIERR_DEVICE_NOT_INSTALLED (MCIERR_BASE + 50)
#define MCIERR_GET_CD (MCIERR_BASE + 51)
#define MCIERR_SET_CD (MCIERR_BASE + 52)
#define MCIERR_SET_DRIVE (MCIERR_BASE + 53)
#define MCIERR_DEVICE_LENGTH (MCIERR_BASE + 54)
#define MCIERR_DEVICE_ORD_LENGTH (MCIERR_BASE + 55)
#define MCIERR_NO_INTEGER (MCIERR_BASE + 56)

#define MCIERR_WAVE_OUTPUTSINUSE (MCIERR_BASE + 64)
#define MCIERR_WAVE_SETOUTPUTINUSE (MCIERR_BASE + 65)
#define MCIERR_WAVE_INPUTSINUSE (MCIERR_BASE + 66)
#define MCIERR_WAVE_SETINPUTINUSE (MCIERR_BASE + 67)
#define MCIERR_WAVE_OUTPUTUNSPECIFIED (MCIERR_BASE + 68)
#define MCIERR_WAVE_INPUTUNSPECIFIED (MCIERR_BASE + 69)
#define MCIERR_WAVE_OUTPUTSUNSUITABLE (MCIERR_BASE + 70)
#define MCIERR_WAVE_SETOUTPUTUNSUITABLE (MCIERR_BASE + 71)
#define MCIERR_WAVE_INPUTSUNSUITABLE (MCIERR_BASE + 72)
#define MCIERR_WAVE_SETINPUTUNSUITABLE (MCIERR_BASE + 73)

#define MCIERR_SEQ_DIV_INCOMPATIBLE (MCIERR_BASE + 80)
#define MCIERR_SEQ_PORT_INUSE (MCIERR_BASE + 81)
#define MCIERR_SEQ_PORT_NONEXISTENT (MCIERR_BASE + 82)
#define MCIERR_SEQ_PORT_MAPNODEVICE (MCIERR_BASE + 83)
#define MCIERR_SEQ_PORT_MISCERROR (MCIERR_BASE + 84)
#define MCIERR_SEQ_TIMER (MCIERR_BASE + 85)
#define MCIERR_SEQ_PORTUNSPECIFIED (MCIERR_BASE + 86)
#define MCIERR_SEQ_NOMIDIPRESENT (MCIERR_BASE + 87)

#define MCIERR_NO_WINDOW (MCIERR_BASE + 90)
#define MCIERR_CREATEWINDOW (MCIERR_BASE + 91)
#define MCIERR_FILE_READ (MCIERR_BASE + 92)
#define MCIERR_FILE_WRITE (MCIERR_BASE + 93)

#define MCIERR_CUSTOM_DRIVER_BASE (MCIERR_BASE + 256)

/* Commands. */
#define MCI_OPEN 0x0803
#define MCI_CLOSE 0x0804
#define MCI_ESCAPE 0x0805
#define MCI_PLAY 0x0806
#define MCI_SEEK 0x0807
#define MCI_STOP 0x0808
#define MCI_PAUSE 0x0809
#define MCI_INFO 0x080A
#define MCI_GETDEVCAPS 0x080B
#define MCI_SPIN 0x080C
#define MCI_SET 0x080D
#define MCI_STEP 0x080E
#define MCI_RECORD 0x080F
#define MCI_SYSINFO 0x0810
#define MCI_BREAK 0x0811
#define MCI_SOUND 0x0812
#define MCI_SAVE 0x0813
#define MCI_STATUS 0x0814
#define MCI_CUE 0x0830
#define MCI_REALIZE 0x0840
#define MCI_WINDOW 0x0841
#define MCI_PUT 0x0842
#define MCI_WHERE 0x0843
#define MCI_FREEZE 0x0844
#define MCI_UNFREEZE 0x0845
#define MCI_LOAD 0x0850
#define MCI_CUT 0x0851
#define MCI_COPY 0x0852
#define MCI_PASTE 0x0853
#define MCI_UPDATE 0x0854
#define MCI_RESUME 0x0855
#define MCI_DELETE 0x0856

#define MCI_USER_MESSAGES (0x400 + DRV_MCI_FIRST)
#define DRV_MCI_FIRST DRV_RESERVED
#define DRV_MCI_LAST (DRV_RESERVED + 0xFFF)

#define MCI_ALL_DEVICE_ID 0xFFFF

/* Device types. */
#define MCI_DEVTYPE_VCR (MCI_STRING_OFFSET + 1)
#define MCI_DEVTYPE_VIDEODISC (MCI_STRING_OFFSET + 2)
#define MCI_DEVTYPE_OVERLAY (MCI_STRING_OFFSET + 3)
#define MCI_DEVTYPE_CD_AUDIO (MCI_STRING_OFFSET + 4)
#define MCI_DEVTYPE_DAT (MCI_STRING_OFFSET + 5)
#define MCI_DEVTYPE_SCANNER (MCI_STRING_OFFSET + 6)
#define MCI_DEVTYPE_ANIMATION (MCI_STRING_OFFSET + 7)
#define MCI_DEVTYPE_DIGITAL_VIDEO (MCI_STRING_OFFSET + 8)
#define MCI_DEVTYPE_OTHER (MCI_STRING_OFFSET + 9)
#define MCI_DEVTYPE_WAVEFORM_AUDIO (MCI_STRING_OFFSET + 10)
#define MCI_DEVTYPE_SEQUENCER (MCI_STRING_OFFSET + 11)
#define MCI_DEVTYPE_FIRST MCI_DEVTYPE_VCR
#define MCI_DEVTYPE_LAST MCI_DEVTYPE_SEQUENCER

/* Modes. */
#define MCI_MODE_NOT_READY (MCI_STRING_OFFSET + 12)
#define MCI_MODE_STOP (MCI_STRING_OFFSET + 13)
#define MCI_MODE_PLAY (MCI_STRING_OFFSET + 14)
#define MCI_MODE_RECORD (MCI_STRING_OFFSET + 15)
#define MCI_MODE_SEEK (MCI_STRING_OFFSET + 16)
#define MCI_MODE_PAUSE (MCI_STRING_OFFSET + 17)
#define MCI_MODE_OPEN (MCI_STRING_OFFSET + 18)

/* Time formats. */
#define MCI_FORMAT_MILLISECONDS 0
#define MCI_FORMAT_HMS 1
#define MCI_FORMAT_MSF 2
#define MCI_FORMAT_FRAMES 3
#define MCI_FORMAT_SMPTE_24 4
#define MCI_FORMAT_SMPTE_25 5
#define MCI_FORMAT_SMPTE_30 6
#define MCI_FORMAT_SMPTE_30DROP 7
#define MCI_FORMAT_BYTES 8
#define MCI_FORMAT_SAMPLES 9
#define MCI_FORMAT_TMSF 10

#define MCI_MSF_MINUTE(msf) ((BYTE)(msf))
#define MCI_MSF_SECOND(msf) ((BYTE)(((WORD)(msf)) >> 8))
#define MCI_MSF_FRAME(msf) ((BYTE)((msf) >> 16))
#define MCI_MAKE_MSF(m, s, f)                                                  \
  ((DWORD)(((BYTE)(m) | ((WORD)(s) << 8)) | (((DWORD)(BYTE)(f)) << 16)))
#define MCI_TMSF_TRACK(tmsf) ((BYTE)(tmsf))
#define MCI_TMSF_MINUTE(tmsf) ((BYTE)(((WORD)(tmsf)) >> 8))
#define MCI_TMSF_SECOND(tmsf) ((BYTE)((tmsf) >> 16))
#define MCI_TMSF_FRAME(tmsf) ((BYTE)((tmsf) >> 24))
#define MCI_MAKE_TMSF(t, m, s, f)                                              \
  ((DWORD)(((BYTE)(t) | ((WORD)(m) << 8)) |                                    \
           (((DWORD)(BYTE)(s) | ((WORD)(f) << 8)) << 16)))
#define MCI_HMS_HOUR(hms) ((BYTE)(hms))
#define MCI_HMS_MINUTE(hms) ((BYTE)(((WORD)(hms)) >> 8))
#define MCI_HMS_SECOND(hms) ((BYTE)((hms) >> 16))
#define MCI_MAKE_HMS(h, m, s)                                                  \
  ((DWORD)(((BYTE)(h) | ((WORD)(m) << 8)) | (((DWORD)(BYTE)(s)) << 16)))

/* MM_MCINOTIFY wParam. */
#define MCI_NOTIFY_SUCCESSFUL 0x0001
#define MCI_NOTIFY_SUPERSEDED 0x0002
#define MCI_NOTIFY_ABORTED 0x0004
#define MCI_NOTIFY_FAILURE 0x0008

/* Flags common to all commands. */
#define MCI_NOTIFY 0x00000001L
#define MCI_WAIT 0x00000002L
#define MCI_FROM 0x00000004L
#define MCI_TO 0x00000008L
#define MCI_TRACK 0x00000010L

#define MCI_OPEN_SHAREABLE 0x00000100L
#define MCI_OPEN_ELEMENT 0x00000200L
#define MCI_OPEN_ALIAS 0x00000400L
#define MCI_OPEN_ELEMENT_ID 0x00000800L
#define MCI_OPEN_TYPE_ID 0x00001000L
#define MCI_OPEN_TYPE 0x00002000L

#define MCI_SEEK_TO_START 0x00000100L
#define MCI_SEEK_TO_END 0x00000200L

#define MCI_STATUS_ITEM 0x00000100L
#define MCI_STATUS_START 0x00000200L

#define MCI_STATUS_LENGTH 0x00000001L
#define MCI_STATUS_POSITION 0x00000002L
#define MCI_STATUS_NUMBER_OF_TRACKS 0x00000003L
#define MCI_STATUS_MODE 0x00000004L
#define MCI_STATUS_MEDIA_PRESENT 0x00000005L
#define MCI_STATUS_TIME_FORMAT 0x00000006L
#define MCI_STATUS_READY 0x00000007L
#define MCI_STATUS_CURRENT_TRACK 0x00000008L

#define MCI_INFO_PRODUCT 0x00000100L
#define MCI_INFO_FILE 0x00000200L

#define MCI_GETDEVCAPS_ITEM 0x00000100L

#define MCI_GETDEVCAPS_CAN_RECORD 0x00000001L
#define MCI_GETDEVCAPS_HAS_AUDIO 0x00000002L
#define MCI_GETDEVCAPS_HAS_VIDEO 0x00000003L
#define MCI_GETDEVCAPS_DEVICE_TYPE 0x00000004L
#define MCI_GETDEVCAPS_USES_FILES 0x00000005L
#define MCI_GETDEVCAPS_COMPOUND_DEVICE 0x00000006L
#define MCI_GETDEVCAPS_CAN_EJECT 0x00000007L
#define MCI_GETDEVCAPS_CAN_PLAY 0x00000008L
#define MCI_GETDEVCAPS_CAN_SAVE 0x00000009L

#define MCI_SYSINFO_QUANTITY 0x00000100L
#define MCI_SYSINFO_OPEN 0x00000200L
#define MCI_SYSINFO_NAME 0x00000400L
#define MCI_SYSINFO_INSTALLNAME 0x00000800L

#define MCI_SET_DOOR_OPEN 0x00000100L
#define MCI_SET_DOOR_CLOSED 0x00000200L
#define MCI_SET_TIME_FORMAT 0x00000400L
#define MCI_SET_AUDIO 0x00000800L
#define MCI_SET_VIDEO 0x00001000L
#define MCI_SET_ON 0x00002000L
#define MCI_SET_OFF 0x00004000L

#define MCI_SET_AUDIO_ALL 0x00000000L
#define MCI_SET_AUDIO_LEFT 0x00000001L
#define MCI_SET_AUDIO_RIGHT 0x00000002L

#define MCI_BREAK_KEY 0x00000100L
#define MCI_BREAK_HWND 0x00000200L
#define MCI_BREAK_OFF 0x00000400L

#define MCI_RECORD_INSERT 0x00000100L
#define MCI_RECORD_OVERWRITE 0x00000200L

#define MCI_SOUND_NAME 0x00000100L

#define MCI_SAVE_FILE 0x00000100L

#define MCI_LOAD_FILE 0x00000100L

/* Generic parameter blocks. */
typedef struct tagMCI_GENERIC_PARMS {
  DWORD dwCallback;
} MCI_GENERIC_PARMS;
typedef MCI_GENERIC_PARMS FAR *LPMCI_GENERIC_PARMS;

typedef struct tagMCI_OPEN_PARMS {
  DWORD dwCallback;
  UINT wDeviceID;
  UINT wReserved0;
  LPCSTR lpstrDeviceType;
  LPCSTR lpstrElementName;
  LPCSTR lpstrAlias;
} MCI_OPEN_PARMS;
typedef MCI_OPEN_PARMS FAR *LPMCI_OPEN_PARMS;

typedef struct tagMCI_PLAY_PARMS {
  DWORD dwCallback;
  DWORD dwFrom;
  DWORD dwTo;
} MCI_PLAY_PARMS;
typedef MCI_PLAY_PARMS FAR *LPMCI_PLAY_PARMS;

typedef struct tagMCI_SEEK_PARMS {
  DWORD dwCallback;
  DWORD dwTo;
} MCI_SEEK_PARMS;
typedef MCI_SEEK_PARMS FAR *LPMCI_SEEK_PARMS;

typedef struct tagMCI_STATUS_PARMS {
  DWORD dwCallback;
  DWORD dwReturn;
  DWORD dwItem;
  DWORD dwTrack;
} MCI_STATUS_PARMS;
typedef MCI_STATUS_PARMS FAR *LPMCI_STATUS_PARMS;

typedef struct tagMCI_INFO_PARMS {
  DWORD dwCallback;
  LPSTR lpstrReturn;
  DWORD dwRetSize;
} MCI_INFO_PARMS;
typedef MCI_INFO_PARMS FAR *LPMCI_INFO_PARMS;

typedef struct tagMCI_GETDEVCAPS_PARMS {
  DWORD dwCallback;
  DWORD dwReturn;
  DWORD dwItem;
} MCI_GETDEVCAPS_PARMS;
typedef MCI_GETDEVCAPS_PARMS FAR *LPMCI_GETDEVCAPS_PARMS;

typedef struct tagMCI_SYSINFO_PARMS {
  DWORD dwCallback;
  LPSTR lpstrReturn;
  DWORD dwRetSize;
  DWORD dwNumber;
  UINT wDeviceType;
  UINT wReserved0;
} MCI_SYSINFO_PARMS;
typedef MCI_SYSINFO_PARMS FAR *LPMCI_SYSINFO_PARMS;

typedef struct tagMCI_SET_PARMS {
  DWORD dwCallback;
  DWORD dwTimeFormat;
  DWORD dwAudio;
} MCI_SET_PARMS;
typedef MCI_SET_PARMS FAR *LPMCI_SET_PARMS;

typedef struct tagMCI_BREAK_PARMS {
  DWORD dwCallback;
  int nVirtKey;
  UINT wReserved0;
  HWND hwndBreak;
  UINT wReserved1;
} MCI_BREAK_PARMS;
typedef MCI_BREAK_PARMS FAR *LPMCI_BREAK_PARMS;

typedef struct tagMCI_SOUND_PARMS {
  DWORD dwCallback;
  LPCSTR lpstrSoundName;
} MCI_SOUND_PARMS;
typedef MCI_SOUND_PARMS FAR *LPMCI_SOUND_PARMS;

typedef struct tagMCI_SAVE_PARMS {
  DWORD dwCallback;
  LPCSTR lpfilename;
} MCI_SAVE_PARMS;
typedef MCI_SAVE_PARMS FAR *LPMCI_SAVE_PARMS;

typedef struct tagMCI_LOAD_PARMS {
  DWORD dwCallback;
  LPCSTR lpfilename;
} MCI_LOAD_PARMS;
typedef MCI_LOAD_PARMS FAR *LPMCI_LOAD_PARMS;

typedef struct tagMCI_RECORD_PARMS {
  DWORD dwCallback;
  DWORD dwFrom;
  DWORD dwTo;
} MCI_RECORD_PARMS;
typedef MCI_RECORD_PARMS FAR *LPMCI_RECORD_PARMS;

/* Videodisc players. */
#define MCI_VD_MODE_PARK (MCI_VD_OFFSET + 1)
#define MCI_VD_MEDIA_CLV (MCI_VD_OFFSET + 2)
#define MCI_VD_MEDIA_CAV (MCI_VD_OFFSET + 3)
#define MCI_VD_MEDIA_OTHER (MCI_VD_OFFSET + 4)
#define MCI_VD_FORMAT_TRACK 0x4001

#define MCI_VD_PLAY_REVERSE 0x00010000L
#define MCI_VD_PLAY_FAST 0x00020000L
#define MCI_VD_PLAY_SPEED 0x00040000L
#define MCI_VD_PLAY_SCAN 0x00080000L
#define MCI_VD_PLAY_SLOW 0x00100000L
#define MCI_VD_SEEK_REVERSE 0x00010000L
#define MCI_VD_STATUS_SPEED 0x00004002L
#define MCI_VD_STATUS_FORWARD 0x00004003L
#define MCI_VD_STATUS_MEDIA_TYPE 0x00004004L
#define MCI_VD_STATUS_SIDE 0x00004005L
#define MCI_VD_STATUS_DISC_SIZE 0x00004006L
#define MCI_VD_GETDEVCAPS_CLV 0x00010000L
#define MCI_VD_GETDEVCAPS_CAV 0x00020000L
#define MCI_VD_SPIN_UP 0x00010000L
#define MCI_VD_SPIN_DOWN 0x00020000L
#define MCI_VD_GETDEVCAPS_CAN_REVERSE 0x00004002L
#define MCI_VD_GETDEVCAPS_FAST_RATE 0x00004003L
#define MCI_VD_GETDEVCAPS_SLOW_RATE 0x00004004L
#define MCI_VD_GETDEVCAPS_NORMAL_RATE 0x00004005L
#define MCI_VD_STEP_FRAMES 0x00010000L
#define MCI_VD_STEP_REVERSE 0x00020000L
#define MCI_VD_ESCAPE_STRING 0x00000100L

typedef struct tagMCI_VD_PLAY_PARMS {
  DWORD dwCallback;
  DWORD dwFrom;
  DWORD dwTo;
  DWORD dwSpeed;
} MCI_VD_PLAY_PARMS;
typedef MCI_VD_PLAY_PARMS FAR *LPMCI_VD_PLAY_PARMS;

typedef struct tagMCI_VD_STEP_PARMS {
  DWORD dwCallback;
  DWORD dwFrames;
} MCI_VD_STEP_PARMS;
typedef MCI_VD_STEP_PARMS FAR *LPMCI_VD_STEP_PARMS;

typedef struct tagMCI_VD_ESCAPE_PARMS {
  DWORD dwCallback;
  LPCSTR lpstrCommand;
} MCI_VD_ESCAPE_PARMS;
typedef MCI_VD_ESCAPE_PARMS FAR *LPMCI_VD_ESCAPE_PARMS;

/* Waveform audio. */
#define MCI_WAVE_PCM (MCI_WAVE_OFFSET + 0)
#define MCI_WAVE_MAPPER (MCI_WAVE_OFFSET + 1)

#define MCI_WAVE_OPEN_BUFFER 0x00010000L

#define MCI_WAVE_SET_FORMATTAG 0x00010000L
#define MCI_WAVE_SET_CHANNELS 0x00020000L
#define MCI_WAVE_SET_SAMPLESPERSEC 0x00040000L
#define MCI_WAVE_SET_AVGBYTESPERSEC 0x00080000L
#define MCI_WAVE_SET_BLOCKALIGN 0x00100000L
#define MCI_WAVE_SET_BITSPERSAMPLE 0x00200000L

#define MCI_WAVE_INPUT 0x00400000L
#define MCI_WAVE_OUTPUT 0x00800000L

#define MCI_WAVE_STATUS_FORMATTAG 0x00004001L
#define MCI_WAVE_STATUS_CHANNELS 0x00004002L
#define MCI_WAVE_STATUS_SAMPLESPERSEC 0x00004003L
#define MCI_WAVE_STATUS_AVGBYTESPERSEC 0x00004004L
#define MCI_WAVE_STATUS_BLOCKALIGN 0x00004005L
#define MCI_WAVE_STATUS_BITSPERSAMPLE 0x00004006L
#define MCI_WAVE_STATUS_LEVEL 0x00004007L

#define MCI_WAVE_SET_ANYINPUT 0x04000000L
#define MCI_WAVE_SET_ANYOUTPUT 0x08000000L

#define MCI_WAVE_GETDEVCAPS_INPUTS 0x00004001L
#define MCI_WAVE_GETDEVCAPS_OUTPUTS 0x00004002L

typedef struct tagMCI_WAVE_OPEN_PARMS {
  DWORD dwCallback;
  UINT wDeviceID;
  UINT wReserved0;
  LPCSTR lpstrDeviceType;
  LPCSTR lpstrElementName;
  LPCSTR lpstrAlias;
  DWORD dwBufferSeconds;
} MCI_WAVE_OPEN_PARMS;
typedef MCI_WAVE_OPEN_PARMS FAR *LPMCI_WAVE_OPEN_PARMS;

typedef struct tagMCI_WAVE_DELETE_PARMS {
  DWORD dwCallback;
  DWORD dwFrom;
  DWORD dwTo;
} MCI_WAVE_DELETE_PARMS;
typedef MCI_WAVE_DELETE_PARMS FAR *LPMCI_WAVE_DELETE_PARMS;

typedef struct tagMCI_WAVE_SET_PARMS {
  DWORD dwCallback;
  DWORD dwTimeFormat;
  DWORD dwAudio;
  UINT wInput;
  UINT wReserved0;
  UINT wOutput;
  UINT wReserved1;
  UINT wFormatTag;
  UINT wReserved2;
  UINT nChannels;
  UINT wReserved3;
  DWORD nSamplesPerSec;
  DWORD nAvgBytesPerSec;
  UINT nBlockAlign;
  UINT wReserved4;
  UINT wBitsPerSample;
  UINT wReserved5;
} MCI_WAVE_SET_PARMS;
typedef MCI_WAVE_SET_PARMS FAR *LPMCI_WAVE_SET_PARMS;

/* MIDI sequencer. */
#define MCI_SEQ_DIV_PPQN (0 + MCI_SEQ_OFFSET)
#define MCI_SEQ_DIV_SMPTE_24 (1 + MCI_SEQ_OFFSET)
#define MCI_SEQ_DIV_SMPTE_25 (2 + MCI_SEQ_OFFSET)
#define MCI_SEQ_DIV_SMPTE_30DROP (3 + MCI_SEQ_OFFSET)
#define MCI_SEQ_DIV_SMPTE_30 (4 + MCI_SEQ_OFFSET)

#define MCI_SEQ_FORMAT_SONGPTR 0x4001
#define MCI_SEQ_FILE 0x4002
#define MCI_SEQ_MIDI 0x4003
#define MCI_SEQ_SMPTE 0x4004
#define MCI_SEQ_NONE 65533
#define MCI_SEQ_MAPPER 65535

#define MCI_SEQ_STATUS_TEMPO 0x00004002L
#define MCI_SEQ_STATUS_PORT 0x00004003L
#define MCI_SEQ_STATUS_SLAVE 0x00004007L
#define MCI_SEQ_STATUS_MASTER 0x00004008L
#define MCI_SEQ_STATUS_OFFSET 0x00004009L
#define MCI_SEQ_STATUS_DIVTYPE 0x0000400AL

#define MCI_SEQ_SET_TEMPO 0x00010000L
#define MCI_SEQ_SET_PORT 0x00020000L
#define MCI_SEQ_SET_SLAVE 0x00040000L
#define MCI_SEQ_SET_MASTER 0x00080000L
#define MCI_SEQ_SET_OFFSET 0x01000000L

typedef struct tagMCI_SEQ_SET_PARMS {
  DWORD dwCallback;
  DWORD dwTimeFormat;
  DWORD dwAudio;
  DWORD dwTempo;
  DWORD dwPort;
  DWORD dwSlave;
  DWORD dwMaster;
  DWORD dwOffset;
} MCI_SEQ_SET_PARMS;
typedef MCI_SEQ_SET_PARMS FAR *LPMCI_SEQ_SET_PARMS;

/* Animation. */
#define MCI_ANIM_OPEN_WS 0x00010000L
#define MCI_ANIM_OPEN_PARENT 0x00020000L
#define MCI_ANIM_OPEN_NOSTATIC 0x00040000L

#define MCI_ANIM_PLAY_SPEED 0x00010000L
#define MCI_ANIM_PLAY_REVERSE 0x00020000L
#define MCI_ANIM_PLAY_FAST 0x00040000L
#define MCI_ANIM_PLAY_SLOW 0x00080000L
#define MCI_ANIM_PLAY_SCAN 0x00100000L

#define MCI_ANIM_STEP_REVERSE 0x00010000L
#define MCI_ANIM_STEP_FRAMES 0x00020000L

#define MCI_ANIM_STATUS_SPEED 0x00004001L
#define MCI_ANIM_STATUS_FORWARD 0x00004002L
#define MCI_ANIM_STATUS_HWND 0x00004003L
#define MCI_ANIM_STATUS_HPAL 0x00004004L
#define MCI_ANIM_STATUS_STRETCH 0x00004005L

#define MCI_ANIM_INFO_TEXT 0x00010000L

#define MCI_ANIM_GETDEVCAPS_CAN_REVERSE 0x00004001L
#define MCI_ANIM_GETDEVCAPS_FAST_RATE 0x00004002L
#define MCI_ANIM_GETDEVCAPS_SLOW_RATE 0x00004003L
#define MCI_ANIM_GETDEVCAPS_NORMAL_RATE 0x00004004L
#define MCI_ANIM_GETDEVCAPS_PALETTES 0x00004006L
#define MCI_ANIM_GETDEVCAPS_CAN_STRETCH 0x00004007L
#define MCI_ANIM_GETDEVCAPS_MAX_WINDOWS 0x00004008L

#define MCI_ANIM_REALIZE_NORM 0x00010000L
#define MCI_ANIM_REALIZE_BKGD 0x00020000L

#define MCI_ANIM_WINDOW_HWND 0x00010000L
#define MCI_ANIM_WINDOW_STATE 0x00040000L
#define MCI_ANIM_WINDOW_TEXT 0x00080000L
#define MCI_ANIM_WINDOW_ENABLE_STRETCH 0x00100000L
#define MCI_ANIM_WINDOW_DISABLE_STRETCH 0x00200000L
#define MCI_ANIM_WINDOW_DEFAULT 0x00000000L

#define MCI_ANIM_RECT 0x00010000L
#define MCI_ANIM_PUT_SOURCE 0x00020000L
#define MCI_ANIM_PUT_DESTINATION 0x00040000L

#define MCI_ANIM_WHERE_SOURCE 0x00020000L
#define MCI_ANIM_WHERE_DESTINATION 0x00040000L

#define MCI_ANIM_UPDATE_HDC 0x00020000L

typedef struct tagMCI_ANIM_OPEN_PARMS {
  DWORD dwCallback;
  UINT wDeviceID;
  UINT wReserved0;
  LPCSTR lpstrDeviceType;
  LPCSTR lpstrElementName;
  LPCSTR lpstrAlias;
  DWORD dwStyle;
  HWND hWndParent;
  UINT wReserved1;
} MCI_ANIM_OPEN_PARMS;
typedef MCI_ANIM_OPEN_PARMS FAR *LPMCI_ANIM_OPEN_PARMS;

typedef struct tagMCI_ANIM_PLAY_PARMS {
  DWORD dwCallback;
  DWORD dwFrom;
  DWORD dwTo;
  DWORD dwSpeed;
} MCI_ANIM_PLAY_PARMS;
typedef MCI_ANIM_PLAY_PARMS FAR *LPMCI_ANIM_PLAY_PARMS;

typedef struct tagMCI_ANIM_STEP_PARMS {
  DWORD dwCallback;
  DWORD dwFrames;
} MCI_ANIM_STEP_PARMS;
typedef MCI_ANIM_STEP_PARMS FAR *LPMCI_ANIM_STEP_PARMS;

typedef struct tagMCI_ANIM_WINDOW_PARMS {
  DWORD dwCallback;
  HWND hWnd;
  UINT wReserved1;
  UINT nCmdShow;
  UINT wReserved2;
  LPCSTR lpstrText;
} MCI_ANIM_WINDOW_PARMS;
typedef MCI_ANIM_WINDOW_PARMS FAR *LPMCI_ANIM_WINDOW_PARMS;

typedef struct tagMCI_ANIM_RECT_PARMS {
  DWORD dwCallback;
#ifdef MCI_USE_OFFEXT
  POINT ptOffset;
  POINT ptExtent;
#else
  RECT rc;
#endif
} MCI_ANIM_RECT_PARMS;
typedef MCI_ANIM_RECT_PARMS FAR *LPMCI_ANIM_RECT_PARMS;

typedef struct tagMCI_ANIM_UPDATE_PARMS {
  DWORD dwCallback;
  RECT rc;
  HDC hDC;
} MCI_ANIM_UPDATE_PARMS;
typedef MCI_ANIM_UPDATE_PARMS FAR *LPMCI_ANIM_UPDATE_PARMS;

/* Video overlay. */
#define MCI_OVLY_OPEN_WS 0x00010000L
#define MCI_OVLY_OPEN_PARENT 0x00020000L

#define MCI_OVLY_STATUS_HWND 0x00004001L
#define MCI_OVLY_STATUS_STRETCH 0x00004002L

#define MCI_OVLY_INFO_TEXT 0x00010000L

#define MCI_OVLY_GETDEVCAPS_CAN_STRETCH 0x00004001L
#define MCI_OVLY_GETDEVCAPS_CAN_FREEZE 0x00004002L
#define MCI_OVLY_GETDEVCAPS_MAX_WINDOWS 0x00004003L

#define MCI_OVLY_WINDOW_HWND 0x00010000L
#define MCI_OVLY_WINDOW_STATE 0x00040000L
#define MCI_OVLY_WINDOW_TEXT 0x00080000L
#define MCI_OVLY_WINDOW_ENABLE_STRETCH 0x00100000L
#define MCI_OVLY_WINDOW_DISABLE_STRETCH 0x00200000L
#define MCI_OVLY_WINDOW_DEFAULT 0x00000000L

#define MCI_OVLY_RECT 0x00010000L
#define MCI_OVLY_PUT_SOURCE 0x00020000L
#define MCI_OVLY_PUT_DESTINATION 0x00040000L
#define MCI_OVLY_PUT_FRAME 0x00080000L
#define MCI_OVLY_PUT_VIDEO 0x00100000L

#define MCI_OVLY_WHERE_SOURCE 0x00020000L
#define MCI_OVLY_WHERE_DESTINATION 0x00040000L
#define MCI_OVLY_WHERE_FRAME 0x00080000L
#define MCI_OVLY_WHERE_VIDEO 0x00100000L

typedef struct tagMCI_OVLY_OPEN_PARMS {
  DWORD dwCallback;
  UINT wDeviceID;
  UINT wReserved0;
  LPCSTR lpstrDeviceType;
  LPCSTR lpstrElementName;
  LPCSTR lpstrAlias;
  DWORD dwStyle;
  HWND hWndParent;
  UINT wReserved1;
} MCI_OVLY_OPEN_PARMS;
typedef MCI_OVLY_OPEN_PARMS FAR *LPMCI_OVLY_OPEN_PARMS;

typedef struct tagMCI_OVLY_WINDOW_PARMS {
  DWORD dwCallback;
  HWND hWnd;
  UINT wReserved1;
  UINT nCmdShow;
  UINT wReserved2;
  LPCSTR lpstrText;
} MCI_OVLY_WINDOW_PARMS;
typedef MCI_OVLY_WINDOW_PARMS FAR *LPMCI_OVLY_WINDOW_PARMS;

typedef struct tagMCI_OVLY_RECT_PARMS {
  DWORD dwCallback;
#ifdef MCI_USE_OFFEXT
  POINT ptOffset;
  POINT ptExtent;
#else
  RECT rc;
#endif
} MCI_OVLY_RECT_PARMS;
typedef MCI_OVLY_RECT_PARMS FAR *LPMCI_OVLY_RECT_PARMS;

typedef struct tagMCI_OVLY_SAVE_PARMS {
  DWORD dwCallback;
  LPCSTR lpfilename;
  RECT rc;
} MCI_OVLY_SAVE_PARMS;
typedef MCI_OVLY_SAVE_PARMS FAR *LPMCI_OVLY_SAVE_PARMS;

typedef struct tagMCI_OVLY_LOAD_PARMS {
  DWORD dwCallback;
  LPCSTR lpfilename;
  RECT rc;
} MCI_OVLY_LOAD_PARMS;
typedef MCI_OVLY_LOAD_PARMS FAR *LPMCI_OVLY_LOAD_PARMS;

/* CD audio. */
#define MCI_CDA_STATUS_TYPE_TRACK 0x00004001L
#define MCI_CDA_TRACK_AUDIO (MCI_CD_OFFSET + 0)
#define MCI_CDA_TRACK_OTHER (MCI_CD_OFFSET + 1)
#endif /* MMNOMCI */

#ifdef __cplusplus
}
#endif

#pragma pack(pop)
#endif /* _MMSYSTEM_H */
