#if !defined(AFX_THANKS_H__C133D521_02A4_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_THANKS_H__C133D521_02A4_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Thanks.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThanksDlg dialog

class CThanksDlg : public CDialog
{
// Construction
public:
	CThanksDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CThanksDlg)
	enum { IDD = IDD_HELP_THANKS };
	CEdit	m_edit;
	CString	m_text;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThanksDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont	m_textFont;

	// Generated message map functions
	//{{AFX_MSG(CThanksDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THANKS_H__C133D521_02A4_11D6_BC64_004005E3BC2E__INCLUDED_)
