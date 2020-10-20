//-----------------------------------------------------------------------------
#if !defined(ARX__GRIDDLG_H__20140206_115329)
#define ARX__GRIDDLG_H__20140206_115329

//-----------------------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Common\MfcGridCtrl\GridCtrl.h"
#include "resource.h"

//-----------------------------------------------------------------------------
class CGridDlg : public CAcUiDialog 
{
	DECLARE_DYNAMIC (CGridDlg)

public:
	CGridDlg (CWnd* pParent =NULL, HINSTANCE hInstance =NULL) ;

	//{{AFX_DATA(CGridDlg)
	enum { IDD = IDD_GRID } ;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CGridDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CGridDlg)
	afx_msg LONG OnAcadKeepFocus(UINT, UINT);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	// 获得所有列的标题
	static std::vector<CString> GetAllColumnName();

	// 填充输出列表格
	void UpdateOutColGrid();

private:
	CGridCtrl m_grid;
} ;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //----- !defined(ARX__GRIDDLG_H__20140206_115329)
