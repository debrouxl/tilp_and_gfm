#if !defined(AFX_FILEPROPERTIES_H__26F30644_7DDA_4885_A835_2C376FB52810__INCLUDED_)
#define AFX_FILEPROPERTIES_H__26F30644_7DDA_4885_A835_2C376FB52810__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileProperties.h : header file
//

#include "../src/tilp_core.h"

/////////////////////////////////////////////////////////////////////////////
// CFileProperties dialog

class CFileProperties : public CDialog
{
// Construction
public:
	CFileProperties(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileProperties)
	enum { IDD = IDD_VIEW_TIFILE };
	CEdit	m_var_path;
	CEdit	m_comment;
	CEdit	m_var_atrb;
	CEdit	m_var_size;
	CEdit	m_var_type;
	CEdit	m_var_name;
	CEdit	m_file_nvars;
	CEdit	m_file_dsize;
	CEdit	m_file_size;
	CEdit	m_file_type;
	CEdit	m_file_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
#ifdef HAVE_LIBTIFFEP
	TiffepFileInfo *fi;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFileProperties)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEPROPERTIES_H__26F30644_7DDA_4885_A835_2C376FB52810__INCLUDED_)
