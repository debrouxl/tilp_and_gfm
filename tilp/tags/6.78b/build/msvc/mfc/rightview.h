// RightView.h : interface of the CRightView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RIGHTVIEW_H__043BEF81_0234_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_RIGHTVIEW_H__043BEF81_0234_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct tagITEMINFO {
	CString		strFileName;
	DWORD		nFileSizeLow;
	FILETIME	ftLastWriteTime;
	DWORD		dwFileAttributes; 
} ITEMINFO;

class CRightView : public CListView
{
protected: // create from serialization only
	CRightView();
	DECLARE_DYNCREATE(CRightView)

// Attributes
public:
	CLeftDoc* GetDocument();

// Operations
public:
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, 
		LPARAM lParamSort);
	void SelectAll();
	void InvertSelection();
	void ForceRefresh();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRightView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRightView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString		m_strPath;
	CImageList	m_ilSmall;
	CImageList	m_ilLarge;
	CPoint		m_ptMsg;
	CString		m_szMsg;

	BOOL		BitmapToImageList(CImageList *list, UINT nResourceID);
	BOOL		BitmapToImageListFromFile(CImageList *list, LPCSTR lpszFilename);
	void		SetListView(DWORD dwView);
	void		FreeItemMemory ();
	BOOL		AddItem (int nIndex, WIN32_FIND_DATA* pfd);
	int			Refresh(LPCTSTR pszPath);

// Generated message map functions
protected:
	//{{AFX_MSG(CRightView)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRbmFileUntar();
	afx_msg void OnRbmFileUnzip();
	afx_msg void OnRbmFileProp();
	afx_msg void OnRbmFileRename();
	afx_msg void OnRbmFileView();
	afx_msg void OnCompRefresh();
	afx_msg void OnCompTrash();
	afx_msg void OnCompMkdir();
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRbmEditSel();
	afx_msg void OnRbmEditUnsel();
	afx_msg void OnRbmEditMove();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnRbmGfmGroup();
	afx_msg void OnRbmGfmOpen();
	afx_msg void OnRbmGfmUngroup();
	afx_msg void OnRbmMiscAms2rom();
	afx_msg void OnRbmMiscSetdir();
	afx_msg void OnRbmMiscSign();
	//}}AFX_MSG
	afx_msg void OnRbmDrive(UINT nID);
	afx_msg void OnUpdateRbmDrive(CCmdUI* pCmdUI);
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RightView.cpp
inline CLeftDoc* CRightView::GetDocument()
   { return (CLeftDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIGHTVIEW_H__043BEF81_0234_11D6_BC64_004005E3BC2E__INCLUDED_)
