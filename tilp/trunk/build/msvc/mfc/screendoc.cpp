// screenDoc.cpp : implementation of the CScreenDoc class
//

#include "stdafx.h"
//#include "screen.h"

#include "screenDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScreenDoc

IMPLEMENT_DYNCREATE(CScreenDoc, CDocument)

BEGIN_MESSAGE_MAP(CScreenDoc, CDocument)
	//{{AFX_MSG_MAP(CScreenDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScreenDoc construction/destruction

CScreenDoc::CScreenDoc()
{
	// TODO: add one-time construction code here

}

CScreenDoc::~CScreenDoc()
{
}

BOOL CScreenDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CScreenDoc serialization

void CScreenDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CScreenDoc diagnostics

#ifdef _DEBUG
void CScreenDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CScreenDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScreenDoc commands
