#if !defined(AFX_COMMSHT_H__CF7B104D_1DDE_4CBE_B566_42FBA225B6F1__INCLUDED_)
#define AFX_COMMSHT_H__CF7B104D_1DDE_4CBE_B566_42FBA225B6F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommSht.h : header file
//

#include "CommPg1.h"
#include "CommPg2.h"
#include "CommPg3.h"

/////////////////////////////////////////////////////////////////////////////
// CCommSht

class CCommSht : public CPropertySheet
{
	DECLARE_DYNAMIC(CCommSht)

// Construction
public:
	CCommSht(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CCommSht(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

protected:
	void AddControlPages(void);

// Attributes
public:

// Operations
public:
	CCommPg1		m_page1;
	CCommPg2		m_page2;
	CCommPg3		m_page3;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommSht)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCommSht();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCommSht)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMSHT_H__CF7B104D_1DDE_4CBE_B566_42FBA225B6F1__INCLUDED_)
