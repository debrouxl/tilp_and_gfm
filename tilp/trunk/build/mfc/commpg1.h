#if !defined(AFX_COMMPG1_H__6B876525_5A30_41B3_9B81_7ED1BE0F16D4__INCLUDED_)
#define AFX_COMMPG1_H__6B876525_5A30_41B3_9B81_7ED1BE0F16D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommPg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommPg1 dialog

class CCommPg1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CCommPg1)

// Construction
public:
	CCommPg1();
	~CCommPg1();

// Dialog Data
	//{{AFX_DATA(CCommPg1)
	enum { IDD = IDD_SETUP_COMM1 };
	CButton m_tgl;
	CButton m_ser;
	CButton m_par;
	CButton m_avr;
	CButton m_tie;
	CButton m_vti;
	CButton m_ugl;
	CButton m_port1;
	CButton m_port2;
	CButton m_port3;
	CButton m_port4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCommPg1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCommPg1)
	virtual void OnOK();
	virtual BOOL OnApply();
	afx_msg void OnSerLink();
	afx_msg void OnTglLink();
	afx_msg void OnTieLink();
	afx_msg void OnUglLink();
	afx_msg void OnVtiLink();
	virtual BOOL OnInitDialog();
	afx_msg void OnAvrLink();
	afx_msg void OnParLink();
	afx_msg void OnPort1();
	afx_msg void OnPort2();
	afx_msg void OnPort3();
	afx_msg void OnPort4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMPG1_H__6B876525_5A30_41B3_9B81_7ED1BE0F16D4__INCLUDED_)
