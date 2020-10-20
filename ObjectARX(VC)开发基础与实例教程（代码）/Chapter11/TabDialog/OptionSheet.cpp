//-----------------------------------------------------------------------------
//----- OptionSheet.cpp : implementation file
#include "StdAfx.h"
#include "resource.h"
#include "OptionSheet.h"

//-----------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (COptionSheet, CAcUiTabMainDialog)

BEGIN_MESSAGE_MAP(COptionSheet, CAcUiTabMainDialog)
	//{{AFX_MSG_MAP(COptionSheet)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)    // Needed for modeless dialog.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
COptionSheet::COptionSheet (CWnd* pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiTabMainDialog (COptionSheet::IDD, pParent, hInstance) {
	//{{AFX_DATA_INIT(COptionSheet)
	//}}AFX_DATA_INIT
}

void COptionSheet::DoDataExchange (CDataExchange *pDX) {
	CAcUiTabMainDialog::DoDataExchange (pDX) ;
	//{{AFX_DATA_MAP(COptionSheet)
	DDX_Control(pDX, IDC_TAB, m_tabCtrl);
	//}}AFX_DATA_MAP
}

// Needed for modeless dialogs to keep focus.
// Return FALSE to not keep the focus, return TRUE to keep the focus
LONG COptionSheet::OnAcadKeepFocus(UINT, UINT)
{
  return TRUE;
}

//-----------------------------------------------------------------------------

BOOL COptionSheet::OnInitDialog() 
{
	CAcUiTabMainDialog::OnInitDialog();
	
	// 添加选项卡
	SetAcadTabPointer(&m_tabCtrl);
	m_tabCtrl.AddTab(0, TEXT("文字"), CTextPage::IDD, &m_textPage);
	m_tabCtrl.AddTab(1, TEXT("控件"), CControlPage::IDD, &m_controlPage);
	m_tabCtrl.SetActiveTab(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionSheet::OnOK() 
{
	if (!m_textPage.SaveProfiles() || !m_controlPage.SaveProfiles())
	{
		return;
	}
	
	CAcUiTabMainDialog::OnOK();
}
