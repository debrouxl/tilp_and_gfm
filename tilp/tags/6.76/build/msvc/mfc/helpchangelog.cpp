// ChangelogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "HelpChangelog.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangelogDlg dialog


CChangelogDlg::CChangelogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangelogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangelogDlg)
	//}}AFX_DATA_INIT
	m_textFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Arial");
}


void CChangelogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangelogDlg)
	DDX_Control(pDX, IDC_CLOG_EDIT, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangelogDlg, CDialog)
	//{{AFX_MSG_MAP(CChangelogDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangelogDlg message handlers

BOOL CChangelogDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	FILE *fd;
	char buffer[65536];
	strcpy(buffer, inst_paths.base_dir);  // retrieve base path
	strcat(buffer, SHARE_DIR);          // 
	strcat(buffer, DIR_SEPARATOR);
	strcat(buffer, "ChangeLog.txt");

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
