// ScreenPg2.cpp : implementation file
//

#include "stdafx.h"
#include "tilp.h"
#include "ScreenPg2.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScreenPg2 property page

IMPLEMENT_DYNCREATE(CScreenPg2, CPropertyPage)

CScreenPg2::CScreenPg2() : CPropertyPage(CScreenPg2::IDD)
{
	//{{AFX_DATA_INIT(CScreenPg2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CScreenPg2::~CScreenPg2()
{
}

void CScreenPg2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScreenPg2)
	DDX_Control(pDX, IDC_BLURRY, m_grayscale);
	DDX_Control(pDX, IDC_FULL_SCREEN, m_full_screen);
	DDX_Control(pDX, IDC_CLIPPED_SCREEN, m_clipped_screen);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScreenPg2, CPropertyPage)
	//{{AFX_MSG_MAP(CScreenPg2)
	ON_BN_CLICKED(IDC_CLIPPED_SCREEN, OnClippedScreen)
	ON_BN_CLICKED(IDC_FULL_SCREEN, OnFullScreen)
	ON_BN_CLICKED(IDC_BLURRY, OnBlurry)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScreenPg2 message handlers

BOOL CScreenPg2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
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

void CScreenPg2::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

BOOL CScreenPg2::OnApply() 
{
	// TODO: Add extra cleanup here
	if(m_full_screen.GetCheck()) options.screen_clipping = FULL_SCREEN;
	if(m_clipped_screen.GetCheck()) options.screen_clipping = CLIPPED_SCREEN;

	if(m_grayscale.GetCheck() == 1)
		options.screen_blurry = !0;
	else
		options.screen_blurry = 0;
	
	return TRUE;
}

void CScreenPg2::OnFullScreen() 
{
	// TODO: Add your control notification handler code here
	m_clipped_screen.SetCheck(0);

	SetModified(TRUE);
}

void CScreenPg2::OnClippedScreen() 
{
	// TODO: Add your control notification handler code here
	m_full_screen.SetCheck(0);

	SetModified(TRUE);
}

void CScreenPg2::OnBlurry() 
{
	// TODO: Add your control notification handler code here
	SetModified(TRUE);
}
