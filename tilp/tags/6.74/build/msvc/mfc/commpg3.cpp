// CommPg3.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "CommPg3.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommPg3 property page

IMPLEMENT_DYNCREATE(CCommPg3, CPropertyPage)

CCommPg3::CCommPg3() : CPropertyPage(CCommPg3::IDD)
{
	//{{AFX_DATA_INIT(CCommPg3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCommPg3::~CCommPg3()
{
}

void CCommPg3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommPg3)
	DDX_Control(pDX, IDC_SPIN_DELAY, m_spin_delay);
	DDX_Control(pDX, IDC_SPIN_TIMEOUT, m_spin_timeout);
	DDX_Control(pDX, IDC_RTS_CTS, m_rts_cts);
	DDX_Control(pDX, IDC_BAUD_RATE, m_baud_rate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommPg3, CPropertyPage)
	//{{AFX_MSG_MAP(CCommPg3)
	ON_EN_CHANGE(IDC_DELAY, OnChangeDelay)
	ON_EN_CHANGE(IDC_TIMEOUT, OnChangeTimeout)
	ON_CBN_CLOSEUP(IDC_BAUD_RATE, OnCloseupBaudRate)
	ON_CBN_EDITUPDATE(IDC_BAUD_RATE, OnEditupdateBaudRate)
	ON_BN_CLICKED(IDC_RTS_CTS, OnRtsCts)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommPg3 message handlers

BOOL CCommPg3::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_TIMEOUT);
	m_spin_timeout.SetBuddy(pWnd);
	pWnd = GetDlgItem(IDC_DELAY);
	m_spin_delay.SetBuddy(pWnd);
	
	m_spin_timeout.SetBase(10);
	m_spin_timeout.SetRange(10, 600);
	m_spin_timeout.SetPos(options.lp.timeout);
	
	m_spin_delay.SetBase(10);
	m_spin_delay.SetRange(1, 100);
	m_spin_delay.SetPos(options.lp.delay);

	m_baud_rate.AddString("9600");
	m_baud_rate.AddString("19200");
	m_baud_rate.AddString("38400");
	m_baud_rate.AddString("57600");

	switch(options.lp.baud_rate)
	{
		case BR9600: m_baud_rate.SetWindowText("9600"); break;
		case BR19200: m_baud_rate.SetWindowText("19200"); break;
		case BR38400: m_baud_rate.SetWindowText("38400"); break;
		case BR57600: m_baud_rate.SetWindowText("57600"); break;
	}

	if(options.lp.hfc == HFC_ON)
		m_rts_cts.SetCheck(1);
	else
		m_rts_cts.SetCheck(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCommPg3::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

BOOL CCommPg3::OnApply()
{
	// TODO: Add extra validation here
	CString szChoice;
	int nChoice;

	options.lp.timeout = m_spin_timeout.GetPos();
	options.lp.delay = m_spin_delay.GetPos();

	m_baud_rate.GetWindowText(szChoice);

	if(szChoice == "9600")
		options.lp.baud_rate = BR9600;
	if(szChoice == "19200")
		options.lp.baud_rate = BR19200;
	if(szChoice == "38400")
		options.lp.baud_rate = BR38400;
	if(szChoice == "57600")
		options.lp.baud_rate = BR57600;

	if(m_rts_cts.GetCheck() == 1)
		options.lp.hfc = HFC_ON;
	else
		options.lp.hfc = HFC_OFF;

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

void CCommPg3::OnChangeDelay() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	SetModified(TRUE);
}

void CCommPg3::OnChangeTimeout() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	SetModified(TRUE);
}

void CCommPg3::OnCloseupBaudRate() 
{
	// TODO: Add your control notification handler code here
	CString szChoice;
	int nChoice;

	m_baud_rate.GetWindowText(szChoice);
	nChoice = m_baud_rate.GetCurSel();
	if(nChoice != CB_ERR)
	{	// Valid choice
		m_baud_rate.GetLBText(nChoice, szChoice);
	}
	else if(szChoice.IsEmpty() == TRUE)
	{	// No selection from the list and the text field is empty
	}
	else if(m_baud_rate.FindStringExact(-1, szChoice) != CB_ERR)
	{
		// Entry selected by user is now in the text field
	}
	else
	{
		// The text field contains an entry typed by the user but
		// this entry is not included with the list set
	}

	SetModified(TRUE);
}

void CCommPg3::OnEditupdateBaudRate() 
{
	// TODO: Add your control notification handler code here
	 CString szChoice;
	m_baud_rate.GetWindowText(szChoice);	

	SetModified(TRUE);
}

void CCommPg3::OnRtsCts() 
{
	// TODO: Add your control notification handler code here
	SetModified(TRUE);	
}
