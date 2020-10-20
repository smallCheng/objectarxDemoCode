//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Entity\EllipseUtil.h"

// This is command 'ADDELLIPSE'
void ZffChap2AddEllipse()
{
	// 使用中心点、所在平面、长轴矢量和短长轴比例来创建椭圆
	AcGeVector3d vecNormal(0, 0, 1);
	AcGeVector3d majorAxis(40, 0, 0);
	AcDbObjectId entId;
	entId = CEllipseUtil::Add(AcGePoint3d::kOrigin, vecNormal, majorAxis, 0.5);
	
	// 使用外接矩形来创建椭圆
	AcGePoint2d pt1(60, 80), pt2(140, 120);
	CEllipseUtil::Add(pt1, pt2);
}

// This is command 'ADDSPLINE'
void ZffCHAP2AddSpline()
{
	// 使用样本点直接创建样条曲线
	AcGePoint3d pt1(0, 0, 0), pt2(10, 30, 0), pt3(60, 80, 0), pt4(100, 100, 0);
	AcGePoint3dArray points;
	points.append(pt1);
	points.append(pt2);
	points.append(pt3);
	points.append(pt4);
	CSplineUtil::Add(points);	
	
	// 指定起始点和终止点的切线方向，创建样条曲线
	pt2.set(30, 10, 0);
	pt3.set(80, 60, 0);
	
	points.removeSubArray(0, 3);
	points.append(pt1);
	points.append(pt2);
	points.append(pt3);
	points.append(pt4);
	
	AcGeVector3d startTangent(5, 1, 0);
	AcGeVector3d endTangent(5, 1, 0);
	CSplineUtil::Add(points, startTangent, endTangent);
}

