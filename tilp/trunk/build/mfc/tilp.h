// TiLP.h : main header file for the TILP application
//

#if !defined(AFX_TILP_H__043BEF77_0234_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_TILP_H__043BEF77_0234_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTiLPApp:
// See TiLP.cpp for the implementation of this class
//

class CTiLPApp : public CWinApp
{
public:
	CTiLPApp();
	BOOL	PeekAndPump();
	void	RetrieveCalcOperations(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTiLPApp)
	public:
	virtual BOOL InitInstance(); //InitInstance, Run & OnIdle, ExitInstance
	virtual BOOL ExitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTiLPApp)
	afx_msg void OnHelpThanks();
	afx_msg void OnHelpChangelog();
	afx_msg void OnHelpHelp();
	afx_msg void OnHelpManpage();
	afx_msg void OnHelpAbout();
	afx_msg void OnSetupScreen();
	afx_msg void OnSetupGeneral();
	afx_msg void OnSetupExternalprograms();
	afx_msg void OnCalcSr();
	afx_msg void OnFileSaveConfig();
	afx_msg void OnFileLoadConfig();
	afx_msg void OnFileDefaultConfig();
	afx_msg void OnSetupComm();
	afx_msg void OnHelpBookmarksTiswebsite();
	afx_msg void OnHelpBookmarksTinewsnet();
	afx_msg void OnHelpBookmarksTilpswebsite();
	afx_msg void OnHelpBookmarksTifrorg();
	afx_msg void OnHelpBookmarksTicalcorg();
	afx_msg void OnHelpBookmarksThelpg();
	afx_msg void OnHelpBookmarksCalcsoftware();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TILP_H__043BEF77_0234_11D6_BC64_004005E3BC2E__INCLUDED_)
