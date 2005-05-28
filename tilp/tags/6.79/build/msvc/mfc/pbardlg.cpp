// PbarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "PbarDlg.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CProgressCtrl	*mPbar2 = NULL;
CProgressCtrl	*mPbar1 = NULL;
CEdit			*mLabel = NULL;
CEdit			*mRate  = NULL;

/////////////////////////////////////////////////////////////////////////////
// CPbar1Dlg dialog


CPbar1Dlg::CPbar1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPbar1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPbar1Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	mRate  = &m_rate;
	mPbar2 = &m_pbar2;
}


void CPbar1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPbar1Dlg)
	DDX_Control(pDX, IDC_PBAR_PROGRESS2, m_pbar2);
	DDX_Control(pDX, IDC_PBAR_EDIT1, m_rate);
	//}}AFX_DATA_MAP
}

void CPbar1Dlg::PassParameters(LPCSTR szTitle, LPCSTR szText)
{
	//DISPLAY("title = <%s>, text = <%s>\n", szTitle, szText);
	this->SetWindowText(szTitle);
	m_rate.SetWindowText(_T("N/A Kbytes/s"));
}

BEGIN_MESSAGE_MAP(CPbar1Dlg, CDialog)
	//{{AFX_MSG_MAP(CPbar1Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPbar1Dlg message handlers

void CPbar1Dlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	info_update.cancel = 1;
	
	CDialog::OnCancel();
}

void CPbar1Dlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	mPbar1 = mPbar2 = NULL;
	mRate = mLabel = NULL;
	
	CDialog::PostNcDestroy();
}

/////////////////////////////////////////////////////////////////////////////
// CPbar2Dlg dialog


CPbar2Dlg::CPbar2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPbar2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPbar2Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	mLabel = &m_label;
}


void CPbar2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPbar2Dlg)
	DDX_Control(pDX, IDC_PBAR_EDIT2, m_label);
	//}}AFX_DATA_MAP
}

void CPbar2Dlg::PassParameters(LPCSTR szTitle, LPCSTR szText)
{
	//DISPLAY("title = <%s>, text = <%s>\n", szTitle, szText);
	this->SetWindowText(szTitle);
	m_label.SetWindowText(_T(szText));
}


BEGIN_MESSAGE_MAP(CPbar2Dlg, CDialog)
	//{{AFX_MSG_MAP(CPbar2Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPbar2Dlg message handlers

void CPbar2Dlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	info_update.cancel = 1;
	
	CDialog::OnCancel();
}

void CPbar2Dlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	mPbar1 = mPbar2 = NULL;
	mRate = mLabel = NULL;
	
	CDialog::PostNcDestroy();
}

/////////////////////////////////////////////////////////////////////////////
// CPbar3Dlg dialog


CPbar3Dlg::CPbar3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPbar3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPbar3Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	mRate  = &m_rate;
	mPbar2 = &m_pbar2;
	mPbar1 = &m_pbar1;
}


void CPbar3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPbar3Dlg)
	DDX_Control(pDX, IDC_PBAR_PROGRESS2, m_pbar2);
	DDX_Control(pDX, IDC_PBAR_PROGRESS1, m_pbar1);
	DDX_Control(pDX, IDC_PBAR_EDIT1, m_rate);
	//}}AFX_DATA_MAP
}

void CPbar3Dlg::PassParameters(LPCSTR szTitle, LPCSTR szText)
{
	//DISPLAY("title = <%s>, text = <%s>\n", szTitle, szText);
	this->SetWindowText(szTitle);
	m_rate.SetWindowText(_T("N/A Kbytes/s"));
}

BEGIN_MESSAGE_MAP(CPbar3Dlg, CDialog)
	//{{AFX_MSG_MAP(CPbar3Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPbar3Dlg message handlers

void CPbar3Dlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	info_update.cancel = 1;
	
	CDialog::OnCancel();
}

void CPbar3Dlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	mPbar1 = mPbar2 = NULL;
	mRate = mLabel = NULL;
	
	CDialog::PostNcDestroy();
}

/////////////////////////////////////////////////////////////////////////////
// CPbar4Dlg dialog


CPbar4Dlg::CPbar4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPbar4Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPbar4Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	mRate  = &m_rate;
	mLabel = &m_label;
	mPbar2 = &m_pbar2;
}


void CPbar4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPbar4Dlg)
	DDX_Control(pDX, IDC_PBAR_EDIT, m_rate);
	DDX_Control(pDX, IDC_PBAR_EDIT2, m_label);
	DDX_Control(pDX, IDC_PBAR_PROGRESS2, m_pbar2);
	//}}AFX_DATA_MAP
}

void CPbar4Dlg::PassParameters(LPCSTR szTitle, LPCSTR szText)
{
	//DISPLAY("title = <%s>, text = <%s>\n", szTitle, szText);
	this->SetWindowText(szTitle);
	m_label.SetWindowText(_T(szText));
	m_rate.SetWindowText(_T("N/A Kbytes/s"));
}

BEGIN_MESSAGE_MAP(CPbar4Dlg, CDialog)
	//{{AFX_MSG_MAP(CPbar4Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPbar4Dlg message handlers

void CPbar4Dlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	info_update.cancel = 1;
	
	CDialog::OnCancel();
}

void CPbar4Dlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	mPbar1 = mPbar2 = NULL;
	mRate = mLabel = NULL;
	
	CDialog::PostNcDestroy();
}

/////////////////////////////////////////////////////////////////////////////
// CPbar5Dlg dialog


CPbar5Dlg::CPbar5Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPbar5Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPbar5Dlg)
	//}}AFX_DATA_INIT
	mRate  = &m_rate;
	mLabel = &m_label;
	mPbar2 = &m_pbar2;
	mPbar1 = &m_pbar1;
}


void CPbar5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPbar5Dlg)
	DDX_Control(pDX, IDC_PBAR_PROGRESS2, m_pbar2);
	DDX_Control(pDX, IDC_PBAR_PROGRESS1, m_pbar1);
	DDX_Control(pDX, IDC_PBAR_EDIT2, m_label);
	DDX_Control(pDX, IDC_PBAR_EDIT1, m_rate);
	//}}AFX_DATA_MAP
}

void CPbar5Dlg::PassParameters(LPCSTR szTitle, LPCSTR szText)
{
	//DISPLAY("title = <%s>, text = <%s>\n", szTitle, szText);
	this->SetWindowText(szTitle);
	m_label.SetWindowText(_T(szText));
	m_rate.SetWindowText(_T("N/A Kbytes/s"));
}

BEGIN_MESSAGE_MAP(CPbar5Dlg, CDialog)
	//{{AFX_MSG_MAP(CPbar5Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPbar5Dlg message handlers

void CPbar5Dlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	info_update.cancel = 1;
	
	CDialog::OnCancel();
}

void CPbar5Dlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	mPbar1 = mPbar2 = NULL;
	mRate = mLabel = NULL;
	
	CDialog::PostNcDestroy();
}

/////////////////////////////////////////////////////////////////////////////
// CPbarDlg dialog


CPbarDlg::CPbarDlg(CWnd* pParent /*=NULL*/, int iType /*=0*/)
	: CDialog(CPbarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPbarDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	type = iType;
	bPbar1 = bPbar2 = bRate = bLabel = false;
	if(type != 2)
		bPbar2 = true;
	if(type==3 || type==5)
		bPbar1 = true;
	if(type != 2)
		bRate = true;
	if(type==2 || type==4 || type==5)
		bLabel = true;
}


void CPbarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	if(bPbar1)
		DDX_Control(pDX, IDC_PBAR_PROGRESS1, m_pbar1);
	if(bPbar2)
		DDX_Control(pDX, IDC_PBAR_PROGRESS2, m_pbar2);
	if(bRate)
		DDX_Control(pDX, IDC_PBAR_EDIT1, m_rate);
	if(bLabel)
		DDX_Control(pDX, IDC_PBAR_EDIT2, m_label);

	//{{AFX_DATA_MAP(CPbarDlg)
	DDX_Control(pDX, IDC_PBAR_EDIT2, m_label);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPbarDlg, CDialog)
	//{{AFX_MSG_MAP(CPbarDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPbarDlg message handlers

BOOL CPbarDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPbarDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	info_update.cancel = 1;
	
	//CDialog::OnCancel();
}

void CPbarDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	//AfxGetMainWnd()->SendMessage(WM_USER_DAILOG_DESTROYED, 0, 0);
	delete this;
}