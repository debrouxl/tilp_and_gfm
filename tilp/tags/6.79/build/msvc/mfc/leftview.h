// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__043BEF83_0234_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_LEFTVIEW_H__043BEF83_0234_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLeftDoc;

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CLeftDoc* GetDocument();

// Operations
public:
	void ForceRefresh();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL	BitmapToImageList(CImageList *list, UINT nResourceID);
	BOOL	BitmapToImageListFromFile(CImageList *list, LPCSTR lpszFilename);
	void BuildSelection();
	void BuildVarsSelection();
	void BuildAppsSelection();
	void DisplayItem(HTREEITEM hItem, LPSTR header);
	void UpdateInfo();
	void ReloadFont();
	void LaunchScreendump();
	void LaunchRomdump();
	int Refresh();

	CImageList m_ilSmall;

	HTREEITEM m_hScreenItem;
	HTREEITEM m_hRomdumpItem;
	HTREEITEM m_hVarsItem;
	HTREEITEM m_hAppsItem;

	HANDLE m_hThread;

	CFont m_tiFont;

	//{{AFX_MSG(CLeftView)
	afx_msg void OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCalcDirlist();
	afx_msg void OnOperationsDirectorylist();
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	afx_msg LRESULT OnThread3Finished(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CLeftDoc* CLeftView::GetDocument()
   { return (CLeftDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__043BEF83_0234_11D6_BC64_004005E3BC2E__INCLUDED_)
