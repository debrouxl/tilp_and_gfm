// DlgClock.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "DlgClock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "tilp_core.h"

static TicalcClock tmp_clk;

/////////////////////////////////////////////////////////////////////////////
// CDlgClock dialog


CDlgClock::CDlgClock(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgClock::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgClock)
	//}}AFX_DATA_INIT
}


void CDlgClock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgClock)
	DDX_Control(pDX, IDC_CLOCK_SPIN_YEAR, m_clock_year);
	DDX_Control(pDX, IDC_CLOCK_SPIN_SEC, m_clock_sec);
	DDX_Control(pDX, IDC_CLOCK_SPIN_MIN, m_clock_min);
	DDX_Control(pDX, IDC_CLOCK_SPIN_HOUR, m_clock_hour);
	DDX_Control(pDX, IDC_CLOCK_SPIN_DAY, m_clock_day);
	DDX_Control(pDX, IDC_CLOCK_MONTH, m_clock_month);
	DDX_Control(pDX, IDC_CLOCK_FORMAT, m_clock_format);
	DDX_Control(pDX, IDC_CLOCK_AMPM, m_clock_ampm);
	DDX_Control(pDX, IDC_CLOCK_24H, m_clock_24h);
	DDX_Control(pDX, IDC_CLOCK_ON, m_clock_on);
	DDX_Control(pDX, IDC_CLOCK_OFF, m_clock_off);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgClock, CDialog)
	//{{AFX_MSG_MAP(CDlgClock)
	ON_BN_CLICKED(IDC_CLOCK_SYNC, OnClockSync)
	ON_BN_CLICKED(IDC_CLOCK_AMPM, OnClockAmpm)
	ON_BN_CLICKED(IDC_CLOCK_24H, OnClock24h)
	ON_BN_CLICKED(IDC_CLOCK_OFF, OnClockOff)
	ON_BN_CLICKED(IDC_CLOCK_ON, OnClockOn)
	ON_CBN_CLOSEUP(IDC_CLOCK_FORMAT, OnCloseupClockFormat)
	ON_CBN_EDITUPDATE(IDC_CLOCK_FORMAT, OnEditupdateClockFormat)
	ON_CBN_CLOSEUP(IDC_CLOCK_MONTH, OnCloseupClockMonth)
	ON_CBN_EDITUPDATE(IDC_CLOCK_MONTH, OnEditupdateClockMonth)
	ON_EN_CHANGE(IDC_CLOCK_EDIT_DAY, OnChangeClockEditDay)
	ON_EN_CHANGE(IDC_CLOCK_EDIT_HOUR, OnChangeClockEditHour)
	ON_EN_CHANGE(IDC_CLOCK_EDIT_MIN, OnChangeClockEditMin)
	ON_EN_CHANGE(IDC_CLOCK_EDIT_SEC, OnChangeClockEditSec)
	ON_EN_CHANGE(IDC_CLOCK_EDIT_YEAR, OnChangeClockEditYear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgClock message handlers

BOOL CDlgClock::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CWnd* pWnd;

	if(tilp_calc_isready())
		return FALSE;
  
	if(tilp_error(ti_calc.get_clock(&tmp_clk, 0)))
		return FALSE;

	DISPLAY("%02i/%02i/%02i %02i:%02i:%02i, %s, %s\n",
	  tmp_clk.day, tmp_clk.month, tmp_clk.year,
	  tmp_clk.hours, tmp_clk.minutes, tmp_clk.seconds,
	  (tmp_clk.time_format == 12) ? "12" : "24",
	  ticalc_format_to_date(tmp_clk.date_format));

	pWnd = GetDlgItem(IDC_CLOCK_EDIT_DAY);
	m_clock_day.SetBuddy(pWnd);
	pWnd = GetDlgItem(IDC_CLOCK_EDIT_YEAR);
	m_clock_year.SetBuddy(pWnd);
	pWnd = GetDlgItem(IDC_CLOCK_EDIT_HOUR);
	m_clock_hour.SetBuddy(pWnd);
	pWnd = GetDlgItem(IDC_CLOCK_EDIT_MIN);
	m_clock_min.SetBuddy(pWnd);
	pWnd = GetDlgItem(IDC_CLOCK_EDIT_SEC);
	m_clock_sec.SetBuddy(pWnd);

	m_clock_day.SetBase(1);
	m_clock_day.SetRange(1, 631);
	m_clock_day.SetPos(tmp_clk.day);
	m_clock_year.SetBase(1);
	m_clock_year.SetRange(1900, 2100);
	m_clock_year.SetPos(tmp_clk.year);
	m_clock_hour.SetBase(1);
	m_clock_hour.SetRange(0, 22);
	m_clock_hour.SetPos(tmp_clk.hours);
	m_clock_min.SetBase(1);
	m_clock_min.SetRange(0, 59);
	m_clock_min.SetPos(tmp_clk.minutes);
	m_clock_sec.SetBase(1);
	m_clock_sec.SetRange(0, 59);
	m_clock_sec.SetPos(tmp_clk.seconds);

	m_clock_month.AddString("Jan");	m_clock_month.AddString("Feb");	
	m_clock_month.AddString("Mar");	m_clock_month.AddString("Apr");
	m_clock_month.AddString("May");	m_clock_month.AddString("Jun");	
	m_clock_month.AddString("Jul");	m_clock_month.AddString("Aug");
	m_clock_month.AddString("Sep");	m_clock_month.AddString("Oct");	
	m_clock_month.AddString("Nov");	m_clock_month.AddString("Dec");

	switch(tmp_clk.month)
	{
		case 1: m_clock_month.SetWindowText("Jan"); break;
		case 2: m_clock_month.SetWindowText("Feb"); break;
		case 3: m_clock_month.SetWindowText("Mar"); break;
		case 4: m_clock_month.SetWindowText("Apr"); break;
		case 5: m_clock_month.SetWindowText("May"); break;
		case 6: m_clock_month.SetWindowText("Jun"); break;
		case 7: m_clock_month.SetWindowText("Jul"); break;
		case 8: m_clock_month.SetWindowText("Aug"); break;
		case 9: m_clock_month.SetWindowText("Sep"); break;
		case 10: m_clock_month.SetWindowText("Oct"); break;
		case 11: m_clock_month.SetWindowText("Nov"); break;
		case 12: m_clock_month.SetWindowText("Dec"); break;
	}

	switch(tmp_clk.time_format)
	{
		case 12: m_clock_ampm.SetCheck(1); break;
		case 24: m_clock_24h.SetCheck(1); break;
	}

	for(int i=0; i<8; i++)
		m_clock_format.AddString(ticalc_format_to_date(i));

	m_clock_format.SetWindowText(ticalc_format_to_date(tmp_clk.date_format));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgClock::OnOK() 
{
	// TODO: Add extra validation here
	CString szChoice;
	int nChoice;

	tmp_clk.day = m_clock_day.GetPos();
	tmp_clk.year = m_clock_year.GetPos();
	tmp_clk.hours = m_clock_hour.GetPos();
	tmp_clk.minutes = m_clock_min.GetPos();
	tmp_clk.seconds = m_clock_sec.GetPos();

	m_clock_month.GetWindowText(szChoice);
	if(szChoice == "Jan")
		tmp_clk.month = 1;
	else if(szChoice == "Feb")
		tmp_clk.month = 2;
	else if(szChoice == "Mar")
		tmp_clk.month = 3;
	else if(szChoice == "Apr")
		tmp_clk.month = 4;
	else if(szChoice == "May")
		tmp_clk.month = 5;
	else if(szChoice == "Jun")
		tmp_clk.month = 6;
	else if(szChoice == "Jul")
		tmp_clk.month = 7;
	else if(szChoice == "Aug")
		tmp_clk.month = 8;
	else if(szChoice == "Sep")
		tmp_clk.month = 9;
	else if(szChoice == "Oct")
		tmp_clk.month = 10;
	else if(szChoice == "Nov")
		tmp_clk.month = 11;
	else if(szChoice == "Dec")
		tmp_clk.month = 12;
	
	if(m_clock_ampm.GetCheck()) tmp_clk.time_format = 12;
	if(m_clock_24h.GetCheck())  tmp_clk.time_format = 24;

	m_clock_format.GetWindowText(szChoice);
	tmp_clk.date_format = ticalc_date_to_format(szChoice);	

	if(tilp_calc_isready())
		return;
  
	if(tilp_error(ti_calc.set_clock(&tmp_clk, 0)))
		return;
	
	CDialog::OnOK();
}

void CDlgClock::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgClock::OnClockSync() 
{
	// TODO: Add your control notification handler code here
	time_t      tt;
	struct tm  *lt;
	TicalcClock tc;

	time(&tt);
	lt = localtime(&tt);
	memcpy(&tc, &tmp_clk, sizeof(TicalcClock));
	tc.day     = lt->tm_mday;
	tc.month   = lt->tm_mon + 1;
	tc.year    = lt->tm_year + 1900;
	tc.hours   = lt->tm_hour;
	tc.minutes = lt->tm_min;
	tc.seconds = lt->tm_sec;

	if(tilp_calc_isready())
		return;
  
	if(tilp_error(ti_calc.set_clock(&tmp_clk, 0)))
		return;
}

void CDlgClock::OnClockAmpm() 
{
	// TODO: Add your control notification handler code here
	m_clock_24h.SetCheck(0);
}

void CDlgClock::OnClock24h() 
{
	// TODO: Add your control notification handler code here
	m_clock_ampm.SetCheck(0);
}

void CDlgClock::OnClockOff() 
{
	// TODO: Add your control notification handler code here
	m_clock_on.SetCheck(0);
}

void CDlgClock::OnClockOn() 
{
	// TODO: Add your control notification handler code here
	m_clock_off.SetCheck(0);
}

void CDlgClock::OnCloseupClockFormat() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgClock::OnEditupdateClockFormat() 
{
	// TODO: Add your control notification handler code here
	CString szChoice;
	int nChoice;

	m_clock_format.GetWindowText(szChoice);
	nChoice = m_clock_format.GetCurSel();
	if(nChoice != CB_ERR)
	{	// Valid choice
		m_clock_format.GetLBText(nChoice, szChoice);
	}
	else if(szChoice.IsEmpty() == TRUE)
	{	// No selection from the list and the text field is empty
	}
	else if(m_clock_format.FindStringExact(-1, szChoice) != CB_ERR)
	{
		// Entry selected by user is now in the text field
	}
	else
	{
		// The text field contains an entry typed by the user but
		// this entry is not included with the list set
	}
}

void CDlgClock::OnCloseupClockMonth() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgClock::OnEditupdateClockMonth() 
{
	// TODO: Add your control notification handler code here
	CString szChoice;
	int nChoice;

	m_clock_month.GetWindowText(szChoice);
	nChoice = m_clock_month.GetCurSel();
	if(nChoice != CB_ERR)
	{	// Valid choice
		m_clock_month.GetLBText(nChoice, szChoice);
	}
	else if(szChoice.IsEmpty() == TRUE)
	{	// No selection from the list and the text field is empty
	}
	else if(m_clock_month.FindStringExact(-1, szChoice) != CB_ERR)
	{
		// Entry selected by user is now in the text field
	}
	else
	{
		// The text field contains an entry typed by the user but
		// this entry is not included with the list set
	}
}

void CDlgClock::OnChangeClockEditDay() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDlgClock::OnChangeClockEditHour() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDlgClock::OnChangeClockEditMin() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDlgClock::OnChangeClockEditSec() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDlgClock::OnChangeClockEditYear() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
