#if !defined(AFX_PBARDLG_H__1EAB6DA1_0852_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_PBARDLG_H__1EAB6DA1_0852_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PbarDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPbarDlg dialog: parent classe for all PBar

class CPbarDlg : public CDialog
{
// Construction
public:
	CPbarDlg(CWnd* pParent = NULL, int iType = 0);   // standard constructor

	bool		bPbar1;
	bool		bPbar2;
	bool		bRate;
	bool		bLabel;

// Dialog Data
	//{{AFX_DATA(CPbarDlg)
	enum { IDD = IDD_PBAR1 };
	int		type;
	CProgressCtrl	m_pbar2;
	CProgressCtrl	m_pbar1;
	CEdit	m_label;
	CEdit	m_rate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPbarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPbarDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CPbar1Dlg dialog

class CPbar1Dlg : public CDialog
{
// Construction
public:
	CPbar1Dlg(CWnd* pParent = NULL);   // standard constructor
	void PassParameters(LPCSTR title, LPCSTR text);

// Dialog Data
	//{{AFX_DATA(CPbar1Dlg)
	enum { IDD = IDD_PBAR1 };
	CProgressCtrl	m_pbar2;
	CEdit	m_rate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPbar1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPbar1Dlg)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CPbar2Dlg dialog

class CPbar2Dlg : public CDialog
{
// Construction
public:
	CPbar2Dlg(CWnd* pParent = NULL);   // standard constructor
	void PassParameters(LPCSTR title, LPCSTR text);

// Dialog Data
	//{{AFX_DATA(CPbar2Dlg)
	enum { IDD = IDD_PBAR2 };
	CEdit	m_label;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPbar2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPbar2Dlg)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CPbar3Dlg dialog

class CPbar3Dlg : public CDialog
{
// Construction
public:
	CPbar3Dlg(CWnd* pParent = NULL);   // standard constructor
	void PassParameters(LPCSTR title, LPCSTR text);

// Dialog Data
	//{{AFX_DATA(CPbar3Dlg)
	enum { IDD = IDD_PBAR3 };
	CProgressCtrl	m_pbar2;
	CProgressCtrl	m_pbar1;
	CEdit	m_rate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPbar3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPbar3Dlg)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CPbar4Dlg dialog

class CPbar4Dlg : public CDialog
{
// Construction
public:
	CPbar4Dlg(CWnd* pParent = NULL);   // standard constructor
	void PassParameters(LPCSTR title, LPCSTR text);

// Dialog Data
	//{{AFX_DATA(CPbar4Dlg)
	enum { IDD = IDD_PBAR4 };
	CEdit	m_rate;
	CEdit	m_label;
	CProgressCtrl	m_pbar2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPbar4Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPbar4Dlg)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CPbar5Dlg dialog

class CPbar5Dlg : public CDialog
{
// Construction
public:
	CPbar5Dlg(CWnd* pParent = NULL);   // standard constructor
	void PassParameters(LPCSTR title, LPCSTR text);

// Dialog Data
	//{{AFX_DATA(CPbar5Dlg)
	enum { IDD = IDD_PBAR5 };
	CProgressCtrl	m_pbar2;
	CProgressCtrl	m_pbar1;
	CEdit	m_label;
	CEdit	m_rate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPbar5Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPbar5Dlg)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PBARDLG_H__1EAB6DA1_0852_11D6_BC64_004005E3BC2E__INCLUDED_)
/*
void mfc_create_pbar_type1(const char *title);
void mfc_create_pbar_type2(const char *title, char *text);
void mfc_create_pbar_type3(const char *title);
void mfc_create_pbar_type4(const char *title, char *text);
void mfc_create_pbar_type5(const char *title, char *text);
void mfc_destroy_pbar(void);
*/