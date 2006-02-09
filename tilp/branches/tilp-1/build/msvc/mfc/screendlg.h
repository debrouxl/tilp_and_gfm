#if !defined(AFX_ScreenDlg_H__530E9CE0_0B89_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_ScreenDlg_H__530E9CE0_0B89_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScreenDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScreenDlg dialog

class CScreenDlg : public CDialog
{
// Construction
public:
	CScreenDlg(CWnd* pParent = NULL);   // standard constructor
	void GetScreenDump();

// Dialog Data
	//{{AFX_DATA(CScreenDlg)
	enum { IDD = IDD_SCREENDUMP };
	CStatic	m_wndStatic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScreenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HANDLE m_hThread;

	// Generated message map functions
	//{{AFX_MSG(CScreenDlg)
	virtual void OnCancel();
	afx_msg void OnScClipboard();
	afx_msg void OnScSave();
	afx_msg void OnScLoad();
	afx_msg void OnScRefresh();
	afx_msg void OnScOptions();
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg LRESULT OnThread2Finished(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ScreenDlg_H__530E9CE0_0B89_11D6_BC64_004005E3BC2E__INCLUDED_)
