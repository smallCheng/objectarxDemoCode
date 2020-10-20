//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include <dbsymtb.h>
#include <AcDbLMgr.h>
#include <dbents.h>

// This is command 'CREATE4VPORTS'
void ZffChap4Create4VPorts()
{
	// 获得视口表
	AcDbViewportTable *pVPortTbl = NULL;
	acdbHostApplicationServices()->workingDatabase()
		->getViewportTable(pVPortTbl, AcDb::kForWrite);
	
	// 分别创建四个视口
	AcGePoint2d pt1, pt2;
	AcDbViewportTableRecord *pVPortTblRcd1 = new AcDbViewportTableRecord;
	pt1.set(0, 0);
	pt2.set(0.5, 0.5);
	pVPortTblRcd1->setLowerLeftCorner(pt1);
	pVPortTblRcd1->setUpperRightCorner(pt2);
	pVPortTblRcd1->setName(TEXT("4VPorts"));
	
	AcDbViewportTableRecord *pVPortTblRcd2 = new AcDbViewportTableRecord;
	pt1.set(0.5, 0);
	pt2.set(1, 0.5);
	pVPortTblRcd2->setLowerLeftCorner(pt1);
	pVPortTblRcd2->setUpperRightCorner(pt2);
	pVPortTblRcd2->setName(TEXT("4VPorts"));
	
	AcDbViewportTableRecord *pVPortTblRcd3 = new AcDbViewportTableRecord;
	pt1.set(0, 0.5);
	pt2.set(0.5, 1);
	pVPortTblRcd3->setLowerLeftCorner(pt1);
	pVPortTblRcd3->setUpperRightCorner(pt2);
	pVPortTblRcd3->setName("4VPorts");
	
	AcDbViewportTableRecord *pVPortTblRcd4 = new AcDbViewportTableRecord;
	pt1.set(0.5, 0.5);
	pt2.set(1, 1);
	pVPortTblRcd4->setLowerLeftCorner(pt1);
	pVPortTblRcd4->setUpperRightCorner(pt2);
	pVPortTblRcd4->setName(TEXT("4VPorts"));	
	
	pVPortTbl->add(pVPortTblRcd1);
	pVPortTbl->add(pVPortTblRcd2);
	pVPortTbl->add(pVPortTblRcd3);
	pVPortTbl->add(pVPortTblRcd4);
	
	pVPortTbl->close();	
	pVPortTblRcd1->close();
	pVPortTblRcd2->close();
	pVPortTblRcd3->close();
	pVPortTblRcd4->close();
	
	// 判断当前的空间
	struct resbuf rb;
	acedGetVar(TEXT("TILEMODE"), &rb);
	if (rb.resval.rint == 1)		// 当前工作空间是模型空间
	{
		acedCommand(RTSTR, TEXT(".-VPORTS"), RTSTR, TEXT("R"), 
			RTSTR, TEXT("4VPorts"), RTNONE);
	}
	else							// 当前工作空间是图纸空间
	{
		acedCommand(RTSTR, TEXT(".-VPORTS"), RTSTR, TEXT("R"), 
			RTSTR, TEXT("4VPorts"), RTSTR, TEXT(""), RTNONE);
	}
}

// This is command 'CREATEVPORTINSPACE'
void ZffChap4CreateVPortInSpace()
{
	// 指定当前布局
	Acad::ErrorStatus es = acdbHostApplicationServices()->layoutManager()
		->setCurrentLayout(TEXT("布局1"));	
	if (es != Acad::eOk)
	{
		return;
	}
	
	// 获得块表
	AcDbBlockTable *pBlkTbl = NULL;
	acdbHostApplicationServices()->workingDatabase()
		->getBlockTable(pBlkTbl, AcDb::kForRead);
	
	// 获得图纸空间的块表记录
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	pBlkTbl->getAt(ACDB_PAPER_SPACE, pBlkTblRcd, AcDb::kForWrite);
	pBlkTbl->close();
	
	// 创建新的布局对象
	AcDbViewport *pViewport = new AcDbViewport();
	pViewport->setCenterPoint(AcGePoint3d(100, 50, 0));
	pViewport->setHeight(80);
	pViewport->setWidth(120);	
	
	// 将新的布局对象添加到图纸空间块表记录中
	AcDbObjectId viewportId;
	pBlkTblRcd->appendAcDbEntity(viewportId, pViewport);
	
	pViewport->close();
	pBlkTblRcd->close();
	
	// 将新建的视口作为当前视口
	AcDbViewport *pVP = NULL;
	if (acdbOpenObject(pVP, viewportId, AcDb::kForWrite) == Acad::eOk)
	{
		pViewport->setOn();
		acedSetCurrentVPort(pVP);
		pVP->close();
	}	
}

