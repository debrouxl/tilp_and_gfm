// ProbeIO.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "ProbeIO.h"

#include "../src/tilp_core.h"

#include <fcntl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if defined(__LINUX__)
#elif defined(__WIN32__)
# define STDIN_FILENO  0//(fileno(CONIN$))
# define STDOUT_FILENO 1//(fileno(CONOUT$))
# define STDERR_FILENO 2//(fileno(CONOUT$))
#endif

/////////////////////////////////////////////////////////////////////////////
// CProbeIODlg dialog


CProbeIODlg::CProbeIODlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProbeIODlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProbeIODlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_textFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Courier New");
}


void CProbeIODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProbeIODlg)
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProbeIODlg, CDialog)
	//{{AFX_MSG_MAP(CProbeIODlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProbeIODlg message handlers

#define MAXC 1024
#define TMPPIPE "C:\\pipe.tmp"

void CProbeIODlg::OnOK() 
{
	char *os;
	TicablePortInfo pi;
	int n;
	char buf[MAXC];
	FILE *old, *f;
	int i;

	// TODO: Add extra validation here

	/* Probe ports: send DISPLAY output to file */
	old = ticable_DISPLAY_set_output_to_file(TMPPIPE);

	ticable_detect_os(&os);
	ticable_detect_port(&pi);
	//ticable_detect_cable(&pi);

	/* Restore DISPLAY output to stderr */
	//f = ticable_DISPLAY_set_output_to_stream(old);
	ticable_DISPLAY_close_file();

	/* Now, open and read file content */
	f = fopen(TMPPIPE, "rb");
	if(f == NULL)
		return;

	int c = 0;
	for(i=0; c != EOF; i++)
	{
		c = buf[i] = fgetc(f);
		if(buf[i] == EOF) break;
	}
	buf[i]='\0';
	fclose(f);
	unlink(TMPPIPE);

	//AfxMessageBox(buf);
	//tilp_process_unix2dos(buf);
	m_edit.SetWindowText(_T(buf));

	//CDialog::OnOK();
}

BOOL CProbeIODlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_edit.SetFont(&m_textFont, TRUE);
	m_edit.SetWindowText(_T("Click on the 'Launch' for running\r\nauto-detection..."));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProbeIODlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
