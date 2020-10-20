// EllipseUtil.cpp: implementation of the CEllipseUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EllipseUtil.h"
#include "..\Document\DwgDatabaseUtil.h"
#include <dbelipse.h>
#include "..\Geometry\GePointUtil.h"
#include "..\Others\ConvertUtil.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEllipseUtil::CEllipseUtil()
{

}

CEllipseUtil::~CEllipseUtil()
{

}

AcDbObjectId CEllipseUtil::Add( const AcGePoint3d &ptCenter, const AcGeVector3d &vecNormal, 
							   const AcGeVector3d &majorAxis, double ratio )
{
	AcDbEllipse *pEllipse = new AcDbEllipse(ptCenter, vecNormal, majorAxis, ratio);
	
	return CDwgDatabaseUtil::PostToModelSpace(pEllipse);
}

AcDbObjectId CEllipseUtil::Add( const AcGePoint2d &pt1, const AcGePoint2d &pt2 )
{
	// 计算椭圆的中心点
	AcGePoint3d ptCenter;
	ptCenter = CGePointUtil::GetMiddlePoint(CConvertUtil::ToPoint3d(pt1), 
		CConvertUtil::ToPoint3d(pt2));
	
	AcGeVector3d vecNormal(0, 0, 1);
	AcGeVector3d majorAxis(fabs(pt1.x - pt2.x) / 2, 0, 0);
	double ratio = fabs((pt1.y - pt2.y) / (pt1.x - pt2.x));
	
	return Add(ptCenter, vecNormal, majorAxis, ratio);
}
