#if !defined(AFX_CHANGELOGDLG_H__C133D556_02A4_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_CHANGELOGDLG_H__C133D556_02A4_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangelogDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangelogDlg dialog

class CChangelogDlg : public CDialog
{
// Construction
public:
	CChangelogDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChangelogDlg)
	enum { IDD = IDD_HELP_CHANGELOG };
	CEdit	m_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangelogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont	m_textFont;

	// Generated message map functions
	//{{AFX_MSG(CChangelogDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGELOGDLG_H__C133D556_02A4_11D6_BC64_004005E3BC2E__INCLUDED_)
