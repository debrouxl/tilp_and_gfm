// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "TiLP.h"

#include "LeftDoc.h"
#include "LeftView.h"
#include "MainFrm.h"
#include "ScreenDlg.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Image indexes
#define ILI_FOLDER_CLOSED	0
#define ILI_FOLDER_OPENED	1
#define ILI_APP				2
#define ILI_VAR				3

static int ili_var = ILI_VAR+1;

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemExpanding)
	ON_COMMAND(ID_CALC_DIRLIST, OnCalcDirlist)
	ON_COMMAND(ID_OPERATIONS_DIRECTORYLIST, OnOperationsDirectorylist)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_SELCHANGING, OnSelchanging)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	ON_MESSAGE (WM_USER_THREAD3_FINISHED, OnThread3Finished)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	if (!CTreeView::PreCreateWindow (cs))
		return FALSE;

    cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS |
        TVS_SHOWSELALWAYS;

	return TRUE;
}

// same function is rightview.cpp
BOOL CLeftView::BitmapToImageList(CImageList *list, UINT nIDRessource)
{
	BOOL bReturn;
	CBitmap bmp;

	bReturn = bmp.LoadBitmap(nIDRessource);
	if(bReturn != FALSE)
	{
		int nReturn = list->Add(&bmp, RGB(255, 255, 255));
		bmp.DeleteObject();
	}
	return bReturn;
}

// same function is rightview.cpp
BOOL CLeftView::BitmapToImageListFromFile(CImageList *list, LPCSTR lpszFilename)
{
	CBitmap bmp;
	HICON hIcon;
	gchar *str, *ext;
	char buf[256];
	
	ext = strstr(lpszFilename, ".ico");
	str = g_strconcat(inst_paths.icon_dir, lpszFilename, (ext == NULL) ? ".ico" : "", NULL);

	hIcon = (HICON)LoadImage(NULL, str, IMAGE_ICON, 0, 0, LR_LOADFROMFILE); 
		//LR_DEFAULTCOLOR | LR_LOADTRANSPARENT | LR_LOADFROMFILE | LR_DEFAULTSIZE);
	if(hIcon != NULL)
		list->Add(hIcon);
	else
		MessageBox(str, "Icon not found", MB_OK);

	g_free(str);
	return (hIcon == NULL) ? FALSE : TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CLeftDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
	CTreeCtrl& refCtrl = GetTreeCtrl();

	//
	// Initialize the image list.
	//
	m_ilSmall.Create (16, 16, TRUE, 7, 1);
	BitmapToImageList(&m_ilSmall, IDB_CTREE_DIR_CLOSED);
	BitmapToImageList(&m_ilSmall, IDB_CTREE_DIR_OPENED);
	BitmapToImageListFromFile(&m_ilSmall, "TIicon4.ico");
	BitmapToImageListFromFile(&m_ilSmall, "TIicon2.ico");
	GetTreeCtrl().SetImageList (&m_ilSmall, TVSIL_NORMAL);

	//
	// Populate the tree view with drive items.
	//
	Refresh();
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView printing

BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLeftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLeftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CLeftDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLeftDoc)));
	return (CLeftDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

int CLeftView::Refresh()
{
	HTREEITEM hItem;
	HTREEITEM hChildItem;
	TNode *vars, *apps;
	int i, j;

	// delete existing items
	GetTreeCtrl().DeleteAllItems();

	// clear image list (partial)
	for(i <= ili_var; i > ILI_VAR; i++)
		m_ilSmall.Remove(i);
	ili_var = ILI_VAR+1;

	ReloadFont();

	m_hVarsItem = GetTreeCtrl ().InsertItem (_T("  Variables"), ILI_VAR, ILI_VAR);
	m_hAppsItem = GetTreeCtrl ().InsertItem (_T("  Applications"), ILI_APP, ILI_APP);
	hChildItem = m_hVarsItem;
	
	GetTreeCtrl().SetItemData(m_hVarsItem, GPOINTER_TO_UINT(NULL));
	GetTreeCtrl().SetItemData(m_hAppsItem, GPOINTER_TO_UINT(NULL));
	
	if(ctree_win.dirlist == NULL) 
		return FALSE;

	//
	// Variables tree
	//
	vars = g_node_nth_child(ctree_win.dirlist, 0);
	for(i=0; i<g_node_n_children(vars); i++)
    {
		GNode *parent = g_node_nth_child(vars, i);
		char **row_text= (char **)calloc(5, sizeof(gchar *));
		TiVarEntry *fe = (TiVarEntry *)(parent->data);

		if((fe != NULL) || ti_calc.has_folder)
		{
			CString szText = CString(fe->name);

			hChildItem = GetTreeCtrl ().InsertItem (_T ("  "+szText), 
				ILI_FOLDER_CLOSED, ILI_FOLDER_OPENED, m_hVarsItem);
				GetTreeCtrl().SetItemData(hChildItem, GPOINTER_TO_UINT(fe));
				GetTreeCtrl().Expand(hChildItem, TVE_EXPAND);
		}

		for(j=0; j<g_node_n_children(parent); j++)
		{
			GNode *node = g_node_nth_child(parent, j);
			TiVarEntry *ve = (TiVarEntry *)(node->data);
			char icon_name[256];
			char *size;
			CString szText;

			tilp_var_get_size(ve, &size);
			szText.Format(" %8s [%5s] %8s %s",ve->trans, tifiles_vartype2string(ve->type), 
				size, tifiles_attribute_to_string(ve->attr)); // the first SPC char is used by selection
			g_free(size);

			strcpy(icon_name, tifiles_vartype2desc(ve->type));
			tilp_file_underscorize(icon_name);
			BitmapToImageListFromFile(&m_ilSmall, icon_name);
			GetTreeCtrl().SetImageList (&m_ilSmall, TVSIL_NORMAL);

			hItem = GetTreeCtrl().InsertItem(_T("  "+szText), 
				ili_var, ili_var++, hChildItem);
			GetTreeCtrl().SetItemData(hItem, GPOINTER_TO_UINT(ve));
			
			GetTreeCtrl().Expand(hChildItem, TVE_EXPAND);
		}
		GetTreeCtrl().Expand(m_hVarsItem, TVE_EXPAND);
	}

	//
	// Appplications tree
	//
	apps = g_node_nth_child(ctree_win.dirlist, 1);
	for(i=0; i<g_node_n_children(apps); i++)
    {
		GNode *node = g_node_nth_child(apps, i);
		TiVarEntry *ve = (TiVarEntry *)(node->data);
		char *size;
		char icon_name[256];
		CString szText;

		tilp_var_get_size(ve, &size);
		szText.Format(" %8s [%5s] %8s", ve->trans, tifiles_vartype2string(ve->type), size, ""); // the first SPC char is used by selection
		g_free(size);

		hChildItem = GetTreeCtrl ().InsertItem (_T ("  "+szText), 
				ILI_APP, ILI_APP, m_hAppsItem);
		GetTreeCtrl().SetItemData(hChildItem, GPOINTER_TO_UINT(ve));
		GetTreeCtrl().Expand(hChildItem, TVE_EXPAND);
      
    }
	GetTreeCtrl().Expand(m_hAppsItem, TVE_EXPAND);
	
	GetTreeCtrl().EnsureVisible(m_hVarsItem);

	return 0;
}

void CLeftView::OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    HTREEITEM hItem = pNMTreeView->itemNew.hItem;

	if(pNMTreeView->action & TVE_EXPAND)
		GetTreeCtrl().SetItemImage(hItem, ILI_FOLDER_OPENED, ILI_FOLDER_OPENED);
	else if(pNMTreeView->action & TVE_COLLAPSE)
		GetTreeCtrl().SetItemImage(hItem, ILI_FOLDER_CLOSED, ILI_FOLDER_CLOSED);

	GetTreeCtrl().Select(hItem, TVGN_CARET);

	*pResult = FALSE;
}

void CLeftView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = FALSE;
}

void CLeftView::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	/*
	TVITEM tvItemNew = pNMTreeView->itemNew;
	TVITEM tvItemOld = pNMTreeView->itemOld;
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	if(tvItemOld.state & TVIS_SELECTED)
		DISPLAY("old selected\n");
	else
		DISPLAY("old unselected\n");
	if(tvItemNew.state & TVIS_SELECTED)
		DISPLAY("new selected\n");
	else
		DISPLAY("new unselected\n");

	tvItemOld.state |= TVIS_SELECTED;
	*/

#undef TEST
//#define TEST

#ifdef TEST
	*pResult = FALSE;
#else
	*pResult = TRUE;	// overriden: TRUE, disable blue selection
#endif
}

void CLeftView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	char str[256];
#ifdef TEST
	*pResult = FALSE;
#else
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	// TODO: Add your control notification handler code here
	DWORD dwPos = GetMessagePos();
	CPoint point ((int)LOWORD(dwPos), (int)HIWORD(dwPos));
	GetTreeCtrl().ScreenToClient(&point);

	HTREEITEM hItem;
	UINT uiFlags;
	hItem = GetTreeCtrl().HitTest(point, &uiFlags);

	if( (hItem != NULL) && (uiFlags & TVHT_ONITEMLABEL) )
	{
		CString cs;
		LPTSTR lpszItem;

		cs = GetTreeCtrl().GetItemText(hItem);
		lpszItem = cs.GetBuffer(1024);
		DWORD dw = GetTreeCtrl().GetItemData(hItem);
		TiVarEntry *ve = (TiVarEntry *)GUINT_TO_POINTER(dw);

		if(ve == NULL) { *pResult = FALSE; return; }

		if(!ti_calc.has_folder || strcmp(ve->folder, ""))
		{	// var: select it
			if(lpszItem[0] == ' ') lpszItem[0]='*'; else lpszItem[0]=' ';
			GetTreeCtrl().SetItemText(hItem, lpszItem);
		}
		else
		{	// folder: select sub-vars
			HTREEITEM hChildItem;
			if ((hChildItem = GetTreeCtrl ().GetChildItem (hItem)) == NULL)
			return;

			do 
			{
				cs = GetTreeCtrl().GetItemText(hChildItem);
				lpszItem = cs.GetBuffer(1024);
				if(lpszItem[0] == ' ') lpszItem[0]='*'; else lpszItem[0]=' ';
				GetTreeCtrl().SetItemText(hChildItem, lpszItem);

				HTREEITEM hNextItem = GetTreeCtrl ().GetNextSiblingItem (hChildItem);
				hChildItem = hNextItem;
				} 
			while (hChildItem != NULL);
		}
		BuildSelection();
	}

	*pResult = FALSE;	// overriden: TRUE,  dbl-click for expanding/collapsing
#endif
}

void CLeftView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	DWORD dwPos = GetMessagePos();
	CPoint point ((int)LOWORD(dwPos), (int)HIWORD(dwPos));
	GetTreeCtrl().ScreenToClient(&point);

	HTREEITEM hItem;
	UINT uiFlags;
	hItem = GetTreeCtrl().HitTest(point, &uiFlags);

	if(hItem == m_hScreenItem)
		LaunchScreendump();
	else if(hItem == m_hRomdumpItem)
		LaunchRomdump();

	*pResult = FALSE;
}

void CLeftView::ForceRefresh()
{
	tilp_ctree_selection_destroy();
	Refresh();
	UpdateInfo();
	BuildSelection();
}

void CLeftView::OnCalcDirlist() 
{
	// TODO: Add your command handler code here
	OnOperationsDirectorylist();
	UpdateInfo();
}

UINT Thread3Func(LPVOID pParam);
void CLeftView::OnOperationsDirectorylist() 
{
	// TODO: Add your command handler code here
	tilp_ctree_selection_destroy();
	
	CWinThread* pThread = AfxBeginThread(Thread3Func, this, 
		THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

	::DuplicateHandle(GetCurrentProcess(), pThread->m_hThread, 
		GetCurrentProcess(), &m_hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);

	pThread->ResumeThread();
}

UINT Thread3Func(LPVOID pParam)
{

	if(tilp_calc_dirlist()) return 0;

	CLeftView *pView = (CLeftView *)pParam;
	pView->PostMessage(WM_USER_THREAD3_FINISHED, 0, 0);

	return 0;
}

LRESULT CLeftView::OnThread3Finished (WPARAM wParam, LPARAM lParam)
{
	// Ensure that thread is terminated
	ASSERT(m_hThread != NULL);
	::WaitForSingleObject(m_hThread, INFINITE);
	::CloseHandle(m_hThread);
	m_hThread = NULL;

	Refresh();
	UpdateInfo();

    return 0;
}

void CLeftView::BuildSelection()
{
	tilp_ctree_selection_destroy();
	BuildVarsSelection();
	BuildAppsSelection();
}

void CLeftView::BuildVarsSelection() 
{	
	// Parse the tree and build the selection
	HTREEITEM hRootItem;
	HTREEITEM hFolderCurrentItem;
	HTREEITEM hFolderNextItem;
	HTREEITEM hVarCurrentItem;
	HTREEITEM hVarNextItem;
	int ct = options.lp.calc_type;

	hRootItem = m_hVarsItem;
	if ((hFolderCurrentItem = GetTreeCtrl ().GetChildItem (hRootItem)) == NULL)
	return;

	do 
	{	// parse folders
		//DisplayItem(hFolderCurrentItem, "folder: ");
		if(ti_calc.has_folder)
		{
			if ((hVarCurrentItem = GetTreeCtrl ().GetChildItem (hFolderCurrentItem)) == NULL)
				break;
		}
		else
			hVarCurrentItem = hFolderCurrentItem;

		do
		{	// parse vars
			DisplayItem(hVarCurrentItem, "var: ");

			CString cs = GetTreeCtrl().GetItemText(hVarCurrentItem);
			LPSTR lpszItem = cs.GetBuffer(1024);
			if(lpszItem[0] == '*')
			{
				DWORD dw = GetTreeCtrl().GetItemData(hVarCurrentItem);
				TiVarEntry *ve = (TiVarEntry *)GUINT_TO_POINTER(dw);
				
				//DisplayItem(hVarCurrentItem, "selected");
				ctree_win.selection = g_list_append(ctree_win.selection, ve);
			}

			hVarNextItem = GetTreeCtrl().GetNextSiblingItem(hVarCurrentItem);
			hVarCurrentItem = hVarNextItem;
		}
		while(hVarCurrentItem != NULL);

		if(ti_calc.has_folder)
		{
			hFolderNextItem = GetTreeCtrl ().GetNextSiblingItem (hFolderCurrentItem);
			hFolderCurrentItem = hFolderNextItem;
		}
		else 
			break;
	} 
	while (hFolderCurrentItem != NULL);
}

void CLeftView::BuildAppsSelection() 
{	
	// Parse the tree and build the selection
	HTREEITEM hRootItem;
	HTREEITEM hAppCurrentItem;
	HTREEITEM hAppNextItem;
		
	hRootItem = m_hAppsItem;
	if ((hAppCurrentItem = GetTreeCtrl ().GetChildItem (hRootItem)) == NULL)
		return;

	do
	{	// parse vars
		//DisplayItem(hAppCurrentItem, "app: ");

		CString cs = GetTreeCtrl().GetItemText(hAppCurrentItem);
		LPSTR lpszItem = cs.GetBuffer(1024);
		if(lpszItem[0] == '*')
		{
			DWORD dw = GetTreeCtrl().GetItemData(hAppCurrentItem);
			TiVarEntry *ve = (TiVarEntry *)GUINT_TO_POINTER(dw);
					
			//DisplayItem(hAppCurrentItem, "selected");
			ctree_win.selection2 = g_list_append(ctree_win.selection2, ve);
		}

		hAppNextItem = GetTreeCtrl().GetNextSiblingItem(hAppCurrentItem);
		hAppCurrentItem = hAppNextItem;
	}
	while(hAppCurrentItem != NULL);

}

void CLeftView::UpdateInfo()
{
	CWnd* pWnd = AfxGetMainWnd();
	CMainFrame *pFrame = (CMainFrame *)pWnd;
	pFrame->m_wndStatusBar.UpdateInfo();
}

void CLeftView::ReloadFont()
{
	BOOL bRes = TRUE;
	char str[256];
	
	m_tiFont.DeleteObject();
	/*
	switch(options.lp.calc_type)
	{
	case CALC_TI73:
		bRes = m_tiFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"FastLink TI-83");
		break;
	case CALC_TI82:
	case CALC_TI83:
	case CALC_TI85:
	case CALC_TI86:
		bRes = m_tiFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"FastLink TI-86");
		break;
	case CALC_TI83P:
		bRes = m_tiFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"FastLink TI-83");
	break;
	case CALC_TI89:
	case CALC_TI92:
	case CALC_TI92P:
		bRes = m_tiFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"FastLink TI-89");
		sprintf(str, "%i\n", bRes);
		MessageBox(str);
			
	break;
	}
	*/
	bRes = m_tiFont.CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Courier New");
	this->SetFont(&m_tiFont, TRUE);
}

void CLeftView::LaunchScreendump()
{
	CScreenDlg*	pScreenDlg;
	pScreenDlg = new CScreenDlg;
	pScreenDlg->Create(IDD_SCREENDUMP);
	pScreenDlg->ShowWindow(SW_SHOW);
	pScreenDlg->GetScreenDump();
}

void CLeftView::LaunchRomdump()
{
	CWnd* pWnd = AfxGetMainWnd();
	CMainFrame *pFrame = (CMainFrame *)pWnd;
	pFrame->CallRomDump();
}

void CLeftView::DisplayItem(HTREEITEM hItem, LPSTR header)
{
	CString cs;
	LPTSTR lpszItem;

	cs = GetTreeCtrl().GetItemText(hItem);
	lpszItem = cs.GetBuffer(1024);
	if(hItem != NULL)
		DISPLAY("%s: <%s>\n", header, lpszItem);
	else
		DISPLAY("%s: null !\n", header);
}

void CLeftView::OnSetFocus(CWnd* pOldWnd) 
{
	CTreeView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	CWnd* pWnd = AfxGetMainWnd();
	if(pWnd == NULL) return;
	CMainFrame *pFrame = (CMainFrame *)pWnd;
	if(pFrame == NULL) return;
	pFrame->m_wndToolBar2.LoadBitmap(IDB_TOOLBAR2_R);
}
