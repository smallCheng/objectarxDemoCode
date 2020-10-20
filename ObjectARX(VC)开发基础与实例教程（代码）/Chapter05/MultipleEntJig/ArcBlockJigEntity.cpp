// ArcBlockJigEntity.cpp: implementation of the CArcBlockJigEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ArcBlockJigEntity.h"
#include "..\..\Common\Entity\LineUtil.h"
#include "..\..\Common\Others\ConvertUtil.h"
#include <acgi.h>
#include <dbents.h>
#include "..\..\Common\Document\DwgDatabaseUtil.h"
#include "..\..\Common\Geometry\MathUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArcBlockJigEntity::CArcBlockJigEntity(const AcGePoint3d &startPoint, const AcGePoint3d &thirdPoint, 
									   const AcGePoint3d &endPoint, AcDbObjectId blkDefId, int count)
{
	m_startPoint = startPoint;
	m_thirdPoint = thirdPoint;
	m_endPoint = endPoint;
	m_blkDefId = blkDefId;
	m_blockCount = count;
}

CArcBlockJigEntity::~CArcBlockJigEntity()
{

}

Adesk::Boolean CArcBlockJigEntity::worldDraw( AcGiWorldDraw* mode )
{
	DrawOrAddSubEnts(mode);

	return Adesk::kTrue;
}

void CArcBlockJigEntity::SetEndPoint( const AcGePoint3d &pt )
{
	// 这句代码能引发worldDraw函数的调用
	assertWriteEnabled();

	m_endPoint = pt;
}

void CArcBlockJigEntity::PostToModelSpace()
{
	DrawOrAddSubEnts(NULL);
}

void CArcBlockJigEntity::DrawOrAddSubEnts( AcGiWorldDraw* mode )
{
	// 绘制圆弧
	AcDbCurve *pCurve = NULL;		// 计算等分点的曲线
	AcGePoint2d startPoint2d = CConvertUtil::ToPoint2d(m_startPoint);
	AcGePoint2d thirdPoint2d = CConvertUtil::ToPoint2d(m_thirdPoint);
	AcGePoint2d endPoint2d = CConvertUtil::ToPoint2d(m_endPoint);
	if (CLineUtil::ThreePointIsCollinear(startPoint2d, thirdPoint2d, endPoint2d))	// 三点共线，绘制直线
	{
		AcGePoint3d verts[2];
		verts[0] = m_startPoint;
		verts[1] = m_endPoint;
		if (mode != NULL)
		{
			mode->geometry().polyline(2, verts);
		}
		
		pCurve = new AcDbLine(m_startPoint, m_endPoint);
	}
	else	// 绘制圆弧
	{
		if (mode != NULL)
		{
			mode->geometry().circularArc(m_startPoint, m_thirdPoint, m_endPoint);
		}
		
		AcGeCircArc2d geArc(startPoint2d, thirdPoint2d, endPoint2d);
		// geArc的起始角度始终是0，因此必须单独计算起始角度和终止角度
		AcGeVector2d vecStart = startPoint2d - geArc.center();
		AcGeVector2d vecEnd = endPoint2d - geArc.center();
		// AcDbArc必须是逆时针的，因此需要根据三点的旋转方向，确定正确的起始角度
		double startAngle = 0;
		if (CLineUtil::PtInLeftOfLine(startPoint2d, thirdPoint2d, endPoint2d) > 0)	// 逆时针
		{
			startAngle = vecStart.angle();
		}
		else
		{
			startAngle = vecEnd.angle();
		}
		double endAngle = startAngle + (geArc.endAng() - geArc.startAng());
		pCurve = new AcDbArc(CConvertUtil::ToPoint3d(geArc.center()), geArc.radius(), startAngle, endAngle);
	}
	
	// 计算等分点，获得块参照插入的位置
	double startParam = 0, endParam = 0;		// 曲线的起点和终点参数
	pCurve->getStartParam(startParam);
	pCurve->getEndParam(endParam);
	int intervalCount = m_blockCount + 1;		// 等分间距份数比块参照数量大1
	double paramInterval = (endParam - startParam) / intervalCount;
	AcGePoint3dArray blkRefPoints;		// 块参照的插入点集合
	for (int i = 1; i < intervalCount; i++)		// 曲线和起点和终点不需要放置图块
	{
		double param = startParam + i * paramInterval;
		AcGePoint3d pt;
		pCurve->getPointAtParam(param, pt);
		blkRefPoints.append(pt);
	}

	if (mode != NULL)	// 显示子实体
	{
		delete pCurve;		// 动态分配的实体，不加入模型空间，使用完毕之后需要释放
	}
	else	// 添加子实体的方式
	{
		CDwgDatabaseUtil::PostToModelSpace(pCurve);
	}
	
	// 绘制几个图块
	m_blkRefIds.setLogicalLength(0);
	for (i = 0; i < blkRefPoints.length(); i++)
	{
		AcDbBlockReference *pBlkRef = new AcDbBlockReference(blkRefPoints[i], m_blkDefId);
		if (mode != NULL)
		{
			pBlkRef->worldDraw(mode);
			delete pBlkRef;
		}
		else
		{
			m_blkRefIds.append(CDwgDatabaseUtil::PostToModelSpace(pBlkRef));
		}
	}
}

AcDbObjectIdArray CArcBlockJigEntity::GetBlkRefIds()
{
	return m_blkRefIds;
}
