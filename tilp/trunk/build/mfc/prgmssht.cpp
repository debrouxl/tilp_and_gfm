// PrgmsSht.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "PrgmsSht.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrgmsSht

IMPLEMENT_DYNAMIC(CPrgmsSht, CPropertySheet)

CPrgmsSht::CPrgmsSht(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddControlPages();
}

CPrgmsSht::CPrgmsSht(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddControlPages();
}

CPrgmsSht::~CPrgmsSht()
{
}


void CPrgmsSht::AddControlPages()
{
	AddPage(&m_page1);
	AddPage(&m_page2);
}

BEGIN_MESSAGE_MAP(CPrgmsSht, CPropertySheet)
	//{{AFX_MSG_MAP(CPrgmsSht)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrgmsSht message handlers

BOOL CPrgmsSht::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
	
	return bResult;
}
