#if !defined(AFX_MISCSHT_H__A7929B46_CED4_11D6_9A65_006008205341__INCLUDED_)
#define AFX_MISCSHT_H__A7929B46_CED4_11D6_9A65_006008205341__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MiscSht.h : header file
//

#include "MiscPg1.h"
#include "MiscPg2.h"

/////////////////////////////////////////////////////////////////////////////
// CMiscSht

class CMiscSht : public CPropertySheet
{
	DECLARE_DYNAMIC(CMiscSht)

// Construction
public:
	CMiscSht(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMiscSht(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

protected:
	void AddControlPages(void);

// Attributes
public:

// Operations
public:
	CMiscPg1		m_page1;
	CMiscPg2		m_page2;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMiscSht)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMiscSht();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMiscSht)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MISCSHT_H__A7929B46_CED4_11D6_9A65_006008205341__INCLUDED_)
