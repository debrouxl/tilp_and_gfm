// CustomStatusBar.h: interface for the CCustomStatusBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CustomStatusBar_H__4BA7D301_AA24_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_CustomStatusBar_H__4BA7D301_AA24_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCustomStatusBar : public CStatusBar  
{
public:
	void SetProgress (int nPercent);
	void SetImageStats(LPCTSTR pszStats);
	void CCustomStatusBar::UpdateInfo();
	CCustomStatusBar();
	virtual ~CCustomStatusBar();

protected:
	CProgressCtrl m_wndProgress;
	afx_msg int OnCreate (LPCREATESTRUCT lpcs);
	afx_msg void OnSize (UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP ()
};

#endif // !defined(AFX_CustomStatusBar_H__4BA7D301_AA24_11D2_8E53_006008A82731__INCLUDED_)
