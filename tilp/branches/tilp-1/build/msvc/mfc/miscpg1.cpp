// MiscPg1.cpp : implementation file
//

#include "stdafx.h"
#include "tilp.h"
#include "MiscPg1.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMiscPg1 property page

IMPLEMENT_DYNCREATE(CMiscPg1, CPropertyPage)

CMiscPg1::CMiscPg1() : CPropertyPage(CMiscPg1::IDD)
{
	//{{AFX_DATA_INIT(CMiscPg1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMiscPg1::~CMiscPg1()
{
}

void CMiscPg1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMiscPg1)
	DDX_Control(pDX, IDC_FILES_ALL, m_files_all);
	DDX_Control(pDX, IDC_FILES_TI, m_files_ti);
	DDX_Control(pDX, IDC_CONFIRM, m_confirmation);
	DDX_Control(pDX, IDC_COMP_BYNAME, m_comp_byname);
	DDX_Control(pDX, IDC_COMP_BYDATE, m_comp_bydate);
	DDX_Control(pDX, IDC_COMP_BYSIZE, m_comp_bysize);
	DDX_Control(pDX, IDC_COMP_BYATTR, m_comp_byattr);
	DDX_Control(pDX, IDC_COMP_BYUP, m_comp_byup);
	DDX_Control(pDX, IDC_COMP_BYDOWN, m_comp_bydown);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMiscPg1, CPropertyPage)
	//{{AFX_MSG_MAP(CMiscPg1)
	ON_BN_CLICKED(IDC_COMP_BYATTR, OnCompByattr)
	ON_BN_CLICKED(IDC_COMP_BYDATE, OnCompBydate)
	ON_BN_CLICKED(IDC_COMP_BYDOWN, OnCompBydown)
	ON_BN_CLICKED(IDC_COMP_BYNAME, OnCompByname)
	ON_BN_CLICKED(IDC_COMP_BYSIZE, OnCompBysize)
	ON_BN_CLICKED(IDC_COMP_BYUP, OnCompByup)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	ON_BN_CLICKED(IDC_FILES_ALL, OnFilesAll)
	ON_BN_CLICKED(IDC_FILES_TI, OnFilesTi)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMiscPg1 message handlers

BOOL CMiscPg1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(options.confirm == CONFIRM_YES)
		m_confirmation.SetCheck(1);
	else
		m_confirmation.SetCheck(0);

	switch(options.file_disp)
	{
		case SHOW_ALL: m_files_all.SetCheck(1); break;
		case SHOW_TIF: m_files_ti.SetCheck(1);	break;
	}

	switch(options.clist_sort)
    {
		case SORT_BY_NAME:  m_comp_byname.SetCheck(1); break;
		case SORT_BY_DATE:  m_comp_bydate.SetCheck(1); break;
		case SORT_BY_SIZE:  m_comp_bysize.SetCheck(1); break;
		case SORT_BY_ATTRB: m_comp_byattr.SetCheck(1); break;
    }

	switch(options.clist_sort_order)
    {
		case SORT_UP: m_comp_byup.SetCheck(1);		break;
		case SORT_DOWN: m_comp_bydown.SetCheck(1);	break;
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMiscPg1::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

BOOL CMiscPg1::OnApply() 
{
	// TODO: Add extra validation here
	if(m_confirmation.GetCheck() == 1)
		options.confirm = CONFIRM_YES;
	else
		options.confirm = CONFIRM_NO;

	if(m_files_all.GetCheck()) options.file_disp = SHOW_ALL;
	if(m_files_ti.GetCheck())  options.file_disp = SHOW_TIF;

	if(m_comp_byname.GetCheck()) options.clist_sort = SORT_BY_NAME;
	if(m_comp_bydate.GetCheck()) options.clist_sort = SORT_BY_DATE;
	if(m_comp_bysize.GetCheck()) options.clist_sort = SORT_BY_SIZE;
	if(m_comp_byattr.GetCheck()) options.clist_sort = SORT_BY_ATTRB;

	if(m_comp_byup.GetCheck())   options.clist_sort_order = SORT_UP;
	if(m_comp_bydown.GetCheck()) options.clist_sort_order = SORT_DOWN;
	
	return TRUE;
}

void CMiscPg1::OnCompByattr() 
{
	// TODO: Add your control notification handler code here
	m_comp_byname.SetCheck(0);
	m_comp_bydate.SetCheck(0);
	m_comp_bysize.SetCheck(0);

	SetModified(TRUE);
}

void CMiscPg1::OnCompBydate() 
{
	// TODO: Add your control notification handler code here
	m_comp_byname.SetCheck(0);
	m_comp_bysize.SetCheck(0);
	m_comp_byattr.SetCheck(0);

	SetModified(TRUE);
}

void CMiscPg1::OnCompBydown() 
{
	// TODO: Add your control notification handler code here
	m_comp_byup.SetCheck(0);

	SetModified(TRUE);
}

void CMiscPg1::OnCompByname() 
{
	// TODO: Add your control notification handler code here
	m_comp_bydate.SetCheck(0);
	m_comp_bysize.SetCheck(0);
	m_comp_byattr.SetCheck(0);
}

void CMiscPg1::OnCompBysize() 
{
	// TODO: Add your control notification handler code here
	m_comp_byname.SetCheck(0);
	m_comp_bydate.SetCheck(0);
	m_comp_byattr.SetCheck(0);

	SetModified(TRUE);
}

void CMiscPg1::OnCompByup() 
{
	// TODO: Add your control notification handler code here
	m_comp_bydown.SetCheck(0);	

	SetModified(TRUE);
}

void CMiscPg1::OnConfirm() 
{
	// TODO: Add your control notification handler code here
	SetModified(TRUE);	
}

void CMiscPg1::OnFilesAll() 
{
	// TODO: Add your control notification handler code here
	m_files_ti.SetCheck(0);	

	SetModified(TRUE);
}

void CMiscPg1::OnFilesTi() 
{
	// TODO: Add your control notification handler code here
	m_files_all.SetCheck(0);	

	SetModified(TRUE);
}