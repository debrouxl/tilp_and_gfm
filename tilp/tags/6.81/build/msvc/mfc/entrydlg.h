#if !defined(AFX_ENTRYDLG_H__D64FDF61_0846_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_ENTRYDLG_H__D64FDF61_0846_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EntryDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEntryDlg dialog

class CEntryDlg : public CDialog
{
// Construction
public:
	CEntryDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEntryDlg)
	enum { IDD = IDD_ENTRY_BOX };
	CButton	m_frame;
	CEdit	m_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEntryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEntryDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTRYDLG_H__D64FDF61_0846_11D6_BC64_004005E3BC2E__INCLUDED_)

char *mfc_dlgbox_entry(const char *title, const char *message,
					   const char *content);
