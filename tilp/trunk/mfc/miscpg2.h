#if !defined(AFX_MISCPG2_H__A7929B45_CED4_11D6_9A65_006008205341__INCLUDED_)
#define AFX_MISCPG2_H__A7929B45_CED4_11D6_9A65_006008205341__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MiscPg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMiscPg2 dialog

class CMiscPg2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CMiscPg2)

// Construction
public:
	CMiscPg2();
	~CMiscPg2();

// Dialog Data
	//{{AFX_DATA(CMiscPg2)
	enum { IDD = IDD_SETUP_GENERAL2 };
	CButton	m_recv_single;
	CButton	m_recv_group;
	CButton m_full_path;
	CButton m_local_path;
	CButton m_calc_byname;
	CButton m_calc_byinfo;
	CButton m_calc_bytype;
	CButton m_calc_bysize;
	CButton m_calc_byup;
	CButton m_calc_bydown;
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMiscPg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMiscPg2)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL OnApply();
	afx_msg void OnLocalPath();
	afx_msg void OnFullPath();
	afx_msg void OnCalcBydown();
	afx_msg void OnCalcByinfo();
	afx_msg void OnCalcByname();
	afx_msg void OnCalcBysize();
	afx_msg void OnCalcBytype();
	afx_msg void OnCalcByup();
	afx_msg void OnRecvSingle();
	afx_msg void OnRecvGroup();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MISCPG2_H__A7929B45_CED4_11D6_9A65_006008205341__INCLUDED_)
