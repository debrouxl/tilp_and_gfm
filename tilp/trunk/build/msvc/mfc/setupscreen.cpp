// SetupScreen.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "SetupScreen.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetupScreenDlg dialog


SetupScreenDlg::SetupScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SetupScreenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SetupScreenDlg)
	//}}AFX_DATA_INIT
}


void SetupScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SetupScreenDlg)
	DDX_Control(pDX, IDC_BLURRY, m_grayscale);
	DDX_Control(pDX, IDC_XPM, m_xpm);
	DDX_Control(pDX, IDC_BMP, m_bmp);
	DDX_Control(pDX, IDC_PCX, m_pcx);
	DDX_Control(pDX, IDC_JPG, m_jpg);
	DDX_Control(pDX, IDC_FULL_SCREEN, m_full_screen);
	DDX_Control(pDX, IDC_CLIPPED_SCREEN, m_clipped_screen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SetupScreenDlg, CDialog)
	//{{AFX_MSG_MAP(SetupScreenDlg)
	ON_BN_CLICKED(IDC_PCX, OnPcx)
	ON_BN_CLICKED(IDC_XPM, OnXpm)
	ON_BN_CLICKED(IDC_JPG, OnJpg)
	ON_BN_CLICKED(IDC_CLIPPED_SCREEN, OnClippedScreen)
	ON_BN_CLICKED(IDC_FULL_SCREEN, OnFullScreen)
	ON_BN_CLICKED(IDC_BMP, OnBmp)
	ON_BN_CLICKED(IDC_BMP, OnBmp)
	ON_BN_CLICKED(IDC_BLURRY, OnBlurry)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SetupScreenDlg message handlers

void SetupScreenDlg::OnOK() 
{
	// TODO: Add extra validation here
	if(m_pcx.GetCheck()) options.screen_format = PCX;
	if(m_bmp.GetCheck()) options.screen_format = BMP;
	if(m_xpm.GetCheck()) options.screen_format = XPM;
	if(m_jpg.GetCheck()) options.screen_format = JPG;

	if(m_full_screen.GetCheck()) options.screen_clipping = FULL_SCREEN;
	if(m_clipped_screen.GetCheck()) options.screen_clipping = CLIPPED_SCREEN;

	if(m_grayscale.GetCheck() == 1)
		options.screen_blurry = !0;
	else
		options.screen_blurry = 0;

	CDialog::OnOK();
}

void SetupScreenDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void SetupScreenDlg::OnPcx() 
{
	// TODO: Add your control notification handler code here
	m_xpm.SetCheck(0);
	m_jpg.SetCheck(0);
	m_bmp.SetCheck(0);
}

void SetupScreenDlg::OnBmp() 
{
	// TODO: Add your control notification handler code here
	m_xpm.SetCheck(0);
	m_jpg.SetCheck(0);
	m_pcx.SetCheck(0);
}

void SetupScreenDlg::OnXpm() 
{
	// TODO: Add your control notification handler code here
	m_pcx.SetCheck(0);
	m_jpg.SetCheck(0);
	m_bmp.SetCheck(0);
}

void SetupScreenDlg::OnJpg() 
{
	// TODO: Add your control notification handler code here
	m_xpm.SetCheck(0);
	m_pcx.SetCheck(0);
	m_bmp.SetCheck(0);
}

BOOL SetupScreenDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	switch(options.screen_format)
	{
		case PCX: m_pcx.SetCheck(1); break;
		case BMP: m_bmp.SetCheck(1); break;
		case XPM: m_xpm.SetCheck(1); break;
		case JPG: m_jpg.SetCheck(1); break;
	}

	switch(options.screen_clipping)
	{
	case FULL_SCREEN: m_full_screen.SetCheck(1); break;
	case CLIPPED_SCREEN: m_clipped_screen.SetCheck(1); break;
	}

	if(options.screen_blurry == !0)
		m_grayscale.SetCheck(1);
	else
		m_grayscale.SetCheck(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SetupScreenDlg::OnFullScreen() 
{
	// TODO: Add your control notification handler code here
	m_clipped_screen.SetCheck(0);
}

void SetupScreenDlg::OnClippedScreen() 
{
	// TODO: Add your control notification handler code here
	m_full_screen.SetCheck(0);
}

void SetupScreenDlg::OnBlurry() 
{
	// TODO: Add your control notification handler code here
	
}
