//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "StdArx.h"
#include "resource.h"

#include "ArxMsgHandler.h"
//-----------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
CArxMsgHandler *pgArxMsgHandler =NULL ;

BOOL CreateArxMsgHandler () {
	if ( pgArxMsgHandler != NULL ) {
		if ( pgArxMsgHandler->GetSafeHwnd () != NULL )
			return (TRUE) ;
	} else {
		pgArxMsgHandler =new CArxMsgHandler ;
	}
	return (pgArxMsgHandler->Create (NULL, NULL, WS_CHILD | WS_MINIMIZE , CRect (0, 0, 1, 1), acedGetAcadFrame (), 10)) ;
}

void DestroyArxMsgHandler () {
	if ( pgArxMsgHandler == NULL )
		return ;
	if ( pgArxMsgHandler->GetSafeHwnd () != NULL )
		pgArxMsgHandler->DestroyWindow () ;
	delete pgArxMsgHandler ;
	pgArxMsgHandler =NULL ;
}

CArxMsgHandler *GetArxMsgHandler () {
	if ( pgArxMsgHandler != NULL && pgArxMsgHandler->GetSafeHwnd () != NULL )
		return (pgArxMsgHandler) ;
	return (NULL) ;
}

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CArxMsgHandler, CWnd)

BEGIN_MESSAGE_MAP(CArxMsgHandler, CWnd)
	//{{AFX_MSG_MAP(CArxMsgHandler)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_BUTTON_FIRST, OnButtonFirst)
	ON_COMMAND(ID_BUTTON_SECOND, OnButtonSecond)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CArxMsgHandler::CArxMsgHandler () {
}

CArxMsgHandler::~CArxMsgHandler () {
}
 

int CArxMsgHandler::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// 创建工具栏
	m_pToolbar = CreateToolBar(IDR_TOOLBAR, this, "工具栏");
	
	return 0;
}

void CArxMsgHandler::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// 销毁工具栏
	delete m_pToolbar;
	acedGetAcadFrame()->RecalcLayout();
}

void CArxMsgHandler::OnButtonFirst() 
{
	AfxMessageBox("按钮1");	
}

void CArxMsgHandler::OnButtonSecond() 
{
	AfxMessageBox("按钮2");
}
