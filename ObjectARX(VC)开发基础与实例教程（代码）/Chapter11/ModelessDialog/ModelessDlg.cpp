//-----------------------------------------------------------------------------
//----- ModelessDlg.cpp : implementation file
#include "StdAfx.h"
#include "resource.h"
#include "ModelessDlg.h"
#include "dbents.h"
#include "..\..\Common\Entity\LineUtil.h"
#include "..\..\Common\Interaction\GetInputUtil.h"


extern CModelessDlg *pDialog;
//-----------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CModelessDlg, CAcUiDialog)

BEGIN_MESSAGE_MAP(CModelessDlg, CAcUiDialog)
	//{{AFX_MSG_MAP(CModelessDlg)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)    // Needed for modeless dialog.
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_LINE, OnButtonLine)
	ON_BN_CLICKED(IDC_BUTTON_PICK_EN, OnButtonPickEn)
	ON_BN_CLICKED(IDC_BUTTON_PICK_ST, OnButtonPickSt)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CModelessDlg::CModelessDlg (CWnd* pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiDialog (CModelessDlg::IDD, pParent, hInstance) {
	//{{AFX_DATA_INIT(CModelessDlg)
	m_strEnX = _T("0");
	m_strEnY = _T("0");
	m_strEnZ = _T("0");
	m_strStX = _T("100");
	m_strStY = _T("100");
	m_strStZ = _T("0");
	//}}AFX_DATA_INIT
}

void CModelessDlg::DoDataExchange (CDataExchange *pDX) {
	CAcUiDialog::DoDataExchange (pDX) ;
	//{{AFX_DATA_MAP(CModelessDlg)
	DDX_Text(pDX, IDC_EDIT_ENX, m_strEnX);
	DDX_Text(pDX, IDC_EDIT_ENY, m_strEnY);
	DDX_Text(pDX, IDC_EDIT_ENZ, m_strEnZ);
	DDX_Text(pDX, IDC_EDIT_STX, m_strStX);
	DDX_Text(pDX, IDC_EDIT_STY, m_strStY);
	DDX_Text(pDX, IDC_EDIT_STZ, m_strStZ);
	DDX_Control(pDX, IDC_BUTTON_PICK_EN, m_btnPickEnd);
	DDX_Control(pDX, IDC_BUTTON_PICK_ST, m_btnPickStart);
	//}}AFX_DATA_MAP
}

// Needed for modeless dialogs to keep focus.
// Return FALSE to not keep the focus, return TRUE to keep the focus
LONG CModelessDlg::OnAcadKeepFocus(UINT, UINT)
{
  return TRUE;
}

//-----------------------------------------------------------------------------

void CModelessDlg::OnButtonClose() 
{
	// 销毁对话框
	DestroyWindow();	
}

void CModelessDlg::OnButtonLine() 
{
	// 获得起点和终点的坐标
	AcGePoint3d ptStart(atof(m_strStX), atof(m_strStY), atof(m_strStZ));
	AcGePoint3d ptEnd(atof(m_strEnX), atof(m_strEnY), atof(m_strEnZ));

	// 锁定文档
	acDocManager->lockDocument(curDoc());
	
	CLineUtil::Add(ptStart, ptEnd);
	
	// 解锁文档
	acDocManager->unlockDocument(curDoc());
}

void CModelessDlg::OnButtonPickEn() 
{
	// 隐藏对话框把控制权交给AutoCAD
	BeginEditorCommand();
	
	// 提示用户输入一个点
	AcGePoint3d pt;
	if (CGetInputUtil::GetPoint(TEXT("\n输入一个点:"), pt))
	{
		// 如果点有效，继续执行
		CompleteEditorCommand();
		m_strEnX.Format("%.2f", pt.x);
		m_strEnY.Format("%.2f", pt.y);
		m_strEnZ.Format("%.2f", pt.z);		
	}
	else
	{
		// 否则取消命令（包括对话框）
		CancelEditorCommand();
	}	

	// 用成员变量的值更新文本框显示的内容
	UpdateData(FALSE);
}

void CModelessDlg::OnButtonPickSt() 
{
	// 隐藏对话框把控制权交给AutoCAD
	BeginEditorCommand();
	
	// 提示用户输入一个点
	AcGePoint3d pt;
	if (CGetInputUtil::GetPoint(TEXT("\n输入一个点:"), pt))
	{
		// 如果点有效，继续执行
		CompleteEditorCommand();
		m_strStX.Format("%.2f", pt.x);
		m_strStY.Format("%.2f", pt.y);
		m_strStZ.Format("%.2f", pt.z);
	}
	else
	{
		// 否则取消命令（包括对话框）
		CancelEditorCommand();
	}	
	
	// 用成员变量的值更新文本框显示的内容
	UpdateData(FALSE);	
}

void CModelessDlg::PostNcDestroy() 
{
	// 释放非模态对话框的内存
	delete this;
	
	if (pDialog != NULL)
	{
		pDialog = NULL;
	}	
	
	CAcUiDialog::PostNcDestroy();
}

void CModelessDlg::OnClose() 
{	
	CAcUiDialog::OnClose();

	// 销毁对话框
	DestroyWindow();	
}

BOOL CModelessDlg::OnInitDialog() 
{
	CAcUiDialog::OnInitDialog();
	
	// “拾取点”按钮位图的加载
	m_btnPickEnd.AutoLoad();
	m_btnPickStart.AutoLoad();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
