// LineUtil.h: interface for the CLineUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINEUTIL_H__7B01AAA2_B236_4E0C_A689_D549EE8A77D1__INCLUDED_)
#define AFX_LINEUTIL_H__7B01AAA2_B236_4E0C_A689_D549EE8A77D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLineUtil  
{
public:
	CLineUtil();
	virtual ~CLineUtil();

	// 添加一条直线
	static AcDbObjectId Add(const AcGePoint3d &startPoint, const AcGePoint3d &endPoint, 
		AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase());

	// 三点是否共线
	static bool ThreePointIsCollinear(const AcGePoint2d &pt1, const AcGePoint2d &pt2, const AcGePoint2d &pt3);

	// 判断点是否在直线的左侧（从直线的起点到终点为观察方向）
	// tol: 两个矢量决定的平行四边形的面积，对于返回值为0的情况仅能做粗略地比较
	// 返回值：1表示在直线的左侧，0表示在直线上，-1表示在直线的右侧
	static int PtInLeftOfLine(const AcGePoint3d &ptStart, const AcGePoint3d &ptEnd, const AcGePoint3d &pt, double tol = 1.0E-7);
	static int PtInLeftOfLine(const AcGePoint2d &ptStart, const AcGePoint2d &ptEnd, const AcGePoint2d &pt, double tol = 1.0E-7);
	static int PtInLeftOfLine(double x1, double y1, double x2, double y2, double x3, double y3, double tol = 1.0E-7);
};

#endif // !defined(AFX_LINEUTIL_H__7B01AAA2_B236_4E0C_A689_D549EE8A77D1__INCLUDED_)
