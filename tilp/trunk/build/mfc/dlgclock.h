#if !defined(AFX_DLGCLOCK_H__72C5CE9E_1918_421D_967A_ED2044970ADD__INCLUDED_)
#define AFX_DLGCLOCK_H__72C5CE9E_1918_421D_967A_ED2044970ADD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgClock.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgClock dialog

class CDlgClock : public CDialog
{
// Construction
public:
	CDlgClock(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgClock)
	enum { IDD = IDD_MISC_CLOCK };
	CSpinButtonCtrl	m_clock_year;
	CSpinButtonCtrl	m_clock_sec;
	CSpinButtonCtrl	m_clock_min;
	CSpinButtonCtrl	m_clock_hour;
	CSpinButtonCtrl	m_clock_day;
	CComboBox	m_clock_month;
	CComboBox	m_clock_format;
	CButton	m_clock_ampm;
	CButton	m_clock_24h;
	CButton	m_clock_on;
	CButton	m_clock_off;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgClock)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgClock)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClockSync();
	afx_msg void OnClockAmpm();
	afx_msg void OnClock24h();
	afx_msg void OnClockOff();
	afx_msg void OnClockOn();
	afx_msg void OnCloseupClockFormat();
	afx_msg void OnEditupdateClockFormat();
	afx_msg void OnCloseupClockMonth();
	afx_msg void OnEditupdateClockMonth();
	afx_msg void OnChangeClockEditDay();
	afx_msg void OnChangeClockEditHour();
	afx_msg void OnChangeClockEditMin();
	afx_msg void OnChangeClockEditSec();
	afx_msg void OnChangeClockEditYear();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCLOCK_H__72C5CE9E_1918_421D_967A_ED2044970ADD__INCLUDED_)
