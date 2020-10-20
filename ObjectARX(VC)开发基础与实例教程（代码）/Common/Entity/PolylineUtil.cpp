// PolylineUtil.cpp: implementation of the CPolylineUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PolylineUtil.h"
#include <dbpl.h>
#include "..\Document\DwgDatabaseUtil.h"
#include <dbents.h>
#include "..\Geometry\MathUtil.h"
#include <complex>
#include "EntityUtil.h"
#include <geray2d.h>
#include "..\Geometry\GePointUtil.h"
#include "..\Others\ConvertUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPolylineUtil::CPolylineUtil()
{

}

CPolylineUtil::~CPolylineUtil()
{

}

AcDbObjectId CPolylineUtil::Add( const AcGePoint2dArray &points, double width )
{
	int numVertices = points.length();	
	AcDbPolyline *pPoly = new AcDbPolyline(numVertices);
	
	for (int i = 0; i < numVertices; i++)
	{
		pPoly->addVertexAt(i, points.at(i), 0, width, width);
	}
	
	AcDbObjectId polyId;
	polyId = CDwgDatabaseUtil::PostToModelSpace(pPoly);
	
	return polyId;
}

AcDbObjectId CPolylineUtil::Add( const AcGePoint2d &ptStart, const AcGePoint2d &ptEnd, double width )
{
	AcGePoint2dArray points;
	points.append(ptStart);
	points.append(ptEnd);
	
	return Add(points, width);
}

AcDbObjectId CPolylineUtil::Add3dPolyline( const AcGePoint3dArray &points )
{
	AcGePoint3dArray verts = points;
	AcDb3dPolyline *pPoly3d = new AcDb3dPolyline(AcDb::k3dSimplePoly, verts);
	
	return CDwgDatabaseUtil::PostToModelSpace(pPoly3d);
}

AcDbObjectId CPolylineUtil::AddPolygon( const AcGePoint2d &ptCenter, int number, double radius, 
									   double rotation, double width )
{	
	double angle = 2 * CMathUtil::PI() / (double)number;
	AcGePoint2dArray points;
	for (int i = 0; i < number; i++)
	{
		AcGePoint2d pt;
		pt.x = ptCenter.x + radius * cos(i * angle);
		pt.y = ptCenter.y + radius * sin(i * angle);
		
		points.append(pt);
	}
	
	AcDbObjectId polyId = Add(points, width);
	
	// 将其闭合
	AcDbEntity *pEnt = NULL;
	if (acdbOpenAcDbEntity(pEnt, polyId, AcDb::kForWrite) == Acad::eOk)
	{
		AcDbPolyline *pPoly = AcDbPolyline::cast(pEnt);
		if (pPoly != NULL)
		{
			pPoly->setClosed(Adesk::kTrue);
		}
		pEnt->close();
	}
	
	CEntityUtil::Rotate(polyId, ptCenter, rotation);
	
	return polyId;
}

AcDbObjectId CPolylineUtil::AddRectangle( const AcGePoint2d &pt1, const AcGePoint2d &pt2, double width )
{
	// 提取两个角点的坐标值
	double x1 = pt1.x, x2 = pt2.x;
	double y1 = pt1.y, y2 = pt2.y;
	
	// 计算矩形的角点
	AcGePoint2d ptLeftBottom(min(x1, x2), min(y1, y2));
	AcGePoint2d ptRightBottom(max(x1, x2), min(y1, y2));
	AcGePoint2d ptRightTop(max(x1, x2), max(y1, y2));
	AcGePoint2d ptLeftTop(min(x1, x2), max(y1, y2));
	
	// 创建对应的多段线
	AcDbPolyline *pPoly = new AcDbPolyline(4);
	pPoly->addVertexAt(0, ptLeftBottom, 0, width, width);
	pPoly->addVertexAt(1, ptRightBottom, 0, width, width);
	pPoly->addVertexAt(2, ptRightTop, 0, width, width);
	pPoly->addVertexAt(3, ptLeftTop, 0, width, width);
	pPoly->setClosed(Adesk::kTrue);
	
	// 将多段线添加到模型空间
	AcDbObjectId polyId;
	polyId = CDwgDatabaseUtil::PostToModelSpace(pPoly);
	
	return polyId;
}

AcDbObjectId CPolylineUtil::AddPolyCircle( const AcGePoint2d &ptCenter, double radius, double width )
{
	// 计算顶点的位置
	AcGePoint2d pt1, pt2, pt3;
	pt1.x = ptCenter.x + radius;
	pt1.y = ptCenter.y;
	pt2.x = ptCenter.x - radius;
	pt2.y = ptCenter.y;
	pt3.x = ptCenter.x + radius;
	pt3.y = ptCenter.y;
	
	// 创建多段线
	AcDbPolyline *pPoly = new AcDbPolyline(3);
	pPoly->addVertexAt(0, pt1, 1, width, width);
	pPoly->addVertexAt(1, pt2, 1, width, width);
	pPoly->addVertexAt(2, pt3, 1, width, width);
	pPoly->setClosed(Adesk::kTrue);
	
	// 将多段线添加到模型空间
	AcDbObjectId polyId = CDwgDatabaseUtil::PostToModelSpace(pPoly);
	
	return polyId;
}

AcDbObjectId CPolylineUtil::AddPolyArc( const AcGePoint2d &ptCenter, double radius, 
									   double angleStart, double angleEnd, double width )
{
	// 计算顶点的位置
	AcGePoint2d pt1, pt2;
	pt1.x = ptCenter.x + radius * cos(angleStart);
	pt1.y = ptCenter.y + radius * sin(angleStart);
	pt2.x = ptCenter.x + radius * cos(angleEnd);
	pt2.y = ptCenter.y + radius * sin(angleEnd);
	
	// 创建多段线
	AcDbPolyline *pPoly = new AcDbPolyline(3);
	pPoly->addVertexAt(0, pt1, tan((angleEnd - angleStart) / 4), width, width);
	pPoly->addVertexAt(1, pt2, 0, width, width);	
	
	// 将多段线添加到模型空间
	AcDbObjectId polyId = CDwgDatabaseUtil::PostToModelSpace(pPoly);
	
	return polyId;
}

// 几何类射线和多段线计算交点
static void IntersectWithGeRay( AcDbPolyline *pPoly, const AcGeRay2d &geRay, AcGePoint3dArray &intPoints, double tol /*= 1.0E-7*/ )
{
	intPoints.setLogicalLength(0);
	AcGePoint2dArray intPoints2d;
	
	// 多段线的每一段分别与射线计算交点
	AcGeTol geTol;
	geTol.setEqualPoint(tol);
	for (int i = 0; i < pPoly->numVerts(); i++)
	{
		if (i < pPoly->numVerts() - 1 || pPoly->isClosed() == Adesk::kTrue)
		{
			double bulge = 0;
			pPoly->getBulgeAt(i, bulge);
			if (fabs(bulge) < 1.0E-7)
			{
				// 构建几何类的线段来计算交点
				AcGeLineSeg2d geLine;
				Acad::ErrorStatus es = pPoly->getLineSegAt(i, geLine);
				AcGePoint2d intPoint;
				if (geLine.intersectWith(geRay, intPoint, geTol) == Adesk::kTrue)
				{
					if (CGePointUtil::FindPoint(intPoints2d, intPoint, tol) < 0)
					{
						intPoints2d.append(intPoint);
					}
				}
			}
			else
			{
				// 构建几何类的圆弧来计算交点
				AcGeCircArc2d geArc;
				pPoly->getArcSegAt(i, geArc);
				AcGePoint2d pt1, pt2;
				int count = 0;
				if (geArc.intersectWith(geRay, count, pt1, pt2, geTol) == Adesk::kTrue)
				{
					if (CGePointUtil::FindPoint(intPoints2d, pt1, tol) < 0)
					{
						intPoints2d.append(pt1);
					}
					if (count > 1 && CGePointUtil::FindPoint(intPoints2d, pt2, tol) < 0)
					{
						intPoints2d.append(pt2);
					}
				}
			}
		}
	}
	
	double z = pPoly->elevation();
	for (i = 0; i < intPoints2d.length(); i++)
	{
		intPoints.append(AcGePoint3d(intPoints2d[i].x, intPoints2d[i].y, z));
	}
}

// 点是否是多段线的顶点
static bool PointIsPolyVert( AcDbPolyline *pPoly, const AcGePoint2d &pt, double tol )
{
	for (int i = 0; i < (int)pPoly->numVerts(); i++)
	{
		AcGePoint3d vert;
		pPoly->getPointAt(i, vert);
		
		if (CGePointUtil::IsEqual(CConvertUtil::ToPoint2d(vert), pt, tol))
		{
			return true;
		}
	}
	
	return false;
}

int CPolylineUtil::PtRelationToPoly( AcDbPolyline *pPoly, const AcGePoint2d &pt, double tol /*= 1.0E-7*/ )
{
	assert (pPoly);

	// 1.如果点到多段线的最近点和给定的点重合，表示点在多段线上
	AcGePoint3d closestPoint;
	pPoly->getClosestPointTo(CConvertUtil::ToPoint3d(pt, pPoly->elevation()), closestPoint);		// 多段线上与给定点距离最近的点	
	if (fabs(closestPoint.x - pt.x) < tol && fabs(closestPoint.y - pt.y) < tol)			// 点在多段线上
	{
		return 0;
	}

	// 2.第一个射线的方向是从最近点到当前点，起点是当前点
	// 射线的起点是pt，方向为从最近点到pt，如果反向做判断，则最近点距离pt太近的时候，最近点也会被作为一个交点（这个交点不太容易被排除掉）
	// 此外，这样的射线方向很容易判断出点不在内部的情况
	AcGeVector3d vec(-(closestPoint[X] - pt[X]), -(closestPoint[Y] - pt[Y]), 0);
	AcGeRay2d geRay(AcGePoint2d(pt.x, pt.y), AcGePoint2d(pt.x + vec.x, pt.y + vec.y));

	// 3.射线与多段线计算交点
	AcGePoint3dArray intPoints;
	IntersectWithGeRay(pPoly, geRay, intPoints, 1.0E-4);
	// IntersectWith函数经常会得到很近的交点，这些点必须进行过滤
	CGePointUtil::FilterEqualPoints(intPoints, 1.0E-4);	

	// 4.判断点和多段线的位置关系
RETRY:
	// 4.1 如果射线和多段线没有交点，表示点在多段线的外部
	if (intPoints.length() == 0)
	{
			return -1;
	}
	else
	{
		// 3.1 过滤掉由于射线被反向延长带来的影响
		CGePointUtil::FilterEqualPoints(intPoints, CConvertUtil::ToPoint2d(closestPoint));		// 2008-0907修订记录：当pt距离最近点比较近的时候，最近点竟然被作为一个交点！
		// 3.2 如果某个交点与最近点在给定点的同一方向，要去掉这个点（这个点明显不是交点，还是由于intersectwith函数的Bug）	
		for (int i = intPoints.length() - 1; i >= 0; i--)
		{
			if ((intPoints[i][X] - pt[X]) * (closestPoint[X] - pt[X]) >= 0 && 
				(intPoints[i][Y] - pt[Y]) * (closestPoint[Y] - pt[Y]) >= 0)
			{
				intPoints.removeAt(i);
			}
		}

		int count = intPoints.length();
		for (i = 0; i < intPoints.length(); i++)
		{
			if (PointIsPolyVert(pPoly, CConvertUtil::ToPoint2d(intPoints[i]), 1.0E-4))		// 只要有交点是多段线的顶点就重新进行判断
			{
				// 处理给定点很靠近多段线顶点的情况(如果与顶点距离很近，就认为这个点在多段线上，因为这种情况没有什么好的判断方法)
				if (PointIsPolyVert(pPoly, AcGePoint2d(pt.x, pt.y), 1.0E-4))
				{
					return 0;
				}

				// 将射线旋转一个极小的角度(2度)再次判断（假定这样不会再通过上次判断到的顶点）
				vec = vec.rotateBy(0.035, AcGeVector3d::kZAxis);				
				geRay.set(AcGePoint2d(pt.x, pt.y), AcGePoint2d(pt.x + vec.x, pt.y + vec.y));
				intPoints.setLogicalLength(0);
				IntersectWithGeRay(pPoly, geRay, intPoints, 1.0E-4);
				goto RETRY;		// 继续判断结果
			}
		}
		
		if (count % 2 == 0)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
}
