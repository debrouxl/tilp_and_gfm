#define MAX_STRINGS 12

/*
class CMyApp : public CWinApp
{
public:
    virtual BOOL InitInstance ();
};
*/

class CRemoteControl : public CWnd
{
protected:
    int m_cxChar;			// Average character width
    int m_cyChar;			// Character height
    int m_cyLine;			// Vertical line spacing in message box
    int m_nTextPos;			// Index of current character in text box
    int m_nTabStops[7];		// Tab stop locations for tabbed output
    int m_nTextLimit;		// Maximum width of text in text box
    int m_nMsgPos;			// Current position in m_strMessages array
    
    HCURSOR m_hCursorArrow;		// Handle of arrow cursor
    HCURSOR m_hCursorIBeam;		// Handle of I-beam cursor

    CPoint m_ptTextOrigin;      // Origin for drawing input text
    CPoint m_ptHeaderOrigin;    // Origin for drawing header text
    CPoint m_ptUpperMsgOrigin;	// Origin of first line in message box
    CPoint m_ptLowerMsgOrigin;	// Origin of last line in message box
    CPoint m_ptCaretPos;		// Current caret position

    CRect m_rcTextBox;			// Coordinates of text box
    CRect m_rcTextBoxBorder;	// Coordinates of text box border
    CRect m_rcMsgBoxBorder;		// Coordinates of message box border
    CRect m_rcScroll;			// Coordinates of scroll rectangle

    CString m_strInputText;             // Input text
    CString m_strMessages[MAX_STRINGS];	// Array of message strings

public:
    CRemoteControl ();

protected:
    int GetNearestPos (CPoint point);
    void PositionCaret (CDC* pDC = NULL);
    void DrawInputText (CDC* pDC);
    void ShowMessage (LPCTSTR pszMessage, UINT nChar, UINT nRepCnt,
        UINT nFlags);
    void DrawMessageHeader (CDC* pDC);
    void DrawMessages (CDC* pDC);

	void ShowInformations(LPCTSTR pszMessage, UINT line);
	void PreProcessKey (UINT nChar, UINT nFlags);
	void Send83pKey (UINT ScanCode, UINT Char);
	void Send89Key  (UINT ScanCode, UINT Char);
	void Send92pKey (UINT ScanCode, UINT Char);

protected:
    virtual void PostNcDestroy ();

    afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnPaint ();
    afx_msg void OnSetFocus (CWnd* pWnd);
    afx_msg void OnKillFocus (CWnd* pWnd);
    afx_msg BOOL OnSetCursor (CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnLButtonDown (UINT nFlags, CPoint point);
    afx_msg void OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyUp (UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSysKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSysKeyUp (UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnChar (UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSysChar (UINT nChar, UINT nRepCnt, UINT nFlags);

    DECLARE_MESSAGE_MAP ()
};
