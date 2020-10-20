//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Entity\PolylineUtil.h"
#include "..\..\Common\Others\ConvertUtil.h"

// This is command 'ADDPOLYLINE'
void ZffChap2AddPolyline()
{
	// 创建仅包含一段直线的多段线
	AcGePoint2d ptStart(0, 0), ptEnd(100, 100);
	CPolylineUtil::Add(ptStart, ptEnd, 1);
	
	// 创建三维多段线
	AcGePoint3d pt1(0, 0, 0), pt2(100, 0, 0), pt3(100, 100, 0);
	AcGePoint3dArray points;
	points.append(pt1);
	points.append(pt2);
	points.append(pt3);
	CPolylineUtil::Add3dPolyline(points);
	
	// 创建正多边形
	CPolylineUtil::AddPolygon(AcGePoint2d::kOrigin, 6, 30, 0, 1);
	
	// 创建矩形
	AcGePoint2d pt(60, 70);
	CPolylineUtil::AddRectangle(pt, ptEnd, 1);
	
	// 创建圆
	pt.set(50, 50);
	CPolylineUtil::AddPolyCircle(pt, 30, 1);
	
	// 创建圆弧
	CPolylineUtil::AddPolyArc(pt, 50, CConvertUtil::AngleToRadian(45), 
		CConvertUtil::AngleToRadian(225), 1);
}

