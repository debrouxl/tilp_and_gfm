// RemoteControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TiLP.h"
#include "RemoteControlDlg.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRemoteControlDlg dialog


CRemoteControlDlg::CRemoteControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRemoteControlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRemoteControlDlg)
	//}}AFX_DATA_INIT
	m_textFont.CreateFont(13, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Courier New");
}


void CRemoteControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRemoteControlDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_RCONTROL_INFO, m_info);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRemoteControlDlg, CDialog)
	//{{AFX_MSG_MAP(CRemoteControlDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemoteControlDlg message handlers

BOOL CRemoteControlDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	static CString strLabel[] = {
        _T ("TI83(+)"),
        _T ("TI89"),
        _T ("TI92(+)")
    };

    // Set the tab width to 96 pixels.
    m_tab.SetItemSize (CSize (96, 0));

    // Add three tabs.
    TC_ITEM item;
    item.mask = TCIF_TEXT;
    for (int i=0; i<3; i++) {
        item.pszText = (LPTSTR) (LPCTSTR) strLabel[i];
        item.cchTextMax = strLabel[i].GetLength ();
        m_tab.InsertItem (i, &item);
    }

	m_info.SetFont(&m_textFont, TRUE);
	m_list.SetFont(&m_textFont, TRUE);
	m_list.InsertItem(1, _T("Ready !"));
	m_list.SetFocus();

	switch(options.lp.calc_type)
	{
	case CALC_TI83:
	case CALC_TI83P:
		m_tab.SetCurSel(0);
		RefreshTabs();
		break;
	case CALC_TI89:
		m_tab.SetCurSel(1);
		RefreshTabs();
		break;
	case CALC_TI92:
		m_tab.SetCurSel(2);
		RefreshTabs();
		break;
	}
	//EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CRemoteControlDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CRemoteControlDlg::RefreshTabs()
{
	int nIndex = m_tab.GetCurSel();

	switch(nIndex)
	{
	case 0:
		m_info.SetWindowText(_T(
			"Y= = F1     Window = F2   Zoom = F3     Trace = F4   \r\n"
			"Graph = F5  MODE = Esc    Alpha = CAPS  X,T,theta = `\r\n"
			"Stat = =    Math = F6     Matrx = F7    Prgm = F8    \r\n"	
			"Vars = F9   Clear = PgDn  X^-1 = End    SIN = Ins    \r\n"
			"COS = Home  TAN = PgUp    ^ = NumLock   x^2 = ;      \r\n"
			"log = '     ln = \\        STO = Tab                     "
			));
		break;
	case 1:
		m_info.SetWindowText(_T(
			"^ = SHIFT      Diamond = CTRL   2nd = Alt    alpha = CAPS\r\n"
			"CATALOG = F6   APPS = F9        STO> = Tab   Hand=CAPS   \r\n"
			"MODE = '       | = \\            EE = Ins     CLEAR = Del\r\n"	
			""
			));
		break;
	case 2:
		m_info.SetWindowText(_T(
			"^ = SHIFT     Diamond = CTRL   2nd = Alt    Hand=CAPS  \r\n"
			"F9 = APPS     Theta = ;        STO = Tab    MODE = '   \r\n"
			"LN = \\        SIN = Ins        COS = Home   TAN = PgUp\r\n"
			"CLEAR = Del   (-) = Enter (NumPad)         "	
			));
		break;
	}
}

void CRemoteControlDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	RefreshTabs();

	*pResult = 0;
}

void CRemoteControlDlg::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	CString szStr;
	szStr.Format("VK = %i",  pLVKeyDow->wVKey);
	AfxMessageBox(szStr, MB_OK);
	szStr.Format("GetKeyState = %i\n", GetKeyState('A'));
	AfxMessageBox(szStr, MB_OK);
	
	*pResult = 0;
}

void CRemoteControlDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}
