#if !defined(AFX_PROBEIO_H__710CA202_24A7_11D6_BC64_004005E3BC2E__INCLUDED_)
#define AFX_PROBEIO_H__710CA202_24A7_11D6_BC64_004005E3BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProbeIO.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProbeIODlg dialog

class CProbeIODlg : public CDialog
{
// Construction
public:
	CProbeIODlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProbeIODlg)
	enum { IDD = IDD_PROBEIO };
	CEdit	m_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProbeIODlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont	m_textFont;

	// Generated message map functions
	//{{AFX_MSG(CProbeIODlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROBEIO_H__710CA202_24A7_11D6_BC64_004005E3BC2E__INCLUDED_)
