// CommPg2.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "CommPg2.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommPg2 property page

IMPLEMENT_DYNCREATE(CCommPg2, CPropertyPage)

CCommPg2::CCommPg2() : CPropertyPage(CCommPg2::IDD)
{
	//{{AFX_DATA_INIT(CCommPg2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCommPg2::~CCommPg2()
{
}

void CCommPg2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommPg2)
	DDX_Control(pDX, IDC_CALC_V200, m_v200);
	DDX_Control(pDX, IDC_CALC_92P, m_ti92p);
	DDX_Control(pDX, IDC_CALC_92, m_ti92);
	DDX_Control(pDX, IDC_CALC_89, m_ti89);
	DDX_Control(pDX, IDC_CALC_86, m_ti86);
	DDX_Control(pDX, IDC_CALC_85, m_ti85);
	DDX_Control(pDX, IDC_CALC_83P, m_ti83p);
	DDX_Control(pDX, IDC_CALC_83, m_ti83);
	DDX_Control(pDX, IDC_CALC_82, m_ti82);
	DDX_Control(pDX, IDC_CALC_73, m_ti73);
	DDX_Control(pDX, IDC_AUTO_DETECT, m_autodetect);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommPg2, CPropertyPage)
	//{{AFX_MSG_MAP(CCommPg2)
	ON_BN_CLICKED(IDC_AUTO_DETECT, OnAutoDetect)
	ON_BN_CLICKED(IDC_CALC_73, OnCalc73)
	ON_BN_CLICKED(IDC_CALC_82, OnCalc82)
	ON_BN_CLICKED(IDC_CALC_83, OnCalc83)
	ON_BN_CLICKED(IDC_CALC_83P, OnCalc83p)
	ON_BN_CLICKED(IDC_CALC_85, OnCalc85)
	ON_BN_CLICKED(IDC_CALC_86, OnCalc86)
	ON_BN_CLICKED(IDC_CALC_89, OnCalc89)
	ON_BN_CLICKED(IDC_CALC_92, OnCalc92)
	ON_BN_CLICKED(IDC_CALC_92P, OnCalc92p)
	ON_BN_CLICKED(IDC_CALC_V200, OnCalcV200)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommPg2 message handlers

void CCommPg2::OnOK() 
{
	// TODO: Add extra validation here
	CPropertyPage::OnOK();
}

BOOL CCommPg2::OnApply()
{
	// TODO: Add extra validation here
	if(m_v200.GetCheck())  options.lp.calc_type = CALC_V200;
	if(m_ti92p.GetCheck()) options.lp.calc_type = CALC_TI92P;
	if(m_ti92.GetCheck())  options.lp.calc_type = CALC_TI92;
	if(m_ti89.GetCheck())  options.lp.calc_type = CALC_TI89;
	if(m_ti86.GetCheck())  options.lp.calc_type = CALC_TI86;
	if(m_ti85.GetCheck())  options.lp.calc_type = CALC_TI85;
	if(m_ti83p.GetCheck()) options.lp.calc_type = CALC_TI83P;
	if(m_ti83.GetCheck())  options.lp.calc_type = CALC_TI83;
	if(m_ti82.GetCheck())  options.lp.calc_type = CALC_TI82;
	if(m_ti73.GetCheck())  options.lp.calc_type = CALC_TI73;

	if(m_autodetect.GetCheck() == 1)
		options.auto_detect = !0;
	else
		options.auto_detect = 0;

	// Update link parameters
	if(tilp_error(link_cable.exit())) 
		return FALSE;

	ticable_set_param(&options.lp);
	tilp_error(ticable_set_cable(options.lp.link_type, &link_cable));
	ticalc_set_cable(&link_cable);
	ticalc_set_calc(options.lp.calc_type, &ti_calc);

	if(tilp_error(link_cable.init())) 
		return FALSE;

	return TRUE;
}

void CCommPg2::OnAutoDetect() 
{
	// TODO: Add your control notification handler code here
	SetModified(TRUE);	
}

BOOL CCommPg2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	switch(options.lp.calc_type)
	{
		case CALC_V200:  m_v200.SetCheck(1);  m_autodetect.EnableWindow(FALSE); break;
		case CALC_TI92P: m_ti92p.SetCheck(1); m_autodetect.EnableWindow(TRUE);  break;
		case CALC_TI92:  m_ti92.SetCheck(1);  m_autodetect.EnableWindow(FALSE); break;
		case CALC_TI89:  m_ti89.SetCheck(1);  m_autodetect.EnableWindow(TRUE);  break;
		case CALC_TI86:  m_ti86.SetCheck(1);  m_autodetect.EnableWindow(FALSE); break;
		case CALC_TI85:  m_ti85.SetCheck(1);  m_autodetect.EnableWindow(FALSE); break;
		case CALC_TI83P: m_ti83p.SetCheck(1); m_autodetect.EnableWindow(TRUE);  break;
		case CALC_TI83:  m_ti83.SetCheck(1);  m_autodetect.EnableWindow(FALSE); break;
		case CALC_TI82:  m_ti82.SetCheck(1);  m_autodetect.EnableWindow(FALSE); break;
		case CALC_TI73:  m_ti73.SetCheck(1);  m_autodetect.EnableWindow(TRUE);  break;
	}

	if(options.auto_detect)
		m_autodetect.SetCheck(1);
	else
		m_autodetect.SetCheck(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCommPg2::OnCalc73() 
{
	// TODO: Add your control notification handler code here
	m_ti82.SetCheck(0);
	m_ti83.SetCheck(0);
	m_ti83p.SetCheck(0);
	m_ti85.SetCheck(0);
	m_ti86.SetCheck(0);
	m_ti89.SetCheck(0);
	m_ti92.SetCheck(0);
	m_ti92p.SetCheck(0);
	m_v200.SetCheck(0);

	m_autodetect.EnableWindow(TRUE);

	SetModified(TRUE);
}

void CCommPg2::OnCalc82() 
{
	// TODO: Add your control notification handler code here
	m_ti73.SetCheck(0);
	m_ti83.SetCheck(0);
	m_ti83p.SetCheck(0);
	m_ti85.SetCheck(0);
	m_ti86.SetCheck(0);
	m_ti89.SetCheck(0);
	m_ti92.SetCheck(0);
	m_ti92p.SetCheck(0);
	m_v200.SetCheck(0);

	m_autodetect.EnableWindow(FALSE);

	SetModified(TRUE);
}

void CCommPg2::OnCalc83() 
{
	// TODO: Add your control notification handler code here
	m_ti73.SetCheck(0);
	m_ti82.SetCheck(0);
	m_ti83p.SetCheck(0);
	m_ti85.SetCheck(0);
	m_ti86.SetCheck(0);
	m_ti89.SetCheck(0);
	m_ti92.SetCheck(0);
	m_ti92p.SetCheck(0);
	m_v200.SetCheck(0);

	m_autodetect.EnableWindow(FALSE);

	SetModified(TRUE);
}

void CCommPg2::OnCalc83p() 
{
	// TODO: Add your control notification handler code here
	m_ti73.SetCheck(0);
	m_ti82.SetCheck(0);
	m_ti83.SetCheck(0);
	m_ti85.SetCheck(0);
	m_ti86.SetCheck(0);
	m_ti89.SetCheck(0);
	m_ti92.SetCheck(0);
	m_ti92p.SetCheck(0);
	m_v200.SetCheck(0);

	m_autodetect.EnableWindow(TRUE);

	SetModified(TRUE);
}

void CCommPg2::OnCalc85() 
{
	// TODO: Add your control notification handler code here
	m_ti73.SetCheck(0);
	m_ti82.SetCheck(0);
	m_ti83.SetCheck(0);
	m_ti83p.SetCheck(0);
	m_ti86.SetCheck(0);
	m_ti89.SetCheck(0);
	m_ti92.SetCheck(0);
	m_ti92p.SetCheck(0);
	m_v200.SetCheck(0);

	m_autodetect.EnableWindow(FALSE);

	SetModified(TRUE);
}

void CCommPg2::OnCalc86() 
{
	// TODO: Add your control notification handler code here
	m_ti73.SetCheck(0);
	m_ti82.SetCheck(0);
	m_ti83.SetCheck(0);
	m_ti83p.SetCheck(0);
	m_ti85.SetCheck(0);
	m_ti89.SetCheck(0);
	m_ti92.SetCheck(0);
	m_ti92p.SetCheck(0);
	m_v200.SetCheck(0);

	m_autodetect.EnableWindow(FALSE);

	SetModified(TRUE);
}

void CCommPg2::OnCalc89() 
{
	// TODO: Add your control notification handler code here
	m_ti73.SetCheck(0);
	m_ti82.SetCheck(0);
	m_ti83.SetCheck(0);
	m_ti83p.SetCheck(0);
	m_ti85.SetCheck(0);
	m_ti86.SetCheck(0);
	m_ti92.SetCheck(0);
	m_ti92p.SetCheck(0);
	m_v200.SetCheck(0);

	m_autodetect.EnableWindow(TRUE);

	SetModified(TRUE);
}

void CCommPg2::OnCalc92() 
{
	// TODO: Add your control notification handler code here
	m_ti73.SetCheck(0);
	m_ti82.SetCheck(0);
	m_ti83.SetCheck(0);
	m_ti83p.SetCheck(0);
	m_ti85.SetCheck(0);
	m_ti86.SetCheck(0);
	m_ti89.SetCheck(0);
	m_ti92p.SetCheck(0);
	m_v200.SetCheck(0);

	m_autodetect.EnableWindow(FALSE);

	SetModified(TRUE);
}

void CCommPg2::OnCalc92p() 
{
	// TODO: Add your control notification handler code here
	m_ti73.SetCheck(0);
	m_ti82.SetCheck(0);
	m_ti83.SetCheck(0);
	m_ti83p.SetCheck(0);
	m_ti85.SetCheck(0);
	m_ti86.SetCheck(0);
	m_ti89.SetCheck(0);
	m_ti92.SetCheck(0);
	m_v200.SetCheck(0);

	m_autodetect.EnableWindow(TRUE);

	SetModified(TRUE);
}

void CCommPg2::OnCalcV200() 
{
	// TODO: Add your control notification handler code here
	m_ti82.SetCheck(0);
	m_ti83.SetCheck(0);
	m_ti83p.SetCheck(0);
	m_ti85.SetCheck(0);
	m_ti86.SetCheck(0);
	m_ti89.SetCheck(0);
	m_ti92.SetCheck(0);
	m_ti92p.SetCheck(0);
	m_v200.SetCheck(0);

	m_autodetect.EnableWindow(FALSE);

	SetModified(TRUE);
}
