// CommPg1.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "CommPg1.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommPg1 property page

IMPLEMENT_DYNCREATE(CCommPg1, CPropertyPage)

CCommPg1::CCommPg1() : CPropertyPage(CCommPg1::IDD)
{
	//{{AFX_DATA_INIT(CCommPg1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCommPg1::~CCommPg1()
{
}

void CCommPg1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommPg1)
	DDX_Control(pDX, IDC_TGL_LINK, m_tgl);
	DDX_Control(pDX, IDC_SER_LINK, m_ser);
	DDX_Control(pDX, IDC_PAR_LINK, m_par);
	DDX_Control(pDX, IDC_AVR_LINK, m_avr);
	DDX_Control(pDX, IDC_TIE_LINK, m_tie);
	DDX_Control(pDX, IDC_VTI_LINK, m_vti);
	DDX_Control(pDX, IDC_UGL_LINK, m_ugl);
	DDX_Control(pDX, IDC_PORT1, m_port1);
	DDX_Control(pDX, IDC_PORT2, m_port2);
	DDX_Control(pDX, IDC_PORT3, m_port3);
	DDX_Control(pDX, IDC_PORT4, m_port4);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommPg1, CPropertyPage)
	//{{AFX_MSG_MAP(CCommPg1)
	ON_BN_CLICKED(IDC_SER_LINK, OnSerLink)
	ON_BN_CLICKED(IDC_TGL_LINK, OnTglLink)
	ON_BN_CLICKED(IDC_TIE_LINK, OnTieLink)
	ON_BN_CLICKED(IDC_UGL_LINK, OnUglLink)
	ON_BN_CLICKED(IDC_VTI_LINK, OnVtiLink)
	ON_BN_CLICKED(IDC_AVR_LINK, OnAvrLink)
	ON_BN_CLICKED(IDC_PAR_LINK, OnParLink)
	ON_BN_CLICKED(IDC_PORT1, OnPort1)
	ON_BN_CLICKED(IDC_PORT2, OnPort2)
	ON_BN_CLICKED(IDC_PORT3, OnPort3)
	ON_BN_CLICKED(IDC_PORT4, OnPort4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommPg1 message handlers

BOOL CCommPg1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	switch(options.lp.link_type)
	{
		case LINK_TGL: m_tgl.SetCheck(1); OnTglLink(); break;
		case LINK_SER: m_ser.SetCheck(1); OnSerLink(); break;
		case LINK_PAR: m_par.SetCheck(1); OnParLink(); break;
		case LINK_AVR: m_avr.SetCheck(1); OnAvrLink(); break;
		case LINK_TIE: m_tie.SetCheck(1); OnTieLink(); break;
		case LINK_VTI: m_vti.SetCheck(1); OnVtiLink(); break;
		case LINK_UGL: m_ugl.SetCheck(1); OnUglLink(); break;
	}

	switch(options.lp.port)
	{
		case PARALLEL_PORT_1:
		case SERIAL_PORT_1:
		case VIRTUAL_PORT_1:
		case USB_PORT_1: 
			m_port1.SetCheck(1); 
		break;
		case PARALLEL_PORT_2:
		case SERIAL_PORT_2:
		case VIRTUAL_PORT_2:
		case USB_PORT_2: 
			m_port2.SetCheck(1); 
		break;
		case PARALLEL_PORT_3:
		case SERIAL_PORT_3:
		case USB_PORT_3: 
			m_port3.SetCheck(1); 
		break;
		case SERIAL_PORT_4:
		case USB_PORT_4: 
			m_port4.SetCheck(1); 
		break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCommPg1::OnOK() 
{
	// TODO: Add extra validation here
	CPropertyPage::OnOK();
}

BOOL CCommPg1::OnApply()
{
	// TODO: Add extra validation here
	if(m_tgl.GetCheck()) options.lp.link_type = LINK_TGL;
	if(m_ser.GetCheck()) options.lp.link_type = LINK_SER;
	if(m_par.GetCheck()) options.lp.link_type = LINK_PAR;
	if(m_avr.GetCheck()) options.lp.link_type = LINK_AVR;
	if(m_tie.GetCheck()) options.lp.link_type = LINK_TIE;
	if(m_vti.GetCheck()) options.lp.link_type = LINK_VTI;
	if(m_ugl.GetCheck()) options.lp.link_type = LINK_UGL;

	switch(options.lp.link_type)
	{
		case LINK_PAR:
			if(m_port1.GetCheck()) options.lp.port = PARALLEL_PORT_1;
			if(m_port2.GetCheck()) options.lp.port = PARALLEL_PORT_2;
			if(m_port3.GetCheck()) options.lp.port = PARALLEL_PORT_3;
			break;
		case LINK_SER:
		case LINK_AVR:
		case LINK_TGL:
			if(m_port1.GetCheck()) options.lp.port = SERIAL_PORT_1;
			if(m_port2.GetCheck()) options.lp.port = SERIAL_PORT_2;
			if(m_port3.GetCheck()) options.lp.port = SERIAL_PORT_3;
			if(m_port4.GetCheck()) options.lp.port = SERIAL_PORT_4;
			break;
		case LINK_TIE:
		case LINK_VTI:
			if(m_port1.GetCheck()) options.lp.port = VIRTUAL_PORT_1;
			if(m_port2.GetCheck()) options.lp.port = VIRTUAL_PORT_2;
			break;
		case LINK_UGL:
			if(m_port1.GetCheck()) options.lp.port = USB_PORT_1;
			if(m_port2.GetCheck()) options.lp.port = USB_PORT_2;
			if(m_port3.GetCheck()) options.lp.port = USB_PORT_3;
			if(m_port4.GetCheck()) options.lp.port = USB_PORT_4;
			break;
	}

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

void CCommPg1::OnSerLink() 
{
	// TODO: Add your control notification handler code here
	m_port1.SetWindowText("Serial port #1");
	m_port2.SetWindowText("Serial port #2");
	m_port3.SetWindowText("Serial port #3");
	m_port4.SetWindowText("Serial port #4");
	m_port1.ShowWindow(SW_SHOW);
	m_port2.ShowWindow(SW_SHOW);
	m_port3.ShowWindow(SW_SHOW);
	m_port4.ShowWindow(SW_SHOW);

	SetModified(TRUE);
}

void CCommPg1::OnTglLink() 
{
	// TODO: Add your control notification handler code here
	m_port1.SetWindowText("Serial port #1");
	m_port2.SetWindowText("Serial port #2");
	m_port3.SetWindowText("Serial port #3");
	m_port4.SetWindowText("Serial port #4");
	m_port1.ShowWindow(SW_SHOW);
	m_port2.ShowWindow(SW_SHOW);
	m_port3.ShowWindow(SW_SHOW);
	m_port4.ShowWindow(SW_SHOW);

	SetModified(TRUE);
}

void CCommPg1::OnTieLink() 
{
	// TODO: Add your control notification handler code here
	m_port1.SetWindowText("Virtual port #1");
	m_port2.SetWindowText("Virtual port #2");
	m_port1.ShowWindow(SW_SHOW);
	m_port2.ShowWindow(SW_SHOW);
	m_port3.ShowWindow(SW_HIDE);
	m_port4.ShowWindow(SW_HIDE);
	SetModified(TRUE);
}

void CCommPg1::OnUglLink() 
{
	// TODO: Add your control notification handler code here
	m_port1.SetWindowText("USB Link #1");
	m_port2.SetWindowText("USB Link #2");
	m_port3.SetWindowText("USB Link #3");
	m_port4.SetWindowText("USB Link #4");
	m_port1.ShowWindow(SW_SHOW);
	m_port2.ShowWindow(SW_SHOW);
	m_port3.ShowWindow(SW_SHOW);
	m_port4.ShowWindow(SW_SHOW);

	SetModified(TRUE);
}

void CCommPg1::OnVtiLink() 
{
	// TODO: Add your control notification handler code here
	m_port1.SetWindowText("Virtual port #1");
	m_port2.SetWindowText("Virtual port #2");
	m_port1.ShowWindow(SW_SHOW);
	m_port2.ShowWindow(SW_SHOW);
	m_port3.ShowWindow(SW_HIDE);
	m_port4.ShowWindow(SW_HIDE);

	SetModified(TRUE);
}

void CCommPg1::OnAvrLink() 
{
	// TODO: Add your control notification handler code here
	m_port1.SetWindowText("Serial port #1");
	m_port2.SetWindowText("Serial port #2");
	m_port3.SetWindowText("Serial port #3");
	m_port4.SetWindowText("Serial port #4");
	m_port1.ShowWindow(SW_SHOW);
	m_port2.ShowWindow(SW_SHOW);
	m_port3.ShowWindow(SW_SHOW);
	m_port4.ShowWindow(SW_SHOW);

	SetModified(TRUE);
}

void CCommPg1::OnParLink() 
{
	// TODO: Add your control notification handler code here
	m_port1.SetWindowText("Parallel port #1");
	m_port2.SetWindowText("Parallel port #2");
	m_port3.SetWindowText("Parallel port #3");
	m_port1.ShowWindow(SW_SHOW);
	m_port2.ShowWindow(SW_SHOW);
	m_port3.ShowWindow(SW_SHOW);
	m_port4.ShowWindow(SW_HIDE);

	SetModified(TRUE);
}

void CCommPg1::OnPort1() 
{
	// TODO: Add your control notification handler code here
	SetModified(TRUE);
}

void CCommPg1::OnPort2() 
{
	// TODO: Add your control notification handler code here
	SetModified(TRUE);
}

void CCommPg1::OnPort3() 
{
	// TODO: Add your control notification handler code here
	SetModified(TRUE);
}

void CCommPg1::OnPort4() 
{
	// TODO: Add your control notification handler code here
	SetModified(TRUE);
}
