// ScreenView.h : interface of the CScreenView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREENVIEW_H__270FB7BF_0B7C_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_SCREENVIEW_H__270FB7BF_0B7C_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CScreenDoc;

class CScreenView : public CView
{
protected: // create from serialization only
	CScreenView();
	DECLARE_DYNCREATE(CScreenView)

// Attributes
public:
	CScreenDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScreenView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScreenView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CScreenView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ScreenView.cpp
inline CScreenDoc* CScreenView::GetDocument()
   { return (CScreenDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREENVIEW_H__270FB7BF_0B7C_11D6_BC64_004005E3BC2E__INCLUDED_)
