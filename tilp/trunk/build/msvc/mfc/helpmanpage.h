#if !defined(AFX_MANPAGE_H__C133D558_02A4_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_MANPAGE_H__C133D558_02A4_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Manpage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CManpageDlg dialog

class CManpageDlg : public CDialog
{
// Construction
public:
	CManpageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CManpageDlg)
	enum { IDD = IDD_HELP_MANPAGE };
	CEdit	m_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManpageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont	m_textFont;

	// Generated message map functions
	//{{AFX_MSG(CManpageDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANPAGE_H__C133D558_02A4_11D6_BC64_004005E3BC2E__INCLUDED_)
