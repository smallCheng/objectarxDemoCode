//-----------------------------------------------------------------------------
//----- GridDlg.cpp : implementation file
#include "StdAfx.h"
#include "GridDlg.h"
#include "..\..\Common\MfcGridCtrl\GridCtrlUtil.h"

//-----------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CGridDlg, CAcUiDialog)

BEGIN_MESSAGE_MAP(CGridDlg, CAcUiDialog)
	//{{AFX_MSG_MAP(CGridDlg)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)    // Needed for modeless dialog.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CGridDlg::CGridDlg (CWnd* pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiDialog (CGridDlg::IDD, pParent, hInstance) {
	//{{AFX_DATA_INIT(CGridDlg)
	//}}AFX_DATA_INIT
}

void CGridDlg::DoDataExchange (CDataExchange *pDX) {
	CAcUiDialog::DoDataExchange (pDX) ;
	//{{AFX_DATA_MAP(CGridDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_GRID, m_grid);
}

// Needed for modeless dialogs to keep focus.
// Return FALSE to not keep the focus, return TRUE to keep the focus
LONG CGridDlg::OnAcadKeepFocus(UINT, UINT)
{
  return TRUE;
}

//-----------------------------------------------------------------------------

void CGridDlg::UpdateOutColGrid()
{
	m_grid.SetRowCount(1);
	
	int row = 1, col = 0;
	std::vector<CString> colNames = GetAllColumnName();
	m_grid.SetRowCount(colNames.size() + 1);
	for (int i = 0; i < colNames.size(); i++)
	{
		m_grid.SetItemText(row + i, col, colNames[i]);
	}
	
	// 精度下拉框的内容
	std::vector<CString> precisionStrs;
	CString val = TEXT("0");
	int precisionCount = 9;
	for (i = 0; i < precisionCount; i++)
	{
		precisionStrs.push_back(val);
		if (i == 0)
		{
			val += TEXT(".");
		}
		val += TEXT("0");
	}
	
	// 文字对齐方式的选项值
	std::vector<CString> textAlignments;
	textAlignments.push_back(TEXT("左"));
	textAlignments.push_back(TEXT("中"));
	textAlignments.push_back(TEXT("右"));
	
	int defaultAligmentIndex = 2;
	// 设置单元格的内容和状态
	int colWidth = 80;
	for (i = 1; i < m_grid.GetRowCount(); i++)
	{
		// 第一列为不可编辑
		m_grid.SetItemState(i, 0, GVIS_READONLY);
		
		// 设置第二列为复选框
		int col = 1;
		bool cellCheck = true;
		CGridCtrlUtil::SetCellCheckType(cellCheck, m_grid, i, col);
		m_grid.SetItemData(i, col, 1);
		
		// 设置第三列为下拉框
		col = 2;		
		if (i != m_grid.GetRowCount() - 2)
		{
			m_grid.SetItemState(i, col, GVIS_READONLY);
		}
		else
		{
			CGridCtrlUtil::SetCellComboType(m_grid, i, col);
			CGridCtrlUtil::SetCellComboDwStyle(m_grid, i, col, CBS_DROPDOWNLIST);
			CGridCtrlUtil::SetCellComboOptions(m_grid, i, col, precisionStrs);
			m_grid.SetColumnWidth(col, colWidth);
			m_grid.SetItemText(i, col, TEXT("0.00"));
		}
		
		// 文字对齐方式列
		col = 3;
		CGridCtrlUtil::SetCellComboType(m_grid, i, col);
		CGridCtrlUtil::SetCellComboDwStyle(m_grid, i, col, CBS_DROPDOWNLIST);
		CGridCtrlUtil::SetCellComboOptions(m_grid, i, col, textAlignments);
		// 设置默认的对齐方式
		if (i == 1 || (i == m_grid.GetRowCount() - 1))	// 编号列、备注列为文字列，默认对齐方式为左对齐
		{
			defaultAligmentIndex = 0;		// 左对齐
		}
		else
		{
			defaultAligmentIndex = 1;		// 居中
		}
		m_grid.SetItemText(i, col, textAlignments[defaultAligmentIndex]);
	}
	
	m_grid.AutoSizeRows();
}

BOOL CGridDlg::OnInitDialog() 
{
	CAcUiDialog::OnInitDialog();
	
	// 输出列Grid初始化
	m_grid.SetRowCount(GetAllColumnName().size());
	m_grid.SetFixedRowCount(1);
	m_grid.SetColumnCount(4);	
	m_grid.SetItemText(0, 0, TEXT("列名"));
	m_grid.SetItemText(0, 1, TEXT("输出"));
	m_grid.SetItemText(0, 2, TEXT("精度"));
	m_grid.SetItemText(0, 3, TEXT("文字对齐"));
	m_grid.SetColumnWidth(0, 160);
	m_grid.SetColumnWidth(1, 50);
	m_grid.SetColumnWidth(2, 75);
	m_grid.SetColumnWidth(3, 75);
	
	UpdateOutColGrid();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGridDlg::OnOK() 
{
	if (!UpdateData())
	{
		return;
	}

	// 获取各个输出列的内容
	for (int i = 1; i < m_grid.GetRowCount(); i++)
	{
		if (CGridCtrlUtil::GetCellChecked(m_grid, i, 1) && m_grid.GetRowHeight(i) > 0)		// 是否输出
		{
			int index = i - 1;
			CString colName = m_grid.GetItemText(i, 0);	// 列名
			CString precisionStr = m_grid.GetItemText(i, 2);		// 显示精度
			CString strTextAlignment = m_grid.GetItemText(i, 3);		// 文字水平对齐方式
			int textAlignment = 0;
			if (strTextAlignment.CompareNoCase(TEXT("左")) == 0)
			{
				textAlignment = 0;
			}
			else if (strTextAlignment.CompareNoCase(TEXT("中")) == 0)
			{
				textAlignment = 1;
			}
			else	//strTextAlignment.CompareNoCase(TEXT("右")) == 0
			{
				textAlignment = 2;
			}
		}
	}
	
	CAcUiDialog::OnOK();
}

std::vector<CString> CGridDlg::GetAllColumnName()
{
	std::vector<CString> colNames;
	colNames.push_back(TEXT("序号"));
	colNames.push_back(TEXT("图例"));
	colNames.push_back(TEXT("设备及材料名称"));
	colNames.push_back(TEXT("规格及型号"));
	colNames.push_back(TEXT("单位"));
	colNames.push_back(TEXT("数量"));
	colNames.push_back(TEXT("备注"));
	return colNames;
}
