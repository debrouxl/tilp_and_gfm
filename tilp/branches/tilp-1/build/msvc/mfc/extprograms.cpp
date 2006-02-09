// ExtPrograms.cpp : implementation file
//

#include <afxdlgs.h>

#include "stdafx.h"
#include "TiLP.h"
#include "ExtPrograms.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtProgramsDlg dialog


CExtProgramsDlg::CExtProgramsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExtProgramsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExtProgramsDlg)
	m_tar_location = _T("");
	m_tar_options = _T("");
	m_zip_location = _T("");
	m_zip_options = _T("");
	m_app_options = _T("");
	m_app_location = _T("");
	//}}AFX_DATA_INIT
}


void CExtProgramsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExtProgramsDlg)
	DDX_Text(pDX, IDC_EDIT_TAR_LOC, m_tar_location);
	DDX_Text(pDX, IDC_EDIT_TAR_OPT, m_tar_options);
	DDX_Text(pDX, IDC_EDIT_ZIP_LOC, m_zip_location);
	DDX_Text(pDX, IDC_EDIT_ZIP_OPT, m_zip_options);
	DDX_Text(pDX, IDC_EDIT_APPSIGN_OPT, m_app_options);
	DDX_Text(pDX, IDC_EDIT_APPSIGN_LOC, m_app_location);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExtProgramsDlg, CDialog)
	//{{AFX_MSG_MAP(CExtProgramsDlg)
	ON_BN_CLICKED(IDC_BUTTON_ZIP, OnButtonZip)
	ON_BN_CLICKED(IDC_BUTTON_TAR, OnButtonTar)
	ON_BN_CLICKED(IDC_BUTTON_APPSIGN, OnButtonAppsign)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtProgramsDlg message handlers

BOOL CExtProgramsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_zip_location = options.unzip_location;
	m_zip_options = options.unzip_options;
	m_tar_location = options.tar_location;
	m_tar_options = options.tar_options;
	m_tar_location = options.appsign_location;
	m_tar_options = options.appsign_options;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CExtProgramsDlg::OnButtonZip() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE szFilter[] = "Executable Files (*.exe)|*.exe|";
	CFileDialog dlgFile(TRUE, ".exe", "wzunzip", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	dlgFile.m_ofn.lpstrInitialDir = _T("C:\\Program Files\\WinZip");

	if(dlgFile.DoModal() == IDOK)
	{
		m_zip_location = dlgFile.GetPathName();
		UpdateData(FALSE);
	}
}

void CExtProgramsDlg::OnButtonTar() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE szFilter[] = "Executable Files (*.exe)|*.exe|";
	CFileDialog dlgFile(TRUE, ".exe", "wzunzip", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	dlgFile.m_ofn.lpstrInitialDir = _T("C:\\Program Files\\WinZip");

	if(dlgFile.DoModal() == IDOK)
	{
		m_tar_location = dlgFile.GetPathName();
		UpdateData(FALSE);
	}
}

void CExtProgramsDlg::OnButtonAppsign() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE szFilter[] = "Executable Files (*.exe)|*.exe|";
	CFileDialog dlgFile(TRUE, ".exe", "appsign", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	dlgFile.m_ofn.lpstrInitialDir = _T("C:\\Program Files\\TiLP");

	if(dlgFile.DoModal() == IDOK)
	{
		m_app_location = dlgFile.GetPathName();
		UpdateData(FALSE);
	}
}

void CExtProgramsDlg::OnOK() 
{
	// TODO: Add extra validation here

	CDialog::OnOK();

	g_free(options.unzip_location);
	g_free(options.unzip_options);
	g_free(options.tar_location);
	g_free(options.tar_options);
	g_free(options.appsign_location);
	g_free(options.appsign_options);

	options.unzip_location = g_strdup(m_zip_location.GetBuffer(256));
	options.unzip_options = g_strdup(m_zip_options.GetBuffer(256));
	options.tar_location = g_strdup(m_tar_location.GetBuffer(256));
	options.tar_options = g_strdup(m_tar_options.GetBuffer(256));
	options.appsign_location = g_strdup(m_app_location.GetBuffer(256));
	options.appsign_options = g_strdup(m_app_options.GetBuffer(256));
}
