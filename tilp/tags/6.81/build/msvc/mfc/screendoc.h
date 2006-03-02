// screenDoc.h : interface of the CScreenDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREENDOC_H__270FB7BD_0B7C_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_SCREENDOC_H__270FB7BD_0B7C_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CScreenDoc : public CDocument
{
protected: // create from serialization only
	CScreenDoc();
	DECLARE_DYNCREATE(CScreenDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScreenDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScreenDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CScreenDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREENDOC_H__270FB7BD_0B7C_11D6_BC64_004005E3BC2E__INCLUDED_)
