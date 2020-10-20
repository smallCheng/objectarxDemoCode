//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Document\DwgDatabaseUtil.h"
#include <dbents.h>
#include "..\..\Common\Entity\LineUtil.h"
#include "..\..\Common\Entity\circleutil.h"
#include "..\..\Common\IO\AppDirectoryUtil.h"

// This is command 'NEWDOCDRAWENTS'
void ZffChap7NewDocDrawEnts()
{
	// 1.当前图形中的计算
	// 必须锁定文档才能访问图形数据库的内容
	acDocManager->lockDocument(acDocManager->curDocument());

	// 找出图形中直线的数量
	AcDbObjectIdArray allEntIds = CDwgDatabaseUtil::GetAllEntityIds();
	int lineCount = 0;
	for (int i = 0; i < allEntIds.length(); i++)
	{
		AcDbLine *pLine = NULL;
		if (acdbOpenObject(pLine, allEntIds[i], AcDb::kForRead) == Acad::eOk)
		{
			lineCount++;
			pLine->close();
		}
	}

	// 解锁文档，返回应用程序范围
	acDocManager->unlockDocument(acDocManager->curDocument());

	// 2.创建一个新图形文档并作为当前文档
	Acad::ErrorStatus es = acDocManager->appContextNewDocument(NULL);

	// 3.在新的图形文档中绘图
	// 必须锁定文档才能访问图形数据库的内容
	acDocManager->lockDocument(acDocManager->curDocument());

	// 绘制与原来图形中相同数量的直线
	for (i = 0; i < lineCount; i++)
	{
		double y = i * 20;
		AcGePoint3d startPoint(0, y, 0);
		AcGePoint3d endPoint(100, y, 0);
		CLineUtil::Add(startPoint, endPoint);
	}

	// 解锁文档，返回应用程序范围
	acDocManager->unlockDocument(acDocManager->curDocument());
}

// This is command 'SAVEDWGOPENDOC'
void ZffChap7SaveDwgOpenDoc()
{
	// 1.当前图形中的计算
	// 必须锁定文档才能访问图形数据库的内容
	acDocManager->lockDocument(acDocManager->curDocument());
	
	// 找出图形中直线的数量
	AcDbObjectIdArray allEntIds = CDwgDatabaseUtil::GetAllEntityIds();
	int lineCount = 0, circleCount = 0;
	for (int i = 0; i < allEntIds.length(); i++)
	{
		AcDbEntity *pEnt = NULL;
		if (acdbOpenObject(pEnt, allEntIds[i], AcDb::kForRead) == Acad::eOk)
		{
			if (pEnt->isKindOf(AcDbLine::desc()))
			{
				lineCount++;
			}
			else if (pEnt->isKindOf(AcDbCircle::desc()))
			{
				circleCount++;
			}
			pEnt->close();
		}
	}

	// 创建两个新DWG文件
	AcDbDatabase *pDb1 = new AcDbDatabase(true, false);
	for (i = 0; i < lineCount; i++)
	{
		double y = i * 20;
		AcGePoint3d startPoint(0, y, 0);
		AcGePoint3d endPoint(100, y, 0);
		CLineUtil::Add(startPoint, endPoint, pDb1);
	}
	CString fileName1 = CAppDirectoryUtil::GetCurrentDirectory() + TEXT("\\db1.dwg");
	pDb1->saveAs(fileName1);
	delete pDb1;
	AcDbDatabase *pDb2 = new AcDbDatabase(true, false);
	for (i = 0; i < circleCount; i++)
	{
		double y = i * 20;
		AcGePoint3d center(0, y, 0);
		CCircleUtil::Add(center, 5, pDb2);
	}
	CString fileName2 = CAppDirectoryUtil::GetCurrentDirectory() + TEXT("\\db2.dwg");
	pDb2->saveAs(fileName2);
	delete pDb2;
	
	// 解锁文档，返回应用程序范围
	acDocManager->unlockDocument(acDocManager->curDocument());
	
	// 2.打开已经存在的DWG文件，并切换为当前文档
	Acad::ErrorStatus es = acDocManager->appContextOpenDocument(fileName1);
	es = acDocManager->appContextOpenDocument(fileName2);
}

