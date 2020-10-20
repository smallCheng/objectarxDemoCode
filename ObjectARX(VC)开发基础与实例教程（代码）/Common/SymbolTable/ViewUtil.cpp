// ViewUtil.cpp: implementation of the CViewUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ViewUtil.h"
#include <dbsymtb.h>
#include "..\Others\ConvertUtil.h"
#include <math.h>
#include "..\Document\DwgDatabaseUtil.h"
#include "..\..\..\..\..\..\Autodesk\ARX基础类库\inc\Common\Geometry\GePointUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CViewUtil::CViewUtil()
{

}

CViewUtil::~CViewUtil()
{

}

void CViewUtil::GetCurrentView( AcDbViewTableRecord &view )
{
	struct resbuf rb;
	struct resbuf wcs, ucs, dcs;	// 转换坐标时使用的坐标系统标记
	
	wcs.restype = RTSHORT;
	wcs.resval.rint = 0;
	ucs.restype = RTSHORT;
	ucs.resval.rint = 1;
	dcs.restype = RTSHORT;
	dcs.resval.rint = 2;
	
	// 获得当前视口的"查看"模式
	acedGetVar(TEXT("VIEWMODE"), &rb);
	view.setPerspectiveEnabled((rb.resval.rint & 1) != 0);
	view.setFrontClipEnabled((rb.resval.rint & 2) != 0);
	view.setBackClipEnabled((rb.resval.rint & 4) != 0);
	view.setFrontClipAtEye((rb.resval.rint & 16) == 0);
	
	// 当前视口中视图的中心点（UCS坐标）
	acedGetVar(TEXT("VIEWCTR"), &rb);
	acedTrans(rb.resval.rpoint, &ucs, &dcs, 0, rb.resval.rpoint);
	view.setCenterPoint(AcGePoint2d(rb.resval.rpoint[X], 
		rb.resval.rpoint[Y]));	
	
	// 当前视口透视图中的镜头焦距长度（单位为毫米）
	acedGetVar(TEXT("LENSLENGTH"), &rb);
	view.setLensLength(rb.resval.rreal);
	
	// 当前视口中目标点的位置（以 UCS 坐标表示）
	acedGetVar(TEXT("TARGET"), &rb);
	acedTrans(rb.resval.rpoint, &ucs, &wcs, 0, rb.resval.rpoint);
	view.setTarget(AcGePoint3d(rb.resval.rpoint[X], 
		rb.resval.rpoint[Y], rb.resval.rpoint[Z]));
	
	// 当前视口的观察方向（UCS）
	acedGetVar(TEXT("VIEWDIR"), &rb);
	acedTrans(rb.resval.rpoint, &ucs, &wcs, 1, rb.resval.rpoint);
	view.setViewDirection(AcGeVector3d(rb.resval.rpoint[X], 
						  rb.resval.rpoint[Y], rb.resval.rpoint[Z]));
	
	// 当前视口的视图高度（图形单位）
	acedGetVar(TEXT("VIEWSIZE"), &rb);
	view.setHeight(rb.resval.rreal);
	double height = rb.resval.rreal;
	
	// 以像素为单位的当前视口的大小（X 和 Y 值）
	acedGetVar(TEXT("SCREENSIZE"), &rb);
	view.setWidth(rb.resval.rpoint[X] / rb.resval.rpoint[Y] * height);
	
	// 当前视口的视图扭转角
	acedGetVar(TEXT("VIEWTWIST"), &rb);
	view.setViewTwist(rb.resval.rreal);
	
	// 将模型选项卡或最后一个布局选项卡置为当前
	acedGetVar(TEXT("TILEMODE"), &rb);
	int tileMode = rb.resval.rint;
	// 设置当前视口的标识码
	acedGetVar(TEXT("CVPORT"), &rb);
	int cvport = rb.resval.rint;
	
	// 是否是模型空间的视图
	bool paperspace = ((tileMode == 0) && (cvport == 1)) ? true : false;
	view.setIsPaperspaceView(paperspace);
	
	if (!paperspace)
	{
		// 当前视口中前向剪裁平面到目标平面的偏移量
		acedGetVar(TEXT("FRONTZ"), &rb);
		view.setFrontClipDistance(rb.resval.rreal);
		
		// 获得当前视口后向剪裁平面到目标平面的偏移值
		acedGetVar(TEXT("BACKZ"), &rb);
		view.setBackClipDistance(rb.resval.rreal);
	}
	else
	{
		view.setFrontClipDistance(0.0);
		view.setBackClipDistance(0.0);
	}
}

void CViewUtil::Set( const AcGePoint3d &ptMin, const AcGePoint3d &ptMax, double scale )
{
	AcDbViewTableRecord view;
	GetCurrentView(view);

	// 将参数的两个点从世界坐标系转换到显示坐标系
	AcGePoint3d ptMinDcs = CConvertUtil::WcsToDcsPoint(ptMin);
	AcGePoint3d ptMaxDcs = CConvertUtil::WcsToDcsPoint(ptMax);
	
	// 设置视图的中心点
	view.setCenterPoint(AcGePoint2d((ptMinDcs.x + ptMaxDcs.x) / 2, (ptMinDcs.y + ptMaxDcs.y) / 2));
	
	// 设置视图的高度和宽度
	view.setHeight(fabs(ptMinDcs.y - ptMaxDcs.y) * scale);
	view.setWidth(fabs(ptMinDcs.x - ptMaxDcs.x) * scale);
	
	// 将视图对象设置为当前视图
	acedSetCurrentView(&view, NULL);
}

void CViewUtil::SetCenter( const AcGePoint3d &center )
{
	AcDbViewTableRecord view;
	GetCurrentView(view);
	
	// 将参数的点从世界坐标系转换到显示坐标系
	AcGePoint3d centerDcs = CConvertUtil::WcsToDcsPoint(center);
	
	// 设置视图的中心点
	view.setCenterPoint(CConvertUtil::ToPoint2d(centerDcs));
	
	// 将视图对象设置为当前视图
	acedSetCurrentView(&view, NULL);
}

void CViewUtil::ZoomExtent()
{
	// 获得当前图形中所有实体的最小包围盒
	AcDbBlockTable *pBlkTbl;
	AcDbBlockTableRecord *pBlkTblRcd;
	acdbHostApplicationServices()->workingDatabase()
		->getBlockTable(pBlkTbl, AcDb::kForRead);
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForRead);
	pBlkTbl->close();
	
	AcDbExtents extent;		// 模型空间的包围盒
	extent.addBlockExt(pBlkTblRcd);
	pBlkTblRcd->close();
	
	// 包围盒是长方体，长方体被变换到DCS中之后每个顶点都有可能是最大、最小角点
	AcGePoint3dArray verts;
	verts.append(extent.minPoint());
	verts.append(AcGePoint3d(extent.maxPoint().x, extent.minPoint().y, extent.minPoint().z));
	verts.append(AcGePoint3d(extent.maxPoint().x, extent.maxPoint().y, extent.minPoint().z));
	verts.append(AcGePoint3d(extent.minPoint().x, extent.maxPoint().y, extent.minPoint().z));
	verts.append(AcGePoint3d(extent.minPoint().x, extent.minPoint().y, extent.maxPoint().z));
	verts.append(AcGePoint3d(extent.maxPoint().x, extent.minPoint().y, extent.maxPoint().z));
	verts.append(extent.maxPoint());
	verts.append(AcGePoint3d(extent.minPoint().x, extent.maxPoint().y, extent.maxPoint().z));
	
	// 将长方体的所有角点转移到DCS中
	for (int i = 0; i < verts.length(); i++)
	{
		verts[i] = CConvertUtil::WcsToDcsPoint(verts[i]);
	}
	
	// 获得所有角点在DCS中最小的包围矩形
	double xmin = 1.0E30, ymin = 1.0E30;
	double xmax = -1.0E30, ymax = -1.0E30;
	for (i = 0; i < verts.length(); i++)
	{
		xmin = min(xmin, verts[i].x);
		ymin = min(ymin, verts[i].y);
		xmax = max(xmax, verts[i].x);
		ymax = max(ymax, verts[i].y);
	}
	
	AcDbViewTableRecord view;
	GetCurrentView(view);
	
	// 设置视图的中心点
	view.setCenterPoint(AcGePoint2d((xmin + xmax) / 2, (ymin + ymax) / 2));
	
	// 设置视图的高度和宽度
	view.setHeight(fabs(ymax - ymin));
	view.setWidth(fabs(xmax - xmin));
	
	// 将视图对象设置为当前视图
	Acad::ErrorStatus es = acedSetCurrentView(&view, NULL);
}

void CViewUtil::DwgZoomExtent( AcDbDatabase *pDb )
{
	assert (pDb);
	
	// 获得模型空间所有实体的最小包围框
	AcDbExtents ext = CDwgDatabaseUtil::GetModelSpaceExtent(pDb);
	
	AcDbViewportTable* pViewportTable = NULL;
	if (pDb->getViewportTable(pViewportTable, AcDb::kForWrite) == Acad::eOk)
	{
		AcDbViewportTableRecord *pRecord = NULL;
		if (pViewportTable->getAt(TEXT("*ACTIVE"), pRecord, AcDb::kForWrite) == Acad::eOk)
		{
			AcGePoint3d center = CGePointUtil::GetMiddlePoint(ext.minPoint(), ext.maxPoint());
			double height = ext.maxPoint().y - ext.minPoint().y;
			double width = ext.maxPoint().x - ext.minPoint().x;
			pRecord->setCenterPoint(CConvertUtil::ToPoint2d(center));
			pRecord->setHeight(height * 1.2);
			pRecord->setWidth(width * 1.2);
			pRecord->close();
		}				
		pViewportTable->close();
	}
}
