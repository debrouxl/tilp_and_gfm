#if !defined(AFX_MISCPG1_H__A7929B44_CED4_11D6_9A65_006008205341__INCLUDED_)
#define AFX_MISCPG1_H__A7929B44_CED4_11D6_9A65_006008205341__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MiscPg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMiscPg1 dialog

class CMiscPg1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CMiscPg1)

// Construction
public:
	CMiscPg1();
	~CMiscPg1();

// Dialog Data
	//{{AFX_DATA(CMiscPg1)
	enum { IDD = IDD_SETUP_GENERAL1 };
	CButton	m_files_all;
	CButton m_files_ti;
	CButton	m_confirmation;
	CButton m_comp_byname;
	CButton m_comp_bydate;
	CButton m_comp_bysize;
	CButton m_comp_byattr;
	CButton m_comp_byup;
	CButton m_comp_bydown;
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMiscPg1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMiscPg1)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL OnApply();
	afx_msg void OnCompByattr();
	afx_msg void OnCompBydate();
	afx_msg void OnCompBydown();
	afx_msg void OnCompByname();
	afx_msg void OnCompBysize();
	afx_msg void OnCompByup();
	afx_msg void OnConfirm();
	afx_msg void OnFilesAll();
	afx_msg void OnFilesTi();
	afx_msg void OnRecvSingle();
	afx_msg void OnRecvGroup();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MISCPG1_H__A7929B44_CED4_11D6_9A65_006008205341__INCLUDED_)
