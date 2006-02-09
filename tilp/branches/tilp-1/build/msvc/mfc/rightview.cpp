// RightView.cpp : implementation of the CRightView class
//

// roms: some code comes from this book: "Programming Windows with MFC",
// Second Edition, Jeff Prosise, page 586

#include "stdafx.h"
#include "TiLP.h"

#include "LeftDoc.h"
#include "RightView.h"
#include "MainFrm.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Image indexes
#define ILI_DOTDOT	0
#define ILI_DIR		1
#define ILI_DOC		2

static int ili_doc = ILI_DOC+1;

/////////////////////////////////////////////////////////////////////////////
// CRightView

IMPLEMENT_DYNCREATE(CRightView, CListView)

BEGIN_MESSAGE_MAP(CRightView, CListView)
	//{{AFX_MSG_MAP(CRightView)
	ON_WM_CONTEXTMENU()
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetDispInfo)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_COMMAND(ID_RBM_FILE_RENAME, OnRbmFileRename)
	ON_COMMAND(ID_RBM_FILE_VIEW, OnRbmFileView)
	ON_COMMAND(ID_COMP_REFRESH, OnCompRefresh)
	ON_COMMAND(ID_COMP_TRASH, OnCompTrash)
	ON_COMMAND(ID_COMP_MKDIR, OnCompMkdir)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_COMMAND(ID_RBM_EDIT_SEL, OnRbmEditSel)
	ON_COMMAND(ID_RBM_EDIT_UNSEL, OnRbmEditUnsel)
	ON_COMMAND(ID_RBM_EDIT_MOVE, OnRbmEditMove)
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_RBM_GFM_GROUP, OnRbmGfmGroup)
	ON_COMMAND(ID_RBM_GFM_OPEN, OnRbmGfmOpen)
	ON_COMMAND(ID_RBM_GFM_UNGROUP, OnRbmGfmUngroup)
	ON_COMMAND(ID_RBM_MISC_SETDIR, OnRbmMiscSetdir)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND_RANGE(ID_RBM_DRIVE_A, ID_RBM_DRIVE_Z, OnRbmDrive)
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRightView construction/destruction

CRightView::CRightView()
{
	// TODO: add construction code here
	m_ptMsg = CPoint(0,0);						// Popup menu
}

CRightView::~CRightView()
{
}

BOOL CRightView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

BOOL CRightView::BitmapToImageList(CImageList *list, UINT nIDRessource)
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

// same function in leftview.cpp
BOOL CRightView::BitmapToImageListFromFile(CImageList *list, LPCSTR lpszFilename)
{
	CBitmap bmp;
	HICON hIcon;
	gchar *str, *ext;
	char buf[256];
	
	ext = strstr(lpszFilename, ".ico");
	str = g_strconcat(inst_paths.icon_dir, lpszFilename, (ext == NULL) ? ".ico" : "", NULL);

	hIcon = (HICON)LoadImage(NULL, str, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	if(hIcon != NULL)
		list->Add(hIcon);
	else
		MessageBox(str, "Icon not found", MB_OK);
	
	g_free(str);
	return (hIcon == NULL) ? FALSE : TRUE;
}

void CRightView::SetListView(DWORD dwNewStyle)
{
	DWORD dwOldStyle;
	CListCtrl& refCtrl = GetListCtrl();
	HWND hWndList = refCtrl.GetSafeHwnd();

	dwOldStyle = GetWindowLong(hWndList, GWL_STYLE);

	if((dwOldStyle & LVS_TYPEMASK) != dwNewStyle)
	{
		dwOldStyle &= ~LVS_TYPEMASK;
		dwNewStyle |= dwOldStyle;
		SetWindowLong(hWndList, GWL_STYLE, dwNewStyle);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRightView drawing

void CRightView::OnDraw(CDC* pDC)
{
	CLeftDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CRightView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
	SetListView(LVS_REPORT);
	//
	// Initialize the image list.
	//
    m_ilLarge.Create (32, 32, TRUE, 3, 1);
	BitmapToImageListFromFile(&m_ilLarge, "up.ico");
	BitmapToImageList(&m_ilLarge, IDB_CLIST_DIR_LARGE);
	BitmapToImageList(&m_ilLarge, IDB_CLIST_DOC_LARGE);
	GetListCtrl ().SetImageList (&m_ilLarge, LVSIL_NORMAL);

    m_ilSmall.Create (16, 16, TRUE, 3, 1);
	BitmapToImageListFromFile(&m_ilSmall, "up.ico");
	BitmapToImageList(&m_ilSmall, IDB_CLIST_DIR_SMALL);
	BitmapToImageList(&m_ilSmall, IDB_CLIST_DOC_SMALL);
    GetListCtrl ().SetImageList (&m_ilSmall, LVSIL_SMALL);

	//
	// Add columns to the list view.
	//
    GetListCtrl ().InsertColumn (0, _T ("File Name"), LVCFMT_LEFT, 150);
	GetListCtrl ().InsertColumn (1, _T ("Type"), LVCFMT_LEFT, 80);
    GetListCtrl ().InsertColumn (2, _T ("Size"), LVCFMT_RIGHT, 80);
    GetListCtrl ().InsertColumn (3, _T ("Last Modified"), LVCFMT_CENTER, 128);

	//
	// Populate the list view with items.
	//
	TCHAR szPath[MAX_PATH];
	::GetCurrentDirectory (sizeof (szPath) / sizeof (TCHAR), szPath);
	Refresh (szPath);
}

/////////////////////////////////////////////////////////////////////////////
// CRightView printing

BOOL CRightView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRightView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRightView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRightView diagnostics

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CListView::AssertValid();
}

void CRightView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CLeftDoc* CRightView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLeftDoc)));
	return (CLeftDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRightView message handlers
void CRightView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}

void CRightView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CMenu rbmMenu;
	DWORD dwBitMask;
	TCHAR tcBuffer[1024] = { 0 };
	char str[256];

	// Load contextual menu
	m_ptMsg = point;
	ScreenToClient(&m_ptMsg);
	rbmMenu.LoadMenu(IDR_RBM);
	CMenu* pPopup = rbmMenu.GetSubMenu(0);
	CMenu* pDrive = pPopup->GetSubMenu(3);	// think to update it if resource is modified

	// Dynamically create the 'Change drive' sub-menu
	dwBitMask = GetLogicalDrives();
	for(int drive=26; drive>2; drive--)
	{	
		DWORD dwMask = 1 << drive;
		if(!(dwBitMask & dwMask))
			pDrive->DeleteMenu(ID_RBM_DRIVE_A + drive - 1, MF_BYCOMMAND);
	}

	// and display it
	int nCmd = (int)pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CRightView::OnRbmDrive(UINT nID)
{
	tilp_drive_change(nID - ID_RBM_DRIVE_A + 'A');
	Refresh(clist_win.cur_dir);
}

int CRightView::Refresh(LPCTSTR pszPath)
{
	HANDLE hFind;
    WIN32_FIND_DATA fd;
    int nCount = 0;
    CString strPath = pszPath;
	int i;

    if (strPath.Right (1) != _T ("\\"))
        strPath += _T ("\\");
    strPath += _T ("*.*");

    if ((hFind = ::FindFirstFile (strPath, &fd)) != INVALID_HANDLE_VALUE) 
	{
		// Delete existing items (if any).
		GetListCtrl ().DeleteAllItems ();

		// clear image list (partial)
		for(i <= ili_doc; i > ILI_DOC; i++)
			m_ilSmall.Remove(i);
		for(i <= ili_doc; i > ILI_DOC; i++)
			m_ilLarge.Remove(i);
		ili_doc = ILI_DOC+1;

		//
		// Show the path name in the frame window's title bar.
		//
		TCHAR szFullPath[MAX_PATH];
		::GetFullPathName (pszPath, sizeof (szFullPath) / sizeof (TCHAR),
			szFullPath, NULL);
		m_strPath = szFullPath;

		CString strTitle = _T ("TiLP - ");
		strTitle += szFullPath;
		AfxGetMainWnd ()->SetWindowText (strTitle);

		//
		// Add items representing files to the list view.
		//
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            AddItem (nCount++, &fd);

        while (::FindNextFile (hFind, &fd)) 
		{
			if( (options.file_disp == SHOW_ALL) || tifiles_is_a_ti_file(fd.cFileName) || 
				(tifiles_is_a_ti_file(fd.cFileName) && 
				(tifiles_which_calc_type(fd.cFileName) == options.lp.calc_type)) )
			{
                if (!AddItem (nCount++, &fd))
                    break;
			}
        }
        ::FindClose (hFind);
    }

	// Sort items
	GetListCtrl ().SortItems (CompareFunc, 4);
	switch(options.clist_sort)
    {
    case SORT_BY_NAME:
      GetListCtrl ().SortItems (CompareFunc, 0);
      break;
	case SORT_BY_TYPE:
      GetListCtrl ().SortItems (CompareFunc, 1);
      break;
    case SORT_BY_DATE:
      GetListCtrl ().SortItems (CompareFunc, 2);
      break;
    case SORT_BY_SIZE:
      GetListCtrl ().SortItems (CompareFunc, 3);
      break;
    }

    return nCount;
}

BOOL CRightView::AddItem(int nIndex, WIN32_FIND_DATA *pfd)
{
	//
	// Allocate a new ITEMINFO structure and initialize it with information
	// about the item.
	//
    ITEMINFO* pItem;
    try {
        pItem = new ITEMINFO;
    }
    catch (CMemoryException* e) {
        e->Delete ();
        return FALSE;
    }

    pItem->strFileName = pfd->cFileName;
    pItem->nFileSizeLow = pfd->nFileSizeLow;
    pItem->ftLastWriteTime = pfd->ftLastWriteTime;
	pItem->dwFileAttributes = pfd->dwFileAttributes;

	//
	// Add the item to the list view.
	//
    LV_ITEM lvi;
    lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
    lvi.iItem = nIndex; 
    lvi.iSubItem = 0; 
	if(pfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		if(strcmp(pfd->cFileName, ".."))
			lvi.iImage = ILI_DIR;
		else
			lvi.iImage = ILI_DOTDOT;
	}
	else
	{
		char icon_name[256];

		strcpy(icon_name, tifiles_file_descriptive(pfd->cFileName));
		if(!strcmp(icon_name, ""))
			strcpy(icon_name, "TIicon1");

		tilp_file_underscorize(icon_name);

		BitmapToImageListFromFile(&m_ilSmall,icon_name);
		GetListCtrl().SetImageList (&m_ilSmall, LVSIL_SMALL);
		BitmapToImageListFromFile(&m_ilLarge,icon_name);
		GetListCtrl().SetImageList (&m_ilLarge, LVSIL_NORMAL);

		lvi.iImage = ili_doc++;
	}		
    
	lvi.pszText = LPSTR_TEXTCALLBACK; 
    lvi.lParam = (LPARAM) pItem;

    if (GetListCtrl ().InsertItem (&lvi) == -1)
        return FALSE;

    return TRUE;
}

void CRightView::FreeItemMemory()
{
    int nCount = GetListCtrl ().GetItemCount ();
    if (nCount) {
        for (int i=0; i<nCount; i++)
            delete (ITEMINFO*) GetListCtrl ().GetItemData (i);
    }
}

void CRightView::OnDestroy() 
{
	FreeItemMemory ();
	CListView::OnDestroy ();
}

void CRightView::OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
    CString string;
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*) pNMHDR;

    if (pDispInfo->item.mask & LVIF_TEXT) {
        ITEMINFO* pItem = (ITEMINFO*) pDispInfo->item.lParam;

        switch (pDispInfo->item.iSubItem) {

        case 0: // File name
            ::lstrcpy (pDispInfo->item.pszText, pItem->strFileName);
            break;

		case 1: // File type
			::lstrcpy(pDispInfo->item.pszText, tifiles_file_descriptive(pItem->strFileName));
			break;

        case 2: // File size
			if(pItem->nFileSizeLow > 1024*1024)
				string.Format (_T ("%u MB"), pItem->nFileSizeLow >> 20);
			else if(pItem->nFileSizeLow > 1024)
				string.Format (_T ("%u KB"), pItem->nFileSizeLow >> 10);
			else
				string.Format (_T ("%u"), pItem->nFileSizeLow);
            ::lstrcpy (pDispInfo->item.pszText, string);
            break;

        case 3: // Date and time
            CTime time (pItem->ftLastWriteTime);

            BOOL pm = FALSE;
            int nHour = time.GetHour ();
            if (nHour == 0)
                nHour = 12;
            else if (nHour == 12)
                pm = TRUE;
            else if (nHour > 12) {
                nHour -= 12;
                pm = TRUE;
            }

            string.Format (_T ("%d/%0.2d/%0.2d (%d:%0.2d%c)"),
                time.GetMonth (), time.GetDay (), time.GetYear () % 100,
                nHour, time.GetMinute (), pm ? _T ('p') : _T ('a'));
            ::lstrcpy (pDispInfo->item.pszText, string);
            break;
        }
    }
	*pResult = 0;
}

void CRightView::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*) pNMHDR;
	GetListCtrl ().SortItems (CompareFunc, 4);
    GetListCtrl ().SortItems (CompareFunc, pNMListView->iSubItem);

	*pResult = 0;
}

static int sortable(ITEMINFO* pItem1, ITEMINFO* pItem2)
{
	return ((pItem1->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			 (pItem2->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) ||
			(!(pItem1->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			 !(pItem2->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
}

int CALLBACK CRightView::CompareFunc (LPARAM lParam1, LPARAM lParam2,
    LPARAM lParamSort)
{
    ITEMINFO* pItem1 = (ITEMINFO*) lParam1;
    ITEMINFO* pItem2 = (ITEMINFO*) lParam2;
    int nResult = 0;

    switch (lParamSort) {

    case 0: // File name
		if(sortable(pItem1, pItem2))
			nResult = pItem1->strFileName.CompareNoCase (pItem2->strFileName);
        break;

	case 1: // File type
		if(sortable(pItem1, pItem2))
			nResult = pItem1->strFileName.CompareNoCase (pItem2->strFileName);

    case 2: // File size
		if(sortable(pItem1, pItem2))
			nResult = pItem1->nFileSizeLow - pItem2->nFileSizeLow;
        break;

    case 3: // Date and time
		if(sortable(pItem1, pItem2))
			nResult = ::CompareFileTime (&pItem1->ftLastWriteTime,
										 &pItem2->ftLastWriteTime);
        break;

	case 4: // Type (file/dir): used for separating the items
		if(pItem1->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			nResult = -1;
		else
			nResult = 1;
		break;
    }
    return nResult;
}

// Simple click: selection
void CRightView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DWORD dwPos = GetMessagePos();
	CPoint point ((int)LOWORD(dwPos), (int)HIWORD(dwPos));
	GetListCtrl().ScreenToClient(&point);

	tilp_clist_selection_destroy();

	POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		while (pos)
		{
			int nItem = GetListCtrl().GetNextSelectedItem(pos);
			//DISPLAY("Item %d was selected <%s>!\n", nItem, GetListCtrl().GetItemText(nItem, 0).GetBuffer(256));
			ITEMINFO *iF = (ITEMINFO*) GetListCtrl ().GetItemData (nItem);

			if(!(iF->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				TilpFileInfo *fi;
				char *full_name;
				fi=(TilpFileInfo *)g_malloc0(sizeof(TilpFileInfo));
				fi->name = g_strdup(iF->strFileName);
				fi->size = iF->nFileSizeLow;
				fi->actions = NULL;
				//fi->date = iF->ftLastWriteTime;

				clist_win.selection = g_list_append(clist_win.selection, fi);
				full_name=g_strconcat(clist_win.cur_dir, DIR_SEPARATOR, iF->strFileName, NULL);
				tilp_add_file_to_file_selection(full_name);
			}
			else
			{
				char *full_name;
				full_name=g_strconcat(clist_win.cur_dir, DIR_SEPARATOR, iF->strFileName, NULL);
				//tilp_add_file_to_file_selection(full_name);

				GetListCtrl().SetItemState(nItem, GetListCtrl().GetItemState(nItem, LVIF_STATE) & ~LVIS_SELECTED, LVIF_STATE);

			}
		}
	}
	
	*pResult = 0;
}

void CRightView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnClick(pNMHDR, pResult);
	
	*pResult = 0;
}

// Double-click: change current dir
void CRightView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DWORD dwPos = GetMessagePos();
	CPoint point ((int)LOWORD(dwPos), (int)HIWORD(dwPos));
	GetListCtrl().ScreenToClient(&point);

	int nIndex;
	if((nIndex = GetListCtrl().HitTest(point)) != -1)
	{
		CString string = GetListCtrl().GetItemText(nIndex, 0);

		ITEMINFO *iF = (ITEMINFO*) GetListCtrl ().GetItemData (nIndex);
		if(iF->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(tilp_chdir(string))
				gif->msg_box(_("Error"), _("Unable to change of directory."));
		}
	}

	/* Retrieve current working directory */
	g_free(clist_win.cur_dir);
	clist_win.cur_dir = g_get_current_dir();

	Refresh(clist_win.cur_dir);
	
	*pResult = 0;
}


void CRightView::SelectAll()
{
	/*
	//GetListCtrl ().GetNextItem(-1, LVNI_ALL));
	int nItem = 2;
	LVITEM pItem;
	LPTSTR szStr;
	//GetListCtrl().SetItemState(nItem, GetListCtrl().GetItemState(nItem, LVIF_STATE) & ~LVIS_SELECTED, LVIF_STATE);
	pItem.mask = LVIF_TEXT;
	pItem.stateMask = (UINT)-1;
	GetListCtrl().GetItem(&pItem);

	pItem.mask = LVIF_TEXT;
	szStr = pItem.pszText;
	szStr = "toto";
	GetListCtrl().SetItem(&pItem);

	CRect rect;
	GetListCtrl().GetItemRect(2, &rect, LVIR_LABEL);
	this->InvalidateRect(&rect, TRUE);
	*/
}

void CRightView::InvertSelection()
{

}

void CRightView::ForceRefresh()
{
	OnCompRefresh();
}

void CRightView::OnCompRefresh() 
{
	// TODO: Add your command handler code here
	tilp_clist_selection_destroy();
	Refresh(clist_win.cur_dir);	
}

void CRightView::OnCompMkdir() 
{
	// TODO: Add your command handler code here
	gchar *dirname;

	dirname=gif->dlgbox_entry(_("Make a new directory"), 
			    _("Name: "), 
			    _("new_directory"));
	if(dirname == NULL) return;

	if(!CreateDirectory(dirname, NULL))
	{
		gif->msg_box(_("Information"), _("Unable to create the directory.\n\n"));
		g_free(dirname);
	}
	g_free(dirname);

	Refresh(clist_win.cur_dir);
}

void CRightView::OnCompTrash() 
{
	// TODO: Add your command handler code here
	tilp_delete_selected_files();

	OnCompRefresh();
}

void CRightView::OnRbmFileRename() 
{
	// TODO: Add your command handler code here
	tilp_rename_selected_files();

	OnCompRefresh();
}

void CRightView::OnRbmFileView() 
{
	// TODO: Add your command handler code here
	//TiFFEP
}

void CRightView::OnRbmEditSel() 
{
	// TODO: Add your command handler code here
	SelectAll();
}

void CRightView::OnRbmEditUnsel() 
{
	// TODO: Add your command handler code here
	InvertSelection();
}

void CRightView::OnRbmEditMove() 
{
	// TODO: Add your command handler code here
	char *home_dir;

	if(chdir(".."))
		gif->msg_box(_("Error"), _("Chdir error.\n"));

	g_free(clist_win.cur_dir);
	clist_win.cur_dir = g_get_current_dir();
  
	OnCompRefresh();
}

void CRightView::OnSetFocus(CWnd* pOldWnd) 
{
	CListView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	CWnd* pWnd = AfxGetMainWnd();
	if(pWnd == NULL) return;
	CMainFrame *pFrame = (CMainFrame *)pWnd;
	if(pFrame == NULL) return;
	pFrame->m_wndToolBar2.LoadBitmap(IDB_TOOLBAR2_S);
}

void CRightView::OnEditCut() 
{
	// TODO: Add your command handler code here
	clist_win.copy_cut = CUT_FILE;
}

void CRightView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CRightView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	clist_win.copy_cut = COPY_FILE;
}

void CRightView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CRightView::OnEditPaste() 
{
	// TODO: Add your command handler code here
	BOOL bRes = 0;
	GList *ptr;
	char *src;
	char *dst;
  
	/* If no selection, quits */
	if(clist_win.file_selection == NULL) return;

	/* Move every file */
	ptr=clist_win.file_selection;
	while(ptr != NULL)
    {
		src=(gchar *)(ptr->data);
		dst = g_strconcat(clist_win.cur_dir, DIR_SEPARATOR,
				g_basename(src), NULL);

		if(clist_win.copy_cut == COPY_FILE)
		{
			bRes = CopyFile(src, dst, TRUE);
			//if(!bRes)
			//{
			//	gif->msg_box(_("Error"), _("Unable to copy the file.\n"));
			//}
		}
      else
		{
			bRes = MoveFile(src, dst);
			if(!bRes)
			{
				gif->msg_box(_("Error"), _("Unable to move the file.\n"));
			}
		}
		g_free(dst);

		ptr=ptr->next;
    }

	tilp_clist_file_selection_destroy();

	OnCompRefresh();
}

void CRightView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(clist_win.copy_cut == 0)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

void CRightView::OnEditUndo() 
{
	// TODO: Add your command handler code here
	
}

void CRightView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CRightView::OnRbmGfmUngroup() 
{
	// TODO: Add your command handler code here
	tilp_tifiles_ungroup();

	tilp_clist_selection_destroy();
	tilp_dirlist_local();

	OnCompRefresh();
}

void CRightView::OnRbmGfmGroup() 
{
	// TODO: Add your command handler code here
	tilp_tifiles_group();

	tilp_clist_selection_destroy();
	tilp_dirlist_local();
	
	OnCompRefresh();
}

void CRightView::OnRbmGfmOpen() 
{
	// TODO: Add your command handler code here
	GList *sel;
  
	if((sel = clist_win.selection) == NULL) 
		return;

	while(sel != NULL)
    {
		TilpFileInfo *f = (TilpFileInfo *)sel->data;
		//display_gfm_dbox(f->name);

		sel = g_list_next(sel);
    }
}

void CRightView::OnRbmMiscSetdir() 
{
	// TODO: Add your command handler code here
	g_free(options.working_dir);
	options.working_dir = g_get_current_dir();
	tilp_config_save();
}
