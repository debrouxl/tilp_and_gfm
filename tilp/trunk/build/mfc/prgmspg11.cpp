// PrgmsPg11.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "PrgmsPg11.h"

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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPrgmsPg1::~CPrgmsPg1()
{
}

void CPrgmsPg1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrgmsPg1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrgmsPg1, CPropertyPage)
	//{{AFX_MSG_MAP(CPrgmsPg1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrgmsPg1 message handlers

BOOL CPrgmsPg1::OnApply() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnApply();
}

void CPrgmsPg1::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CPropertyPage::OnOK();
}
