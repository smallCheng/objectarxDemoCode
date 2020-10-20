//-----------------------------------------------------------------------------
#ifndef ARX__TEXTPAGE_H__20140205_174120
#define ARX__TEXTPAGE_H__20140205_174120

//-----------------------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

//-----------------------------------------------------------------------------
class CTextPage : public CAcUiTabChildDialog {
	DECLARE_DYNAMIC (CTextPage)

public:
	CTextPage (CWnd *pParent =NULL, HINSTANCE hDialogResource =NULL) ;

	virtual void OnTabActivation (BOOL bActivate) ;
	virtual BOOL OnTabChanging () ;

public:
	//{{AFX_DATA(CTextPage)
	enum { IDD = IDD_TEXT_PAGE };
	CComboBox	m_cboTextStyle;
	double	m_textHeight;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTextPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CTextPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	bool SaveProfiles();
} ;

//////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif //----- ARX__TEXTPAGE_H__20140205_174120
