// FileProperties.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "FileProperties.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileProperties dialog


CFileProperties::CFileProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CFileProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileProperties)
	//}}AFX_DATA_INIT
#ifdef HAVE_LIBTIFFEP
	fi = NULL;
#endif
}


void CFileProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileProperties)
	DDX_Control(pDX, IDC_VAR_PATH, m_var_path);
	DDX_Control(pDX, IDC_COMMENT, m_comment);
	DDX_Control(pDX, IDC_VAR_ATRB, m_var_atrb);
	DDX_Control(pDX, IDC_VAR_SIZE, m_var_size);
	DDX_Control(pDX, IDC_VAR_TYPE, m_var_type);
	DDX_Control(pDX, IDC_VAR_NAME, m_var_name);
	DDX_Control(pDX, IDC_FILE_NVARS, m_file_nvars);
	DDX_Control(pDX, IDC_FILE_DSIZE, m_file_dsize);
	DDX_Control(pDX, IDC_FILE_SIZE, m_file_size);
	DDX_Control(pDX, IDC_FILE_TYPE, m_file_type);
	DDX_Control(pDX, IDC_FILE_NAME, m_file_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileProperties, CDialog)
	//{{AFX_MSG_MAP(CFileProperties)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileProperties message handlers

void CFileProperties::OnCancel() 
{
	// TODO: Add extra cleanup here
#ifdef HAVE_LIBTIFFEP
	tiffep_free_fi_struct(&fi);
#endif
	
	CDialog::OnCancel();
}

char *ti_filename_for_tiffep = NULL;

BOOL CFileProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
#ifdef HAVE_LIBTIFFEP
	int err;
	char *ti_filename = ti_filename_for_tiffep;

	err = tiffep_load_file_informations(ti_filename, &fi);
	if(err)
	{
		char buffer[MAXCHARS];
		tiffep_get_error(err, buffer);
		gif->msg_box(_("Error"), buffer);
		return FALSE;
	}

	if(FILEINFO_VARLIST(fi) == NULL)
    {
      gif->msg_box(_("Error"), _("Invalid TI file."));
      tiffep_free_fi_struct(&fi);
      return FALSE;
    }

	CString szStr;
	m_comment.SetWindowText(_T(FILEINFO_COMMENT(fi)));

	m_file_name.SetWindowText(_T(FILEINFO_NAME(fi)));
	szStr.Format("TI%s", tiffep_calc_type_to_string(FILEINFO_CALCTYPE(fi)));
	m_file_type.SetWindowText(_T(szStr));
	szStr.Format("%i", FILEINFO_FILESIZE(fi));
	m_file_size.SetWindowText(_T(szStr));
	szStr.Format("%i", FILEINFO_DATASIZE(fi));
	m_file_dsize.SetWindowText(_T(szStr));
	szStr.Format("%i", FILEINFO_NUMVARS(fi));
	m_file_nvars.SetWindowText(_T(szStr));

	m_var_name.SetWindowText(_T(VARINFO_REALNAME(VARLIST_DATA(FILEINFO_VARLIST(fi)))));
	m_var_type.SetWindowText(_T(tiffep_var_type_to_string(VARINFO_TYPE(VARLIST_DATA(FILEINFO_VARLIST(fi))))));
	m_var_path.SetWindowText(_T(VARINFO_PATH(VARLIST_DATA(FILEINFO_VARLIST(fi)))));
	szStr.Format("%i", VARINFO_SIZE(VARLIST_DATA(FILEINFO_VARLIST(fi))));
	m_var_size.SetWindowText(_T(szStr));
	m_var_atrb.SetWindowText(_T(tiffep_attribute_to_string(VARINFO_ATTRIBUTE(VARLIST_DATA(FILEINFO_VARLIST(fi))))));
#else
	AfxMessageBox("TiLP has been compiled without TiFFEP support. I forgot to compile it: please mail me !", MB_OK);
#endif
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
