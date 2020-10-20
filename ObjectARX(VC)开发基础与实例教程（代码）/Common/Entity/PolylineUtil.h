// PolylineUtil.h: interface for the CPolylineUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYLINEUTIL_H__EEB1ED65_B3FE_4181_AD86_5B54BF6533BA__INCLUDED_)
#define AFX_POLYLINEUTIL_H__EEB1ED65_B3FE_4181_AD86_5B54BF6533BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <acaplmgr.h>
#include <dbpl.h>

class CPolylineUtil  
{
public:
	CPolylineUtil();
	virtual ~CPolylineUtil();

	// 创建优化多段线
	static AcDbObjectId Add(const AcGePoint2dArray &points, double width = 0);
	static AcDbObjectId Add(const AcGePoint2d &ptStart, const AcGePoint2d &ptEnd, 
		double width = 0);

	// 创建三维多段线
	static AcDbObjectId Add3dPolyline(const AcGePoint3dArray &points);

	// 创建正多边形
	static AcDbObjectId AddPolygon(const AcGePoint2d &ptCenter, int number, 
		double radius, double rotation, double width);

	// 创建矩形
	static AcDbObjectId AddRectangle(const AcGePoint2d &pt1, const AcGePoint2d &pt2, 
		double width);

	// 创建圆形的多段线
	static AcDbObjectId AddPolyCircle(const AcGePoint2d &ptCenter, double radius, double width);

	// 创建一段圆弧的多段线
	static AcDbObjectId AddPolyArc(const AcGePoint2d &ptCenter, double radius, 
		double angleStart, double angleEnd, double width);

	// 点和多段线的位置关系
	// 返回值：-1表示在多段线外部，0表示在多段线上，1表示在多段线内部
	static int PtRelationToPoly(AcDbPolyline *pPoly, const AcGePoint2d &pt, double tol = 1.0E-7);
};

#endif // !defined(AFX_POLYLINEUTIL_H__EEB1ED65_B3FE_4181_AD86_5B54BF6533BA__INCLUDED_)
