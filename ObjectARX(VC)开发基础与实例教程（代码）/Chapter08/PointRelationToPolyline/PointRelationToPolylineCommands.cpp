//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Interaction\SelectUtil.h"
#include <dbpl.h>
#include "..\..\Common\Geometry\MathUtil.h"
#include "..\..\Common\Entity\PolylineUtil.h"
#include <dbents.h>
#include "..\..\Common\Document\DwgDatabaseUtil.h"

// This is command 'TESTPTINPOLY'
void ZffChap8TestPtInPoly()
{	
    int count = 100000;		// 随机点测试的数量
    // 提示用户选择一条多段线
	AcDbEntity *pEnt = NULL;
	AcGePoint3d pickPoint;
	if (CSelectUtil::PromptSelectEntity(TEXT("\n选择需要进行测试的闭合多段线:"), AcDbPolyline::desc(), pEnt, pickPoint))
	{
		// 在多段线包围框范围内随机生成点，测试点和多段线的位置关系
		AcDbExtents ext;
		pEnt->getGeomExtents(ext);
		double margin = 10;
		double xmin = ext.minPoint().x - margin;
		double ymin = ext.minPoint().y - margin;
		double xSpan = ext.maxPoint().x - ext.minPoint().x + 2 * margin;
		double ySpan = ext.maxPoint().y - ext.minPoint().y + 2 * margin;
		
		AcDbPolyline *pPoly = AcDbPolyline::cast(pEnt);
		srand((unsigned)time(NULL));
		for (int i = 0; i < count; i++)
		{
			// 在0～maxRand之间产生随机数
			int maxRand = 100000;
			int xRand = CMathUtil::GetRand(0, maxRand);
			int yRand = CMathUtil::GetRand(0, maxRand);
			
			double x = xmin + ((double)xRand / maxRand) * xSpan;
			double y = ymin + ((double)yRand / maxRand) * ySpan;
			int relation = CPolylineUtil::PtRelationToPoly(pPoly, AcGePoint2d(x, y), 1.0E-4);
			
			int colorIndex = 0;
			switch (relation)
			{
			case -1:
				colorIndex = 1;
				break;
			case 0:
				colorIndex = 5;
				break;
			case 1:
				colorIndex = 6;
				break;
			default:
				break;
			}
			AcDbPoint *pPoint = new AcDbPoint(AcGePoint3d(x, y, 0));
			pPoint->setColorIndex(colorIndex);
			CDwgDatabaseUtil::PostToModelSpace(pPoint);
		}

		pEnt->close();
	}
}

