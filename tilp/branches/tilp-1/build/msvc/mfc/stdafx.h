// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__043BEF79_0234_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_STDAFX_H__043BEF79_0234_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcview.h>
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxmt.h>

#define WM_USER_CREATE_PBAR			WM_USER+0x100
#define WM_USER_CREATE_PBAR1		WM_USER+0x101
#define WM_USER_CREATE_PBAR2		WM_USER+0x102
#define WM_USER_CREATE_PBAR3		WM_USER+0x103
#define WM_USER_CREATE_PBAR4		WM_USER+0x104
#define WM_USER_CREATE_PBAR5		WM_USER+0x105
#define WM_USER_DESTROY_PBAR		WM_USER+0x106

#define WM_USER_REFRESH_PBAR1		WM_USER+0x107
#define WM_USER_REFRESH_PBAR2		WM_USER+0x108
#define WM_USER_REFRESH_LABEL		WM_USER+0x109

#define WM_USER_THREAD1_FINISHED	WM_USER+0x110	// ready (unused)
#define WM_USER_THREAD2_FINISHED	WM_USER+0x111	// screendump
#define WM_USER_THREAD3_FINISHED	WM_USER+0x112	// dirlist
#define WM_USER_THREAD4_FINISHED	WM_USER+0x113	// backup
#define WM_USER_THREAD5_FINISHED	WM_USER+0x114	// restore
#define WM_USER_THREAD6_FINISHED	WM_USER+0x115	// recv var
#define WM_USER_THREAD7_FINISHED	WM_USER+0x116	// send var
#define WM_USER_THREAD8_FINISHED	WM_USER+0x117	// romdump
#define WM_USER_THREAD9_FINISHED	WM_USER+0x118	// FLASH app (send)
#define WM_USER_THREAD10_FINISHED	WM_USER+0x119	// FLASH OS
#define WM_USER_THREAD11_FINISHED	WM_USER+0x120	// AMS2ROM
#define WM_USER_THREAD12_FINISHED	WM_USER+0x121	// FLASH app (recv)


typedef struct tagTHREADPARMS {
    CWnd*	pWnd;
	CString cStr;
	int iRet;
} THREADPARMS;

typedef struct tagCALCOPS {
	BOOL bReady;
	BOOL bRemote;
	BOOL bScreen;
	BOOL bDirlist;
	BOOL bBackup;
	BOOL bVar;
	BOOL bFlash;
	BOOL bIdlist;
	BOOL bRomDump;
	BOOL bRomVersion;
	BOOL bClock;
} CALCOPS;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__043BEF79_0234_11D6_BC64_004005E3BC2E__INCLUDED_)
