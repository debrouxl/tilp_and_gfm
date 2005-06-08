#if !defined(AFX_REMOTECONTROLDLG_H__51B2E798_A50A_4B06_8506_D43B9E4EBCC4__INCLUDED_)
#define AFX_REMOTECONTROLDLG_H__51B2E798_A50A_4B06_8506_D43B9E4EBCC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RemoteControlDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRemoteControlDlg dialog

class CRemoteControlDlg : public CDialog
{
// Construction
public:
	CRemoteControlDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRemoteControlDlg)
	enum { IDD = IDD_RCONTROL };
	CListCtrl	m_list;
	CEdit	m_info;
	CTabCtrl	m_tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemoteControlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont	m_textFont;
	void	RefreshTabs();

	// Generated message map functions
	//{{AFX_MSG(CRemoteControlDlg)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REMOTECONTROLDLG_H__51B2E798_A50A_4B06_8506_D43B9E4EBCC4__INCLUDED_)
