// SpecialStatusBar.cpp: implementation of the CSpecialStatusBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpecialStatusBar.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CSpecialStatusBar, CStatusBar)
	ON_WM_CREATE ()
	ON_WM_SIZE ()
END_MESSAGE_MAP()

CSpecialStatusBar::CSpecialStatusBar()
{
}

CSpecialStatusBar::~CSpecialStatusBar()
{
}

int CSpecialStatusBar::OnCreate (LPCREATESTRUCT lpcs)
{
	static UINT nIndicators[] =
	{
		ID_SEPARATOR,
		ID_SEPARATOR,
		ID_SEPARATOR,

		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL,
	};

	if (CStatusBar::OnCreate (lpcs) == -1)
		return -1;

	//
	// Add panes to the status bar.
	//
	SetIndicators (nIndicators, sizeof (nIndicators) / sizeof (UINT));

	//
	// Size the status bar panes.
	//
    TEXTMETRIC tm;
    CClientDC dc (this);
    CFont* pFont = GetFont ();
    CFont* pOldFont = dc.SelectObject (pFont);
    dc.GetTextMetrics (&tm);
    dc.SelectObject (pOldFont);

    int cxWidth;
    UINT nID, nStyle;
    GetPaneInfo (1, nID, nStyle, cxWidth);
    SetPaneInfo (1, nID, nStyle, tm.tmAveCharWidth * 30);
    GetPaneInfo (2, nID, nStyle, cxWidth);
    SetPaneInfo (2, nID, SBPS_NOBORDERS, tm.tmAveCharWidth * 24);

	//
	// Place a progress control in the rightmost pane.
	//
	CRect rect;
	GetItemRect (2, &rect);
	m_wndProgress.Create (WS_CHILD | WS_VISIBLE | PBS_SMOOTH, rect, this, -1);
	m_wndProgress.SetRange (0, 100);
	m_wndProgress.SetPos (0);

	SetProgress(50);
	//SetImageStats("coucou");
	UpdateInfo();

	return 0;
}

void CSpecialStatusBar::OnSize (UINT nType, int cx, int cy)
{
/*
	CStatusBar::OnSize (nType, cx, cy);

	//
	// Resize the rightmost pane to fit the resized status bar.
	//
	CRect rect;
	GetItemRect (2, &rect);
	m_wndProgress.SetWindowPos (NULL, rect.left, rect.top,
		rect.Width (), rect.Height (), SWP_NOZORDER);
*/
}

void CSpecialStatusBar::SetImageStats(LPCTSTR pszStats)
{
	SetPaneText (1, "Hello !", TRUE);
}

void CSpecialStatusBar::UpdateInfo()
{
	CString cs; //cs.Format(_("Memory used: %i bytes"), ctree_win.memory);

	switch(ti_calc.memory)
    {
    case MEMORY_FREE:
		cs.Format(_("Memory free: %lu bytes"), ctree_win.memory);
	break;
      
    case MEMORY_USED:
      cs.Format(_("Memory used: %lu bytes"), ctree_win.memory);
    break;

    case MEMORY_NONE:
      cs.Format(_("Memory used: %lu bytes"), _("N/A"));
    break;
    }
}

void CSpecialStatusBar::SetProgress(int nPercent)
{
	ASSERT (nPercent >= 0 && nPercent <= 100);
	m_wndProgress.SetPos (nPercent);
}
