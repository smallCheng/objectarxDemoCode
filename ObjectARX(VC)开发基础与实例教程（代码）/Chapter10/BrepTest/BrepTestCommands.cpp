//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Interaction\SelectUtil.h"
#include <dbsol3d.h>
#include <brbrep.h>
#include <brbftrav.h>
#include <brface.h>
#include <gexbndsf.h>
#include <gecylndr.h>
#include <brbetrav.h>
#include <bredge.h>
#include <geextc3d.h>
#include "..\..\Common\Entity\PolylineUtil.h"

// This is command 'GETCYLINDERINFO'
void ZffChap10GetCylinderInfo()
{
	// 提示用户选择实体
	AcDbEntity *pEnt = NULL;
	AcGePoint3d pickPoint;
	if (CSelectUtil::PromptSelectEntity(TEXT("\n选择三维实体:"), AcDb3dSolid::desc(), pEnt, pickPoint))
	{
		// 建立一个brep对象
		AcBrBrep brepEnt;
		brepEnt.set(*pEnt);

		// 创建一个面的遍历器
		AcBr::ErrorStatus returnValue = AcBr::eOk;
		AcBrBrepFaceTraverser brepFaceTrav;
		returnValue = brepFaceTrav.setBrep(brepEnt);

		// 遍历面
		while (!brepFaceTrav.done() && (returnValue == AcBr::eOk))
		{
			// 获得面对象
			AcBrFace brFace;
			AcBr::ErrorStatus es =	brepFaceTrav.getFace(brFace);
			if (es == AcBr::eOk)
			{
				// 获得几何面对象
				AcGeSurface* pAcGeSurface;
				brFace.getSurface(pAcGeSurface);
				
				// 转换成边界面对象
				AcGeExternalBoundedSurface* ebSurf = (AcGeExternalBoundedSurface*)pAcGeSurface;
				if (ebSurf != NULL && ebSurf->isCylinder())
				{
					AcGeCylinder* pCylinder = (AcGeCylinder*)ebSurf;
					acutPrintf(TEXT("\n圆柱面信息:"));
					acutPrintf(TEXT("\n半径:%.2f"), pCylinder->radius());
					AcGePoint3d center = pCylinder->origin();
					acutPrintf(TEXT("\n中心点:(%.2f, %.2f, %.2f)"), center.x, center.y, center.z);
					AcGeVector3d axis = pCylinder->axisOfSymmetry();
					acutPrintf(TEXT("\n轴线向量:(%.2f, %.2f, %.2f)"), axis.x, axis.y, axis.z);
				}
				delete pAcGeSurface;
			}
			returnValue = brepFaceTrav.next();
		}

		pEnt->close();
	}
}

// This is command 'GETBOUNDAYCURVES'
void ZffChap10GetBoundayCurves()
{
	// 提示用户选择实体
	AcDbEntity *pEnt = NULL;
	AcGePoint3d pickPoint;
	if (CSelectUtil::PromptSelectEntity(TEXT("\n选择三维实体:"), AcDb3dSolid::desc(), pEnt, pickPoint))
	{
		// 建立一个brep对象
		AcBrBrep brepEnt;
		brepEnt.set(*pEnt);
		
		// 建立一个边的遍历器
		AcBrBrepEdgeTraverser brepEdgeTrav;
		AcBr::ErrorStatus returnValue = brepEdgeTrav.setBrep(brepEnt);
		if (returnValue == AcBr::eOk) 
		{
			while (!brepEdgeTrav.done() && (returnValue == AcBr::eOk)) 
			{
				// 获取当前边的信息
				AcBrEdge brEdge;
				brepEdgeTrav.getEdge(brEdge);
				AcGeCurve3d *pGeCurve = NULL;
				if (brEdge.getCurve(pGeCurve) == AcBr::eOk)
				{
					// 将边转换为普通的几何曲线
					AcGeCurve3d *pNativeCurve = NULL;
					Adesk::Boolean bRet = ((AcGeExternalCurve3d*)pGeCurve)->isNativeCurve(pNativeCurve);

					int numSample = 180;	// 简化操作，直接等分为180份
					AcGePoint3dArray points;
					pNativeCurve->getSamplePoints(numSample, points);
					if (pNativeCurve->isClosed() && points.length() > 0)
					{
						points.append(points[0]);
					}
					delete pNativeCurve;
					delete pGeCurve;
					
					if (points.length() > 2)
					{
						CPolylineUtil::Add3dPolyline(points);
					}
				}
				
				returnValue = brepEdgeTrav.next();				
			} 
		}

		pEnt->close();
	}
}

