// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__043BEF7B_0234_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_MAINFRM_H__043BEF7B_0234_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CustomStatusBar.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	CToolBar			m_wndToolBar2; // should be both protected but I'm lazy...
	CCustomStatusBar	m_wndStatusBar;

// Operations
public:
	CALCOPS CalcOps;
	void	RefreshLeftView();
	void	RefreshRightView();
	void	RefreshBothView();
	void	CallRomDump();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMenu		m_wndMenu;
	CToolBar	m_wndToolBar1;

// Generated message map functions
protected:
	HANDLE m_hThread;
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnOperationsScreenshot();
	afx_msg void OnOperationsRomRomdump();
	afx_msg void OnOperationsRemoteandterminal();
	afx_msg void OnOperationsReady();
	afx_msg void OnOperationsRomRomversion();
	afx_msg void OnOperationsBackupReceive();
	afx_msg void OnOperationsBackupSend();
	afx_msg void OnOperationsFlashSendapp();
	afx_msg void OnOperationsFlashSendos();
	afx_msg void OnOperationsFlashReceiveapp();
	afx_msg void OnOperationsFlashGetidlist();
	afx_msg void OnUpdateOperationsReady(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOperationsScreenshot(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOperationsFlashSendos(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOperationsFlashSendapp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOperationsFlashReceiveapp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOperationsFlashGetidlist(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOperationsBackupSend(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOperationsBackupReceive(CCmdUI* pCmdUI);
	afx_msg void OnOperationsRemote();
	afx_msg void OnUpdateOperationsRemote(CCmdUI* pCmdUI);
	afx_msg void OnOperationsRomVersion();
	afx_msg void OnUpdateOperationsRomVersion(CCmdUI* pCmdUI);
	afx_msg void OnOperationsVarSr();
	afx_msg void OnOperationsVarSend();
	afx_msg void OnOperationsVarRecv();
	afx_msg void OnUpdateOperationsVarSr(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOperationsDirectorylist(CCmdUI* pCmdUI);
	afx_msg void OnOperationsRomDump();
	afx_msg void OnUpdateOperationsRomDump(CCmdUI* pCmdUI);
	afx_msg void OnFileAms2rom();
	afx_msg void OnOperationsClock();
	afx_msg void OnUpdateOperationsClock(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT OnCreatePbar1(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCreatePbar2(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCreatePbar3(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCreatePbar4(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCreatePbar5(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDestroyPbar(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRefreshPbar1(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRefreshPbar2(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRefreshLabel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThread4Finished(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThread5Finished(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThread6Finished(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThread7Finished(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThread8Finished(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThread9Finished(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThread10Finished(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThread11Finished(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThread12Finished(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__043BEF7B_0234_11D6_BC64_004005E3BC2E__INCLUDED_)
