#if !defined(AFX_PRGMSSHT_H__90AAEC1E_405B_4EFA_AB83_8AE3A7CBC069__INCLUDED_)
#define AFX_PRGMSSHT_H__90AAEC1E_405B_4EFA_AB83_8AE3A7CBC069__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrgmsSht.h : header file
//

#include "PrgmsPg1.h"
#include "PrgmsPg2.h"

/////////////////////////////////////////////////////////////////////////////
// CPrgmsSht

class CPrgmsSht : public CPropertySheet
{
	DECLARE_DYNAMIC(CPrgmsSht)

// Construction
public:
	CPrgmsSht(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPrgmsSht(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

protected:
	void AddControlPages(void);

// Attributes
public:

// Operations
public:
	CPrgmsPg1		m_page1;
	CPrgmsPg2		m_page2;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrgmsSht)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPrgmsSht();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPrgmsSht)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRGMSSHT_H__90AAEC1E_405B_4EFA_AB83_8AE3A7CBC069__INCLUDED_)
