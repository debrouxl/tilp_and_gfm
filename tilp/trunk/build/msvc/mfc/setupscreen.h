#if !defined(AFX_SETUPSCREEN_H__69815120_02BF_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_SETUPSCREEN_H__69815120_02BF_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupScreen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetupScreenDlg dialog

class SetupScreenDlg : public CDialog
{
// Construction
public:
	SetupScreenDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SetupScreenDlg)
	enum { IDD = IDD_SETUP_SCREEN };
	CButton	m_grayscale;
	CButton	m_xpm;
	CButton	m_bmp;
	CButton	m_pcx;
	CButton	m_jpg;
	CButton m_full_screen;
	CButton m_clipped_screen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetupScreenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SetupScreenDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPcx();
	afx_msg void OnXpm();
	afx_msg void OnJpg();
	virtual BOOL OnInitDialog();
	afx_msg void OnClippedScreen();
	afx_msg void OnFullScreen();
	afx_msg void OnBmp();
	afx_msg void OnBlurry();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPSCREEN_H__69815120_02BF_11D6_BC64_004005E3BC2E__INCLUDED_)
