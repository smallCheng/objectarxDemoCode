// GridCtrlUtility.cpp: implementation of the CGridCtrlUtility class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCtrlUtil.h"
#include <assert.h>
#include <algorithm>
#include <functional>
#include "CellTypes\GridCellCheck.h"
#include "CellTypes\GridCellCombo.h"
#include "CellTypes\GridCellButton.h"

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridCtrlUtil::CGridCtrlUtil()
{
}

CGridCtrlUtil::~CGridCtrlUtil()
{

}

// 设置单元格为复选框类型
void CGridCtrlUtil::SetCellCheckType( bool bIsCheck, CGridCtrl &gridCtrl, int rowIndex, 
										int columnIndex)
{
	gridCtrl.SetCellType(rowIndex, columnIndex, RUNTIME_CLASS(CGridCellCheck));
	CGridCellCheck* pCheckCell = (CGridCellCheck*)gridCtrl.GetCell(rowIndex, columnIndex);
	if (pCheckCell != NULL)
	{
		pCheckCell->SetCheck(bIsCheck);
	}
}

// 获得复选框单元格用户是否选中
bool CGridCtrlUtil::GetCellChecked(CGridCtrl &gridCtrl, int rowIndex, int columnIndex)
{
	if (gridCtrl.GetCell(rowIndex, columnIndex)->IsKindOf(RUNTIME_CLASS(CGridCellCheck)))
	{
		CGridCellCheck* pCheckCell = (CGridCellCheck*)gridCtrl.GetCell(rowIndex, columnIndex);
		if (pCheckCell != NULL)
		{
			return pCheckCell->GetCheck() == TRUE;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

// 获得复选框单元格的选中状态
void CGridCtrlUtil::SetCellChecked( CGridCtrl &grid, int rowIndex, int colIndex, bool bChecked )
{	
	if (grid.GetCell(rowIndex, colIndex)->IsKindOf(RUNTIME_CLASS(CGridCellCheck)))
	{
		((CGridCellCheck*)grid.GetCell(rowIndex, colIndex))->SetCheck(bChecked);
	}
}

// 设置单元格为组合框类型
void CGridCtrlUtil::SetCellComboType( CGridCtrl &gridCtrl, int row, int col )
{
	gridCtrl.SetCellType(row, col, RUNTIME_CLASS(CGridCellCombo));
}

// 设置组合框单元格的可选项
void CGridCtrlUtil::SetCellComboOptions( CGridCtrl &gridCtrl, int row, int col, const CStringArray &ar )
{
	CGridCellCombo *pCell = (CGridCellCombo*) gridCtrl.GetCell(row, col);
	pCell->SetOptions(ar);
}

// 设置组合框单元格的可选项
void CGridCtrlUtil::SetCellComboOptions( CGridCtrl &gridCtrl, int row, int col, const std::vector<CString> &items )
{
	CStringArray ar;
	for (int i = 0; i < items.size(); i++)
	{
		ar.Add(items[i]);
	}
	SetCellComboOptions(gridCtrl, row, col, ar);
}

// 设置组合框单元格的样式
void CGridCtrlUtil::SetCellComboDwStyle( CGridCtrl &gridCtrl, int row, int col, DWORD dwStyle )
{
	CGridCellCombo *pCell = (CGridCellCombo*) gridCtrl.GetCell(row, col);
	pCell->SetStyle(dwStyle);
}

// 设置单元格为普通的编辑框类型
void CGridCtrlUtil::SetCellEditType( CGridCtrl &gridCtrl, int row, int col )
{
	gridCtrl.SetCellType(row, col, RUNTIME_CLASS(CGridCell));
}

// 设置单元格为按钮类型
void CGridCtrlUtil::SetCellButtonType( CGridCtrl &gridCtrl, int row, int col )
{
	gridCtrl.SetCellType(row, col, RUNTIME_CLASS(CGridCellButton));
}

// 某个单元格是否是复选框类型
bool CGridCtrlUtil::CellIsCheckType( CGridCtrl &grid, int row, int col )
{
	return (grid.GetCell(row, col)->IsKindOf(RUNTIME_CLASS(CGridCellCheck)) == TRUE);
}
