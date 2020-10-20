//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include <dbsymtb.h>
#include <gemat3d.h>
#include <math.h>
#include <dbents.h>
#include <geassign.h>
#include "..\..\Common\Document\DwgDatabaseUtil.h"

// This is command 'NEWUCS'
void ZffChap4NewUcs()
{
	// 获得当前图形的UCS表
	AcDbUCSTable *pUcsTbl = NULL;
	acdbHostApplicationServices()->workingDatabase()
		->getUCSTable(pUcsTbl, AcDb::kForWrite);
	
	// 定义UCS的参数
	AcGePoint3d ptOrigin(0, 0, 0);
	AcGeVector3d vecXAxis(1, 1, 0);
	AcGeVector3d vecYAxis(-1, 1, 0);
	
	// 创建新的UCS表记录
	AcDbUCSTableRecord *pUcsTblRcd = new AcDbUCSTableRecord();
	
	// 设置UCS的参数
	Acad::ErrorStatus es = pUcsTblRcd->setName(TEXT("NewUcs"));
	if (es != Acad::eOk)
	{
		delete pUcsTblRcd;
		pUcsTbl->close();
		return;
	}
	pUcsTblRcd->setOrigin(ptOrigin);
	pUcsTblRcd->setXAxis(vecXAxis);
	pUcsTblRcd->setYAxis(vecYAxis);
	
	// 将新建的UCS表记录添加到UCS表中
	es = pUcsTbl->add(pUcsTblRcd);
	if (es != Acad::eOk)
	{
		delete pUcsTblRcd;
		pUcsTbl->close();
		return;
	}
	
	// 关闭对象
	pUcsTblRcd->close();
	pUcsTbl->close();
}

// This is command 'SETCURUCS'
void ZffCHAP4SetCurUcs()
{
	// 提示用户输入UCS的名称
	TCHAR ucsName[40];
	if (acedGetString(NULL, TEXT("\n输入用户坐标系的名称:"), ucsName) != RTNORM)
		return;
	
	// 获得指定的UCS表记录
	AcDbUCSTable *pUcsTbl = NULL;
	acdbHostApplicationServices()->workingDatabase()
		->getUCSTable(pUcsTbl, AcDb::kForRead);
	if (!pUcsTbl->has(ucsName))
	{
		pUcsTbl->close();
		return;
	}
	AcDbUCSTableRecord *pUcsTblRcd;
	pUcsTbl->getAt(ucsName, pUcsTblRcd, AcDb::kForRead);
	
	// 获得UCS的变换矩阵
	AcGeMatrix3d mat;
	AcGeVector3d vecXAxis, vecYAxis, vecZAxis;
	vecXAxis = pUcsTblRcd->xAxis();
	vecYAxis = pUcsTblRcd->yAxis();
	vecZAxis = vecXAxis.crossProduct(vecYAxis);
	mat.setCoordSystem(pUcsTblRcd->origin(), vecXAxis, 
		vecYAxis, vecZAxis);
	
	// 关闭UCS表和UCS表记录
	pUcsTblRcd->close();
	pUcsTbl->close();
	
	// 设置当前的UCS
	acedSetCurrentUCS(mat);
}

// This is command 'MOVEUCSORIGIN'
void ZffCHAP4MoveUcsOrigin()
{
	// 获得当前UCS的变换矩阵
	AcGeMatrix3d mat;
	Acad::ErrorStatus es = acedGetCurrentUCS(mat);
	
	// 根据变换矩阵获得UCS的参数
	AcGePoint3d ptOrigin;
	AcGeVector3d vecXAxis, vecYAxis, vecZAxis;
	mat.getCoordSystem(ptOrigin, vecXAxis, vecYAxis, vecZAxis);
	
	// 移动UCS的原点
	AcGeVector3d vec(100, 100, 0);
	ptOrigin += vec;
	
	// 更新变换矩阵
	mat.setCoordSystem(ptOrigin, vecXAxis, vecYAxis, vecZAxis);
	
	// 应用新的UCS
	acedSetCurrentUCS(mat);
}

// This is command 'ROTATEUCS'
void ZffCHAP4RotateUcs()
{
	// 获得当前UCS的变换矩阵
	AcGeMatrix3d mat;
	Acad::ErrorStatus es = acedGetCurrentUCS(mat);
	
	// 根据变换矩阵获得UCS的参数
	AcGePoint3d ptOrigin;
	AcGeVector3d vecXAxis, vecYAxis, vecZAxis;
	mat.getCoordSystem(ptOrigin, vecXAxis, vecYAxis, vecZAxis);
	
	// 绕Z轴旋转60度
	vecXAxis.rotateBy(60 * atan(1) * 4 / 180, vecZAxis);
	vecYAxis.rotateBy(60 * atan(1) * 4 / 180, vecZAxis);
	
	// 更新变换矩阵
	mat.setCoordSystem(ptOrigin, vecXAxis, vecYAxis, vecZAxis);
	
	// 应用新的UCS
	acedSetCurrentUCS(mat);
}

// This is command 'ADDENTINUCS'
void ZffCHAP4AddEntInUcs()
{
	// 提示用户输入直线的起点和终点
	ads_point pt1, pt2;
	if (acedGetPoint(NULL, TEXT("\n拾取直线的起点:"), pt1) != RTNORM)
		return;	
	if (acedGetPoint(pt1, TEXT("拾取直线的终点:"), pt2) != RTNORM)
		return;

	// 按照UCS坐标创建实体
	AcDbLine *pLine = new AcDbLine(asPnt3d(pt1), asPnt3d(pt2));

	// 对实体进行几何变换
	AcGeMatrix3d mat;
	Acad::ErrorStatus es = acedGetCurrentUCS(mat);
	pLine->transformBy(mat);

	// 加入到模型空间
	CDwgDatabaseUtil::PostToModelSpace(pLine);
}

