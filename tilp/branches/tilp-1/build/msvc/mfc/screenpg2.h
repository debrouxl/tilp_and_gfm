#if !defined(AFX_SCREENPG2_H__A7929B42_CED4_11D6_9A65_006008205341__INCLUDED_)
#define AFX_SCREENPG2_H__A7929B42_CED4_11D6_9A65_006008205341__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScreenPg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScreenPg2 dialog

class CScreenPg2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CScreenPg2)

// Construction
public:
	CScreenPg2();
	~CScreenPg2();

// Dialog Data
	//{{AFX_DATA(CScreenPg2)
	enum { IDD = IDD_SETUP_SCREEN2 };
	CButton m_full_screen;
	CButton m_clipped_screen;
	CButton	m_grayscale;
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CScreenPg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CScreenPg2)
	virtual void OnOK();
	virtual BOOL OnApply();
	virtual BOOL OnInitDialog();
	afx_msg void OnClippedScreen();
	afx_msg void OnFullScreen();
	afx_msg void OnBlurry();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREENPG2_H__A7929B42_CED4_11D6_9A65_006008205341__INCLUDED_)
