//-----------------------------------------------------------------------------
#if !defined(ARX__CHILDDLG_H__20081001_112508)
#define ARX__CHILDDLG_H__20081001_112508

//-----------------------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//-----------------------------------------------------------------------------
class CChildDlg : public CAcUiDialog 
{
	DECLARE_DYNAMIC (CChildDlg)

public:
	CChildDlg (CWnd* pParent =NULL, HINSTANCE hInstance =NULL) ;

	//{{AFX_DATA(CChildDlg)
	enum { IDD = IDD_DIALOG } ;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CChildDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CChildDlg)
	afx_msg LONG OnAcadKeepFocus(UINT, UINT);
	afx_msg void OnLine();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
} ;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //----- !defined(ARX__CHILDDLG_H__20081001_112508)
