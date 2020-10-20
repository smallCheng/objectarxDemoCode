//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include <dbsymtb.h>
#include <dbents.h>
#include "..\..\Common\Document\DwgDatabaseUtil.h"
#include "..\..\Common\SymbolTable\ViewUtil.h"

// 获得AutoCAD应用程序的全路径名称
bool GetAcadPath(CString &acadPath)
{		
	DWORD dwRet = ::GetModuleFileName(acedGetAcadWinApp()->m_hInstance, 
		acadPath.GetBuffer(_MAX_PATH) , _MAX_PATH);
	acadPath.ReleaseBuffer();
	
	if (dwRet == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// This is command 'CREATEDWG'
void ZffChap7CreateDwg()
{
	// 创建新的图形数据库，分配内存空间
    AcDbDatabase *pDb = new AcDbDatabase(true, false);
	
    AcDbBlockTable *pBlkTbl = NULL;
    pDb->getSymbolTable(pBlkTbl, AcDb::kForRead);
	
    AcDbBlockTableRecord *pBlkTblRcd = NULL;
    pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd,
        AcDb::kForWrite);
    pBlkTbl->close();
	
    // 创建两个圆
    AcDbCircle *pCir1 = new AcDbCircle(AcGePoint3d(1,1,1), AcGeVector3d(0,0,1), 1.0);
    pBlkTblRcd->appendAcDbEntity(pCir1);
    pCir1->close();    
	AcDbCircle *pCir2 = new AcDbCircle(AcGePoint3d(4,4,4), AcGeVector3d(0,0,1), 2.0);
	pBlkTblRcd->appendAcDbEntity(pCir2);
    pCir2->close();
    pBlkTblRcd->close();
	
	// 获得acad.exe的位置
    CString acadPath;	
    GetAcadPath(acadPath);

    // 去掉路径最后的"acad.exe"字符串，得到AutoCAD安装路径
    acadPath = acadPath.Left(acadPath.GetLength() - 8);
    CString filePath = acadPath + TEXT("test.dwg");

    // 使用saveAs成员函数时，必须指定包含dwg扩展名的文件名称 
    pDb->saveAs(filePath);

    delete pDb;		// pDb不是数据库的常驻对象，必须手工销毁
}

// This is command 'READDWG'
void ZffChap7ReadDwg()
{
	// 使用false作为构造函数的参数，创建一个空的图形数据库
    // 这样保证图形数据库仅仅包含读入的内容    
    AcDbDatabase *pDb = new AcDbDatabase(false);
	
    // AcDbDatabase::readDwgFile()函数可以自动添加dwg扩展名 
    CString acadPath;	
    GetAcadPath(acadPath);
    // 去掉路径最后的"acad.exe"字符串
    acadPath = acadPath.Left(acadPath.GetLength() - 8);
    CString filePath = acadPath + "test.dwg";
    pDb->readDwgFile(filePath, _SH_DENYWR);
	
	// 获得模型空间的所有实体
	AcDbObjectIdArray allEntIds = CDwgDatabaseUtil::GetAllEntityIds(NULL, pDb);
	for (int i = 0; i < allEntIds.length(); i++)
	{
		AcDbEntity *pEnt = NULL;
		if (acdbOpenObject(pEnt, allEntIds[i], AcDb::kForRead) == Acad::eOk)
		{
			acutPrintf(TEXT("\n类名称: %s"), (pEnt->isA())->name());
			pEnt->close();
		}
	}

	// 删除图形数据库
    delete pDb;
}

// This is command 'CREATEDWG2'
void ZffChap7CreateDwg2()
{
	// 创建新的图形数据库，分配内存空间
    AcDbDatabase *pDb = new AcDbDatabase(true, false);
	
    // 创建两个圆
    AcDbCircle *pCir1 = new AcDbCircle(AcGePoint3d(1,1,1), AcGeVector3d(0,0,1), 1.0);
	CDwgDatabaseUtil::PostToModelSpace(pCir1, pDb);   
	AcDbCircle *pCir2 = new AcDbCircle(AcGePoint3d(4,4,4), AcGeVector3d(0,0,1), 2.0);
	CDwgDatabaseUtil::PostToModelSpace(pCir2, pDb);

	// 调整DWG文件的视图
	CViewUtil::DwgZoomExtent(pDb);
	
	// 获得acad.exe的位置
    CString acadPath;	
    GetAcadPath(acadPath);
	
    // 去掉路径最后的"acad.exe"字符串，得到AutoCAD安装路径
    acadPath = acadPath.Left(acadPath.GetLength() - 8);
    CString filePath = acadPath + TEXT("test2.dwg");
	
    // 使用saveAs成员函数时，必须指定包含dwg扩展名的文件名称 
    pDb->saveAs(filePath);
	
    delete pDb;		// pDb不是数据库的常驻对象，必须手工销毁
}

