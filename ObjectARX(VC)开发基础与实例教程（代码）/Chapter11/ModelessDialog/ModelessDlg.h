
#include "Resource.h"

//-----------------------------------------------------------------------------
#if !defined(ARX__MODELESSDLG_H__20050911_115004)
#define ARX__MODELESSDLG_H__20050911_115004


//-----------------------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//-----------------------------------------------------------------------------
class CModelessDlg : public CAcUiDialog {
	DECLARE_DYNAMIC (CModelessDlg)

public:
	CModelessDlg (CWnd* pParent =NULL, HINSTANCE hInstance =NULL) ;

	//{{AFX_DATA(CModelessDlg)
	enum { IDD = IDD_DIALOG_MODELESS };
	CString	m_strEnX;
	CString	m_strEnY;
	CString	m_strEnZ;
	CString	m_strStX;
	CString	m_strStY;
	CString	m_strStZ;
	CAcUiPickButton	m_btnPickEnd;
	CAcUiPickButton	m_btnPickStart;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CModelessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CModelessDlg)
	afx_msg LONG OnAcadKeepFocus(UINT, UINT);
	afx_msg void OnButtonClose();
	afx_msg void OnButtonLine();
	afx_msg void OnButtonPickEn();
	afx_msg void OnButtonPickSt();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
} ;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //----- !defined(ARX__MODELESSDLG_H__20050911_115004)
