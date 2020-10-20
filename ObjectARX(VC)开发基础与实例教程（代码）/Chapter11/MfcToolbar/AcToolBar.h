//-----------------------------------------------------------------------------
#ifndef _ACTOOLBAR_H_
#define _ACTOOLBAR_H_

//-----------------------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//-----------------------------------------------------------------------------
class CAcToolBar : public CToolBar 
{
	DECLARE_DYNAMIC (CAcToolBar)

	CWnd *mpOwner ;

public:
	CAcToolBar () ;

public:
	//{{AFX_VIRTUAL(CAcToolBar)
	//}}AFX_VIRTUAL

public:
	virtual ~CAcToolBar () ;
	BOOL Create (CWnd *pParentWnd, CWnd *pOwnerWnd =NULL,
		DWORD dwStyle =WS_CHILD | WS_VISIBLE | CBRS_SIZE_DYNAMIC | CBRS_FLYBY | CBRS_TOP | CBRS_TOOLTIPS | TBSTYLE_FLAT | TBSTYLE_TRANSPARENT,
		UINT nID =AFX_IDW_TOOLBAR
	) ;

protected:
	//{{AFX_MSG(CAcToolBar)
	//}}AFX_MSG
	afx_msg void OnUpdateToolBar (CCmdUI *pCmdUI) ; //----- See TN031

	DECLARE_MESSAGE_MAP ()
} ;

//-----------------------------------------------------------------------------
CAcToolBar *CreateToolBar (UINT nID, CWnd *pOwner, LPCSTR pszTitle =NULL) ;

#endif //----- _ACTOOLBAR_H_
 