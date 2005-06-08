// TiLP.cpp : Defines the class behaviors for the application.
//

#include "StdAfx.h"
#include "TiLP.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "LeftDoc.h"
#include "LeftView.h"

#include "MiscSht.h"
#include "PrgmsSht.h"
#include "ScreenSht.h"
#include "CommSht.h"

#include "HelpAbout.h"
#include "HelpHelp.h"
#include "HelpManpage.h"

#include "PbarDlg.h"
#include "EntryDlg.h"

#include "../src/tilp_core.h"
#include "mfc_refresh.h"
#include "mfc_indep.h"

TilpGuiFncts gui_functions;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTiLPApp

BEGIN_MESSAGE_MAP(CTiLPApp, CWinApp)
	//{{AFX_MSG_MAP(CTiLPApp)
	ON_COMMAND(ID_HELP_HELP, OnHelpHelp)
	ON_COMMAND(ID_HELP_MANPAGE, OnHelpManpage)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_COMMAND(ID_SETUP_SCREEN, OnSetupScreen)
	ON_COMMAND(ID_SETUP_GENERAL, OnSetupGeneral)
	ON_COMMAND(ID_SETUP_EXTERNALPROGRAMS, OnSetupExternalprograms)
	ON_COMMAND(ID_FILE_SAVECONFIG, OnFileSaveConfig)
	ON_COMMAND(ID_FILE_LOADCONFIG, OnFileLoadConfig)
	ON_COMMAND(ID_FILE_DEFAULTCONFIG, OnFileDefaultConfig)
	ON_COMMAND(ID_SETUP_COMM, OnSetupComm)
	ON_COMMAND(ID_HELP_BOOKMARKS_TISWEBSITE, OnHelpBookmarksTiswebsite)
	ON_COMMAND(ID_HELP_BOOKMARKS_TINEWSNET, OnHelpBookmarksTinewsnet)
	ON_COMMAND(ID_HELP_BOOKMARKS_TILPSWEBSITE, OnHelpBookmarksTilpswebsite)
	ON_COMMAND(ID_HELP_BOOKMARKS_TIFRORG, OnHelpBookmarksTifrorg)
	ON_COMMAND(ID_HELP_BOOKMARKS_TICALCORG, OnHelpBookmarksTicalcorg)
	ON_COMMAND(ID_HELP_BOOKMARKS_THELPG, OnHelpBookmarksThelpg)
	ON_COMMAND(ID_HELP_BOOKMARKS_CALCSOFTWARE, OnHelpBookmarksCalcsoftware)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	// Roms: disabled
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTiLPApp construction

CTiLPApp::CTiLPApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTiLPApp object

CTiLPApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTiLPApp initialization

BOOL CTiLPApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	tilp_paths_init();			// for icons

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Linux Programmer Group"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;

	pDocTemplate = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CLeftDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CLeftView));
	AddDocTemplate(pDocTemplate);
/*
	pDocTemplate = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CScreenDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CScreenView));
	AddDocTemplate(pDocTemplate);
*/
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// DON'T display a new MDI child window during startup!!!
	//cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	if (m_lpCmdLine[0] == _T('\0'))
	{
      // Create a new (empty) document.
      OnFileNew();
	}

	/* Init the tilp core */
	//ticable_DISPLAY_settings(DSP_ON);
	tilp_main(__argc, __argv, NULL);	//sub_main(argc, argv, arge);

	/* Init the GUI independant functions */
	gui_functions.msg_box      = mfc_msg_box;
	gui_functions.user1_box    = mfc_user1_box;
	gui_functions.user2_box    = mfc_user2_box;
	gui_functions.user3_box    = mfc_user3_box;
	gui_functions.dlgbox_entry = mfc_dlgbox_entry;
	gui_functions.create_pbar_type1 = mfc_create_pbar_type1;
	gui_functions.create_pbar_type2 = mfc_create_pbar_type2;
	gui_functions.create_pbar_type3 = mfc_create_pbar_type3;
	gui_functions.create_pbar_type4 = mfc_create_pbar_type4;
	gui_functions.create_pbar_type5 = mfc_create_pbar_type5;
	gui_functions.destroy_pbar      = mfc_destroy_pbar;
	tilp_gui_set_fncts(&gui_functions);
	mfc_init_refresh_functions();

	working_mode = MODE_MFC | MODE_GUI;

	/* display console mode errors (startup) */
	tilp_error(0);

	/* Do a local directory list */
	g_free(clist_win.cur_dir);
	clist_win.cur_dir = g_get_current_dir();

	// Dispatch commands specified on the command line
	// I've commented it since I process the command line by hand
	//if (!ProcessShellCommand(cmdInfo))
	//	return FALSE;

	/* Create the main window */
	// The main window has been initialized, so show and update it.
	RetrieveCalcOperations();
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	/* 
     If variables have been passed on the command line in GUI mode then
     send them 
	*/
	if(working_mode == MODE_MFC)
    {
      tilp_cmdline_send();
    }

	pMainFrame->RefreshRightView();

	return TRUE;
}


BOOL CTiLPApp::ExitInstance()
{
	int err;

	if( (err = link_cable.exit()) )
    {
		DISPLAY_ERROR("link_cable.term_port: error code %i\n", err);
		tilp_error(err);
    }
	ticalc_exit();
	ticable_exit();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTiLPApp message handlers

BOOL CTiLPApp::OnIdle(LONG lCount) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CWinApp::OnIdle(lCount);
}

BOOL CTiLPApp::PeekAndPump()
{
	MSG msg;
	while(::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
	{
		if(!AfxGetApp()->PumpMessage())
		{
			::PostQuitMessage(0);
			return FALSE;
		}
	}

	LONG lIdle = 0;
	while(AfxGetApp()->OnIdle(lIdle++));
	return TRUE;
}

void CTiLPApp::RetrieveCalcOperations()
{
	CWnd* pWnd = AfxGetMainWnd();
	CMainFrame *pFrame = (CMainFrame *)pWnd;

	pFrame->CalcOps.bReady   = (ti_calc.supported_operations() & OPS_ISREADY) ? TRUE : FALSE;
	pFrame->CalcOps.bScreen  = (ti_calc.supported_operations() & OPS_SCREENDUMP) ? TRUE : FALSE;
	pFrame->CalcOps.bDirlist = (ti_calc.supported_operations() & OPS_DIRLIST) ? TRUE : FALSE;
	pFrame->CalcOps.bRemote  = (ti_calc.supported_operations() & OPS_SEND_KEY) ? TRUE : FALSE;
	pFrame->CalcOps.bBackup  = (ti_calc.supported_operations() & OPS_RECV_BACKUP) ? TRUE : FALSE;
	pFrame->CalcOps.bFlash   = (ti_calc.supported_operations() & OPS_RECV_FLASH) ? TRUE : FALSE;
	pFrame->CalcOps.bIdlist  = (ti_calc.supported_operations() & OPS_IDLIST) ? TRUE : FALSE;
	pFrame->CalcOps.bRomDump = (ti_calc.supported_operations() & OPS_ROMDUMP) ? TRUE : FALSE;
	pFrame->CalcOps.bRomVersion = (ti_calc.supported_operations() & OPS_ROMVERSION) ? TRUE : FALSE;
	pFrame->CalcOps.bClock   = (ti_calc.supported_operations() & OPS_CLOCK) ? TRUE : FALSE;
}

/*****************/
/* Menu handlers */
/*****************/

void CTiLPApp::OnFileSaveConfig() 
{
	// TODO: Add your command handler code here
	tilp_config_save();	
}

void CTiLPApp::OnFileLoadConfig() 
{
	// TODO: Add your command handler code here
	tilp_config_load();	
}

void CTiLPApp::OnFileDefaultConfig() 
{
	// TODO: Add your command handler code here
	tilp_config_default();
}

void CTiLPApp::OnSetupGeneral() 
{
	// TODO: Add your command handler code here
	CMiscSht miscSht(_T("General Settings"));
	miscSht.DoModal();
}

void CTiLPApp::OnSetupScreen() 
{
	// TODO: Add your command handler code here
	CScreenSht screenSht(_T("Screenshot Settings"));
	screenSht.DoModal();
}

void CTiLPApp::OnSetupComm() 
{
	// TODO: Add your command handler code here
	CCommSht   commSht(_T("Communication Settings"));
	commSht.DoModal();
}

void CTiLPApp::OnSetupExternalprograms() 
{
	// TODO: Add your command handler code here
	CPrgmsSht prgmsSht(_T("External Programs"));
	prgmsSht.DoModal();
}

void CTiLPApp::OnHelpAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CTiLPApp::OnHelpHelp() 
{
	// TODO: Add your command handler code here
	CString szString = CString("C:\\Program Files\\Internet Explorer\\iexplore.exe");

	szString += " ";
	szString += "file:\\";
	szString += inst_paths.help_dir;
	szString += "User_Manual.html";

	WinExec(szString, SW_SHOW);
}

void CTiLPApp::OnHelpManpage() 
{
	// TODO: Add your command handler code here
	CManpageDlg manpageDlg;
	manpageDlg.DoModal();
}

void CTiLPApp::OnHelpBookmarksTiswebsite() 
{
	// TODO: Add your command handler code here
	WinExec("C:\\Program Files\\Internet Explorer\\iexplore.exe http://education.ti.com", SW_SHOW);
}

void CTiLPApp::OnHelpBookmarksCalcsoftware() 
{
	// TODO: Add your command handler code here
	WinExec("C:\\Program Files\\Internet Explorer\\iexplore.exe http://epsstore.ti.com", SW_SHOW);
}

void CTiLPApp::OnHelpBookmarksTinewsnet() 
{
	// TODO: Add your command handler code here
	WinExec("C:\\Program Files\\Internet Explorer\\iexplore.exe http://www.tinews.net", SW_SHOW);
}

void CTiLPApp::OnHelpBookmarksTilpswebsite() 
{
	// TODO: Add your command handler code here
	WinExec("C:\\Program Files\\Internet Explorer\\iexplore.exe http://tilp.info", SW_SHOW);
}

void CTiLPApp::OnHelpBookmarksTifrorg() 
{
	// TODO: Add your command handler code here
	WinExec("C:\\Program Files\\Internet Explorer\\iexplore.exe http://www.ti-fr.org", SW_SHOW);
}

void CTiLPApp::OnHelpBookmarksTicalcorg() 
{
	// TODO: Add your command handler code here
	WinExec("C:\\Program Files\\Internet Explorer\\iexplore.exe http://www.ticalc.org", SW_SHOW);
}

void CTiLPApp::OnHelpBookmarksThelpg() 
{
	// TODO: Add your command handler code here
	WinExec("C:\\Program Files\\Internet Explorer\\iexplore.exe http://www.ti-lpg.org", SW_SHOW);
}


