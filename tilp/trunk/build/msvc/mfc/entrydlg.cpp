// EntryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "EntryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEntryDlg dialog

static const char *pTitle, *pMessage, *pContent;
static char* final_content = NULL;

CEntryDlg::CEntryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEntryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEntryDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CEntryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEntryDlg)
	DDX_Control(pDX, IDC_ENTRY_FRAME, m_frame);
	DDX_Control(pDX, IDC_ENTRY_EDIT, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEntryDlg, CDialog)
	//{{AFX_MSG_MAP(CEntryDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEntryDlg message handlers

BOOL CEntryDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_edit.SetWindowText(pContent);
	m_frame.SetWindowText(pMessage);
	SetWindowText(pTitle);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEntryDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString szEdit;
	int length;
	
	length = m_edit.GetWindowTextLength();
	m_edit.GetWindowText(szEdit);
	final_content = (char *)malloc(length+1);
	strcpy(final_content, szEdit.GetBuffer(length));
	
	CDialog::OnOK();
}

void CEntryDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

char *mfc_dlgbox_entry(const char *title, const char *message,
						  const char *content)
{
	pTitle = title; pMessage = message; pContent = content;
	final_content = NULL;

	CEntryDlg entryDlg;
	if(entryDlg.DoModal() == IDOK)
	{
		return final_content;
	}

	return NULL;
}
