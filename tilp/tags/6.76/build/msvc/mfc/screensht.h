#if !defined(AFX_SCREENSHT_H__A7929B43_CED4_11D6_9A65_006008205341__INCLUDED_)
#define AFX_SCREENSHT_H__A7929B43_CED4_11D6_9A65_006008205341__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScreenSht.h : header file
//

#include "ScreenPg1.h"
#include "ScreenPg2.h"

/////////////////////////////////////////////////////////////////////////////
// CScreenSht

class CScreenSht : public CPropertySheet
{
	DECLARE_DYNAMIC(CScreenSht)

// Construction
public:
	CScreenSht(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CScreenSht(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

protected:
	void AddControlPages(void);

// Attributes
public:

// Operations
public:
	CScreenPg1		m_page1;
	CScreenPg2		m_page2;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScreenSht)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScreenSht();

	// Generated message map functions
protected:
	//{{AFX_MSG(CScreenSht)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREENSHT_H__A7929B43_CED4_11D6_9A65_006008205341__INCLUDED_)
