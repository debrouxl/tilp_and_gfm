// ScreenSht.cpp : implementation file
//

#include "stdafx.h"
#include "tilp.h"
#include "ScreenSht.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScreenSht

IMPLEMENT_DYNAMIC(CScreenSht, CPropertySheet)

CScreenSht::CScreenSht(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddControlPages();
}

CScreenSht::CScreenSht(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddControlPages();
}

CScreenSht::~CScreenSht()
{
}

void CScreenSht::AddControlPages()
{
	AddPage(&m_page1);
	AddPage(&m_page2);
}

BEGIN_MESSAGE_MAP(CScreenSht, CPropertySheet)
	//{{AFX_MSG_MAP(CScreenSht)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScreenSht message handlers

BOOL CScreenSht::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
	
	return bResult;
}