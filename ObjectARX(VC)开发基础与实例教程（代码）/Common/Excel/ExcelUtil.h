#include "excel.h"
#include <vector>
// ExcelUtil.h: interface for the CExcelUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCELUTIL_H__EA0F9C4C_5901_43F0_ABA7_7FEDB6E681C0__INCLUDED_)
#define AFX_EXCELUTIL_H__EA0F9C4C_5901_43F0_ABA7_7FEDB6E681C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\UI\MfcGridCtrl\GridCtrl.h"
#include "..\ObjectARX\DwgTable\ZhifanDwgTable.h"

#if defined (_ZFGKCOMMONLIB_)
#define ZFGK_DLLIMPEXP __declspec(dllexport)
#else
#define ZFGK_DLLIMPEXP 
#endif

class ZFGK_DLLIMPEXP CExcelUtil  
{
public:
	CExcelUtil();
	virtual ~CExcelUtil();

	// 启动Excel程序
	// 建议在调用程序的InitApplication函数中初始化COM动态链接库：::CoInitialize(NULL);
	// 同时在UnloadApplication函数中关闭COM库的支持：::CoUninitialize();
	static bool RunExcelApp(_Application &excelApp, bool bVisible = true, bool bUserControl = true);

	// 新建一个workbook
	// templateFileName：模板文件位置（扩展名为xlt）
	static bool NewWorkBook(_Application excelApp, const TCHAR* templateFileName, _Workbook &excelBook);
	static void NewWorkBook(_Application excelApp, _Workbook &excelBook);

	// 打开excel文件，获得workbook
	static bool OpenWorkBook(_Application excelApp, const TCHAR* fileName, _Workbook &excelBook, bool bIsReadOnly = true);

	// 根据指定的_Workbook，获得所有WorkSheet的名称
	static void GetWorkSheets(_Workbook &excelBook, std::vector<CString> &vecSheetNames);
	static void GetWorkSheets(_Workbook excelBook, Worksheets &excelSheets);

	// 获得获得worksheet的数量
	static int GetWorkSheetCount(Worksheets excelSheets);

	// 获得指定sheet名称的workSheet
	static bool GetWorkSheet( Worksheets excelSheets, const TCHAR* szWorkSheetName, _Worksheet &excelSheet );	
	static bool GetWorkSheet( _Workbook excelBook, const TCHAR* szWorkSheetName, _Worksheet &excelSheet );

	// 获得指定位置的workSheet
	// i：从【1】开始
	static bool GetWorkSheet( Worksheets excelSheets, int i, _Worksheet &excelSheet);
	static bool GetWorkSheet( _Workbook excelBook, int i, _Worksheet &excelSheet);

	// 获得当前活动的workSheet
	static void GetActiveWorkSheet(_Workbook excelBook, _Worksheet &excelSheet);
	
	// 取得指定excelSheet的有效行列区域
	static void GetUsedRange(_Worksheet excelSheet, Range &excelRange);

	// 取得行数
	static long GetRowCount(Range excelRange);
	static long GetRowCount(_Worksheet excelSheet);

	// 行高
	static double GetRowHeight(_Worksheet sht, int row);
	static void SetRowHeight(_Worksheet sht, int row, double rowHeight);
	
	// 获得列数
	static long GetColumnCount(Range excelRange);
	static long GetColumnCount(_Worksheet excelSheet);

	// 列宽
	static double GetColumnWidth(_Worksheet sht, int col);
	static void SetColumnWidth(_Worksheet sht, int col, double width);

	// 取得指定行指定列的单元格内容
	// 行号、列号从【1】开始计数
	static bool GetCellValue(Range &excelRange, int rowIndex, int columnIndex, CString &strValue);
	static bool GetCellValue(_Worksheet excelSheet, int rowIndex, int columnIndex, CString &strValue);

	// 向excel单元格中写入内容
	static bool SetCellValue( Range &excelRange, int rowIndex, int columnIndex, const TCHAR* szValue );
	static bool SetCellValue( _Worksheet excelSheet, int rowIndex, int columnIndex, const TCHAR* szValue );
	static bool SetCellValue( _Worksheet excelSheet, int rowIndex, int columnIndex, const VARIANT &val );

	// 合并单元格
	static void MergeCells(Range &excelRange, int row, int col, int mergeRows, int mergeCols, bool bHorCenter = true);
	static void MergeCells(_Worksheet excelSheet, int row, int col, int mergeRows, int mergeCols, bool bHorCenter = true);

	// 设置单元格的字体
	static void SetCellFontInfo(_Worksheet sht, int row, int col, int size, bool bBold);

	// 设置边框
	static void SetFrame(Range &excelRange, bool bInnerFrame, bool bExteralFrame);

	// 设置水平对齐方式为居中
	static void SetHorizontalCenter(Range &excelRange);
	static void SetHorizontalCenter(_Worksheet sht, int row, int col);

	// 设置单元格的自动换行
	static void SetAutoWrap(Range &excelRange, bool bAutoWrap);

	// Excel列转换//////////////////////////////////////////////////////////////////////////
	// 字母转化成数字（只支持2个字母）
	static int GetColumnNumberIndex(const TCHAR * column);
	static CString GetColumnName(int col);

	// 将GridCtrl的内容导出为Excel
	static void GridToExcel(CGridCtrl &gridCtrl, const TCHAR* templateFile, const TCHAR* fileName, int startRowIndex = 1);
	static void GridToExcel(CGridCtrl &gridCtrl, const TCHAR* fileName, int startRowIndex = 1);

	// ZhifanDwgTable内容导出为Excel
	static void DwgTableToExcel(ZhifanDwgTable *pTable, int startRowIndex = 1);
};

#endif // !defined(AFX_EXCELUTIL_H__EA0F9C4C_5901_43F0_ABA7_7FEDB6E681C0__INCLUDED_)
