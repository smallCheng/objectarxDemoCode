//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "AcToolBar.h"
#include "rxmfcapi.h"

//-----------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
CAcToolBar *CreateToolBar (UINT nID, CWnd *pOwner, LPCSTR pszTitle) {
	CAcToolBar *p =new CAcToolBar ;
	p->Create (acedGetAcadFrame (), pOwner) ;
	AfxSetResourceHandle (::GetModuleHandle ("ZffMfcToolbar.arx")) ;
	p->LoadToolBar (nID) ;
	AfxSetResourceHandle (acedGetAcadResourceInstance ()) ;
	p->EnableDocking (CBRS_ALIGN_ANY) ;
	if ( pszTitle != NULL )
		p->SetWindowText (pszTitle) ;
	//----- Make the Toolbar floating
	acedGetAcadFrame ()->FloatControlBar (p, CPoint (100, 100), CBRS_ALIGN_TOP) ;
	acedGetAcadFrame ()->ShowControlBar (p, TRUE, TRUE) ;
	return (p) ;
}

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CAcToolBar, CToolBar)

BEGIN_MESSAGE_MAP (CAcToolBar, CToolBar)
	//{{AFX_MSG_MAP(CAcToolBar)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI_RANGE (0x0000, 0xffff, OnUpdateToolBar) //----- See TN031
END_MESSAGE_MAP ()

CAcToolBar::CAcToolBar () {
	mpOwner =NULL ;
}

CAcToolBar::~CAcToolBar () {
}

//-----------------------------------------------------------------------------
BOOL CAcToolBar::Create (CWnd *pParentWnd, CWnd *pOwnerWnd, DWORD dwStyle, UINT nID) {
	if ( CToolBar::Create (pParentWnd, dwStyle, nID) ) {
		mpOwner =(pOwnerWnd == NULL ? pParentWnd : pOwnerWnd) ;
		ASSERT ( mpOwner->GetSafeHwnd () != NULL ) ;
		ASSERT_KINDOF (CWnd, mpOwner) ;
		GetToolBarCtrl ().SetOwner (mpOwner) ;
		//----- Unfortunatelly CToolBar::Create() ignores TBSTYLE_FLAT | TBSTYLE_TRANSPARENT
		ModifyStyle (0, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT, 0) ;
		return (TRUE) ;
	}
	return (FALSE) ;
}

//-----------------------------------------------------------------------------
void CAcToolBar::OnUpdateToolBar (CCmdUI *pCmdUI) {
	pCmdUI->DoUpdate (mpOwner, FALSE) ;
}
 