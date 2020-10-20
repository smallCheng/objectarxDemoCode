//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "MyDockControlBar.h"

//-----------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(CMyDockControlBar, CAcUiDockControlBar)

BEGIN_MESSAGE_MAP(CMyDockControlBar, CAcUiDockControlBar)
	//{{AFX_MSG_MAP(CMyDockControlBar)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
// CMyDockControlBar *pInstance =new CMyDockControlBar ;
// pInstance->Create (acedGetAcadFrame (), "My title bar") ;
// pInstance->EnableDocking (CBRS_ALIGN_ANY) ;
// pInstance->RestoreControlBar () ;

static CLSID clsCMyDockControlBar ={ 0x0950553f, 0x696c, 0x4f37, { 0xb3, 0xfa, 0x0d, 0xd2, 0xcc, 0x58, 0x02, 0x25 } } ;

//-----------------------------------------------------------------------------
CMyDockControlBar::CMyDockControlBar() : CAcUiDockControlBar () {
	//{{AFX_DATA_INIT(CMyDockControlBar)
	m_childDlg = NULL;
	//}}AFX_DATA_INIT
}

BOOL CMyDockControlBar::Create(CWnd*pParent, LPCSTR lpszTitle) {
	CString strWndClass ;
	strWndClass =AfxRegisterWndClass (CS_DBLCLKS, LoadCursor (NULL, IDC_ARROW)) ;
	CRect rect (0, 0, 250, 200) ;
	if ( !CAcUiDockControlBar::Create (
			strWndClass,
			lpszTitle,
			WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN,
			rect,
			pParent, 0
		)
	)
		return (FALSE) ;

	SetToolID (&clsCMyDockControlBar) ;

	//----- TODO: Add your code here
	
	return (TRUE) ;
}

int CMyDockControlBar::OnCreate (LPCREATESTRUCT lpCreateStruct)
{
	if ( CAcUiDockControlBar::OnCreate (lpCreateStruct) == -1 )
		return (-1) ;

	// 显示子窗体
	CAcModuleResourceOverride resourceOverride;
	m_childDlg = new CChildDlg();
	m_childDlg->Create(IDD_DIALOG, this);
	//m_childDlg->ShowWindow(SW_SHOW);
	m_childDlg->MoveWindow(0, 0, 160, 160, TRUE);

	return (0) ;
}

void CMyDockControlBar::SizeChanged (CRect *lpRect, BOOL bFloating, int flags) {
	// 
	CAcModuleResourceOverride resourceOverride;
	if (m_childDlg != NULL)
	{
		m_childDlg->SetWindowPos(this, lpRect->left, lpRect->top, lpRect->Width(), lpRect->Height(), SWP_NOZORDER);
	}
}

void CMyDockControlBar::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// 可以去掉系统的右键菜单
	CAcUiDockControlBar::OnContextMenu(pWnd, point);
}
