// CommSht.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "CommSht.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommSht

IMPLEMENT_DYNAMIC(CCommSht, CPropertySheet)

CCommSht::CCommSht(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddControlPages();
}

CCommSht::CCommSht(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddControlPages();
}

CCommSht::~CCommSht()
{
}

void CCommSht::AddControlPages()
{
	AddPage(&m_page1);
	AddPage(&m_page2);
	AddPage(&m_page3);
}

BEGIN_MESSAGE_MAP(CCommSht, CPropertySheet)
	//{{AFX_MSG_MAP(CCommSht)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommSht message handlers

BOOL CCommSht::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
	
	return bResult;
}
