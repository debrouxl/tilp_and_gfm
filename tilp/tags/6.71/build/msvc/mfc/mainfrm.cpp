// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TiLP.h"

#include "MainFrm.h"
#include "PbarDlg.h"
#include "LeftDoc.h"
#include "ChildFrm.h"
#include "LeftView.h"
#include "RightView.h"
#include "DlgClock.h"
#include "ScreenDlg.h"
#include "VisualKB.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_OPERATIONS_SCREENSHOT, OnOperationsScreenshot)
	ON_COMMAND(ID_OPERATIONS_REMOTEANDTERMINAL, OnOperationsRemoteandterminal)
	ON_COMMAND(ID_OPERATIONS_READY, OnOperationsReady)
	ON_COMMAND(ID_OPERATIONS_BACKUP_RECEIVE, OnOperationsBackupReceive)
	ON_COMMAND(ID_OPERATIONS_BACKUP_SEND, OnOperationsBackupSend)
	ON_COMMAND(ID_OPERATIONS_FLASH_SENDAPP, OnOperationsFlashSendapp)
	ON_COMMAND(ID_OPERATIONS_FLASH_SENDOS, OnOperationsFlashSendos)
	ON_COMMAND(ID_OPERATIONS_FLASH_RECEIVEAPP, OnOperationsFlashReceiveapp)
	ON_COMMAND(ID_OPERATIONS_FLASH_GETIDLIST, OnOperationsFlashGetidlist)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_READY, OnUpdateOperationsReady)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_SCREENSHOT, OnUpdateOperationsScreenshot)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_FLASH_SENDOS, OnUpdateOperationsFlashSendos)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_FLASH_SENDAPP, OnUpdateOperationsFlashSendapp)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_FLASH_RECEIVEAPP, OnUpdateOperationsFlashReceiveapp)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_FLASH_GETIDLIST, OnUpdateOperationsFlashGetidlist)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_BACKUP_SEND, OnUpdateOperationsBackupSend)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_BACKUP_RECEIVE, OnUpdateOperationsBackupReceive)
	ON_COMMAND(ID_OPERATIONS_REMOTE, OnOperationsRemote)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_REMOTE, OnUpdateOperationsRemote)
	ON_COMMAND(ID_OPERATIONS_ROMVERSION, OnOperationsRomVersion)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_ROMVERSION, OnUpdateOperationsRomVersion)
	ON_COMMAND(ID_OPERATIONS_VAR_SR, OnOperationsVarSr)
	ON_COMMAND(ID_OPERATIONS_VAR_SEND, OnOperationsVarSend)
	ON_COMMAND(ID_OPERATIONS_VAR_RECV, OnOperationsVarRecv)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_VAR_SR, OnUpdateOperationsVarSr)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_DIRECTORYLIST, OnUpdateOperationsDirectorylist)
	ON_COMMAND(ID_TEST, OnOperationsRomDump)
	ON_UPDATE_COMMAND_UI(ID_TEST, OnUpdateOperationsRomDump)
	ON_COMMAND(ID_FILE_AMS2ROM, OnFileAms2rom)
	ON_COMMAND(ID_OPERATIONS_CLOCK, OnOperationsClock)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_CLOCK, OnUpdateOperationsClock)
	//}}AFX_MSG_MAP
	// Global help commands
	// Roms: disabled
	//ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	//ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	//ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	//ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
	// Pbar messages
	ON_MESSAGE(WM_USER_CREATE_PBAR1, OnCreatePbar1)
	ON_MESSAGE(WM_USER_CREATE_PBAR2, OnCreatePbar2)
	ON_MESSAGE(WM_USER_CREATE_PBAR3, OnCreatePbar3)
	ON_MESSAGE(WM_USER_CREATE_PBAR4, OnCreatePbar4)
	ON_MESSAGE(WM_USER_CREATE_PBAR5, OnCreatePbar5)
	ON_MESSAGE(WM_USER_DESTROY_PBAR, OnDestroyPbar)
	// Thread termination messages
	ON_MESSAGE (WM_USER_THREAD4_FINISHED, OnThread4Finished)
	ON_MESSAGE (WM_USER_THREAD5_FINISHED, OnThread5Finished)
	ON_MESSAGE (WM_USER_THREAD6_FINISHED, OnThread6Finished)
	ON_MESSAGE (WM_USER_THREAD7_FINISHED, OnThread7Finished)
	ON_MESSAGE (WM_USER_THREAD8_FINISHED, OnThread8Finished)
	ON_MESSAGE (WM_USER_THREAD9_FINISHED, OnThread9Finished)
	ON_MESSAGE (WM_USER_THREAD10_FINISHED, OnThread10Finished)
	ON_MESSAGE (WM_USER_THREAD11_FINISHED, OnThread11Finished)
	ON_MESSAGE (WM_USER_THREAD12_FINISHED, OnThread12Finished)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	memset((void *)(&CalcOps), 1, sizeof(CALCOPS));
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar1.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar1.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// Operations toolbar
	if (!m_wndToolBar2.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_LEFT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar2.LoadToolBar(IDR_OPERATIONS))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar1.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar2.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar1);
	DockControlBar(&m_wndToolBar2);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~FWS_ADDTOTITLE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Progress bar creation/destruction

static	CPbar1Dlg*	m_pPbar1Dlg;
static	CPbar2Dlg*	m_pPbar2Dlg;
static	CPbar3Dlg*	m_pPbar3Dlg;
static	CPbar4Dlg*	m_pPbar4Dlg;
static	CPbar5Dlg*	m_pPbar5Dlg;

LRESULT CMainFrame::OnCreatePbar1 (WPARAM wParam, LPARAM lParam)
{
	CWnd* pWnd = (CWnd *)lParam;

	if(m_pPbar1Dlg != NULL)		// if dbox already exists, focuses it
		m_pPbar1Dlg->SetFocus();
	else
	{
		m_pPbar1Dlg = new CPbar1Dlg;
		m_pPbar1Dlg->Create(IDD_PBAR1);
		m_pPbar1Dlg->ShowWindow(SW_SHOW);
		m_pPbar1Dlg->m_pbar2.SetRange(0, 100);
		m_pPbar1Dlg->PassParameters((LPCSTR)wParam, (LPCSTR)lParam);
		m_pPbar1Dlg->UpdateWindow();
	}

	return 0;
}

LRESULT CMainFrame::OnCreatePbar2 (WPARAM wParam, LPARAM lParam)
{
	if(m_pPbar2Dlg != NULL)		// if dbox already exists, focuses it
		m_pPbar2Dlg->SetFocus();
	else
	{
		m_pPbar2Dlg = new CPbar2Dlg;
		m_pPbar2Dlg->Create(IDD_PBAR2);
		m_pPbar2Dlg->ShowWindow(SW_SHOW);
		m_pPbar2Dlg->PassParameters((LPCSTR)wParam, (LPCSTR)lParam);
	}

	return 0;
}

LRESULT CMainFrame::OnCreatePbar3 (WPARAM wParam, LPARAM lParam)
{
	if(m_pPbar3Dlg != NULL)		// if dbox already exists, focuses it
		m_pPbar3Dlg->SetFocus();
	else
	{
		m_pPbar3Dlg = new CPbar3Dlg;
		m_pPbar3Dlg->Create(IDD_PBAR3);
		m_pPbar3Dlg->ShowWindow(SW_SHOW);
		m_pPbar3Dlg->m_pbar1.SetRange(0, 100);
		m_pPbar3Dlg->m_pbar2.SetRange(0, 100);
		m_pPbar3Dlg->PassParameters((LPCSTR)wParam, (LPCSTR)lParam);
	}

	return 0;
}

LRESULT CMainFrame::OnCreatePbar4 (WPARAM wParam, LPARAM lParam)
{
	if(m_pPbar4Dlg != NULL)		// if dbox already exists, focuses it
		m_pPbar4Dlg->SetFocus();
	else
	{
		m_pPbar4Dlg = new CPbar4Dlg;
		m_pPbar4Dlg->Create(IDD_PBAR4);
		m_pPbar4Dlg->ShowWindow(SW_SHOW);
		m_pPbar4Dlg->m_pbar2.SetRange(0, 100);
		m_pPbar4Dlg->PassParameters((LPCSTR)wParam, (LPCSTR)lParam);
	}	

	return 0;
}

LRESULT CMainFrame::OnCreatePbar5 (WPARAM wParam, LPARAM lParam)
{
	if(m_pPbar5Dlg != NULL)		// if dbox already exists, focuses it
		m_pPbar5Dlg->SetFocus();
	else
	{
		m_pPbar5Dlg = new CPbar5Dlg;
		m_pPbar5Dlg->Create(IDD_PBAR5);
		m_pPbar5Dlg->ShowWindow(SW_SHOW);
		m_pPbar5Dlg->m_pbar1.SetRange(0, 100);
		m_pPbar5Dlg->m_pbar2.SetRange(0, 100);
		m_pPbar5Dlg->PassParameters((LPCSTR)wParam, (LPCSTR)lParam);
	}

	return 0;
}

LRESULT CMainFrame::OnDestroyPbar (WPARAM wParam, LPARAM lParam)
{
	if(m_pPbar1Dlg)
		m_pPbar1Dlg->DestroyWindow();
	if(m_pPbar2Dlg)
		m_pPbar2Dlg->DestroyWindow();
	if(m_pPbar3Dlg)
		m_pPbar3Dlg->DestroyWindow();
	if(m_pPbar4Dlg)
		m_pPbar4Dlg->DestroyWindow();
	if(m_pPbar5Dlg)
		m_pPbar5Dlg->DestroyWindow();

	m_pPbar1Dlg = NULL;
	m_pPbar2Dlg = NULL;
	m_pPbar3Dlg = NULL;
	m_pPbar4Dlg = NULL;
	m_pPbar5Dlg = NULL;

	return 0;
}

extern CProgressCtrl	*mPbar2;
extern CProgressCtrl	*mPbar1;
extern CEdit			*mLabel;
extern CEdit			*mRate ;

LRESULT CMainFrame::OnRefreshPbar1(WPARAM wParam, LPARAM lParam)
{
	mPbar2->SetPos((short)(100 * info_update.percentage));	
	return 0;
}

LRESULT CMainFrame::OnRefreshPbar2(WPARAM wParam, LPARAM lParam)
{
	mPbar1->SetPos((short)(100 * info_update.main_percentage));
	return 0;
}

LRESULT CMainFrame::OnRefreshLabel(WPARAM wParam, LPARAM lParam)
{
	mLabel->SetWindowText(info_update.label_text);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

/*******************/
/* Update handlers */
/*******************/

void CMainFrame::OnUpdateOperationsReady(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(CalcOps.bReady);
}

void CMainFrame::OnUpdateOperationsScreenshot(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(CalcOps.bScreen);
}

void CMainFrame::OnUpdateOperationsFlashSendos(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(CalcOps.bFlash);
}

void CMainFrame::OnUpdateOperationsFlashSendapp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(CalcOps.bFlash);
}

void CMainFrame::OnUpdateOperationsFlashReceiveapp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(CalcOps.bFlash);
}

void CMainFrame::OnUpdateOperationsFlashGetidlist(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(CalcOps.bIdlist);
}

void CMainFrame::OnUpdateOperationsDirectorylist(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//DISPLAY("button = %i\n", this->m_wndToolBar2.GetButtonStyle(5));
	//if(!(this->m_wndToolBar2.GetButtonStyle(5) & TBBS_DISABLED))
	//	pCmdUI->Enable(CalcOps.bDirlist);
}

void CMainFrame::OnUpdateOperationsBackupSend(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(CalcOps.bBackup);
}

void CMainFrame::OnUpdateOperationsBackupReceive(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(CalcOps.bBackup);
}

void CMainFrame::OnUpdateOperationsRomVersion(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(CalcOps.bRomVersion);
}

void CMainFrame::OnUpdateOperationsRemote(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(CalcOps.bRemote);
	if(tifiles_is_ti8x(options.lp.calc_type))
		pCmdUI->Enable(FALSE);
}

void CMainFrame::OnUpdateOperationsRomDump(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(CalcOps.bRomDump);
}

void CMainFrame::OnUpdateOperationsClock(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(CalcOps.bClock);
}

/**********************/
/* Callbacks handlers */
/**********************/

void CMainFrame::OnOperationsReady() 
{
	// TODO: Add your command handler code here
	tilp_calc_isready();
}

void CMainFrame::OnOperationsScreenshot() 
{
	// TODO: Add your command handler code here
	CScreenDlg*	pScreenDlg;
	pScreenDlg = new CScreenDlg;
	pScreenDlg->Create(IDD_SCREENDUMP);
	pScreenDlg->ShowWindow(SW_SHOW);
	pScreenDlg->GetScreenDump();

	return;
}

void CMainFrame::OnOperationsRemoteandterminal() 
{
	// TODO: Add your command handler code here
	//CRemoteControlDlg rcontrolDlg;
	//rcontrolDlg.DoModal();	
	CWnd* pRemoteControl = new CRemoteControl;
	pRemoteControl->ShowWindow(SW_SHOW);
	pRemoteControl->UpdateWindow();
}

UINT Thread4Func(LPVOID pParam);
void CMainFrame::OnOperationsBackupReceive() 
{
	// TODO: Add your command handler code here
	// Package data to pass to the processing thread.
	THREADPARMS* ptp = new THREADPARMS;
    ptp->pWnd = AfxGetMainWnd ();
	ptp->iRet = 0;

	// Launch thread
	CWinThread* pThread = AfxBeginThread(Thread4Func, ptp, 
		THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

	::DuplicateHandle(GetCurrentProcess(), pThread->m_hThread, 
		GetCurrentProcess(), &m_hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);

	pThread->ResumeThread();
}

UINT Thread4Func(LPVOID pParam)
{
	THREADPARMS* ptp = (THREADPARMS*) pParam;

	if(tilp_calc_recv_backup()) return (ptp->iRet = -1);

	CMainFrame *pFrame = (CMainFrame *)(ptp->pWnd);
	pFrame->PostMessage(WM_USER_THREAD4_FINISHED, 0, 0);

	return 0;
}

LRESULT CMainFrame::OnThread4Finished (WPARAM wParam, LPARAM lParam)
{
	gchar src_filename[MAXCHARS];
	gint ret, skip=0;
	gchar buffer[MAXCHARS];
	gchar *dirname;

	// Ensure that thread is terminated
	ASSERT(m_hThread != NULL);
	::WaitForSingleObject(m_hThread, INFINITE);
	::CloseHandle(m_hThread);
	m_hThread = NULL;
	
	// And save the file
	static char BASED_CODE szFilter[] = "Backup Files (*.8?b, *.8?g, *.9?b, *.9?g)|*.???|";
	CFileDialog dlgFile(FALSE, tifiles_backup_file_ext(), "backup", 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	dlgFile.m_ofn.lpstrInitialDir = _T(clist_win.cur_dir);
	if(dlgFile.DoModal() == IDOK)
	{
		strcpy(src_filename, g_get_tmp_dir());
		strcat(src_filename, G_DIR_SEPARATOR_S);
		strcat(src_filename, TMPFILE_BACKUP);

		if(!CopyFile(src_filename, dlgFile.GetPathName().GetBuffer(1024), FALSE))
		{
			gif->msg_box(_("Error"), _("Unable to move the temporary file.\n"));  
		}
	}

	RefreshRightView();

    return 0;
}


UINT Thread5Func(LPVOID pParam);
void CMainFrame::OnOperationsBackupSend() 
{
	// TODO: Add your command handler code here
	static char BASED_CODE szFilter[] = "Group Files (*.8?b, *.8?g, *.9?b, *.9?g)|*.???|";
	CFileDialog dlgFile(TRUE, tifiles_backup_file_ext(), "backup", 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	dlgFile.m_ofn.lpstrInitialDir = _T(clist_win.cur_dir);
	if(dlgFile.DoModal() == IDOK)
	{
		// Package data to pass to the processing thread.
		THREADPARMS* ptp = new THREADPARMS;
        ptp->pWnd = AfxGetMainWnd ();
        ptp->cStr = CString(dlgFile.GetPathName());
		ptp->iRet = 0;

		// Launch thread
		CWinThread* pThread = AfxBeginThread(Thread5Func, ptp, 
			THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

		::DuplicateHandle(GetCurrentProcess(), pThread->m_hThread, 
			GetCurrentProcess(), &m_hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);

		pThread->ResumeThread();
	}
}

UINT Thread5Func(LPVOID pParam)
{
	THREADPARMS* ptp = (THREADPARMS*) pParam;

	if(tilp_calc_send_backup(ptp->cStr.GetBuffer(1024)))
		return (ptp->iRet = -1);

	CMainFrame *pFrame = (CMainFrame *)(ptp->pWnd);
	pFrame->PostMessage(WM_USER_THREAD5_FINISHED, 0, 0);

	return 0;
}

LRESULT CMainFrame::OnThread5Finished (WPARAM wParam, LPARAM lParam)
{
	// Ensure that thread is terminated
	ASSERT(m_hThread != NULL);
	::WaitForSingleObject(m_hThread, INFINITE);
	::CloseHandle(m_hThread);
	m_hThread = NULL;

    return 0;
}


UINT Thread6Func(LPVOID pParam);
void CMainFrame::OnOperationsFlashSendapp() 
{
	// TODO: Add your command handler code here
	char *msg =_("You are going to FLASH the Operating System of your calculator.\nHe is strongly recommended for Windows users to close any application and to turn off your screen saver (this makes the transfer rate decrease !). Tests have been made on a PC350 Mhz and all link cables without any problems.");
	gint ret;

	ret=gif->user2_box(_("Warning"), msg,
		_("Continue"), _("Cancel"));
	if(ret == BUTTON2) return;
  
	static char BASED_CODE szFilter[] = "Flash Files (*.73k, *.8Xk, *.89k, *.9Xk)|*.??k|";
	CFileDialog dlgFile(TRUE, tifiles_flash_app_file_ext(), "FLASHapp", 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	dlgFile.m_ofn.lpstrInitialDir = _T(clist_win.cur_dir);
	if(dlgFile.DoModal() == IDOK)
	{
		// Package data to pass to the processing thread.
		THREADPARMS* ptp = new THREADPARMS;
        ptp->pWnd = AfxGetMainWnd ();
        ptp->cStr = CString(dlgFile.GetPathName());
		ptp->iRet = 0;

		// Launch thread
		CWinThread* pThread = AfxBeginThread(Thread6Func, ptp, 
			THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

		::DuplicateHandle(GetCurrentProcess(), pThread->m_hThread, 
			GetCurrentProcess(), &m_hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);

		pThread->ResumeThread();
	}
}

UINT Thread6Func(LPVOID pParam)
{
	THREADPARMS* ptp = (THREADPARMS*) pParam;

	if(tilp_calc_send_flash_app(ptp->cStr.GetBuffer(1024)))
		return (ptp->iRet = -1);

	CMainFrame *pFrame = (CMainFrame *)(ptp->pWnd);
	pFrame->PostMessage(WM_USER_THREAD6_FINISHED, 0, 0);

	return 0;
}

LRESULT CMainFrame::OnThread6Finished (WPARAM wParam, LPARAM lParam)
{
	// Ensure that thread is terminated
	ASSERT(m_hThread != NULL);
	::WaitForSingleObject(m_hThread, INFINITE);
	::CloseHandle(m_hThread);
	m_hThread = NULL;

    return 0;
}


UINT Thread7Func(LPVOID pParam);
void CMainFrame::OnOperationsFlashSendos() 
{
	// TODO: Add your command handler code here
	char *msg =_("You are going to FLASH the Operating System of your calculator.\nHe is strongly recommended for Windows users to close any application and to turn off your screen saver (this makes the transfer rate decrease !). Tests have been made on a PC350 Mhz and all link cables without any problems.");
	gint ret;

	ret=gif->user2_box(_("Warning"), msg,
		_("Continue"), _("Cancel"));
	if(ret == BUTTON2) return;

	static char BASED_CODE szFilter[] = "Flash Files (*.73u, *.8Xu, *.89u, *.9Xu)|*.??u|";
	CFileDialog dlgFile(TRUE, tifiles_flash_os_file_ext(), "FLASHos", 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	dlgFile.m_ofn.lpstrInitialDir = _T(clist_win.cur_dir);
	if(dlgFile.DoModal() == IDOK)
	{
		// Package data to pass to the processing thread.
		THREADPARMS* ptp = new THREADPARMS;
        ptp->pWnd = AfxGetMainWnd ();
        ptp->cStr = CString(dlgFile.GetPathName());
		ptp->iRet = 0;

		// Launch thread
		CWinThread* pThread = AfxBeginThread(Thread7Func, ptp, 
			THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

		::DuplicateHandle(GetCurrentProcess(), pThread->m_hThread, 
			GetCurrentProcess(), &m_hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);

		pThread->ResumeThread();
	}
}

UINT Thread7Func(LPVOID pParam)
{
	THREADPARMS* ptp = (THREADPARMS*) pParam;

	if(tilp_calc_send_flash_os(ptp->cStr.GetBuffer(1024)))
		return (ptp->iRet = -1);

	CMainFrame *pFrame = (CMainFrame *)(ptp->pWnd);
	pFrame->PostMessage(WM_USER_THREAD7_FINISHED, 0, 0);

	return 0;
}

LRESULT CMainFrame::OnThread7Finished (WPARAM wParam, LPARAM lParam)
{
	// Ensure that thread is terminated
	ASSERT(m_hThread != NULL);
	::WaitForSingleObject(m_hThread, INFINITE);
	::CloseHandle(m_hThread);
	m_hThread = NULL;

    return 0;
}


UINT Thread12Func(LPVOID pParam);
void CMainFrame::OnOperationsFlashReceiveapp() 
{
	// TODO: Add your command handler code here
	// Package data to pass to the processing thread.
	THREADPARMS* ptp = new THREADPARMS;
    ptp->pWnd = AfxGetMainWnd ();
	ptp->iRet = 0;

	// Launch thread
	CWinThread* pThread = AfxBeginThread(Thread12Func, ptp, 
		THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

	::DuplicateHandle(GetCurrentProcess(), pThread->m_hThread, 
		GetCurrentProcess(), &m_hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);

	pThread->ResumeThread();
}

UINT Thread12Func(LPVOID pParam)
{
	THREADPARMS* ptp = (THREADPARMS*) pParam;

	if(tilp_calc_recv_app()) return (ptp->iRet = -1);

	CMainFrame *pFrame = (CMainFrame *)(ptp->pWnd);
	pFrame->PostMessage(WM_USER_THREAD12_FINISHED, 0, 0);

	return 0;
}

LRESULT CMainFrame::OnThread12Finished (WPARAM wParam, LPARAM lParam)
{
	// Ensure that thread is terminated
	ASSERT(m_hThread != NULL);
	::WaitForSingleObject(m_hThread, INFINITE);
	::CloseHandle(m_hThread);
	m_hThread = NULL;

	RefreshLeftView();
	RefreshRightView();

    return 0;
}


void CMainFrame::OnOperationsFlashGetidlist() 
{
	// TODO: Add your command handler code here
	tilp_calc_idlist();	
}

void CMainFrame::OnOperationsRemote() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnOperationsRomVersion() 
{
	// TODO: Add your command handler code here
	//tilp_rom_version();

	RefreshRightView();
}


UINT Thread8Func(LPVOID pParam);
void CMainFrame::OnOperationsVarSend() // should send from CFileDialog...
{
	// TODO: Add your command handler code here
	int ret;

	// Package data to pass to the processing thread.
	THREADPARMS* ptp = new THREADPARMS;
    ptp->pWnd = AfxGetMainWnd ();
    //ptp->cStr = CString(dlgFile.GetPathName());
	ptp->iRet = 0;

	// Launch thread
	CWinThread* pThread = AfxBeginThread(Thread8Func, ptp, 
		THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

	::DuplicateHandle(GetCurrentProcess(), pThread->m_hThread, 
		GetCurrentProcess(), &m_hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);

	pThread->ResumeThread();
}

UINT Thread8Func(LPVOID pParam)
{
	THREADPARMS* ptp = (THREADPARMS*) pParam;

	tilp_calc_send_var();

	CMainFrame *pFrame = (CMainFrame *)(ptp->pWnd);
	pFrame->PostMessage(WM_USER_THREAD8_FINISHED, 0, 0);

	return 0;
}

LRESULT CMainFrame::OnThread8Finished (WPARAM wParam, LPARAM lParam)
{
	// Ensure that thread is terminated
	ASSERT(m_hThread != NULL);
	::WaitForSingleObject(m_hThread, INFINITE);
	::CloseHandle(m_hThread);
	m_hThread = NULL;

    return 0;
}

UINT Thread9Func(LPVOID pParam);
void CMainFrame::OnOperationsVarRecv() 
{
	// TODO: Add your command handler code here

	// Package data to pass to the processing thread.
	THREADPARMS* ptp = new THREADPARMS;
    ptp->pWnd = AfxGetMainWnd ();
	ptp->iRet = 0;

	// Launch thread
	CWinThread* pThread = AfxBeginThread(Thread9Func, ptp, 
		THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

	::DuplicateHandle(GetCurrentProcess(), pThread->m_hThread, 
		GetCurrentProcess(), &m_hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);

	pThread->ResumeThread();
}

int to_save = 0;
UINT Thread9Func(LPVOID pParam)
{
	THREADPARMS* ptp = (THREADPARMS*) pParam;

	ptp->iRet = tilp_calc_recv_var();

	CMainFrame *pFrame = (CMainFrame *)(ptp->pWnd);
	pFrame->PostMessage(WM_USER_THREAD9_FINISHED, ptp->iRet, 0);

	return 0;
}

LRESULT CMainFrame::OnThread9Finished (WPARAM wParam, LPARAM lParam)
{
	gchar src_filename[MAXCHARS];
	gint ret, skip=0;
	gchar buffer[MAXCHARS];
	gchar *dirname;

	// Ensure that thread is terminated
	ASSERT(m_hThread != NULL);
	::WaitForSingleObject(m_hThread, INFINITE);
	::CloseHandle(m_hThread);
	m_hThread = NULL;

	// And save the file
	if( (wParam == -1) || (wParam == 0) )
	{
		//RefreshLeftView();	// <michelrozp@hotmail.com>
		RefreshRightView();
		return 0;
	}

	static char BASED_CODE szFilter[] = "Group Files (*.8?b, *.8?g, *.9?b, *.9?g)|*.???|";
	CFileDialog dlgFile(FALSE, tifiles_group_file_ext(), "group", 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	dlgFile.m_ofn.lpstrInitialDir = _T(clist_win.cur_dir);

	if(dlgFile.DoModal() == IDOK)
	{
		strcpy(src_filename, g_get_tmp_dir());
		strcat(src_filename, G_DIR_SEPARATOR_S);
		strcat(src_filename, TMPFILE_GROUP);

		if(!CopyFile(src_filename, dlgFile.GetPathName().GetBuffer(1024), FALSE))
		{
			gif->msg_box(_("Error"), _("Unable to move the temporary file.\n"));  
		}
	}

	RefreshLeftView();
	RefreshRightView();

    return 0;
}

void CMainFrame::OnOperationsVarSr() 
{
	// TODO: Add your command handler code here
	if( (ctree_win.selection != NULL) || (ctree_win.selection2 != NULL) )
	{
		if(ctree_win.selection != NULL)
			OnOperationsVarRecv();
		if(ctree_win.selection2 != NULL)
			OnOperationsFlashReceiveapp();
	}	
	else if(clist_win.selection != NULL)
		OnOperationsVarSend();
	else if( (options.lp.calc_type == CALC_TI82) || (options.lp.calc_type == CALC_TI85) )
		OnOperationsVarRecv();
}

void CMainFrame::OnUpdateOperationsVarSr(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//this->m_wndToolBar2.SetButtonInfo(5, ID_OPERATIONS_VAR_SR, TBBS_BUTTON, 5);
	if( (ctree_win.selection == NULL) && (ctree_win.selection2 == NULL) &&
		(clist_win.selection == NULL) )
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}


UINT Thread10Func(LPVOID pParam);
void CMainFrame::OnOperationsRomDump()
{
	// TODO: Add your command handler code here
	// Package data to pass to the processing thread.
	THREADPARMS* ptp = new THREADPARMS;
    ptp->pWnd = AfxGetMainWnd ();
	ptp->iRet = 0;

	// Launch thread
	CWinThread* pThread = AfxBeginThread(Thread10Func, ptp, 
		THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

	::DuplicateHandle(GetCurrentProcess(), pThread->m_hThread, 
		GetCurrentProcess(), &m_hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);

	pThread->ResumeThread();
}

UINT Thread10Func(LPVOID pParam)
{
	THREADPARMS* ptp = (THREADPARMS*) pParam;

	if(tilp_calc_rom_dump()) return (ptp->iRet = -1);

	CMainFrame *pFrame = (CMainFrame *)(ptp->pWnd);
	pFrame->PostMessage(WM_USER_THREAD10_FINISHED, 0, 0);

	return 0;
}

LRESULT CMainFrame::OnThread10Finished (WPARAM wParam, LPARAM lParam)
{
	gchar src_filename[MAXCHARS];
	gint ret, skip=0;
	gchar buffer[MAXCHARS];
	gchar *dirname;

	// Ensure that thread is terminated
	ASSERT(m_hThread != NULL);
	::WaitForSingleObject(m_hThread, INFINITE);
	::CloseHandle(m_hThread);
	m_hThread = NULL;
	
	// And save the file
	static char BASED_CODE szFilter[] = "ROM image (*.rom)|*.rom|";
	CFileDialog dlgFile(FALSE, "rom", "image", 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	dlgFile.m_ofn.lpstrInitialDir = _T(clist_win.cur_dir);
	if(dlgFile.DoModal() == IDOK)
	{
		strcpy(src_filename, g_get_tmp_dir());
		strcat(src_filename, G_DIR_SEPARATOR_S);
		strcat(src_filename, TMPFILE_ROMDUMP);

		if(!CopyFile(src_filename, dlgFile.GetPathName().GetBuffer(1024), FALSE))
		{
			gif->msg_box(_("Error"), _("Unable to move the temporary file.\n"));  
		}
	}
	RefreshRightView();

    return 0;
}

void CMainFrame::CallRomDump()
{
	OnOperationsRomDump();
}

UINT Thread11Func(LPVOID pParam);
void CMainFrame::OnFileAms2rom() 
{
	// TODO: Add your command handler code here
	char BASED_CODE szFilter[] = "FLASH Upgrade Files (*.tib;*.89u;*.9Xu)|*.tib;*.89u;*.9Xu|All Files (*.*)|*.*||";
	CFileDialog dlgFile(TRUE, ".tib", "upgrade", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	dlgFile.m_ofn.lpstrInitialDir = _T(clist_win.cur_dir);
	if(dlgFile.DoModal() == IDOK)
	{
		// Package data to pass to the processing thread.
		THREADPARMS* ptp = new THREADPARMS;
        ptp->pWnd = AfxGetMainWnd ();
        ptp->cStr = CString(dlgFile.GetPathName());
		ptp->iRet = 0;

		// Launch thread
		CWinThread* pThread = AfxBeginThread(Thread11Func, ptp, 
			THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

		::DuplicateHandle(GetCurrentProcess(), pThread->m_hThread, 
			GetCurrentProcess(), &m_hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);

		pThread->ResumeThread();
	}
}

UINT Thread11Func(LPVOID pParam)
{
	THREADPARMS* ptp = (THREADPARMS*) pParam;

	if(tilp_calc_ams2rom(ptp->cStr.GetBuffer(1024)))
		return (ptp->iRet = -1);

	CMainFrame *pFrame = (CMainFrame *)(ptp->pWnd);
	pFrame->PostMessage(WM_USER_THREAD11_FINISHED, 0, 0);

	return 0;
}

LRESULT CMainFrame::OnThread11Finished (WPARAM wParam, LPARAM lParam)
{
	// Ensure that thread is terminated
	ASSERT(m_hThread != NULL);
	::WaitForSingleObject(m_hThread, INFINITE);
	::CloseHandle(m_hThread);
	m_hThread = NULL;

	RefreshRightView();

    return 0;
}

void CMainFrame::RefreshLeftView()
{
	// Do a left view refresh (for clearing the selection)
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	ASSERT(pFrame != NULL);

	CChildFrame *pChild = (CChildFrame *) pFrame->GetActiveFrame();
	ASSERT(pChild != NULL);

	CLeftView *pView = (CLeftView *) pChild->m_wndSplitter.GetPane(0, 0);
	ASSERT(pView != NULL);

	pView->ForceRefresh();
}

void CMainFrame::RefreshRightView()
{
	// Do a right view refresh (for clearing the selection)
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	ASSERT(pFrame != NULL);

	CChildFrame *pChild = (CChildFrame *) pFrame->GetActiveFrame();
	ASSERT(pChild != NULL);

	CRightView *pView = (CRightView *) pChild->m_wndSplitter.GetPane(0, 1);
	ASSERT(pView != NULL);

	pView->ForceRefresh();
}

void CMainFrame::RefreshBothView()
{
	RefreshLeftView();
	RefreshRightView();
}

void CMainFrame::OnOperationsClock() 
{
	// TODO: Add your command handler code here
	CDlgClock clockDlg;
	clockDlg.DoModal();	
}
