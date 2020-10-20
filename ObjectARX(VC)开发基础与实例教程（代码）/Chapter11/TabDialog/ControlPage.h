//-----------------------------------------------------------------------------
#ifndef ARX__CONTROLPAGE_H__20140205_174734
#define ARX__CONTROLPAGE_H__20140205_174734

//-----------------------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

//-----------------------------------------------------------------------------
class CControlPage : public CAcUiTabChildDialog {
	DECLARE_DYNAMIC (CControlPage)

public:
	CControlPage (CWnd *pParent =NULL, HINSTANCE hDialogResource =NULL) ;

	virtual void OnTabActivation (BOOL bActivate) ;
	virtual BOOL OnTabChanging () ;

public:
	//{{AFX_DATA(CControlPage)
	enum { IDD = IDD_CONTROL_PAGE };
	BOOL	m_bCheck1;
	int		m_nRadio1;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CControlPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CControlPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	bool SaveProfiles();
} ;

//////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif //----- ARX__CONTROLPAGE_H__20140205_174734
