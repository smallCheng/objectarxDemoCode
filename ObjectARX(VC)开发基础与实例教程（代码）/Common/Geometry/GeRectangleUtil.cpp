// GeRectangleUtil.cpp: implementation of the CGeRectangleUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GeRectangleUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGeRectangleUtil::CGeRectangleUtil()
{

}

CGeRectangleUtil::~CGeRectangleUtil()
{

}

bool CGeRectangleUtil::IntersectWithRectangle( const AcGePoint2d &rect1Point1, const AcGePoint2d &rect1Point2, 
											  const AcGePoint2d &rect2Point1, const AcGePoint2d &rect2Point2 )
{
	// 获得两个矩形的四个边界值
	double rect1MinX = min(rect1Point1[X], rect1Point2[X]);
	double rect1MaxX = max(rect1Point1[X], rect1Point2[X]);
	double rect1MinY = min(rect1Point1[Y], rect1Point2[Y]);
	double rect1MaxY = max(rect1Point1[Y], rect1Point2[Y]);
	double rect2MinX = min(rect2Point1[X], rect2Point2[X]);
	double rect2MaxX = max(rect2Point1[X], rect2Point2[X]);
	double rect2MinY = min(rect2Point1[Y], rect2Point2[Y]);
	double rect2MaxY = max(rect2Point1[Y], rect2Point2[Y]);	
	
	// 判断一个矩形的x/y的最小值是否大于另一个的最大值即可
	double tol = 1.0E-7;
	if (rect1MinX > rect2MaxX + tol || rect2MinX > rect1MaxX + tol || 
		rect1MinY > rect2MaxY + tol || rect2MinY > rect1MaxY + tol)
	{
		return false;
	}		
	else
	{
		return true;
	}
}
