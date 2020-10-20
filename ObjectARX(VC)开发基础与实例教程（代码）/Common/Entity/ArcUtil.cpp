// ArcUtil.cpp: implementation of the CArcUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ArcUtil.h"
#include <dbents.h>
#include "..\Document\DwgDatabaseUtil.h"
#include "..\Others\ConvertUtil.h"
#include <gearc2d.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArcUtil::CArcUtil()
{

}

CArcUtil::~CArcUtil()
{

}

AcDbObjectId CArcUtil::Add( const AcGePoint3d &ptCenter, const AcGeVector3d &vec, double radius, 
						   double startAngle, double endAngle )
{
	AcDbArc *pArc = new AcDbArc(ptCenter, vec, radius, startAngle, endAngle);	
	AcDbObjectId arcId = CDwgDatabaseUtil::PostToModelSpace(pArc);
	
	return arcId;
}

AcDbObjectId CArcUtil::Add( const AcGePoint2d &ptCenter, double radius, double startAngle, 
						   double endAngle )
{
	AcGeVector3d vec(0, 0, 1);
	return Add(CConvertUtil::ToPoint3d(ptCenter), vec, radius, startAngle, endAngle);
}

AcDbObjectId CArcUtil::Add( const AcGePoint2d &ptStart, const AcGePoint2d &ptOnArc, 
						   const AcGePoint2d &ptEnd )
{
	// 使用几何类获得圆心、半径
	AcGeCircArc2d geArc(ptStart, ptOnArc, ptEnd);
	AcGePoint2d ptCenter = geArc.center();
	double radius = geArc.radius();
	
	// 计算起始和终止角度
	AcGeVector2d vecStart(ptStart.x - ptCenter.x, ptStart.y - ptCenter.y);
	AcGeVector2d vecEnd(ptEnd.x - ptCenter.x, ptEnd.y - ptCenter.y);
	double startAngle = vecStart.angle();
	double endAngle = vecEnd.angle();	
	
	return Add(ptCenter, radius, startAngle, endAngle);
}

AcDbObjectId CArcUtil::Add( const AcGePoint2d &ptStart, const AcGePoint2d &ptCenter, double angle )
{
	// 计算半径
	double radius = ptCenter.distanceTo(ptStart);
	
	// 计算起、终点角度
	AcGeVector2d vecStart(ptStart.x - ptCenter.x, ptStart.y - ptCenter.y);
	double startAngle = vecStart.angle();
	double endAngle = startAngle + angle;
	
	// 创建圆弧
	return Add(ptCenter, radius, startAngle, endAngle);
}

AcDbObjectId CArcUtil::AddBySCE( const AcGePoint2d &ptStart, const AcGePoint2d &ptCenter, 
									const AcGePoint2d &ptEnd )
{
	// 计算半径
	double radius = ptCenter.distanceTo(ptStart);
	
	// 计算起、终点角度
	AcGeVector2d vecStart(ptStart.x - ptCenter.x, ptStart.y - ptCenter.y);
	AcGeVector2d vecEnd(ptEnd.x - ptCenter.x, ptEnd.y - ptCenter.y);
	double startAngle = vecStart.angle();
	double endAngle = vecEnd.angle();
	
	// 创建圆弧
	return Add(ptCenter, radius, startAngle, endAngle);
}
