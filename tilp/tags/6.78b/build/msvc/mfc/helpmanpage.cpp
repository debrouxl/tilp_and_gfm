// Manpage.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "HelpManpage.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManpageDlg dialog


CManpageDlg::CManpageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManpageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManpageDlg)
	//}}AFX_DATA_INIT
	m_textFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Courier New");
}


void CManpageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManpageDlg)
	DDX_Control(pDX, IDC_MANPAGE_EDIT, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CManpageDlg, CDialog)
	//{{AFX_MSG_MAP(CManpageDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManpageDlg message handlers

BOOL CManpageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	FILE *fd;
	char buffer[65536];
	strcpy(buffer, inst_paths.base_dir);  // retrieve base path
	strcat(buffer, SHARE_DIR);          // 
	strcat(buffer, DIR_SEPARATOR);
	strcat(buffer, "Manpage.txt");

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
	else
		m_edit.SetWindowText(_T(CString("Unable to find the 'ManPage.txt' file")));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
