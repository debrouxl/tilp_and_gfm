// TiLPDoc.cpp : implementation of the CTiLPDoc class
//

#include "stdafx.h"
#include "TiLP.h"

#include "TiLPDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTiLPDoc

IMPLEMENT_DYNCREATE(CTiLPDoc, CDocument)

BEGIN_MESSAGE_MAP(CTiLPDoc, CDocument)
	//{{AFX_MSG_MAP(CTiLPDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTiLPDoc construction/destruction

CTiLPDoc::CTiLPDoc() :
	m_event (FALSE, TRUE) // Manual-reset event, initially unowned
{
	// TODO: add one-time construction code here
	m_hThread = NULL;
    m_bWorking = FALSE;
}

CTiLPDoc::~CTiLPDoc()
{
}

BOOL CTiLPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTiLPDoc serialization

void CTiLPDoc::Serialize(CArchive& ar)
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
// CTiLPDoc diagnostics

#ifdef _DEBUG
void CTiLPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTiLPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTiLPDoc commands
