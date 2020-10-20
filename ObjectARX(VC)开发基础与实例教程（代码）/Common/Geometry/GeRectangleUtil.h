// GeRectangleUtil.h: interface for the CGeRectangleUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GERECTANGLEUTIL_H__D66803EA_EB61_44C1_9E2E_3E09CB282138__INCLUDED_)
#define AFX_GERECTANGLEUTIL_H__D66803EA_EB61_44C1_9E2E_3E09CB282138__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGeRectangleUtil  
{
public:
	CGeRectangleUtil();
	virtual ~CGeRectangleUtil();

	// 功能: 判断两个矩形是否有相交的部分
	// 参数: const AcGePoint2d & rect1Point1, 第一个矩形的第一个角点
	// 参数: const AcGePoint2d & rect1Point2, 第一个矩形的第二个角点
	// 参数: const AcGePoint2d & rect2Point1, 第二个矩形的第一个角点
	// 参数: const AcGePoint2d & rect2Point2, 第二个矩形的第二个角点
	// 返回值:   bool, 如果两个矩形有相交的部分返回true，否则返回false
	static bool IntersectWithRectangle(const AcGePoint2d &rect1Point1, const AcGePoint2d &rect1Point2, 
		const AcGePoint2d &rect2Point1, const AcGePoint2d &rect2Point2);
};

#endif // !defined(AFX_GERECTANGLEUTIL_H__D66803EA_EB61_44C1_9E2E_3E09CB282138__INCLUDED_)
