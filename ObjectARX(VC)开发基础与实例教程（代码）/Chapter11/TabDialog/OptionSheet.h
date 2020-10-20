//-----------------------------------------------------------------------------
#if !defined(ARX__OPTIONSHEET_H__20140205_173451)
#define ARX__OPTIONSHEET_H__20140205_173451

//-----------------------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "TextPage.h"
#include "ControlPage.h"

//-----------------------------------------------------------------------------
class COptionSheet : public CAcUiTabMainDialog {
	DECLARE_DYNAMIC (COptionSheet)

public:
	COptionSheet (CWnd* pParent =NULL, HINSTANCE hInstance =NULL) ;

	//{{AFX_DATA(COptionSheet)
	enum { IDD = IDD_OPTION_SHEET };
	CAcUiTab	m_tabCtrl;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(COptionSheet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(COptionSheet)
	afx_msg LONG OnAcadKeepFocus(UINT, UINT);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	CTextPage m_textPage;
	CControlPage m_controlPage;
} ;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //----- !defined(ARX__OPTIONSHEET_H__20140205_173451)
