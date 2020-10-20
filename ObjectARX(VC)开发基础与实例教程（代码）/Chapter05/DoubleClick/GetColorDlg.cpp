//-----------------------------------------------------------------------------
//----- GetColorDlg.cpp : implementation file
#include "StdAfx.h"
#include "GetColorDlg.h"

//-----------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CGetColorDlg, CAcUiDialog)

BEGIN_MESSAGE_MAP(CGetColorDlg, CAcUiDialog)
	//{{AFX_MSG_MAP(CGetColorDlg)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)    // Needed for modeless dialog.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CGetColorDlg::CGetColorDlg (CWnd* pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiDialog (CGetColorDlg::IDD, pParent, hInstance) {
	//{{AFX_DATA_INIT(CGetColorDlg)
	m_colorIndex = 0;
	//}}AFX_DATA_INIT
}

void CGetColorDlg::DoDataExchange (CDataExchange *pDX) {
	CAcUiDialog::DoDataExchange (pDX) ;
	//{{AFX_DATA_MAP(CGetColorDlg)
	DDX_Text(pDX, IDC_COLOR_INDEX, m_colorIndex);
	DDV_MinMaxInt(pDX, m_colorIndex, 0, 256);
	//}}AFX_DATA_MAP
}

// Needed for modeless dialogs to keep focus.
// Return FALSE to not keep the focus, return TRUE to keep the focus
LONG CGetColorDlg::OnAcadKeepFocus(UINT, UINT)
{
  return TRUE;
}

//-----------------------------------------------------------------------------

BOOL CGetColorDlg::OnInitDialog() 
{
	CAcUiDialog::OnInitDialog();
	
	// 根据成员变量更新资源控件
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGetColorDlg::OnOK() 
{
	// 根据资源控件更新成员变量
	if (!UpdateData())
	{
		return;
	}
	
	CAcUiDialog::OnOK();
}

void CGetColorDlg::SetParams( int colorIndex )
{
	m_colorIndex = colorIndex;
}

void CGetColorDlg::GetParams( int &colorIndex )
{
	colorIndex = m_colorIndex;
}
