#if !defined(AFX_PrgmsPg2_H__6A1AD1E7_959C_47F1_87A6_062D5C6B5641__INCLUDED_)
#define AFX_PrgmsPg2_H__6A1AD1E7_959C_47F1_87A6_062D5C6B5641__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrgmsPg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrgmsPg2 dialog

class CPrgmsPg2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPrgmsPg2)

// Construction
public:
	CPrgmsPg2();
	~CPrgmsPg2();

// Dialog Data
	//{{AFX_DATA(CPrgmsPg2)
	enum { IDD = IDD_SETUP_PROG2 };
	CString	m_tar_location;
	CString	m_tar_options;
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPrgmsPg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPrgmsPg2)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonZip();
	virtual void OnOK();
	virtual BOOL OnApply();
	afx_msg void OnChangeEditTarLoc();
	afx_msg void OnChangeEditTarOpt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PrgmsPg2_H__6A1AD1E7_959C_47F1_87A6_062D5C6B5641__INCLUDED_)
