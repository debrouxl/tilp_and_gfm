// Thanks.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "HelpThanks.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThanksDlg dialog


CThanksDlg::CThanksDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThanksDlg::IDD, pParent)
{	 
	//{{AFX_DATA_INIT(CThanksDlg)
	m_text = _T("");
	//}}AFX_DATA_INIT
	m_textFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Arial");
}

void CThanksDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThanksDlg)
	DDX_Control(pDX, IDC_THANKS_EDIT, m_edit);
	DDX_Text(pDX, IDC_THANKS_EDIT, m_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CThanksDlg, CDialog)
	//{{AFX_MSG_MAP(CThanksDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThanksDlg message handlers

BOOL CThanksDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	FILE *fd;
	char buffer[65536];
	strcpy(buffer, inst_paths.base_dir);  // retrieve base path
	strcat(buffer, SHARE_DIR);          // 
	strcat(buffer, DIR_SEPARATOR);
	strcat(buffer, "Thanks.txt");

	if(access(buffer, F_OK) == 0 )
    {
		if( (fd=fopen (buffer, "r")) != NULL)
		{
			memset (buffer, 0, sizeof(buffer));
			fread (buffer, 1, sizeof(buffer)-1, fd);
			tilp_process_unix2dos(buffer);
			m_edit.SetFont(&m_textFont, TRUE);
			m_edit.SetWindowText(_T(CString(buffer)));
			fclose (fd);
	    }
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
