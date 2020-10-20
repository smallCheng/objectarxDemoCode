// DimensionUtil.cpp: implementation of the CDimensionUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DimensionUtil.h"
#include <dbdim.h>
#include "..\Document\DwgDatabaseUtil.h"
#include "..\Geometry\GePointUtil.h"
#include "..\Geometry\MathUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDimensionUtil::CDimensionUtil()
{

}

CDimensionUtil::~CDimensionUtil()
{

}

AcDbObjectId CDimensionUtil::AddDimAligned( const AcGePoint3d& pt1, const AcGePoint3d& pt2, 
											  const AcGePoint3d& ptLine, const TCHAR* dimText, 
											  AcDbObjectId dimStyle )
{
	AcDbAlignedDimension *pDim = new AcDbAlignedDimension(pt1, pt2, ptLine, dimText, dimStyle);
	
	return CDwgDatabaseUtil::PostToModelSpace(pDim);
}

AcDbObjectId CDimensionUtil::AddDimAligned( const AcGePoint3d& pt1, const AcGePoint3d& pt2, 
										   const AcGePoint3d& ptLine, const AcGeVector3d& vecOffset, 
										   const TCHAR* dimText )
{
	AcDbAlignedDimension *pDim = new AcDbAlignedDimension(pt1, pt2, 
		ptLine, dimText, AcDbObjectId::kNull);
	
	AcDbObjectId dimensionId;
	dimensionId = CDwgDatabaseUtil::PostToModelSpace(pDim);
	
	// 打开已经创建的标注，对文字的位置进行修改
	AcDbAlignedDimension *pDimension = NULL;
	if (acdbOpenObject(pDimension, dimensionId, AcDb::kForWrite) == Acad::eOk)
	{
		// 移动文字位置前，需先指定尺寸线的变化情况（这里指定为：
		// 尺寸线不动，在文字和尺寸线之间加箭头）
		pDimension->setDimtmove(1);		
		// 根据偏移向量修正文字插入点的位置
		AcGePoint3d ptText = pDimension->textPosition();
		ptText = ptText + vecOffset;
		pDimension->setTextPosition(ptText);

		pDimension->close();
	}
	
	return dimensionId;
}

AcDbObjectId CDimensionUtil::AddDimRotated( const AcGePoint3d& pt1, const AcGePoint3d& pt2, const AcGePoint3d& ptLine, 
										   double rotation, const TCHAR* dimText, AcDbObjectId dimStyle )
{
	AcDbRotatedDimension *pDim = new AcDbRotatedDimension(rotation, 
		pt1, pt2, ptLine, dimText, dimStyle);
	
	return CDwgDatabaseUtil::PostToModelSpace(pDim);
}

AcDbObjectId CDimensionUtil::AddDimRadial( const AcGePoint3d& ptCenter, const AcGePoint3d& ptChord, 
										  double leaderLength, const TCHAR* dimText, AcDbObjectId dimStyle )
{
	AcDbRadialDimension *pDim = new AcDbRadialDimension(ptCenter, 
		ptChord, leaderLength, dimText, dimStyle);
	
	return CDwgDatabaseUtil::PostToModelSpace(pDim);
}

AcDbObjectId CDimensionUtil::AddDimRadial( const AcGePoint3d& ptCenter, double radius, 
										  double angle, double leaderLength )
{
	AcGePoint3d ptChord = CGePointUtil::PolarPoint(ptCenter, angle, radius);
	
	return AddDimRadial(ptCenter, ptChord, leaderLength);
}

AcDbObjectId CDimensionUtil::AddDimDiametric( const AcGePoint3d& ptChord1, const AcGePoint3d& ptChord2, 
											 double leaderLength, const TCHAR* dimText, AcDbObjectId dimStyle )
{
	AcDbDiametricDimension *pDim = new AcDbDiametricDimension(ptChord1, 
		ptChord2, leaderLength, dimText, dimStyle);
	
	return CDwgDatabaseUtil::PostToModelSpace(pDim);
}

AcDbObjectId CDimensionUtil::AddDimDiametric( const AcGePoint3d& ptCenter, double radius, double angle, double leaderLength )
{
	// 计算标注通过点的位置
	AcGePoint3d ptChord1, ptChord2;
	ptChord1 = CGePointUtil::PolarPoint(ptCenter, angle, radius);
	ptChord2 = CGePointUtil::PolarPoint(ptCenter, angle + CMathUtil::PI(), radius);
	
	return AddDimDiametric(ptChord1, ptChord2, leaderLength);
}

AcDbObjectId CDimensionUtil::AddDim2LineAngular( const AcGePoint3d& ptStart1, const AcGePoint3d& ptEnd1, 
												const AcGePoint3d& ptStart2, const AcGePoint3d& ptEnd2, 
												const AcGePoint3d& ptArc, const TCHAR* dimText, 
												AcDbObjectId dimStyle )
{
	AcDb2LineAngularDimension *pDim = new AcDb2LineAngularDimension(
		ptStart1, ptEnd1, ptStart2, ptEnd2, ptArc, dimText, dimStyle);
	
	return CDwgDatabaseUtil::PostToModelSpace(pDim);
}

AcDbObjectId CDimensionUtil::AddDim3PtAngular( const AcGePoint3d& ptCenter, const AcGePoint3d& ptEnd1, 
											  const AcGePoint3d& ptEnd2, const AcGePoint3d& ptArc, 
											  const TCHAR* dimText, AcDbObjectId dimStyle )
{
	AcDb3PointAngularDimension *pDim = new AcDb3PointAngularDimension(
		ptCenter, ptEnd1, ptEnd2, ptArc, dimText, dimStyle);
	
	return CDwgDatabaseUtil::PostToModelSpace(pDim);
}

AcDbObjectId CDimensionUtil::AddDimOrdinate( Adesk::Boolean xAxis, const AcGePoint3d& ptStart, 
											const AcGePoint3d& ptEnd, const TCHAR* dimText, AcDbObjectId dimStyle )
{
	AcDbOrdinateDimension *pDim = new AcDbOrdinateDimension(xAxis, 
		ptStart, ptEnd, dimText, dimStyle);
	
	return CDwgDatabaseUtil::PostToModelSpace(pDim);
}

AcDbObjectIdArray CDimensionUtil::AddDimOrdinate( const AcGePoint3d& ptDef, const AcGePoint3d& ptTextX, 
												 const AcGePoint3d& ptTextY )
{
	AcDbObjectId dimId;
	AcDbObjectIdArray dimIds;
	
	dimId = AddDimOrdinate(Adesk::kTrue, ptDef, ptTextX);
	dimIds.append(dimId);
	dimId = AddDimOrdinate(Adesk::kFalse, ptDef, ptTextY);
	dimIds.append(dimId);
	
	return dimIds;
}

AcDbObjectIdArray CDimensionUtil::AddDimOrdinate( const AcGePoint3d& ptDef, const AcGeVector3d& vecOffsetX, 
												 const AcGeVector3d& vecOffsetY )
{
	AcGePoint3d ptTextX = ptDef + vecOffsetX;
	AcGePoint3d ptTextY = ptDef + vecOffsetY;
	
	return AddDimOrdinate(ptDef, ptTextX, ptTextY);
}
