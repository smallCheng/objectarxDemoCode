//-----------------------------------------------------------------------------
//----- ArxDialog.cpp : implementation file
#include "StdAfx.h"
#include "resource.h"
#include "ArxDialog.h"
#include <math.h>
#include "..\..\Common\Others\ConvertUtil.h"

//-----------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CArxDialog, CAcUiDialog)

BEGIN_MESSAGE_MAP(CArxDialog, CAcUiDialog)
	//{{AFX_MSG_MAP(CArxDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)    // Needed for modeless dialog.
	ON_BN_CLICKED(IDC_BUTTON_ANGLE, OnButtonAngle)
	ON_BN_CLICKED(IDC_BUTTON_POINT, OnButtonPoint)
	ON_WM_CLOSE()
	ON_EN_KILLFOCUS(IDC_EDIT_ANGLE, OnKillfocusEditAngle)
	ON_EN_KILLFOCUS(IDC_EDIT_XPT, OnKillfocusEditXpt)
	ON_EN_KILLFOCUS(IDC_EDIT_YPT, OnKillfocusEditYpt)
	ON_EN_KILLFOCUS(IDC_EDIT_ZPT, OnKillfocusEditZpt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CArxDialog::CArxDialog (CWnd* pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiDialog (CArxDialog::IDD, pParent, hInstance) {
	//{{AFX_DATA_INIT(CArxDialog)
	//}}AFX_DATA_INIT
}

void CArxDialog::DoDataExchange (CDataExchange *pDX) {
	CAcUiDialog::DoDataExchange (pDX) ;
	//{{AFX_DATA_MAP(CArxDialog)
	DDX_Control(pDX, IDC_BUTTON_ANGLE, m_btnAngle);
	DDX_Control(pDX, IDC_BUTTON_POINT, m_btnPick);
	DDX_Control(pDX, IDC_EDIT_ANGLE, m_editAngle);
	DDX_Control(pDX, IDC_EDIT_XPT, m_editXPt);
	DDX_Control(pDX, IDC_EDIT_YPT, m_editYPt);
	DDX_Control(pDX, IDC_EDIT_ZPT, m_editZPt);
	//}}AFX_DATA_MAP
}

// Needed for modeless dialogs to keep focus.
// Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT CArxDialog::OnAcadKeepFocus(WPARAM, LPARAM)
{
  return TRUE;
}

//-----------------------------------------------------------------------------

BOOL CArxDialog::OnInitDialog() 
{
	CAcUiDialog::OnInitDialog();
	
	// 设置输入点的范围
	m_editXPt.SetRange(-100.0, 100.0);
	m_editYPt.SetRange(-100.0, 100.0);
	m_editZPt.SetRange(-100.0, 100.0);

	// 设置角度的输入范围
	m_editAngle.SetRange(0.0, 90.0);

	// 加载默认的位图
	m_btnPick.AutoLoad();
	m_btnAngle.AutoLoad();
	
	// 设置文本框的默认值
	m_strAngle = "0.0";
	m_strXPt = "0.0";
	m_strYPt = "0.0";
	m_strZPt = "0.0";

	// 显示初始点的坐标和角度值
	DisplayPoint();
	DisplayAngle();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CArxDialog::OnButtonAngle() 
{
	// 隐藏对话框把控制权交给AutoCAD
    BeginEditorCommand();
	
    // 将当前选择的点的位置作为基点
    ads_point pt; 
    acdbDisToF(m_strXPt, -1, &pt[X]);
    acdbDisToF(m_strYPt, -1, &pt[Y]);
    acdbDisToF(m_strZPt, -1, &pt[Z]);    
	
    // 提示用户输入一点
	double angle;
	const double PI = 4 * atan(1.0);
    if (acedGetAngle(pt, TEXT("\n输入角度:"), &angle) == RTNORM) 
	{
        // 如果正确获得角度，返回对话框
        CompleteEditorCommand();
        // 将角度值转换为弧度值
        m_strAngle.Format(TEXT("%.2f"), angle * (180.0/PI));

		// 显示角度值
        DisplayAngle();
    } 
	else 
	{
        // 否则取消命令（包括对话框）
        CancelEditorCommand();
    }
}

void CArxDialog::OnButtonPoint() 
{
	// 隐藏对话框把控制权交给AutoCAD
	BeginEditorCommand();
	
	// 提示用户输入一个点
	ads_point pt;
	if (acedGetPoint(NULL, TEXT("\n输入一个点:"), pt) == RTNORM)
	{
		// 如果点有效，继续执行
		CompleteEditorCommand();
		m_strXPt.Format(TEXT("%.2f"), pt[X]);
		m_strYPt.Format(TEXT("%.2f"), pt[Y]);
		m_strZPt.Format(TEXT("%.2f"), pt[Z]);

		// 显示点的坐标
		DisplayPoint();
	}
	else
	{
		// 否则取消命令（包括对话框）
		CancelEditorCommand();
	}
}

void CArxDialog::DisplayPoint()
{
	// 在对话框中显示点的坐标
	m_editXPt.SetWindowText(m_strXPt);
	m_editXPt.Convert();	// 更新控件和其关联的成员变量
	m_editYPt.SetWindowText(m_strYPt);
	m_editYPt.Convert();
	m_editZPt.SetWindowText(m_strZPt);
	m_editZPt.Convert();
}


void CArxDialog::DisplayAngle()
{
	// 在对话框中显示角度值
	m_editAngle.SetWindowText(m_strAngle);
	m_editAngle.Convert();
}

void CArxDialog::OnClose() 
{
	// 在AutoCAD命令窗口输出选择点的结果
	double x = CConvertUtil::ToDouble(m_strXPt);
	double y = CConvertUtil::ToDouble(m_strYPt);
	double z = CConvertUtil::ToDouble(m_strZPt);
	acutPrintf(TEXT("\n选择的点坐标为(%.2f, %.2f, %.2f)."), x, y, z);
	
	CAcUiDialog::OnClose();
}

void CArxDialog::OnKillfocusEditAngle() 
{
	// 获得并更新用户输入的值
	m_editAngle.Convert();		
	m_editAngle.GetWindowText(m_strAngle);
}

void CArxDialog::OnKillfocusEditXpt() 
{
	// 获得并更新用户输入的值
	m_editXPt.Convert();		
	m_editXPt.GetWindowText(m_strXPt);
}

void CArxDialog::OnKillfocusEditYpt() 
{
	// 获得并更新用户输入的值
	m_editYPt.Convert();		
	m_editYPt.GetWindowText(m_strYPt);
}

void CArxDialog::OnKillfocusEditZpt() 
{
	// 获得并更新用户输入的值
	m_editZPt.Convert();		
	m_editZPt.GetWindowText(m_strZPt);	
}

