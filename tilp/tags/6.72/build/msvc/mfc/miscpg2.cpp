// MiscPg2.cpp : implementation file
//

#include "stdafx.h"
#include "tilp.h"
#include "MiscPg2.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMiscPg2 property page

IMPLEMENT_DYNCREATE(CMiscPg2, CPropertyPage)

CMiscPg2::CMiscPg2() : CPropertyPage(CMiscPg2::IDD)
{
	//{{AFX_DATA_INIT(CMiscPg2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMiscPg2::~CMiscPg2()
{
}

void CMiscPg2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMiscPg2)
	DDX_Control(pDX, IDC_RECV_SINGLE, m_recv_single);
	DDX_Control(pDX, IDC_RECV_GROUP, m_recv_group);
	DDX_Control(pDX, IDC_FULL_PATH, m_full_path);
	DDX_Control(pDX, IDC_LOCAL_PATH, m_local_path);
	DDX_Control(pDX, IDC_CALC_BYNAME, m_calc_byname);
	DDX_Control(pDX, IDC_CALC_BYINFO, m_calc_byinfo);
	DDX_Control(pDX, IDC_CALC_BYTYPE, m_calc_bytype);
	DDX_Control(pDX, IDC_CALC_BYSIZE, m_calc_bysize);
	DDX_Control(pDX, IDC_CALC_BYUP, m_calc_byup);
	DDX_Control(pDX, IDC_CALC_BYDOWN, m_calc_bydown);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMiscPg2, CPropertyPage)
	//{{AFX_MSG_MAP(CMiscPg2)
	ON_BN_CLICKED(IDC_LOCAL_PATH, OnLocalPath)
	ON_BN_CLICKED(IDC_FULL_PATH, OnFullPath)
	ON_BN_CLICKED(IDC_CALC_BYDOWN, OnCalcBydown)
	ON_BN_CLICKED(IDC_CALC_BYINFO, OnCalcByinfo)
	ON_BN_CLICKED(IDC_CALC_BYNAME, OnCalcByname)
	ON_BN_CLICKED(IDC_CALC_BYSIZE, OnCalcBysize)
	ON_BN_CLICKED(IDC_CALC_BYTYPE, OnCalcBytype)
	ON_BN_CLICKED(IDC_CALC_BYUP, OnCalcByup)
	ON_BN_CLICKED(IDC_RECV_SINGLE, OnRecvSingle)
	ON_BN_CLICKED(IDC_RECV_GROUP, OnRecvGroup)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMiscPg2 message handlers

BOOL CMiscPg2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	switch(options.path_mode)
	{
		case FULL_PATH: m_full_path.SetCheck(1); break;
		case LOCAL_PATH: m_local_path.SetCheck(1); break;
	}

	switch(options.ctree_sort)
    {
		case SORT_BY_NAME: m_calc_byname.SetCheck(1); break;
		case SORT_BY_INFO: m_calc_byinfo.SetCheck(1); break;
		case SORT_BY_TYPE: m_calc_bytype.SetCheck(1); break;
		case SORT_BY_SIZE: m_calc_bysize.SetCheck(1); break;
    }

	switch(options.ctree_sort_order)
    {
		case SORT_UP: m_calc_byup.SetCheck(1);		break;
		case SORT_DOWN: m_calc_bydown.SetCheck(1);	break;
    }

	switch(options.single_or_group)
	{
		case RECV_AS_SINGLE: m_recv_single.SetCheck(1); break;
		case RECV_AS_GROUP:  m_recv_group.SetCheck(1);	break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMiscPg2::OnOK() 
{
	// TODO: Add extra validation here

	CDialog::OnOK();
}

BOOL CMiscPg2::OnApply() 
{
	// TODO: Add extra validation here
	if(m_full_path.GetCheck())  options.path_mode = FULL_PATH;
	if(m_local_path.GetCheck()) options.path_mode = LOCAL_PATH;

	if(m_calc_byname.GetCheck()) options.ctree_sort = SORT_BY_NAME;
	if(m_calc_byinfo.GetCheck()) options.ctree_sort = SORT_BY_INFO;
	if(m_calc_bytype.GetCheck()) options.ctree_sort = SORT_BY_TYPE;
	if(m_calc_bysize.GetCheck()) options.ctree_sort = SORT_BY_SIZE;

	if(m_calc_byup.GetCheck())   options.ctree_sort_order = SORT_UP;
	if(m_calc_bydown.GetCheck()) options.ctree_sort_order = SORT_DOWN;

	if(m_recv_single.GetCheck()) options.single_or_group = RECV_AS_SINGLE;
	if(m_recv_group.GetCheck())  options.single_or_group = RECV_AS_GROUP;

	return TRUE;
}

void CMiscPg2::OnFullPath() 
{
	// TODO: Add your control notification handler code here
	m_local_path.SetCheck(0);

	SetModified(TRUE);
}

void CMiscPg2::OnLocalPath() 
{
	// TODO: Add your control notification handler code here
	m_full_path.SetCheck(0);

	SetModified(TRUE);
}

void CMiscPg2::OnCalcBydown() 
{
	// TODO: Add your control notification handler code here
	m_calc_byup.SetCheck(0);

	SetModified(TRUE);
}

void CMiscPg2::OnCalcByinfo() 
{
	// TODO: Add your control notification handler code here
	m_calc_byname.SetCheck(0);
	m_calc_bytype.SetCheck(0);
	m_calc_bysize.SetCheck(0);

	SetModified(TRUE);
}

void CMiscPg2::OnCalcByname() 
{
	// TODO: Add your control notification handler code here
	m_calc_byinfo.SetCheck(0);
	m_calc_bytype.SetCheck(0);
	m_calc_bysize.SetCheck(0);

	SetModified(TRUE);
}

void CMiscPg2::OnCalcBysize() 
{
	// TODO: Add your control notification handler code here
	m_calc_byname.SetCheck(0);
	m_calc_byinfo.SetCheck(0);
	m_calc_bytype.SetCheck(0);

	SetModified(TRUE);
}

void CMiscPg2::OnCalcBytype() 
{
	// TODO: Add your control notification handler code here
	m_calc_byname.SetCheck(0);
	m_calc_byinfo.SetCheck(0);
	m_calc_bysize.SetCheck(0);

	SetModified(TRUE);
}

void CMiscPg2::OnCalcByup() 
{
	// TODO: Add your control notification handler code here
	m_calc_bydown.SetCheck(0);	

	SetModified(TRUE);
}

void CMiscPg2::OnRecvSingle() 
{
	// TODO: Add your control notification handler code here
	m_recv_group.SetCheck(0);

	SetModified(TRUE);
}

void CMiscPg2::OnRecvGroup() 
{
	// TODO: Add your control notification handler code here
	m_recv_single.SetCheck(0);

	SetModified(TRUE);
}
