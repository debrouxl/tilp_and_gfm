#if !defined(AFX_EXTPROGRAMS_H__69815123_02BF_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_EXTPROGRAMS_H__69815123_02BF_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtPrograms.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExtProgramsDlg dialog

class CExtProgramsDlg : public CDialog
{
// Construction
public:
	CExtProgramsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExtProgramsDlg)
	enum { IDD = IDD_SETUP_PROG };
	CString	m_tar_location;
	CString	m_tar_options;
	CString	m_zip_location;
	CString	m_zip_options;
	CString	m_app_options;
	CString	m_app_location;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtProgramsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExtProgramsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonZip();
	afx_msg void OnButtonTar();
	virtual void OnOK();
	afx_msg void OnButtonAppsign();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTPROGRAMS_H__69815123_02BF_11D6_BC64_004005E3BC2E__INCLUDED_)
