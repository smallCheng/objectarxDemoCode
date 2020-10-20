//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Geometry\GePointUtil.h"
#include "..\..\Common\Entity\LineUtil.h"
#include "..\..\Common\Entity\circleutil.h"
#include "..\..\Common\Entity\DimensionUtil.h"
#include "..\..\Common\Geometry\MathUtil.h"

// This is command 'ADDDIMENSION'
void ZffChap2AddDimension()
{
	// 指定起始点位置
	AcGePoint3d pt1(200, 160, 0);
	AcGePoint3d pt2= CGePointUtil::RelativePoint(pt1, -40, 0);
	AcGePoint3d pt3 = CGePointUtil::PolarPoint(pt2, 
		7 * CMathUtil::PI() / 6, 20);
	AcGePoint3d pt4 = CGePointUtil::RelativePoint(pt3, 6, -10);
	AcGePoint3d pt5 = CGePointUtil::RelativePoint(pt1, 0, -20);
	
	// 绘制外轮廓线
	CLineUtil::Add(pt1, pt2);
	CLineUtil::Add(pt2, pt3);
	CLineUtil::Add(pt3, pt4);
	CLineUtil::Add(pt4, pt5);
	CLineUtil::Add(pt5, pt1);
	
	// 绘制圆形
	AcGePoint3d ptCenter1, ptCenter2;
	ptCenter1 = CGePointUtil::RelativePoint(pt3, 16, 0);
	ptCenter2 = CGePointUtil::RelativePoint(ptCenter1, 25, 0);
	CCircleUtil::Add(ptCenter1, 3);
	CCircleUtil::Add(ptCenter2, 4);
	
	AcGePoint3d ptTemp1, ptTemp2;
	// 水平标注
	ptTemp1 = CGePointUtil::RelativePoint(pt1, -20, 3);
	CDimensionUtil::AddDimRotated(pt1, pt2, ptTemp1, 0);
	
	// 垂直标注
	ptTemp1 = CGePointUtil::RelativePoint(pt1, 4, 10);
	CDimensionUtil::AddDimRotated(pt1, pt5, ptTemp1, 
		CMathUtil::PI() / 2);
	
	// 转角标注
	ptTemp1 = CGePointUtil::RelativePoint(pt3, -3, -6);
	CDimensionUtil::AddDimRotated(pt3, pt4, ptTemp1, 
		7 * CMathUtil::PI() / 4);
	
	// 对齐标注
	ptTemp1 = CGePointUtil::RelativePoint(pt2, -3, 4);
	CDimensionUtil::AddDimAligned(pt2, pt3, ptTemp1, 
		AcGeVector3d(4, 10, 0), TEXT("new position"));
	
	// 角度标注
	ptTemp1 = CGePointUtil::RelativePoint(pt5, -5, 5);
	CDimensionUtil::AddDim3PtAngular(pt5, pt1, pt4, ptTemp1);
	
	// 半径标注
	ptTemp1 = CGePointUtil::PolarPoint(ptCenter1, 
		CMathUtil::PI() / 4, 3);
	CDimensionUtil::AddDimRadial(ptCenter1, ptTemp1, -3);
	
	// 直径标注
	ptTemp1 = CGePointUtil::PolarPoint(ptCenter2, CMathUtil::PI() / 4, 4);
	ptTemp2 = CGePointUtil::PolarPoint(ptCenter2, CMathUtil::PI() / 4, -4);
	CDimensionUtil::AddDimDiametric(ptTemp1, ptTemp2, 0);
	
	// 坐标标注
	CDimensionUtil::AddDimOrdinate(ptCenter2, AcGeVector3d(0, -10, 0), 
		AcGeVector3d(10, 0, 0));
}

