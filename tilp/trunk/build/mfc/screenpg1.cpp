// ScreenPg1.cpp : implementation file
//

#include "stdafx.h"
#include "tilp.h"
#include "ScreenPg1.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScreenPg1 property page

IMPLEMENT_DYNCREATE(CScreenPg1, CPropertyPage)

CScreenPg1::CScreenPg1() : CPropertyPage(CScreenPg1::IDD)
{
	//{{AFX_DATA_INIT(CScreenPg1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CScreenPg1::~CScreenPg1()
{
}

void CScreenPg1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScreenPg1)
	DDX_Control(pDX, IDC_XPM, m_xpm);
	DDX_Control(pDX, IDC_BMP, m_bmp);
	DDX_Control(pDX, IDC_PCX, m_pcx);
	DDX_Control(pDX, IDC_JPG, m_jpg);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScreenPg1, CPropertyPage)
	//{{AFX_MSG_MAP(CScreenPg1)
	ON_BN_CLICKED(IDC_PCX, OnPcx)
	ON_BN_CLICKED(IDC_XPM, OnXpm)
	ON_BN_CLICKED(IDC_JPG, OnJpg)
	ON_BN_CLICKED(IDC_BMP, OnBmp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScreenPg1 message handlers

BOOL CScreenPg1::OnInitDialog() 
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

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CScreenPg1::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

BOOL CScreenPg1::OnApply() 
{
	// TODO: Add extra cleanup here
	if(m_pcx.GetCheck()) options.screen_format = PCX;
	if(m_bmp.GetCheck()) options.screen_format = BMP;
	if(m_xpm.GetCheck()) options.screen_format = XPM;
	if(m_jpg.GetCheck()) options.screen_format = JPG;

	return TRUE;
}

void CScreenPg1::OnPcx() 
{
	// TODO: Add your control notification handler code here
	m_xpm.SetCheck(0);
	m_jpg.SetCheck(0);
	m_bmp.SetCheck(0);

	SetModified(TRUE);
}

void CScreenPg1::OnBmp() 
{
	// TODO: Add your control notification handler code here
	m_xpm.SetCheck(0);
	m_jpg.SetCheck(0);
	m_pcx.SetCheck(0);

	SetModified(TRUE);
}

void CScreenPg1::OnXpm() 
{
	// TODO: Add your control notification handler code here
	m_pcx.SetCheck(0);
	m_jpg.SetCheck(0);
	m_bmp.SetCheck(0);

	SetModified(TRUE);
}

void CScreenPg1::OnJpg() 
{
	// TODO: Add your control notification handler code here
	m_xpm.SetCheck(0);
	m_pcx.SetCheck(0);
	m_bmp.SetCheck(0);

	SetModified(TRUE);
}
