// TiLPDoc.h : interface of the CTiLPDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TILPDOC_H__043BEF7F_0234_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_TILPDOC_H__043BEF7F_0234_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTiLPDoc : public CDocument
{
protected: // create from serialization only
	CTiLPDoc();
	DECLARE_DYNCREATE(CTiLPDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTiLPDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTiLPDoc();
	void ThreadAborted();
	void ThreadFinished();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CCriticalSection m_cs;
	CEvent m_event;
	HANDLE m_hThread;
	BOOL m_bWorking;
	//{{AFX_MSG(CTiLPDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TILPDOC_H__043BEF7F_0234_11D6_BC64_004005E3BC2E__INCLUDED_)
