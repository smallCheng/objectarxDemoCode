#if !defined(AFX_MFCDIALOG_H__DD394A61_67E9_4724_B725_2F59E17566EC__INCLUDED_)
#define AFX_MFCDIALOG_H__DD394A61_67E9_4724_B725_2F59E17566EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MfcDialog.h : header file
//
#include "Resource.h"
/////////////////////////////////////////////////////////////////////////////
// CMfcDialog dialog

class CMfcDialog : public CDialog
{
// Construction
public:
	CMfcDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMfcDialog)
	enum { IDD = IDD_MFC_MODAL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMfcDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDIALOG_H__DD394A61_67E9_4724_B725_2F59E17566EC__INCLUDED_)
