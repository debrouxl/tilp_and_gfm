#if !defined(AFX_PRGMSPG11_H__8F839E05_09C4_4D0E_B39F_DE0BA0BBA88A__INCLUDED_)
#define AFX_PRGMSPG11_H__8F839E05_09C4_4D0E_B39F_DE0BA0BBA88A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrgmsPg11.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrgmsPg1 dialog

class CPrgmsPg1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPrgmsPg1)

// Construction
public:
	CPrgmsPg1();
	~CPrgmsPg1();

// Dialog Data
	//{{AFX_DATA(CPrgmsPg1)
	enum { IDD = IDD_SETUP_PROG1 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPrgmsPg1)
	public:
	virtual BOOL OnApply();
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPrgmsPg1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRGMSPG11_H__8F839E05_09C4_4D0E_B39F_DE0BA0BBA88A__INCLUDED_)
