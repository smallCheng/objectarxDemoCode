//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Entity\circleutil.h"

// This is command 'ADDCIRCLE'
void ZffChap2AddCircle()
{
	// "圆心、半径"法创建一个圆
	AcGePoint3d ptCenter(100, 100, 0);
	CCircleUtil::Add(ptCenter, 20);
	
	// 两点法创建一个圆
	AcGePoint2d pt1(70, 100);
	AcGePoint2d pt2(130, 100);
	CCircleUtil::Add(pt1, pt2);
	
	// 三点法创建一个圆
	pt1.set(60, 100);
	pt2.set(140, 100);
	AcGePoint2d pt3(100, 60);
	CCircleUtil::Add(pt1, pt2, pt3);
}

