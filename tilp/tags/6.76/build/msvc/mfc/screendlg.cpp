// ScreenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "ScreenDlg.h"
#include "ScreenSht.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScreenDlg dialog


CScreenDlg::CScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScreenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScreenDlg)
	//}}AFX_DATA_INIT
}

void CScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScreenDlg)
	DDX_Control(pDX, IDC_SCREEN_IMAGE, m_wndStatic);
	//}}AFX_DATA_MAP
	int iOffset = 10;
	m_wndStatic.DestroyWindow();
	m_wndStatic.Create(_T(""), WS_CHILD | WS_VISIBLE | SS_ICON | SS_CENTERIMAGE, 
		CRect(iOffset, iOffset, iOffset+ti_screen.img.width, iOffset+ti_screen.img.height), 
		(CWnd *)(this), IDC_STATIC);
}


BEGIN_MESSAGE_MAP(CScreenDlg, CDialog)
	//{{AFX_MSG_MAP(CScreenDlg)
	ON_BN_CLICKED(ID_SC_CLIPBOARD, OnScClipboard)
	ON_BN_CLICKED(ID_SC_SAVE, OnScSave)
	ON_BN_CLICKED(ID_SC_LOAD, OnScLoad)
	ON_BN_CLICKED(ID_SC_REFRESH, OnScRefresh)
	ON_BN_CLICKED(ID_SC_OPTIONS, OnScOptions)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_MESSAGE (WM_USER_THREAD2_FINISHED, OnThread2Finished)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScreenDlg message handlers

void CScreenDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	m_wndStatic.DestroyWindow();
	DestroyWindow();
	
	//CDialog::OnCancel();
}

void CScreenDlg::OnScClipboard() 
{
	// TODO: Add your control notification handler code here
	
}

void CScreenDlg::OnScSave() 
{
	// TODO: Add your control notification handler code here
	CString ext;
	char BASED_CODE *szFilter;

	if(options.screen_format == XPM) {
		ext = ".xpm";
		szFilter = "XPM Files (*.xpm)|*.xpm|PCX Files (*.pcx)|*.pcx|JPEG Files (*.jpg)|*.jpg|Bitmap Files (*.bmp)|*.bmp||";
	}
	else if(options.screen_format == PCX) {
		ext = ".pcx";
		szFilter = "PCX Files (*.pcx)|*.pcx|Pixmap Files (*.xpm)|*.xpm|JPEG Files (*.jpg)|*.jpg|Bitmap Files (*.bmp)|*.bmp||";
	}
	else if(options.screen_format == JPG) {
		ext = ".jpg";
		szFilter = "JPG Files (*.jpg)|*.jpg|Pixmap Files (*.xpm)|*.xpm|PCX Files (*.pcx)|*.pcx|Bitmap Files (*.bmp)|*.bmp||";
	}
	else if(options.screen_format == BMP) {
		ext = ".bmp";
		szFilter = "BMP Files (*.bmp)|*.bmp|Pixmap Files (*.xpm)|*.xpm|JPEG Files (*.jpg)|*.jpg|PCX Files (*.pcx)|*.pcx||";
	}

	//char BASED_CODE szFilter[] = "PCX Files (*.pcx)|*.pcx|Pixmap Files (*.xpm)|*.xpm|JPEG Files (*.jpg)|*.jpg|Bitmap Files (*.bmp)|*.bmp||";
	CFileDialog dlgFile(FALSE, ext, "screenshot", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	dlgFile.m_ofn.lpstrInitialDir = _T(clist_win.cur_dir);

	if(dlgFile.DoModal() == IDOK)
	{
		if(tilp_screen_save(dlgFile.GetPathName().GetBuffer(1024)))
			AfxMessageBox("Error while saving image");
	}
}


#define strcasecmp _stricmp

void CScreenDlg::OnScLoad() 
{
	char BASED_CODE *szFilter;

	// TODO: Add your control notification handler code here
	if(options.screen_format == XPM) {
		szFilter = "XPM Files (*.xpm)|*.xpm|PCX Files (*.pcx)|*.pcx|JPEG Files (*.jpg)|*.jpg|Bitmap Files (*.bmp)|*.bmp||";
	}
	else if(options.screen_format == PCX) {
		szFilter = "PCX Files (*.pcx)|*.pcx|Pixmap Files (*.xpm)|*.xpm|JPEG Files (*.jpg)|*.jpg|Bitmap Files (*.bmp)|*.bmp||";
	}
	else if(options.screen_format == JPG) {
		szFilter = "JPG Files (*.jpg)|*.jpg|Pixmap Files (*.xpm)|*.xpm|PCX Files (*.pcx)|*.pcx|Bitmap Files (*.bmp)|*.bmp||";
	}
	else if(options.screen_format == BMP) {
		szFilter = "BMP Files (*.bmp)|*.bmp|Pixmap Files (*.xpm)|*.xpm|JPEG Files (*.jpg)|*.jpg|PCX Files (*.pcx)|*.pcx||";
	}

	CFileDialog dlgFile(TRUE, ".pcx", "screenshot", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	dlgFile.m_ofn.lpstrInitialDir = _T(clist_win.cur_dir);

	if(dlgFile.DoModal() == IDOK)
	{
		FILE *f;
		char *ext;
		char *filename;
		
		filename = g_strdup(dlgFile.GetPathName().GetBuffer(1024));
		ext = (char *)strrchr(filename, '.');

		f = fopen(filename, "rb");
		if(f == NULL)
		{
			gif->msg_box("Error", "Unable to open the file.");
			return ;
		}
	
		ti_screen.img.depth = 2;
		if(!strcasecmp(ext, ".pcx"))
			read_pcx_format(f, &(ti_screen.img));
		else if(!strcasecmp(ext, ".xpm"))
			read_xpm_format(f, &(ti_screen.img));
		else if(!strcasecmp(ext, ".jpg"))
			read_jpg_format(f, &(ti_screen.img));
		else if(!strcasecmp(ext, ".bmp"))
			read_bmp_format(f, &(ti_screen.img));
		else
		{
			gif->msg_box("Error", "Invalid file.");
			return;
		}
		fclose(f);
		g_free(filename);

		// Display image
		CDC *pDC;
		CDC dcMem;
		CBitmap bmp;
		BITMAP bm;
		CBitmap* pOldBmp;

		pDC = m_wndStatic.GetDC();
/*
		for(int i=0; i<(ti_screen.img.width * ti_screen.img.height) / 8; i++) {
			ti_screen.img.bitmap[i] = ~i;
		}
*/
		bmp.CreateBitmap(ti_screen.img.width, ti_screen.img.height,
							1, 1, ti_screen.img.bitmap);
		bmp.GetObject(sizeof(BITMAP), &bm);
		dcMem.CreateCompatibleDC(pDC);

		pOldBmp = dcMem.SelectObject(&bmp);
		pDC->BitBlt((240 - bm.bmWidth) >> 1, 
					(128 - bm.bmHeight) >> 1, 
					bm.bmWidth, 
					bm.bmHeight, 
					&dcMem, 0, 0, SRCCOPY);

		dcMem.SelectObject(pOldBmp);
	}
}

UINT Thread2Func(LPVOID pParam);
void CScreenDlg::OnScRefresh() 
{
	// TODO: Add your control notification handler code here
	/* Get a screen capture */
	CWinThread* pThread = AfxBeginThread(Thread2Func, this, 
		THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

	::DuplicateHandle(GetCurrentProcess(), pThread->m_hThread, 
		GetCurrentProcess(), &m_hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);

	pThread->ResumeThread();

	return;
}

static clock_t start, finish;
static double duration;

UINT Thread2Func(LPVOID pParam)
{
	start = clock();
	if(tilp_screen_capture()) 
		return 0;
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;

	CScreenDlg *pBox = (CScreenDlg *)pParam;
	pBox->PostMessage(WM_USER_THREAD2_FINISHED, 0, 0);

	return 0;
}

LRESULT CScreenDlg::OnThread2Finished (WPARAM wParam, LPARAM lParam)
{
	// Ensure that thread is terminated
	ASSERT(m_hThread != NULL);
	::WaitForSingleObject(m_hThread, INFINITE);
	::CloseHandle(m_hThread);
	m_hThread = NULL;

	tilp_invert_bitmap(&ti_screen.img);	// bug ?
	OnPaint();

    return 0;
}

void CScreenDlg::GetScreenDump()
{
	OnScRefresh();
}

void CScreenDlg::OnScOptions() 
{
	// TODO: Add your control notification handler code here
	CScreenSht screenSht(_T("Screenshot Settings"));
	screenSht.DoModal();
}

void CScreenDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDC *pDC;
	CDC dcMem;
	CBitmap bmp;
	BITMAP bm;
	CBitmap* pOldBmp;

	pDC = m_wndStatic.GetDC();
	bmp.CreateBitmap(ti_screen.img.width, ti_screen.img.height,
						1, 1, ti_screen.img.bitmap);
	bmp.GetObject(sizeof(BITMAP), &bm);
	dcMem.CreateCompatibleDC(pDC);

	pOldBmp = dcMem.SelectObject(&bmp);
	pDC->BitBlt((240 - bm.bmWidth) >> 1, 
				(128 - bm.bmHeight) >> 1, 
				bm.bmWidth, 
				bm.bmHeight, 
				&dcMem, 0, 0, SRCCOPY);

	dcMem.SelectObject(pOldBmp);
	// Do not call CDialog::OnPaint() for painting messages
}
