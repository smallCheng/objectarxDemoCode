// ArcUtil.h: interface for the CArcUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARCUTIL_H__512CA8A8_80C3_478A_9C59_93F5874E1C2E__INCLUDED_)
#define AFX_ARCUTIL_H__512CA8A8_80C3_478A_9C59_93F5874E1C2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CArcUtil  
{
public:
	CArcUtil();
	virtual ~CArcUtil();

	// 添加圆弧
	static AcDbObjectId Add(const AcGePoint3d &ptCenter, const AcGeVector3d &vec, 
		double radius, double startAngle, double endAngle);
	static AcDbObjectId Add(const AcGePoint2d &ptCenter, double radius, 
		double startAngle, double endAngle);
	// 三点法
	static AcDbObjectId Add(const AcGePoint2d &ptStart, const AcGePoint2d &ptOnArc, 
		const AcGePoint2d &ptEnd);
	// 起点、圆心、终点
	static AcDbObjectId AddBySCE(const AcGePoint2d &ptStart, const AcGePoint2d &ptCenter, 
		const AcGePoint2d &ptEnd);
	// 起点、圆心、圆弧角度
	static AcDbObjectId Add(const AcGePoint2d &ptStart, const AcGePoint2d &ptCenter, 
		double angle);
};

#endif // !defined(AFX_ARCUTIL_H__512CA8A8_80C3_478A_9C59_93F5874E1C2E__INCLUDED_)
