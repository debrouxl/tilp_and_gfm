// LeftDoc.h : interface of the CLeftDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TILPDOC_H__043BEF7F_0234_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_TILPDOC_H__043BEF7F_0234_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLeftDoc : public CDocument
{
protected: // create from serialization only
	CLeftDoc();
	DECLARE_DYNCREATE(CLeftDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLeftDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLeftDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TILPDOC_H__043BEF7F_0234_11D6_BC64_004005E3BC2E__INCLUDED_)
