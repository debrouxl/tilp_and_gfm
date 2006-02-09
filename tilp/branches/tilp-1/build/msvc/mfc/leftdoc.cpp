// LeftDoc.cpp : implementation of the CLeftDoc class
//

#include "stdafx.h"
#include "TiLP.h"

#include "LeftDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftDoc

IMPLEMENT_DYNCREATE(CLeftDoc, CDocument)

BEGIN_MESSAGE_MAP(CLeftDoc, CDocument)
	//{{AFX_MSG_MAP(CLeftDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftDoc construction/destruction

CLeftDoc::CLeftDoc()
{
	// TODO: add one-time construction code here
}

CLeftDoc::~CLeftDoc()
{
}

BOOL CLeftDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLeftDoc serialization

void CLeftDoc::Serialize(CArchive& ar)
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
// CLeftDoc diagnostics

#ifdef _DEBUG
void CLeftDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLeftDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftDoc commands
