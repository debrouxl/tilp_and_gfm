// MiscSht.cpp : implementation file
//

#include "stdafx.h"
#include "tilp.h"
#include "MiscSht.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMiscSht

IMPLEMENT_DYNAMIC(CMiscSht, CPropertySheet)

CMiscSht::CMiscSht(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddControlPages();
}

CMiscSht::CMiscSht(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddControlPages();
}

CMiscSht::~CMiscSht()
{
}

void CMiscSht::AddControlPages()
{
	AddPage(&m_page1);
	AddPage(&m_page2);
}

BEGIN_MESSAGE_MAP(CMiscSht, CPropertySheet)
	//{{AFX_MSG_MAP(CMiscSht)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMiscSht message handlers

BOOL CMiscSht::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
	
	return bResult;
}