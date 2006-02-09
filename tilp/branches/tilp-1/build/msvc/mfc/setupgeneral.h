#if !defined(AFX_SETUPGENERAL_H__F488DAE3_02C9_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_SETUPGENERAL_H__F488DAE3_02C9_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupGeneral.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetupGeneralDlg dialog

class CSetupGeneralDlg : public CDialog
{
// Construction
public:
	CSetupGeneralDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetupGeneralDlg)
	enum { IDD = IDD_SETUP_GENERAL };
	CButton	m_recv_single;
	CButton	m_recv_group;
	CButton	m_files_all;
	CButton m_files_ti;
	CButton	m_confirmation;
	CButton m_full_path;
	CButton m_local_path;
	CButton m_calc_byname;
	CButton m_calc_byinfo;
	CButton m_calc_bytype;
	CButton m_calc_bysize;
	CButton m_calc_byup;
	CButton m_calc_bydown;
	CButton m_comp_byname;
	CButton m_comp_bydate;
	CButton m_comp_bysize;
	CButton m_comp_byattr;
	CButton m_comp_byup;
	CButton m_comp_bydown;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupGeneralDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetupGeneralDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnShowFiles();
	afx_msg void OnLocalPath();
	afx_msg void OnKeepArch();
	afx_msg void OnHideFiles();
	afx_msg void OnFullPath();
	afx_msg void OnCalcBydown();
	afx_msg void OnCalcByinfo();
	afx_msg void OnCalcByname();
	afx_msg void OnCalcBysize();
	afx_msg void OnCalcBytype();
	afx_msg void OnCalcByup();
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPGENERAL_H__F488DAE3_02C9_11D6_BC64_004005E3BC2E__INCLUDED_)
