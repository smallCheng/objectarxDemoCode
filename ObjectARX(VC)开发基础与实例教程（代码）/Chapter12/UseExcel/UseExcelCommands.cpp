//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Document\DwgDatabaseUtil.h"
#include <dbents.h>
#include "excel.h"
#include "..\..\Common\Others\ConvertUtil.h"
#include <comdef.h>
#include "..\..\Common\Entity\LineUtil.h"
#include "..\..\Common\Entity\circleutil.h"

// 启动Excel程序
// 建议在调用程序的InitApplication函数中初始化COM动态链接库：::CoInitialize(NULL);
// 同时在UnloadApplication函数中关闭COM库的支持：::CoUninitialize();
static bool RunExcelApp( _Application &excelApp, bool bVisible, bool bUserControl )
{
	// 启动Excel
	// 先检查是否已经启动
	CLSID clsId;
	::CLSIDFromProgID(L"Excel.Application", &clsId); // from registry
	IUnknown* pUnk = NULL;
	if (::GetActiveObject(clsId, NULL, &pUnk) == S_OK) 		
	{
		LPDISPATCH pDispatch;
		VERIFY(pUnk->QueryInterface(IID_IDispatch,(void**) &pDispatch) == S_OK);
		excelApp.AttachDispatch(pDispatch);
		pUnk->Release();
	} 
	else		
	{
		if(!excelApp.CreateDispatch(TEXT("Excel.Application")))
		{
			AfxMessageBox(TEXT("当前计算机没有安装Excel!"));
			return false;
		}
	}
	
	excelApp.SetVisible(bVisible);
	excelApp.SetUserControl(bUserControl);	// 是否允许其他用户控制Excel
	
	return true;
}

// 新建一个workbook
static void NewWorkBook( _Application excelApp, _Workbook &excelBook )
{
	// 获得Workbooks
	LPDISPATCH pDispatch = excelApp.GetWorkbooks();
	Workbooks excelBooks;
	excelBooks.AttachDispatch(pDispatch);
	
	// 获得当前活动的Workbook
	COleVariant vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	pDispatch = excelBooks.Add(vOptional);
	excelBook.AttachDispatch(pDispatch);
}

// 获得指定位置的workSheet
// i：从1开始
static bool GetWorkSheet( _Workbook excelBook, int i, _Worksheet &excelSheet)
{
	LPDISPATCH pDispatch = excelBook.GetWorksheets();
	Worksheets excelSheets;
	excelSheets.AttachDispatch(pDispatch);

	if (i > 0 && i <= excelSheets.GetCount())
	{
		LPDISPATCH pDispatch = excelSheets.GetItem(COleVariant(long(i)));
		excelSheet.AttachDispatch(pDispatch);

		return true;
	}
	else
	{
		return false;
	}
}

// 提示用户选择一个文件
// fileDesc:文件类型描述，例如“图片文件(*.jpg)”中的“图片文件”
// fileExtName:扩展名
static bool SelectFileToOpen(const TCHAR* filedesc, const TCHAR* fileExtName, CString &selectedFile)
{
	CString extensionNameHaveDot = TEXT(".");
	extensionNameHaveDot += fileExtName;
	
	// 弹出打开对话框
	CString filter;
	filter.Format(TEXT("%s(*.%s)|*.%s"), filedesc, fileExtName, fileExtName);
	filter += TEXT("|所有文件(*.*)|*.*||");
	
	// 	TRUE/FALSE打开或另存对话框   
	BOOL bOpenFile = TRUE;
	CFileDialog cFileDlg(bOpenFile, extensionNameHaveDot, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter);
	cFileDlg.m_ofn.lStructSize = 88;  // 打开Office风格的打开文件对话框
	
	// 取得全路径文件名
	if (cFileDlg.DoModal() == IDOK)
	{
		selectedFile = cFileDlg.GetPathName();		
		return true;
	}
	else
	{   
		return false;
	}
}

// 打开excel文件，获得workbook
static bool OpenWorkBook(_Application excelApp, const TCHAR* fileName, _Workbook &excelBook, bool bIsReadOnly = true)
{
	try
	{
		COleVariant vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);  //表示一个为optional的值
		COleVariant vIsReadOnly((short)bIsReadOnly);	// 只读		
		
		// 获得Workbooks
		LPDISPATCH pDispatch = excelApp.GetWorkbooks();
		Workbooks excelBooks;
		excelBooks.AttachDispatch(pDispatch);
		
		//打开Excel文件
		pDispatch = excelBooks.Open(fileName, vOptional, vIsReadOnly, vOptional, vOptional, 
			vOptional, vOptional, vOptional, vOptional, vOptional, vOptional, 
			vOptional, vOptional, vOptional, vOptional); 
		
		excelBook.AttachDispatch(pDispatch);
	}
	catch (_com_error e)
	{
		assert(false);
		AfxMessageBox(e.ErrorMessage());
		return false;
	}
	
	return true;
}

// 取得行数
static long GetRowCount(_Worksheet excelSheet)
{
	Range excelRange;
	excelRange.AttachDispatch(excelSheet.GetUsedRange());
	
	Range rowRange;
	rowRange.AttachDispatch(excelRange.GetRows());
	return rowRange.GetCount();
}

// This is command 'EXPORTTOEXCEL'
void ZffChap12ExportToExcel()
{
	// 1.获取直线、圆形集合
	AcDbObjectIdArray allEntIds = CDwgDatabaseUtil::GetAllEntityIds();
	AcDbObjectIdArray lineIds, circleIds;
	for (int i = 0; i < allEntIds.length(); i++)
	{
		AcDbEntity *pEnt = NULL;
		if (acdbOpenObject(pEnt, allEntIds[i], AcDb::kForRead) == Acad::eOk)
		{
			if (pEnt->isKindOf(AcDbLine::desc()))
			{
				lineIds.append(pEnt->objectId());
			}
			else if (pEnt->isKindOf(AcDbCircle::desc()))
			{
				circleIds.append(pEnt->objectId());
			}
			
			pEnt->close();
		}
	}

	// 2.启动Excel
	_Application excelApp;
	RunExcelApp(excelApp, true, true);

	// 3.新建一个WorkBook
	_Workbook excelBook;
	NewWorkBook(excelApp, excelBook);

	// 4.导出直线内容
	// 获得Sheet1
	_Worksheet excelSheet1;
	GetWorkSheet(excelBook, 1, excelSheet1);
	Range cells1;
	cells1.AttachDispatch(excelSheet1.GetCells());
	// 第一行的内容
	long row = 1, col = 1;
	cells1.SetItem(COleVariant(row), COleVariant(col++), COleVariant(TEXT("序号")));
	cells1.SetItem(COleVariant(row), COleVariant(col++), COleVariant(TEXT("起点X")));
	cells1.SetItem(COleVariant(row), COleVariant(col++), COleVariant(TEXT("起点Y")));
	cells1.SetItem(COleVariant(row), COleVariant(col++), COleVariant(TEXT("起点Z")));
	cells1.SetItem(COleVariant(row), COleVariant(col++), COleVariant(TEXT("终点X")));
	cells1.SetItem(COleVariant(row), COleVariant(col++), COleVariant(TEXT("终点Y")));
	cells1.SetItem(COleVariant(row), COleVariant(col++), COleVariant(TEXT("终点Z")));
	// 数据行的内容
	for (i = 0; i < lineIds.length(); i++)
	{
		AcDbLine *pLine = NULL;
		if (acdbOpenObject(pLine, lineIds[i], AcDb::kForRead) == Acad::eOk)
		{
			AcGePoint3d startPoint = pLine->startPoint();
			AcGePoint3d endPoint = pLine->endPoint();

			row = i + 2;
			col = 1;
			cells1.SetItem(COleVariant(row), COleVariant(col++), COleVariant(CConvertUtil::ToString(row - 1)));
			cells1.SetItem(COleVariant(row), COleVariant(col++), COleVariant(CConvertUtil::ToString(startPoint.x)));
			cells1.SetItem(COleVariant(row), COleVariant(col++), COleVariant(CConvertUtil::ToString(startPoint.y)));
			cells1.SetItem(COleVariant(row), COleVariant(col++), COleVariant(CConvertUtil::ToString(startPoint.z)));
			cells1.SetItem(COleVariant(row), COleVariant(col++), COleVariant(CConvertUtil::ToString(endPoint.x)));
			cells1.SetItem(COleVariant(row), COleVariant(col++), COleVariant(CConvertUtil::ToString(endPoint.y)));
			cells1.SetItem(COleVariant(row), COleVariant(col++), COleVariant(CConvertUtil::ToString(endPoint.z)));

			pLine->close();
		}
	}

	// 5.导出圆数据
	// 获得Sheet2
	_Worksheet excelSheet2;
	GetWorkSheet(excelBook, 2, excelSheet2);
	Range cells2;
	cells2.AttachDispatch(excelSheet2.GetCells());
	// 第一行的内容
	row = 1, col = 1;
	cells2.SetItem(COleVariant(row), COleVariant(col++), COleVariant(TEXT("序号")));
	cells2.SetItem(COleVariant(row), COleVariant(col++), COleVariant(TEXT("圆心X")));
	cells2.SetItem(COleVariant(row), COleVariant(col++), COleVariant(TEXT("圆心Y")));
	cells2.SetItem(COleVariant(row), COleVariant(col++), COleVariant(TEXT("圆心Z")));
	cells2.SetItem(COleVariant(row), COleVariant(col++), COleVariant(TEXT("半径")));
	// 数据行的内容
	for (i = 0; i < circleIds.length(); i++)
	{
		AcDbCircle *pCircle = NULL;
		if (acdbOpenObject(pCircle, circleIds[i], AcDb::kForRead) == Acad::eOk)
		{
			AcGePoint3d center = pCircle->center();
			double radius = pCircle->radius();
			
			row = i + 2;
			col = 1;
			cells2.SetItem(COleVariant(row), COleVariant(col++), COleVariant(CConvertUtil::ToString(row - 1)));
			cells2.SetItem(COleVariant(row), COleVariant(col++), COleVariant(CConvertUtil::ToString(center.x)));
			cells2.SetItem(COleVariant(row), COleVariant(col++), COleVariant(CConvertUtil::ToString(center.y)));
			cells2.SetItem(COleVariant(row), COleVariant(col++), COleVariant(CConvertUtil::ToString(center.z)));
			cells2.SetItem(COleVariant(row), COleVariant(col++), COleVariant(CConvertUtil::ToString(radius)));
			
			pCircle->close();
		}
	}
}

// 获得单元格的值
static bool GetCellValue( Range &excelRange, long rowIndex, long columnIndex, CString &strValue )
{
	assert(rowIndex > 0);
	assert(columnIndex > 0);
	
	COleVariant vValue;
	vValue = excelRange.GetItem(COleVariant(rowIndex), COleVariant(columnIndex));
	strValue = (LPCTSTR)_bstr_t(vValue);
	
	return true;
}

// 获得单元格的值
static bool GetCellValue( Range &excelRange, long rowIndex, long columnIndex, double &val )
{
	CString strValue;
	bool bRet = GetCellValue(excelRange, rowIndex, columnIndex, strValue);
	val = CConvertUtil::ToDouble(strValue);

	return bRet;
}

// This is command 'IMPORTFROMEXCEL'
void ZffCHAP12ImportFromExcel()
{
	// 1.提示用户选择Excel文件
	CString excelFileName;
	if (!SelectFileToOpen(TEXT("Excel文件"), TEXT("xls"), excelFileName))
	{
		return;
	}

	// 2.启动Excel
	_Application excelApp;
	RunExcelApp(excelApp, true, true);
	
	// 3.打开指定的文件
	_Workbook excelBook;
	OpenWorkBook(excelApp, excelFileName, excelBook);
	
	// 4.导入直线内容
	// 获得Sheet1
	_Worksheet excelSheet1;
	GetWorkSheet(excelBook, 1, excelSheet1);
	long rowCount = GetRowCount(excelSheet1);
	Range cells1;
	cells1.AttachDispatch(excelSheet1.GetCells());
	// 数据行的内容（从第二行开始）
	for (long row = 2; row <= rowCount; row++)
	{
		AcGePoint3d startPoint, endPoint;
		long col = 2;
		GetCellValue(cells1, row, col++, startPoint.x);
		GetCellValue(cells1, row, col++, startPoint.y);
		GetCellValue(cells1, row, col++, startPoint.z);
		GetCellValue(cells1, row, col++, endPoint.x);
		GetCellValue(cells1, row, col++, endPoint.y);
		GetCellValue(cells1, row, col++, endPoint.z);
		CLineUtil::Add(startPoint, endPoint);
	}
	
	// 5.导入圆数据
	// 获得Sheet2
	_Worksheet excelSheet2;
	GetWorkSheet(excelBook, 2, excelSheet2);
	rowCount = GetRowCount(excelSheet2);
	Range cells2;
	cells2.AttachDispatch(excelSheet2.GetCells());
	// 数据行的内容（从第二行开始）
	for (row = 2; row <= rowCount; row++)
	{
		AcGePoint3d center;
		double radius = 0;
		long col = 2;
		GetCellValue(cells2, row, col++, center.x);
		GetCellValue(cells2, row, col++, center.y);
		GetCellValue(cells2, row, col++, center.z);
		GetCellValue(cells2, row, col++, radius);
		CCircleUtil::Add(center, radius);
	}
}

