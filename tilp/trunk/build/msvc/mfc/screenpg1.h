#if !defined(AFX_SCREENPG1_H__A7929B41_CED4_11D6_9A65_006008205341__INCLUDED_)
#define AFX_SCREENPG1_H__A7929B41_CED4_11D6_9A65_006008205341__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScreenPg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScreenPg1 dialog

class CScreenPg1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CScreenPg1)

// Construction
public:
	CScreenPg1();
	~CScreenPg1();

// Dialog Data
	//{{AFX_DATA(CScreenPg1)
	enum { IDD = IDD_SETUP_SCREEN1 };
	CButton	m_xpm;
	CButton	m_bmp;
	CButton	m_pcx;
	CButton	m_jpg;
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CScreenPg1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CScreenPg1)
	virtual void OnOK();
	virtual BOOL OnApply();
	afx_msg void OnPcx();
	afx_msg void OnXpm();
	afx_msg void OnJpg();
	afx_msg void OnBmp();
	virtual BOOL OnInitDialog();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREENPG1_H__A7929B41_CED4_11D6_9A65_006008205341__INCLUDED_)
