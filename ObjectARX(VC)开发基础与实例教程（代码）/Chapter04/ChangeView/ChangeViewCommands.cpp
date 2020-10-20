//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Others\ConvertUtil.h"
#include "..\..\Common\SymbolTable\ViewUtil.h"
#include <geassign.h>
#include "..\..\Common\Document\DwgDatabaseUtil.h"
#include <dbents.h>

// This is command 'ZOOMWINDOW'
void ZffChap4ZoomWindow()
{
	// 提示用户选择定义缩放窗口的两个角点
	ads_point pt1, pt2;
	if (acedGetPoint(NULL, TEXT("\n输入第一个角点:"), pt1) != RTNORM)
		return;
	if (acedGetCorner(pt1, TEXT("\n输入第二个角点:"), pt2) != RTNORM)
		return;

	// 将两个角点的坐标转换到世界坐标系
	AcGePoint3d pt1Wcs = CConvertUtil::UcsToWcsPoint(asPnt3d(pt1));
	AcGePoint3d pt2Wcs = CConvertUtil::UcsToWcsPoint(asPnt3d(pt2));
	
	CViewUtil::Set(pt1Wcs, pt2Wcs, 1.0);
}

// This is command 'ZOOMEXTENT'
void ZffCHAP4ZoomExtent()
{
	CViewUtil::ZoomExtent();
}

// This is command 'ZOOMENTITY'
void ZffCHAP4ZoomEntity()
{
	// 寻找图形中的圆形的包围框
	AcDbObjectIdArray allEntIds = CDwgDatabaseUtil::GetAllEntityIds();
	bool bFound = false;
	AcDbExtents ext;
	for (int i = 0; i < allEntIds.length(); i++)
	{
		AcDbCircle *pCircle = NULL;
		if (acdbOpenObject(pCircle, allEntIds[i], AcDb::kForRead) == Acad::eOk)
		{
			pCircle->getGeomExtents(ext);
			bFound = true;

			pCircle->close();
		}
	}

	// 将图形中的圆形显示在图形窗口的中心
	if (bFound)
	{
		CViewUtil::Set(ext.minPoint(), ext.maxPoint(), 5.0);
	}
}

