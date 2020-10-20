//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Document\DwgDatabaseUtil.h"
#include <dbsol3d.h>
#include <gemat3d.h>
#include <math.h>
#include <dbents.h>
#include "..\..\Common\Entity\RegionUtil.h"
#include <dbregion.h>

// This is command 'ADDBOX'
void ZffChap10AddBox()
{
	AcDb3dSolid *pSolid = new AcDb3dSolid();
	Acad::ErrorStatus es = pSolid->createBox(40, 50, 30);
	if (es != Acad::eOk)
	{
		acedAlert("创建长方体失败!");
		delete pSolid;
		return;
	}
	
	// 使用几何变换矩阵移动长方体
	AcGeMatrix3d xform;
	AcGeVector3d vec(100, 100, 100);
	xform.setToTranslation(vec);
	es = pSolid->transformBy(xform);
	
	// 将长方体添加到模型空间
	CDwgDatabaseUtil::PostToModelSpace(pSolid);
}

// This is command 'ADDCYLINDER'
void ZffChap10AddCylinder()
{
	// 创建特定参数的圆柱体（实际上是一个圆锥体）
	AcDb3dSolid *pSolid = new AcDb3dSolid();
	pSolid->createFrustum(30, 10, 10, 0);
	
	// 将圆锥体添加到模型空间
	CDwgDatabaseUtil::PostToModelSpace(pSolid);
}

// This is command 'ADDSPIRE'
void ZffChap10AddSpire()
{
	// 指定创建螺旋线的参数
	double radius, deltaVertical;	// 半径和每一周在垂直方向的增量
	double number, segment;			// 螺旋线的旋转圈数和组成一圈的分段数
	
	radius = 30, deltaVertical = 12;
	number = 5, segment = 30;
	
	// 计算点的个数和角度间隔
	int n = number * segment;	// 点的个数实际上是n+1
	double angle = 8 * atan(1) / segment;	// 两点之间的旋转角度
	
	// 计算控制点的坐标
	AcGePoint3dArray points;	// 控制点坐标数组
	for (int i = 0; i < n+1; i++)
	{
		AcGePoint3d vertex;
		vertex[X] = radius * cos(8 * i * atan(1) / segment);
		vertex[Y] = radius * sin(8 * i * atan(1) / segment);
		vertex[Z] = i * deltaVertical / segment;
		points.append(vertex);
	}
	
	// 创建螺旋线路径
	AcDb3dPolyline *p3dPoly = new AcDb3dPolyline(AcDb::k3dSimplePoly, points);
	
	// 将路径添加到模型空间
	AcDbObjectId spireId = CDwgDatabaseUtil::PostToModelSpace(p3dPoly);
	
	// 创建一个圆作为拉伸的截面
	AcGeVector3d vec(0, 1, 0);			// 圆所在平面的法矢量
	AcGePoint3d ptCenter(30, 0, 0);		// 圆心位置与半径的大小有关
	AcDbCircle *pCircle = new AcDbCircle(ptCenter, vec, 3);
	AcDbObjectId circleId = CDwgDatabaseUtil::PostToModelSpace(pCircle);
	
	// 根据圆创建一个面域
	AcDbObjectIdArray boundaryIds, regionIds;
	boundaryIds.append(circleId);
	regionIds = CRegionUtil::Add(boundaryIds);
	
	// 打开拉伸截面和拉伸路径
	AcDbRegion *pRegion = NULL;
	if (acdbOpenObject(pRegion, regionIds.at(0), AcDb::kForRead) == Acad::eOk)
	{
		AcDb3dPolyline *pPoly = NULL;
		if (acdbOpenObject(pPoly, spireId, AcDb::kForRead) == Acad::eOk)
		{
			// 进行拉伸操作
			AcDb3dSolid *pSolid = new AcDb3dSolid();
			pSolid->extrudeAlongPath(pRegion, pPoly);
			CDwgDatabaseUtil::PostToModelSpace(pSolid);
			
			pPoly->close();
		}
		
		pRegion->close();
	}
}

// This is command 'REVOLVEENT'
void ZffChap10RevolveEnt()
{
	// 设置顶点的坐标
	AcGePoint3d vertex[5];
	vertex[0] = AcGePoint3d(15, 0, 0);
	vertex[1] = AcGePoint3d(45, 0, 0);
	vertex[2] = AcGePoint3d(35, 9, 0);
	vertex[3] = AcGePoint3d(41, 18, 0);
	vertex[4] = AcGePoint3d(15, 18, 0);
	AcGePoint3dArray points;
	for (int i = 0; i <= 4; i++)
	{
		points.append(vertex[i]);
	}
	
	// 创建作为旋转截面的多段线
	AcDb3dPolyline *p3dPoly = new AcDb3dPolyline(AcDb::k3dSimplePoly, 
		points, true);
	AcDbObjectId polyId = CDwgDatabaseUtil::PostToModelSpace(p3dPoly);
	
	// 将闭合的多段线转化成面域
	AcDbObjectIdArray boundaryIds, regionIds;
	boundaryIds.append(polyId);
	regionIds = CRegionUtil::Add(boundaryIds);
	
	// 进行旋转操作
	AcDbRegion *pRegion = NULL;
	if (acdbOpenObject(pRegion, regionIds.at(0), AcDb::kForRead) == Acad::eOk)
	{
		AcDb3dSolid *pSolid = new AcDb3dSolid();
		pSolid->revolve(pRegion, AcGePoint3d::kOrigin, AcGeVector3d(0, 1, 0), 8 * atan(1));
		CDwgDatabaseUtil::PostToModelSpace(pSolid);
		
		pRegion->close();
	}
}

// This is command 'BOOLEAN'
void ZffChap10Boolean()
{
	// 创建两个长方体
	AcDb3dSolid *pSolid1 = new AcDb3dSolid();
	pSolid1->createBox(40, 50, 30);
	AcDb3dSolid *pSolid2 = new AcDb3dSolid();
	pSolid2->createBox(40, 50, 30);
	
	// 使用几何变换矩阵移动长方体
	AcGeMatrix3d xform;
	AcGeVector3d vec(20, 25, 15);
	xform.setToTranslation(vec);
	pSolid1->transformBy(xform);
	
	// 将长方体添加到模型空间
	AcDbObjectId solidId1 = CDwgDatabaseUtil::PostToModelSpace(pSolid1);
	AcDbObjectId solidId2 = CDwgDatabaseUtil::PostToModelSpace(pSolid2);
	
	// 进行布尔运算，生成新的实体
	acdbOpenObject(pSolid1, solidId1, AcDb::kForWrite);
	acdbOpenObject(pSolid2, solidId2, AcDb::kForWrite);
	
	Acad::ErrorStatus es = pSolid1->booleanOper(AcDb::kBoolUnite, pSolid2);
	assert(pSolid2->isNull());
	pSolid2->erase();	// 手工将其删除
	
	pSolid2->close();	// 删除之后还是需要关闭该实体
	pSolid1->close();
}

