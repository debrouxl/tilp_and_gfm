#if !defined(AFX_PrgmsPg1_H__6ABF7DD2_4B3E_4881_94D3_ED6A694549B4__INCLUDED_)
#define AFX_PrgmsPg1_H__6ABF7DD2_4B3E_4881_94D3_ED6A694549B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrgmsPg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrgmsPg1 dialog

class CPrgmsPg1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPrgmsPg1)

// Construction
public:
	CPrgmsPg1();
	~CPrgmsPg1();

// Dialog Data
	//{{AFX_DATA(CPrgmsPg1)
	enum { IDD = IDD_SETUP_PROG1 };
	CString	m_zip_location;
	CString	m_zip_options;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPrgmsPg1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPrgmsPg1)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonZip();
	virtual void OnOK();
	virtual BOOL OnApply();
	afx_msg void OnChangeEditZipLoc();
	afx_msg void OnChangeEditZipOpt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PrgmsPg1_H__6ABF7DD2_4B3E_4881_94D3_ED6A694549B4__INCLUDED_)
