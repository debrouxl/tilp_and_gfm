// PrgmsPg1.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "PrgmsPg1.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrgmsPg1 property page

IMPLEMENT_DYNCREATE(CPrgmsPg1, CPropertyPage)

CPrgmsPg1::CPrgmsPg1() : CPropertyPage(CPrgmsPg1::IDD)
{
	//{{AFX_DATA_INIT(CPrgmsPg1)
	m_zip_location = _T("");
	m_zip_options = _T("");
	//}}AFX_DATA_INIT
}

CPrgmsPg1::~CPrgmsPg1()
{
}

void CPrgmsPg1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrgmsPg1)
	DDX_Text(pDX, IDC_EDIT_ZIP_LOC, m_zip_location);
	DDX_Text(pDX, IDC_EDIT_ZIP_OPT, m_zip_options);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrgmsPg1, CPropertyPage)
	//{{AFX_MSG_MAP(CPrgmsPg1)
	ON_BN_CLICKED(IDC_BUTTON_ZIP, OnButtonZip)
	ON_EN_CHANGE(IDC_EDIT_ZIP_LOC, OnChangeEditZipLoc)
	ON_EN_CHANGE(IDC_EDIT_ZIP_OPT, OnChangeEditZipOpt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrgmsPg1 message handlers

BOOL CPrgmsPg1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_zip_location = options.unzip_location;
	m_zip_options = options.unzip_options;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrgmsPg1::OnButtonZip() 
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

void CPrgmsPg1::OnOK() 
{
	// TODO: Add extra validation here
	CPropertyPage::OnOK();
}

BOOL CPrgmsPg1::OnApply()
{
	// TODO: Add extra validation here
	g_free(options.unzip_location);
	g_free(options.unzip_options);
	
	options.unzip_location = g_strdup(m_zip_location.GetBuffer(256));
	options.unzip_options = g_strdup(m_zip_options.GetBuffer(256));

	return TRUE;
}
void CPrgmsPg1::OnChangeEditZipLoc() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	SetModified(TRUE);
}

void CPrgmsPg1::OnChangeEditZipOpt() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	SetModified(TRUE);
}
