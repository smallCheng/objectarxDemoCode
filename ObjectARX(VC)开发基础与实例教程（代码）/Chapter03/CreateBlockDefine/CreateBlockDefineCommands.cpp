//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include <dbsymtb.h>
#include <dbents.h>

// This is command 'ADDBLK'
void ZffChap3AddBlk()
{
	// 获得当前图形数据库的块表
	AcDbBlockTable *pBlkTbl = NULL;
	acdbHostApplicationServices()->workingDatabase()
		->getBlockTable(pBlkTbl, AcDb::kForWrite);
	
	// 创建新的块表记录
	AcDbBlockTableRecord *pBlkTblRcd = new AcDbBlockTableRecord();
	
	// 根据用户的输入设置块表记录的名称
	TCHAR blkName[40];
	if (acedGetString(Adesk::kFalse, TEXT("\n输入图块的名称:"), blkName) != RTNORM)
	{
		pBlkTbl->close();
		delete pBlkTblRcd;
		return;
	}
	pBlkTblRcd->setName(blkName);
	
	// 将块表记录添加到块表中
	AcDbObjectId blkDefId;
	pBlkTbl->add(blkDefId, pBlkTblRcd);
	pBlkTbl->close();
	
	// 向块表记录中添加实体
	AcGePoint3d ptStart(-10, 0, 0), ptEnd(10, 0, 0);
	AcDbLine *pLine1 = new AcDbLine(ptStart, ptEnd);	// 创建一条直线
	ptStart.set(0, -10, 0);
	ptEnd.set(0, 10, 0);
	AcDbLine *pLine2 = new AcDbLine(ptStart, ptEnd);	// 创建一条直线
	AcGeVector3d vecNormal(0, 0, 1);
	AcDbCircle *pCircle = new AcDbCircle(AcGePoint3d::kOrigin, vecNormal, 6);
	
	AcDbObjectId entId;
	pBlkTblRcd->appendAcDbEntity(entId, pLine1);
	pBlkTblRcd->appendAcDbEntity(entId, pLine2);
	pBlkTblRcd->appendAcDbEntity(entId, pCircle);
	
	// 关闭实体和块表记录
	pLine1->close();
	pLine2->close();
	pCircle->close();
	pBlkTblRcd->close();
}

