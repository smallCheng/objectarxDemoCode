//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Entity\ArcUtil.h"
#include <complex>

// This is command 'ADDARC'
void ZffChap2AddArc()
{
	// 创建位于XOY平面上的圆弧
	AcGePoint2d ptCenter(50, 50);
	CArcUtil::Add(ptCenter, 100 * sqrt(2) / 2, 5 * CMathUtil::PI() / 4, 
		7 * CMathUtil::PI() / 4);
	
	// 三点法创建圆弧
	AcGePoint2d ptStart(100, 0);
	AcGePoint2d ptOnArc(120, 50);
	AcGePoint2d ptEnd(100, 100);
	CArcUtil::Add(ptStart, ptOnArc, ptEnd);
	
	// "起点、圆心、终点"创建圆弧
	ptStart.set(100, 100);
	ptCenter.set(50, 50);
	ptEnd.set(0, 100);
	CArcUtil::AddBySCE(ptStart, ptCenter, ptEnd);
	
	// "起点、圆心、圆弧角度"创建圆弧
	ptStart.set(0, 100);
	ptCenter.set(50, 50);
	CArcUtil::Add(ptStart, ptCenter, CMathUtil::PI() / 2);
}

