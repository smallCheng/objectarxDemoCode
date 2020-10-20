// GridCtrlUtility.h: interface for the CGridCtrlUtility class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCTRLUTIL_H__1DA720E2_B555_46F7_9B99_304A8B57B54F__INCLUDED_)
#define AFX_GRIDCTRLUTIL_H__1DA720E2_B555_46F7_9B99_304A8B57B54F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCtrl.h"
#include <vector>

class CGridCtrlUtil  
{
public:
	CGridCtrlUtil();
	virtual ~CGridCtrlUtil();

	//////////////////////////////////////////////////////////////////////////
	// 单元格设置为特殊类型
	//////////////////////////////////////////////////////////////////////////
	// 设置单元格为复选框样式
	static void SetCellCheckType( bool bIsCheck, CGridCtrl &gridCtrl, int rowIndex, int columnIndex);
	// 单元格是否是复选框
	static bool CellIsCheckType(CGridCtrl &grid, int row, int col);
	// 设置复选框单元格的选中状态
	static void SetCellChecked(CGridCtrl &grid, int rowIndex, int colIndex, bool bChecked);
	// 判断复选框的单元格是否被选中
	static bool GetCellChecked(CGridCtrl &gridCtrl, int rowIndex, int columnIndex);

	// 设置单元格为组合框类型
	static void SetCellComboType(CGridCtrl &gridCtrl, int row, int col);
	// 设置组合框的选项集合
	static void SetCellComboOptions(CGridCtrl &gridCtrl, int row, int col, const CStringArray &ar);
	static void SetCellComboOptions(CGridCtrl &gridCtrl, int row, int col, const std::vector<CString> &items);
	// 设置组合框的样式
	static void SetCellComboDwStyle(CGridCtrl &gridCtrl, int row, int col, DWORD dwStyle);

	// 设置组合框为按钮类型
	static void SetCellButtonType(CGridCtrl &gridCtrl, int row, int col);

	// 设置单元格为普通类型
	static void SetCellEditType(CGridCtrl &gridCtrl, int row, int col);
};

#endif // !defined(AFX_GRIDCTRLUTIL_H__1DA720E2_B555_46F7_9B99_304A8B57B54F__INCLUDED_)
