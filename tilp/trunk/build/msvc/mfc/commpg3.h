#if !defined(AFX_COMMPG3_H__E3FCAACD_3CD8_4204_BEB5_EBD73CA79B6F__INCLUDED_)
#define AFX_COMMPG3_H__E3FCAACD_3CD8_4204_BEB5_EBD73CA79B6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommPg3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommPg3 dialog

class CCommPg3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CCommPg3)

// Construction
public:
	CCommPg3();
	~CCommPg3();

// Dialog Data
	//{{AFX_DATA(CCommPg3)
	enum { IDD = IDD_SETUP_COMM3 };
	CSpinButtonCtrl	m_spin_delay;
	CSpinButtonCtrl	m_spin_timeout;
	CButton	m_rts_cts;
	CComboBox	m_baud_rate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCommPg3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCommPg3)
	afx_msg void OnChangeDelay();
	afx_msg void OnChangeTimeout();
	afx_msg void OnCloseupBaudRate();
	afx_msg void OnEditupdateBaudRate();
	virtual BOOL OnApply();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnRtsCts();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMPG3_H__E3FCAACD_3CD8_4204_BEB5_EBD73CA79B6F__INCLUDED_)
