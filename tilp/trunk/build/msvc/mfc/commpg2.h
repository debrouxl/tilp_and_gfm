#if !defined(AFX_COMMPG2_H__1F576231_13C0_4268_9CD7_0F42251BE65B__INCLUDED_)
#define AFX_COMMPG2_H__1F576231_13C0_4268_9CD7_0F42251BE65B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommPg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommPg2 dialog

class CCommPg2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CCommPg2)

// Construction
public:
	CCommPg2();
	~CCommPg2();

// Dialog Data
	//{{AFX_DATA(CCommPg2)
	enum { IDD = IDD_SETUP_COMM2 };
	CButton m_v200;
	CButton m_ti92p;
	CButton m_ti92;
	CButton m_ti89;
	CButton m_ti86;
	CButton m_ti85;
	CButton m_ti83p;
	CButton m_ti83;
	CButton m_ti82;
	CButton m_ti73;
	CButton	m_autodetect;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCommPg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCommPg2)
	virtual BOOL OnApply();
	virtual void OnOK();
	afx_msg void OnAutoDetect();
	virtual BOOL OnInitDialog();
	afx_msg void OnCalc73();
	afx_msg void OnCalc82();
	afx_msg void OnCalc83();
	afx_msg void OnCalc83p();
	afx_msg void OnCalc85();
	afx_msg void OnCalc86();
	afx_msg void OnCalc89();
	afx_msg void OnCalc92();
	afx_msg void OnCalc92p();
	afx_msg void OnCalcV200();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMPG2_H__1F576231_13C0_4268_9CD7_0F42251BE65B__INCLUDED_)
