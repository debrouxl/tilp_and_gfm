// SetupGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "SetupGeneral.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupGeneralDlg dialog


CSetupGeneralDlg::CSetupGeneralDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupGeneralDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupGeneralDlg)
	//}}AFX_DATA_INIT
}


void CSetupGeneralDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupGeneralDlg)
	DDX_Control(pDX, IDC_RECV_SINGLE, m_recv_single);
	DDX_Control(pDX, IDC_RECV_GROUP, m_recv_group);
	DDX_Control(pDX, IDC_FILES_ALL, m_files_all);
	DDX_Control(pDX, IDC_FILES_TI, m_files_ti);
	DDX_Control(pDX, IDC_CONFIRM, m_confirmation);
	DDX_Control(pDX, IDC_FULL_PATH, m_full_path);
	DDX_Control(pDX, IDC_LOCAL_PATH, m_local_path);
	DDX_Control(pDX, IDC_CALC_BYNAME, m_calc_byname);
	DDX_Control(pDX, IDC_CALC_BYINFO, m_calc_byinfo);
	DDX_Control(pDX, IDC_CALC_BYTYPE, m_calc_bytype);
	DDX_Control(pDX, IDC_CALC_BYSIZE, m_calc_bysize);
	DDX_Control(pDX, IDC_CALC_BYUP, m_calc_byup);
	DDX_Control(pDX, IDC_CALC_BYDOWN, m_calc_bydown);
	DDX_Control(pDX, IDC_COMP_BYNAME, m_comp_byname);
	DDX_Control(pDX, IDC_COMP_BYDATE, m_comp_bydate);
	DDX_Control(pDX, IDC_COMP_BYSIZE, m_comp_bysize);
	DDX_Control(pDX, IDC_COMP_BYATTR, m_comp_byattr);
	DDX_Control(pDX, IDC_COMP_BYUP, m_comp_byup);
	DDX_Control(pDX, IDC_COMP_BYDOWN, m_comp_bydown);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupGeneralDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupGeneralDlg)
	ON_BN_CLICKED(IDC_LOCAL_PATH, OnLocalPath)
	ON_BN_CLICKED(IDC_FULL_PATH, OnFullPath)
	ON_BN_CLICKED(IDC_CALC_BYDOWN, OnCalcBydown)
	ON_BN_CLICKED(IDC_CALC_BYINFO, OnCalcByinfo)
	ON_BN_CLICKED(IDC_CALC_BYNAME, OnCalcByname)
	ON_BN_CLICKED(IDC_CALC_BYSIZE, OnCalcBysize)
	ON_BN_CLICKED(IDC_CALC_BYTYPE, OnCalcBytype)
	ON_BN_CLICKED(IDC_CALC_BYUP, OnCalcByup)
	ON_BN_CLICKED(IDC_COMP_BYATTR, OnCompByattr)
	ON_BN_CLICKED(IDC_COMP_BYDATE, OnCompBydate)
	ON_BN_CLICKED(IDC_COMP_BYDOWN, OnCompBydown)
	ON_BN_CLICKED(IDC_COMP_BYNAME, OnCompByname)
	ON_BN_CLICKED(IDC_COMP_BYSIZE, OnCompBysize)
	ON_BN_CLICKED(IDC_COMP_BYUP, OnCompByup)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	ON_BN_CLICKED(IDC_FILES_ALL, OnFilesAll)
	ON_BN_CLICKED(IDC_FILES_TI, OnFilesTi)
	ON_BN_CLICKED(IDC_RECV_SINGLE, OnRecvSingle)
	ON_BN_CLICKED(IDC_RECV_GROUP, OnRecvGroup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupGeneralDlg message handlers

BOOL CSetupGeneralDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(options.confirm == CONFIRM_YES)
		m_confirmation.SetCheck(1);
	else
		m_confirmation.SetCheck(0);

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

	switch(options.single_or_group)
	{
		case RECV_AS_SINGLE: m_recv_single.SetCheck(1); break;
		case RECV_AS_GROUP:  m_recv_group.SetCheck(1);	break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetupGeneralDlg::OnOK() 
{
	// TODO: Add extra validation here
	if(m_confirmation.GetCheck() == 1)
		options.confirm = CONFIRM_YES;
	else
		options.confirm = CONFIRM_NO;

	if(m_full_path.GetCheck())  options.path_mode = FULL_PATH;
	if(m_local_path.GetCheck()) options.path_mode = LOCAL_PATH;

	if(m_calc_byname.GetCheck()) options.ctree_sort = SORT_BY_NAME;
	if(m_calc_byinfo.GetCheck()) options.ctree_sort = SORT_BY_INFO;
	if(m_calc_bytype.GetCheck()) options.ctree_sort = SORT_BY_TYPE;
	if(m_calc_bysize.GetCheck()) options.ctree_sort = SORT_BY_SIZE;

	if(m_calc_byup.GetCheck())   options.ctree_sort_order = SORT_UP;
	if(m_calc_bydown.GetCheck()) options.ctree_sort_order = SORT_DOWN;

	if(m_files_all.GetCheck()) options.file_disp = SHOW_ALL;
	if(m_files_ti.GetCheck())  options.file_disp = SHOW_TIF;

	if(m_comp_byname.GetCheck()) options.clist_sort = SORT_BY_NAME;
	if(m_comp_bydate.GetCheck()) options.clist_sort = SORT_BY_DATE;
	if(m_comp_bysize.GetCheck()) options.clist_sort = SORT_BY_SIZE;
	if(m_comp_byattr.GetCheck()) options.clist_sort = SORT_BY_ATTRB;

	if(m_comp_byup.GetCheck())   options.clist_sort_order = SORT_UP;
	if(m_comp_bydown.GetCheck()) options.clist_sort_order = SORT_DOWN;

	if(m_recv_single.GetCheck()) options.single_or_group = RECV_AS_SINGLE;
	if(m_recv_group.GetCheck())  options.single_or_group = RECV_AS_GROUP;

	CDialog::OnOK();
}

void CSetupGeneralDlg::OnFullPath() 
{
	// TODO: Add your control notification handler code here
	m_local_path.SetCheck(0);
}

void CSetupGeneralDlg::OnLocalPath() 
{
	// TODO: Add your control notification handler code here
	m_full_path.SetCheck(0);
}

void CSetupGeneralDlg::OnCalcBydown() 
{
	// TODO: Add your control notification handler code here
	m_calc_byup.SetCheck(0);
}

void CSetupGeneralDlg::OnCalcByinfo() 
{
	// TODO: Add your control notification handler code here
	m_calc_byname.SetCheck(0);
	//m_calc_byinfo.SetCheck(0);
	m_calc_bytype.SetCheck(0);
	m_calc_bysize.SetCheck(0);
}

void CSetupGeneralDlg::OnCalcByname() 
{
	// TODO: Add your control notification handler code here
	//m_calc_byname.SetCheck(0);
	m_calc_byinfo.SetCheck(0);
	m_calc_bytype.SetCheck(0);
	m_calc_bysize.SetCheck(0);
}

void CSetupGeneralDlg::OnCalcBysize() 
{
	// TODO: Add your control notification handler code here
	m_calc_byname.SetCheck(0);
	m_calc_byinfo.SetCheck(0);
	m_calc_bytype.SetCheck(0);
	//m_calc_bysize.SetCheck(0);
}

void CSetupGeneralDlg::OnCalcBytype() 
{
	// TODO: Add your control notification handler code here
	m_calc_byname.SetCheck(0);
	m_calc_byinfo.SetCheck(0);
	//m_calc_bytype.SetCheck(0);
	m_calc_bysize.SetCheck(0);
}

void CSetupGeneralDlg::OnCalcByup() 
{
	// TODO: Add your control notification handler code here
	m_calc_bydown.SetCheck(0);	
}

void CSetupGeneralDlg::OnCompByattr() 
{
	// TODO: Add your control notification handler code here
	m_comp_byname.SetCheck(0);
	m_comp_bydate.SetCheck(0);
	m_comp_bysize.SetCheck(0);
	//m_comp_byattr.SetCheck(0);
}

void CSetupGeneralDlg::OnCompBydate() 
{
	// TODO: Add your control notification handler code here
	m_comp_byname.SetCheck(0);
	//m_comp_bydate.SetCheck(0);
	m_comp_bysize.SetCheck(0);
	m_comp_byattr.SetCheck(0);
}

void CSetupGeneralDlg::OnCompBydown() 
{
	// TODO: Add your control notification handler code here
	m_comp_byup.SetCheck(0);
}

void CSetupGeneralDlg::OnCompByname() 
{
	// TODO: Add your control notification handler code here
	//m_comp_byname.SetCheck(0);
	m_comp_bydate.SetCheck(0);
	m_comp_bysize.SetCheck(0);
	m_comp_byattr.SetCheck(0);
}

void CSetupGeneralDlg::OnCompBysize() 
{
	// TODO: Add your control notification handler code here
	m_comp_byname.SetCheck(0);
	m_comp_bydate.SetCheck(0);
	//m_comp_bysize.SetCheck(0);
	m_comp_byattr.SetCheck(0);
}

void CSetupGeneralDlg::OnCompByup() 
{
	// TODO: Add your control notification handler code here
	m_comp_bydown.SetCheck(0);	
}

void CSetupGeneralDlg::OnConfirm() 
{
	// TODO: Add your control notification handler code here
	
}

void CSetupGeneralDlg::OnFilesAll() 
{
	// TODO: Add your control notification handler code here
	m_files_ti.SetCheck(0);	
}

void CSetupGeneralDlg::OnFilesTi() 
{
	// TODO: Add your control notification handler code here
	m_files_all.SetCheck(0);	
}

void CSetupGeneralDlg::OnRecvSingle() 
{
	// TODO: Add your control notification handler code here
	m_recv_group.SetCheck(0);
}

void CSetupGeneralDlg::OnRecvGroup() 
{
	// TODO: Add your control notification handler code here
	m_recv_single.SetCheck(0);
}
