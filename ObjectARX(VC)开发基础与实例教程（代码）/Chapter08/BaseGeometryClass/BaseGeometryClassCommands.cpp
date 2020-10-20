//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include <gearc2d.h>
#include <geline2d.h>
#include <gelnsg2d.h>
#include <dbents.h>
#include "..\..\Common\Others\ConvertUtil.h"
#include "..\..\Common\Interaction\SelectUtil.h"
#include <dbpl.h>
#include "..\..\Common\Document\DwgDatabaseUtil.h"

// This is command 'INTERSECTWITH'
void ZffChap8IntersectWith()
{
	// 创建所要计算交点的几何类对象
	AcGeCircArc2d geArc(AcGePoint2d::kOrigin, 50, 0, 6);
	AcGeLine2d geLine(AcGePoint2d::kOrigin, AcGePoint2d(10, 10));
	
	// 计算并输出交点
	AcGePoint2d point1, point2;
	int num;
	if (geArc.intersectWith(geLine, num, point1, point2))
	{
		acutPrintf(TEXT("\n直线和圆弧有%d个交点."), num);
		if (num > 0)
		{
			acutPrintf(TEXT("\n交点1坐标: (%.4f, %.4f)."), point1.x, point1.y);
		}
		if (num > 1)
		{
			acutPrintf(TEXT("\n交点2坐标: (%.4f, %.4f)."), point2.x, point2.y);
		}
	}
}

// 根据直线DB对象获得几何类对象
static AcGeLineSeg2d GetGeLineObj(AcDbObjectId lineId)
{
	AcGeLineSeg2d geLine;
	AcDbLine *pLine = NULL;
	if (acdbOpenObject(pLine, lineId, AcDb::kForRead) == Acad::eOk)
	{
		geLine.set(CConvertUtil::ToPoint2d(pLine->startPoint()), CConvertUtil::ToPoint2d(pLine->endPoint()));
		pLine->close();
	}
	
	return geLine;
}

// This is command 'LINEDISTANCE'
void ZffChap8LineDistance()
{
	// 提示用户选择所要计算距离的两条直线
	AcDbObjectIdArray lineIds;
	if (CSelectUtil::PromptSelectEnts(TEXT("\n选择两条直线:"), AcDbLine::desc(), lineIds))
	{
		if (lineIds.length() != 2)
		{
			acutPrintf(TEXT("\n必须选择两条直线."));
			return;
		}

		// 将直线转换成对应的几何类对象
		AcGeLineSeg2d geLine1 = GetGeLineObj(lineIds[0]);
		AcGeLineSeg2d geLine2 = GetGeLineObj(lineIds[1]);
		
		// 计算并输出两者之间的最短距离
		double distance = geLine1.distanceTo(geLine2);
		acutPrintf("\n两条直线之间的最短距离为: %.4f.", distance);
	}	
}

// 获得两个交点之间的曲线
void GetCurveBetweenIntPoints(AcDbPolyline *pPoly, const AcGePoint3dArray &intPoints)
{
	AcDbVoidPtrArray curves;
	pPoly->getSplitCurves(intPoints, curves);
	for (int i = 0; i < curves.length(); i++)
	{
		AcDbCurve *pCurve = static_cast<AcDbCurve*>(curves[i]);		
		
		// 删除首尾两条曲线，其他段的曲线添加到模型空间
		if (i == 0 || i == curves.length() - 1)
		{
			delete pCurve;
		}
		else
		{
			AcDbObjectId curveId = CDwgDatabaseUtil::PostToModelSpace(pCurve);
		}
	}
}

// This is command 'CURVEBOOLEAN'
void ZffChap8CurveBoolean()
{
	// 选择所要操作的两条多段线
	AcDbObjectIdArray polyIds;
	if (CSelectUtil::PromptSelectEnts(TEXT("\n选择两条多段线:"), AcDbPolyline::desc(), polyIds))
	{
		if (polyIds.length() != 2)
		{
			acutPrintf(TEXT("\n必须选择两条多段线."));
			return;
		}
		
		// 获得两条多段线的交点
		bool bOk = false;
		AcDbPolyline *pPoly1 = NULL, *pPoly2 = NULL;
		if (acdbOpenObject(pPoly1, polyIds[0], AcDb::kForWrite) == Acad::eOk)
		{
			if (acdbOpenObject(pPoly2, polyIds[1], AcDb::kForWrite) == Acad::eOk)
			{
				AcGePoint3dArray intPoints;
				pPoly1->intersectWith(pPoly2, AcDb::kOnBothOperands, intPoints);
				if (intPoints.length() >= 2)
				{
					bOk = true;
				}
				else
				{
					acutPrintf("\n多段线之间交点少于2个, 无法进行计算.");
				}
				
				// 根据交点和参数值获得交点之间的曲线
				if (bOk)
				{
					GetCurveBetweenIntPoints(pPoly1, intPoints);
					GetCurveBetweenIntPoints(pPoly2, intPoints);

					pPoly2->erase();
				}

				pPoly2->close();
			}

			if (bOk)
			{
				pPoly1->erase();
			}

			pPoly1->close();
		}
	}
}

