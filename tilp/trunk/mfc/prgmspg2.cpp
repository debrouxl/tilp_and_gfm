// PrgmsPg2.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "PrgmsPg2.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrgmsPg2 property page

IMPLEMENT_DYNCREATE(CPrgmsPg2, CPropertyPage)

CPrgmsPg2::CPrgmsPg2() : CPropertyPage(CPrgmsPg2::IDD)
{
	//{{AFX_DATA_INIT(CPrgmsPg2)
	m_tar_location = _T("");
	m_tar_options = _T("");
	//}}AFX_DATA_INIT
}

CPrgmsPg2::~CPrgmsPg2()
{
}

void CPrgmsPg2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrgmsPg2)
	DDX_Text(pDX, IDC_EDIT_TAR_LOC, m_tar_location);
	DDX_Text(pDX, IDC_EDIT_TAR_OPT, m_tar_options);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrgmsPg2, CPropertyPage)
	//{{AFX_MSG_MAP(CPrgmsPg2)
	ON_BN_CLICKED(IDC_BUTTON_TAR, OnButtonZip)
	ON_EN_CHANGE(IDC_EDIT_TAR_LOC, OnChangeEditTarLoc)
	ON_EN_CHANGE(IDC_EDIT_TAR_OPT, OnChangeEditTarOpt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrgmsPg2 message handlers

BOOL CPrgmsPg2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_tar_location = options.tar_location;
	m_tar_options = options.tar_options;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrgmsPg2::OnButtonZip() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE szFilter[] = "Executable Files (*.exe)|*.exe|";
	CFileDialog dlgFile(TRUE, ".exe", "wzuntar", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	dlgFile.m_ofn.lpstrInitialDir = _T("C:\\Program Files\\WinZip");

	if(dlgFile.DoModal() == IDOK)
	{
		m_tar_location = dlgFile.GetPathName();
		UpdateData(FALSE);
	}
}

void CPrgmsPg2::OnOK() 
{
	// TODO: Add extra validation here
	CPropertyPage::OnOK();
}

BOOL CPrgmsPg2::OnApply()
{
	// TODO: Add extra validation here
	g_free(options.tar_location);
	g_free(options.tar_options);
	
	options.tar_location = g_strdup(m_tar_location.GetBuffer(256));
	options.tar_options = g_strdup(m_tar_options.GetBuffer(256));

	return TRUE;
}
void CPrgmsPg2::OnChangeEditTarLoc() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	SetModified(TRUE);	
}

void CPrgmsPg2::OnChangeEditTarOpt() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	SetModified(TRUE);
}
