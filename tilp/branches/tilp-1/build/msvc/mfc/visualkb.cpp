#include <afxwin.h>
#include "VisualKB.h"

#include "../src/tilp_core.h"
#include "tikeys.h"

UINT uiScanCode;
UINT uiChar;

//CMyApp myApp;

/////////////////////////////////////////////////////////////////////////
// CMyApp member functions
/*
BOOL CMyApp::InitInstance()
{
    m_pMainWnd = new CRemoteControl;
    m_pMainWnd->ShowWindow (m_nCmdShow);
    m_pMainWnd->UpdateWindow();
    return TRUE;
}
*/
/////////////////////////////////////////////////////////////////////////
// CRemoteControl message map and member functions

BEGIN_MESSAGE_MAP (CRemoteControl, CWnd)
    ON_WM_CREATE()
    ON_WM_PAINT()
    ON_WM_SETFOCUS()
    ON_WM_KILLFOCUS()
    ON_WM_SETCURSOR()
    ON_WM_LBUTTONDOWN()
    ON_WM_KEYDOWN()
    ON_WM_KEYUP()
    ON_WM_SYSKEYDOWN()
    ON_WM_SYSKEYUP()
    ON_WM_CHAR()
    ON_WM_SYSCHAR()
END_MESSAGE_MAP()

CRemoteControl::CRemoteControl()
{
    m_nTextPos = 0;
    m_nMsgPos = 0;

	//
	// Load the arrow cursor and the I-beam cursor and save their handles.
	//
    m_hCursorArrow = AfxGetApp()->LoadStandardCursor (IDC_ARROW);
    m_hCursorIBeam = AfxGetApp()->LoadStandardCursor (IDC_IBEAM);

	//
	// Register a WNDCLASS.
	//
    CString strWndClass = AfxRegisterWndClass (
        0,
        NULL,
        (HBRUSH) (COLOR_3DFACE + 1),
        AfxGetApp()->LoadStandardIcon (IDI_WINLOGO)
    );

	//
	// Create a window.
	//
    CreateEx (0, strWndClass, _T ("Remote Control"),
        WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL);
}

int CRemoteControl::OnCreate (LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate (lpCreateStruct) == -1)
        return -1;
    
	//
	// Initialize member variables whose values are dependent upon screen
	// metrics.
	//
    CClientDC dc (this);

    TEXTMETRIC tm;
    dc.GetTextMetrics (&tm);
    m_cxChar = tm.tmAveCharWidth;
    m_cyChar = tm.tmHeight;
    m_cyLine = tm.tmHeight + tm.tmExternalLeading;

    m_rcTextBoxBorder.SetRect (16, 16, (m_cxChar * 64) + 16,
        ((m_cyChar * 3) / 2) + 16);

    m_rcTextBox = m_rcTextBoxBorder;
    m_rcTextBox.InflateRect (-2, -2);
    
    m_rcMsgBoxBorder.SetRect (16, (m_cyChar * 4) + 16,
        (m_cxChar * 64) + 16, (m_cyLine * MAX_STRINGS) +
        (m_cyChar * 6) + 16);

    m_rcScroll.SetRect (m_cxChar + 16, (m_cyChar * 6) + 16,
        (m_cxChar * 63) + 16, (m_cyLine * MAX_STRINGS) +
        (m_cyChar * 5) + 16);

    m_ptTextOrigin.x = m_cxChar + 16;
    m_ptTextOrigin.y = (m_cyChar / 4) + 16;
    m_ptCaretPos = m_ptTextOrigin;
    m_nTextLimit = (m_cxChar * 63) + 16;

    m_ptHeaderOrigin.x = m_cxChar + 16;
    m_ptHeaderOrigin.y = (m_cyChar * 3) + 16;

    m_ptUpperMsgOrigin.x = m_cxChar + 16;
    m_ptUpperMsgOrigin.y = (m_cyChar * 5) + 16;

    m_ptLowerMsgOrigin.x = m_cxChar + 16;
    m_ptLowerMsgOrigin.y = (m_cyChar * 5) +
        (m_cyLine * (MAX_STRINGS - 1)) + 16;

    m_nTabStops[0] = (m_cxChar * 24) + 16;
    m_nTabStops[1] = (m_cxChar * 30) + 16;
    m_nTabStops[2] = (m_cxChar * 36) + 16;
    m_nTabStops[3] = (m_cxChar * 42) + 16;
    m_nTabStops[4] = (m_cxChar * 46) + 16;
    m_nTabStops[5] = (m_cxChar * 50) + 16;
    m_nTabStops[6] = (m_cxChar * 54) + 16;

	//
	// Size the window.
	//
    CRect rect (0, 0, m_rcMsgBoxBorder.right + 16,
        m_rcMsgBoxBorder.bottom + 16);
    CalcWindowRect (&rect);

    SetWindowPos (NULL, 0, 0, rect.Width(), rect.Height(),
        SWP_NOZORDER | SWP_NOMOVE | SWP_NOREDRAW);
    return 0;
}

void CRemoteControl::PostNcDestroy()
{
    delete this;
}

void CRemoteControl::OnPaint()
{
    CPaintDC dc (this);

	//
	// Draw the rectangles surrounding the text box and the message list.
	//
    dc.DrawEdge (m_rcTextBoxBorder, EDGE_SUNKEN, BF_RECT);
    dc.DrawEdge (m_rcMsgBoxBorder, EDGE_SUNKEN, BF_RECT);

	//
	// Draw all the text that appears in the window.
	//
    DrawInputText (&dc);
    DrawMessageHeader (&dc);
    DrawMessages (&dc);

	int iLine=0;
	ShowInformations(_T("Some keys are mapped as is:"), iLine++);
	iLine++;
	switch(options.lp.calc_type)
	{
		case CALC_TI92:
		case CALC_TI92P:
			ShowInformations(_T("^ = SHIFT      Diamond = CTRL      2nd = Alt          "), iLine++);
			ShowInformations(_T("Hand=CAPS      F9 = APPS           Theta = ;          "), iLine++);
			ShowInformations(_T("STO = Tab      MODE = '            LN = \\            "), iLine++);
			ShowInformations(_T("SIN = Ins      COS = Home          TAN = PgUp         "), iLine++);
			ShowInformations(_T("CLEAR = Del    (-) = Enter (NumPad)                   "), iLine++);
			break;
		case CALC_TI89:
			ShowInformations(_T("^ = SHIFT       Diamond = CTRL     2nd = Alt  "), iLine++);
			ShowInformations(_T("alpha = CAPS    CATALOG = F6       APPS = F9  "), iLine++);  
			ShowInformations(_T("STO> = Tab      MODE = '           | = \\     "), iLine++);
			ShowInformations(_T("EE = Ins        CLEAR = Del                   "), iLine++);
			break;
		case CALC_TI83P:
			ShowInformations(_T("Y= = F1     Window = F2   Zoom = F3     Trace = F4    "), iLine++);
			ShowInformations(_T("Graph = F5  MODE = Esc    Alpha = CAPS  X,T,theta = ` "), iLine++);
			ShowInformations(_T("Stat = =    Math = F6     Matrx = F7    Prgm = F8     "), iLine++);
			ShowInformations(_T("Vars = F9   Clear = PgDn  X^-1 = End    SIN = Ins     "), iLine++);
			ShowInformations(_T("COS = Home  TAN = PgUp    ^ = NumLock   x^2 = ;       "), iLine++);
			ShowInformations(_T("log = '     ln = \\        STO = Tab                  "), iLine++);
			break;
	}
	ShowInformations(_T("Use the NumPad for numbers (think to enable it !)."), iLine++);
	iLine++;
	ShowInformations(_T("This mapping has been designed for a 'qwerty' keyboard."), iLine++);
	ShowInformations(_T("Win2k users can easily change their keyboard type with"), iLine++);
	ShowInformations(_T("the toolbar (bottom right)."), iLine++);
}

void CRemoteControl::OnSetFocus (CWnd* pWnd)
{
	//
	// Show the caret when the VisualKB window receives the input focus.
	//
    CreateSolidCaret (max (2, ::GetSystemMetrics (SM_CXBORDER)), m_cyChar);
    SetCaretPos (m_ptCaretPos);
    ShowCaret();
}

void CRemoteControl::OnKillFocus (CWnd* pWnd)
{
	//
	// Hide the caret when the VisualKB window loses the input focus.
	//
    HideCaret();
    m_ptCaretPos = GetCaretPos();
    ::DestroyCaret();
}

BOOL CRemoteControl::OnSetCursor (CWnd* pWnd, UINT nHitTest, UINT message)
{
	//
	// Change the cursor to an I-beam if it's currently over the text box,
	// or to an arrow if it's positioned anywhere else.
	//
    if (nHitTest == HTCLIENT) {
        DWORD dwPos = ::GetMessagePos();
        CPoint point (LOWORD (dwPos), HIWORD (dwPos));
        ScreenToClient (&point);
        ::SetCursor (m_rcTextBox.PtInRect (point) ?
            m_hCursorIBeam : m_hCursorArrow);
        return TRUE;
    }
    return CWnd::OnSetCursor (pWnd, nHitTest, message);
}

void CRemoteControl::OnLButtonDown (UINT nFlags, CPoint point)
{
	//
	// Move the caret if the text box is clicked with the left mouse button.
	//
    if (m_rcTextBox.PtInRect (point)) {
        m_nTextPos = GetNearestPos (point);
        PositionCaret();
    }
}

/* Key handlers */

void CRemoteControl::OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags)
{
	uiScanCode = nChar;
    ShowMessage (_T ("WM_KEYDOWN"), nChar, nRepCnt, nFlags);

	//
	// Move the caret when the left, right is pressed.
	//
    switch (nChar) {

	case VK_DELETE:
		OnChar(nChar, nRepCnt, nFlags);
        break;

    case VK_LEFT:
        if (m_nTextPos != 0) {
            m_nTextPos--;
            PositionCaret();
        }
        break;

    case VK_RIGHT:
        if (m_nTextPos != m_strInputText.GetLength()) {
            m_nTextPos++;
            PositionCaret();
        }
        break;
    }
}

void CRemoteControl::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags)
{
	uiChar = nChar;
    ShowMessage (_T ("WM_CHAR"), nChar, nRepCnt, nFlags);

    CClientDC dc (this);

	//
	// Determine which character was just input from the keyboard.
	//
    switch (nChar) {

	case VK_DELETE:
    case VK_RETURN:
        m_strInputText.Empty();
        m_nTextPos = 0;
        break;

    case VK_BACK:
        if (m_nTextPos != 0) {
            m_strInputText = m_strInputText.Left (m_nTextPos - 1) +
                m_strInputText.Right (m_strInputText.GetLength() -
                m_nTextPos);
            m_nTextPos--;
        }
        break;

    default:
        if ((nChar >= 0) && (nChar <= 31))
            return;

        if (m_nTextPos == m_strInputText.GetLength()) {
            m_strInputText += nChar;
            m_nTextPos++;
        }
        else
            m_strInputText.SetAt (m_nTextPos++, nChar);

        CSize size = dc.GetTextExtent (m_strInputText,
            m_strInputText.GetLength());

        if ((m_ptTextOrigin.x + size.cx) > m_nTextLimit) {
            m_strInputText = nChar;
            m_nTextPos = 1;
        }
        break;
    }

	//
	// Update the contents of the text box.
	//
    HideCaret();
    DrawInputText (&dc);
    PositionCaret (&dc);
    ShowCaret();
}

void CRemoteControl::OnKeyUp (UINT nChar, UINT nRepCnt, UINT nFlags)
{
    ShowMessage (_T ("WM_KEYUP"), nChar, nRepCnt, nFlags);
    //CWnd::OnKeyUp (nChar, nRepCnt, nFlags);

	// Process key for TI
	PreProcessKey(nChar, nFlags);
}

void CRemoteControl::OnSysKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags)
{
	uiScanCode = nChar;
	PreProcessKey(nChar, nFlags);
    ShowMessage (_T ("WM_SYSKEYDOWN"), nChar, nRepCnt, nFlags);
    //CWnd::OnSysKeyDown (nChar, nRepCnt, nFlags);
}

void CRemoteControl::OnSysChar (UINT nChar, UINT nRepCnt, UINT nFlags)
{
    ShowMessage (_T ("WM_SYSCHAR"), nChar, nRepCnt, nFlags);
    //CWnd::OnSysChar (nChar, nRepCnt, nFlags);
}

void CRemoteControl::OnSysKeyUp (UINT nChar, UINT nRepCnt, UINT nFlags)
{
    ShowMessage (_T ("WM_SYSKEYUP"), nChar, nRepCnt, nFlags);
    //CWnd::OnSysKeyUp (nChar, nRepCnt, nFlags);
}

void CRemoteControl::PositionCaret (CDC* pDC)
{
    BOOL bRelease = FALSE;

	//
	// Create a device context if pDC is NULL.
	//
    if (pDC == NULL) {
        pDC = GetDC();
        bRelease = TRUE;
    }

	//
	// Position the caret just right of the character whose 0-based
	// index is stored in m_nTextPos.
	//
    CPoint point = m_ptTextOrigin;
    CString string = m_strInputText.Left (m_nTextPos);
    point.x += (pDC->GetTextExtent (string, string.GetLength())).cx;
    SetCaretPos (point);

	//
	// Release the device context if it was created inside this function.
	//
    if (bRelease)
        ReleaseDC (pDC);
}

int CRemoteControl::GetNearestPos (CPoint point)
{
	//
	// Return 0 if (point.x, point.y) lies to the left of the text in
	// the text box.
	//
    if (point.x <= m_ptTextOrigin.x)
        return 0;

	//
	// Return the string length if (point.x, point.y) lies to the right
	// of the text in the text box.
	//
    CClientDC dc (this);
    int nLen = m_strInputText.GetLength();
    if (point.x >= (m_ptTextOrigin.x +
        (dc.GetTextExtent (m_strInputText, nLen)).cx))
        return nLen;

	//
	// Knowing that (point.x, point.y) lies somewhere within the text
	// in the text box, convert the coordinates into a character index.
	//
    int i = 0;
    int nPrevChar = m_ptTextOrigin.x;
    int nNextChar = m_ptTextOrigin.x;

    while (nNextChar < point.x) {
        i++;
        nPrevChar = nNextChar;      
        nNextChar = m_ptTextOrigin.x +
            (dc.GetTextExtent (m_strInputText.Left (i), i)).cx;
    }
    return ((point.x - nPrevChar) < (nNextChar - point.x)) ? i - 1: i;
}

void CRemoteControl::DrawInputText (CDC* pDC)
{
    pDC->ExtTextOut (m_ptTextOrigin.x, m_ptTextOrigin.y,
        ETO_OPAQUE, m_rcTextBox, m_strInputText, NULL);
}

void CRemoteControl::ShowMessage (LPCTSTR pszMessage, UINT nChar,
    UINT nRepCnt, UINT nFlags)
{
	return;
	//
	// Formulate a message string.
	//
    CString string;
    string.Format (_T ("%s"), pszMessage);

	//
	// Scroll the other message strings up and validate the scroll
	// rectangle to prevent OnPaint from being called.
	//
    ScrollWindow (0, -m_cyLine, &m_rcScroll);
    ValidateRect (m_rcScroll);

	//
	// Record the new message string and display it in the window.
	//
    CClientDC dc (this);
    dc.SetBkColor ((COLORREF) ::GetSysColor (COLOR_3DFACE));

    m_strMessages[m_nMsgPos] = string;
    dc.TabbedTextOut (m_ptLowerMsgOrigin.x, m_ptLowerMsgOrigin.y,
        m_strMessages[m_nMsgPos], m_strMessages[m_nMsgPos].GetLength(),
        sizeof (m_nTabStops), m_nTabStops, m_ptLowerMsgOrigin.x);

	//
	// Update the array index that specifies where the next message
	// string will be stored.
	//
    if (++m_nMsgPos == MAX_STRINGS)
        m_nMsgPos = 0;  
}

void CRemoteControl::DrawMessageHeader (CDC* pDC)
{
	static CString string;
    //static CString string =
    //    _T ("Message\tChar\tRep\tScan\tExt\tCon\tPrv\tTran");
	switch(options.lp.calc_type)
	{
		case CALC_TI83P: string = _T("TI83(+) specific keys:"); break;
		case CALC_TI89:  string = _T("TI89  specific keys:"); break;
		case CALC_TI92P: string = _T("TI92(+) specific keys:"); break;
		default: break;
	}

    pDC->SetBkColor ((COLORREF) ::GetSysColor (COLOR_3DFACE));
    pDC->TabbedTextOut (m_ptHeaderOrigin.x, m_ptHeaderOrigin.y,
        string, string.GetLength(), sizeof (m_nTabStops), m_nTabStops,
        m_ptHeaderOrigin.x);
}

void CRemoteControl::DrawMessages (CDC* pDC)
{
    int nPos = m_nMsgPos;
    pDC->SetBkColor ((COLORREF) ::GetSysColor (COLOR_3DFACE));

    for (int i=0; i<MAX_STRINGS; i++) {
        pDC->TabbedTextOut (m_ptUpperMsgOrigin.x,
            m_ptUpperMsgOrigin.y + (m_cyLine * i),
            m_strMessages[nPos], m_strMessages[nPos].GetLength(),
            sizeof (m_nTabStops), m_nTabStops, m_ptUpperMsgOrigin.x);

        if (++nPos == MAX_STRINGS)
            nPos = 0;    
    }
}

void CRemoteControl::ShowInformations (LPCTSTR pszMessage, UINT line)
{
	//
	// Record the new message string and display it in the window.
	//
    CClientDC dc (this);
    dc.SetBkColor ((COLORREF) ::GetSysColor (COLOR_3DFACE));

	
	CFont newFont;
	newFont.CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Fixedsys");
	CFont* pOldFont = dc.SelectObject (&newFont);

	dc.TextOut(m_ptUpperMsgOrigin.x, m_ptUpperMsgOrigin.y + (m_cyLine * line), pszMessage);
	dc.SelectObject (pOldFont);
}

/*********************************/
/* Key processing and conversion */
/*********************************/

void CRemoteControl::PreProcessKey (UINT nChar, UINT nFlags)
{
	CString szStr;
	int iRes;
	BOOL bRes;
	WCHAR wszBuf[6];
	BYTE keyState[256];   

	switch(options.lp.calc_type)
	{
	case CALC_TI83P:
		Send83pKey(uiScanCode, uiChar);
		break;
	case CALC_TI89:
		Send89Key(uiScanCode, uiChar);
		break;
	case CALC_TI92:
		Send92pKey(uiScanCode, uiChar);
		break;
	default:
		AfxMessageBox("This calculator does not support remote control.");
		break;
	}
}

void CRemoteControl::Send83pKey (UINT ScanCode, UINT Char)
{
	tilp_error(ti_calc.send_key(10));
}

void CRemoteControl::Send89Key (UINT ScanCode, UINT Char)
{
	uint16_t key = 0;
	uint16_t index = 0;
	static int flag = 0;
	int processed = 1;
	static int modifier = 0;

	// PC keyboard processing
	//ticable_DISPLAY_settings(DSP_ON);
	//DISPLAY("nChar = %i <%c> %i <%c>\n", ScanCode, ScanCode, Char, Char);

	switch(ScanCode)
	{
		// Remap some keys (TI specific)
		case VK_F1: index = KEY89_F1; break;
		case VK_F2: index = KEY89_F2; break;
		case VK_F3: index = KEY89_F3; break;
		case VK_F4: index = KEY89_F4; break;
		case VK_F5: index = KEY89_F5; break;
		case VK_F6: index = 278; break;	//KEY89_CATLG
		case VK_F9: index = KEY89_APPS; break;

		case VK_RETURN: index = KEY89_ENTER; break;
		case VK_TAB: index = KEY92P_STO; break;
		case VK_INSERT: index = 149; break;	//KEY89_EE
		case VK_DELETE: index = KEY92P_CLEAR; break;
		case VK_DECIMAL: index = KEY89_NEG; break; // NumPad dot

		case VK_UP: index = KEY89_UP; break;
		case VK_DOWN: index = KEY89_DOWN; break;
		case VK_LEFT: index = KEY89_LEFT; break;
		case VK_RIGHT: index = KEY89_RIGHT; break;

		case VK_NUMPAD0:index = '0'; break;
		case VK_NUMPAD1:index = '1'; break;
		case VK_NUMPAD2:index = '2'; break;
		case VK_NUMPAD3:index = '3'; break;
		case VK_NUMPAD4:index = '4'; break;
		case VK_NUMPAD5:index = '5'; break;
		case VK_NUMPAD6:index = '6'; break;
		case VK_NUMPAD7:index = '7'; break;
		case VK_NUMPAD8:index = '8'; break;
		case VK_NUMPAD9:index = '9'; break;

		// Get modifier keys
		case VK_CONTROL: flag = 1; modifier=1;
		break;
		case VK_SHIFT:	flag = 2; modifier=1;
		break;
		case VK_MENU:	flag = 3; modifier=1;
		break;
		case VK_CAPITAL: flag = 4; modifier=1;
		default: processed = 0; modifier = 0;
			break;
	}

	if(modifier && flag) return;

	// Unicode characters processing
	if(!processed)
	{
		switch(Char)
		{
			case L'\\': index = 124; break;	// KEY89_TUBE
//			case L'\'': index = KEY89_MODE; break;
			default: 
				if( (Char >= 32) && (Char < 256) )
					index = Char; 
				else
					return;
				break;
		}
	}

	// Get the final TI scancode
	if(!flag)
		//key = ticalc_89_keys(index).nothing;
		key = ticalc_89_keys(index).nothing;
	else
	{
		if(flag == 1)
			key = ticalc_89_keys(index).diamond;
		else if(flag == 2)
			key = ticalc_89_keys(index).shift;
		else if(flag == 3)
			key = ticalc_89_keys(index).second;
		else if(flag == 4)
			key = ticalc_89_keys(index).alpha;
		else
			AfxMessageBox("Remote Control: internal key error", MB_OK);
		flag = 0;
	}

	if(key) tilp_error(ti_calc.send_key(key));
}

void CRemoteControl::Send92pKey (UINT ScanCode, UINT Char)
{
	uint16_t key = 0;
	uint16_t index = 0;
	static int flag = 0;
	int processed = 1;
	static int modifier = 0;

	// PC keyboard processing
	switch(ScanCode)
	{
		// Remap some keys (TI specific)
		case VK_F1: index = KEY92P_F1; break;
		case VK_F2: index = KEY92P_F2; break;
		case VK_F3: index = KEY92P_F3; break;
		case VK_F4: index = KEY92P_F4; break;
		case VK_F5: index = KEY92P_F5; break;
		case VK_F6: index = KEY92P_F6; break;
		case VK_F7: index = KEY92P_F7; break;
		case VK_F8: index = KEY92P_F8; break;
		case VK_F9: index = KEY92P_APPS; break;

		case VK_RETURN: index = KEY92P_ENTER; break;
		case VK_TAB: index = KEY92P_STO; break;
		case VK_INSERT: index = KEY92P_SIN; break;
		case VK_HOME: index = KEY92P_COS;   break;
		case VK_PRIOR: index = KEY92P_TAN;  break;
		case VK_DELETE: index = KEY92P_CLEAR; break;
		case VK_DECIMAL: index = KEY92P_NEG; break; // NumPad dot

		case VK_UP: index = KEY92P_UP; break;
		case VK_DOWN: index = KEY92P_DOWN; break;
		case VK_LEFT: index = KEY92P_LEFT; break;
		case VK_RIGHT: index = KEY92P_RIGHT; break;

		case VK_NUMPAD0:index = '0'; break;
		case VK_NUMPAD1:index = '1'; break;
		case VK_NUMPAD2:index = '2'; break;
		case VK_NUMPAD3:index = '3'; break;
		case VK_NUMPAD4:index = '4'; break;
		case VK_NUMPAD5:index = '5'; break;
		case VK_NUMPAD6:index = '6'; break;
		case VK_NUMPAD7:index = '7'; break;
		case VK_NUMPAD8:index = '8'; break;
		case VK_NUMPAD9:index = '9'; break;

		// Get modifier keys
		case VK_CONTROL: flag = 1; modifier=1;
		break;
		case VK_SHIFT:	flag = 2; modifier=1;
		break;
		case VK_MENU:	flag = 3; modifier=1;
		break;
		default: processed = 0; modifier = 0; break;
	}

	if(modifier && flag) return;

	// Unicode characters processing
	if(!processed)
	{
		switch(Char)
		{
			case L'\\': index = KEY92P_LN; break;
			case L';':  index = KEY92P_THETA; break;
			case L'\'': index = KEY92P_MODE; break;
			default: 
				if( (Char >= 32) && (Char < 256) )
					index = Char; 
				else
					return;
				break;
		}
	}

	// Get the final TI scancode
	if(!flag)
		key = ticalc_92p_keys(index).nothing;
	else
	{
		if(flag == 1)
			key = ticalc_92p_keys(index).diamond;
		else if(flag == 2)
			key = ticalc_92p_keys(index).shift;
		else if(flag == 3)
			key = ticalc_92p_keys(index).second;
		else
			AfxMessageBox("Remote Control: internal key error", MB_OK);
		flag = 0;
	}

	if(key) tilp_error(ti_calc.send_key(key));
}