// ScreenView.cpp : implementation of the CScreenView class
//

#include "stdafx.h"
//#include "screen.h"

#include "screenDoc.h"
#include "ScreenView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScreenView

IMPLEMENT_DYNCREATE(CScreenView, CView)

BEGIN_MESSAGE_MAP(CScreenView, CView)
	//{{AFX_MSG_MAP(CScreenView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScreenView construction/destruction

CScreenView::CScreenView()
{
	// TODO: add construction code here

}

CScreenView::~CScreenView()
{
}

BOOL CScreenView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CScreenView drawing

void CScreenView::OnDraw(CDC* pDC)
{
	CScreenDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CScreenView printing

BOOL CScreenView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CScreenView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CScreenView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CScreenView diagnostics

#ifdef _DEBUG
void CScreenView::AssertValid() const
{
	CView::AssertValid();
}

void CScreenView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CScreenDoc* CScreenView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScreenDoc)));
	return (CScreenDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScreenView message handlers
