//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include <dbsymtb.h>
#include <geassign.h>
#include <dbents.h>
#include "..\..\Common\Document\DwgDatabaseUtil.h"
#include "..\..\Common\Entity\BlockUtil.h"

// This is command 'INSERTBLK'
void ZffChap3InsertBlk()
{
	// 获得用户输入的块定义名称	
	TCHAR blkName[40];
	if (acedGetString(Adesk::kFalse, TEXT("\n输入图块的名称:"), blkName) != RTNORM)
	{			
		return;
	}	
	
	// 获得当前数据库的块表
	AcDbBlockTable *pBlkTbl = NULL;
	acdbHostApplicationServices()->workingDatabase()
		->getBlockTable(pBlkTbl, AcDb::kForWrite);
	
	// 查找用户指定的块定义是否存在
	CString strBlkDef;
	strBlkDef.Format(TEXT("%s"), blkName);
	if (!pBlkTbl->has(strBlkDef))
	{
		acutPrintf(TEXT("\n当前图形中未包含指定名称的块定义!"));
		pBlkTbl->close();
		return;
	}
	
	// 获得用户输入的块参照的插入点
	ads_point pt;
	if (acedGetPoint(NULL, TEXT("\n输入块参照的插入点:"), pt) != RTNORM)
	{	
		pBlkTbl->close();
		return;
	}
	AcGePoint3d ptInsert = asPnt3d(pt);
	
	// 获得用户指定的块表记录	
	AcDbObjectId blkDefId;
	pBlkTbl->getAt(strBlkDef, blkDefId);
	pBlkTbl->close();
	
	// 创建块参照对象
	AcDbBlockReference *pBlkRef = new AcDbBlockReference(ptInsert, blkDefId);
	
	// 将块参照添加到模型空间
	CDwgDatabaseUtil::PostToModelSpace(pBlkRef);	
}

// This is command 'INSERTBLK2'
void ZffCHAP3InsertBlk2()
{
	// 获得用户输入的块定义名称	
	TCHAR blkName[40];
	if (acedGetString(Adesk::kFalse, TEXT("\n输入图块的名称:"), blkName) != RTNORM)
	{			
		return;
	}	
	
	// 查找用户指定的块定义是否存在
	AcDbObjectId blkDefId = CBlockUtil::GetBlkDefId(blkName);
	if (blkDefId.isNull())
	{
		acutPrintf(TEXT("\n当前图形中未包含指定名称的块定义!"));
		return;
	}
	
	// 获得用户输入的块参照的插入点
	ads_point pt;
	if (acedGetPoint(NULL, TEXT("\n输入块参照的插入点:"), pt) != RTNORM)
	{		
		return;
	}
	AcGePoint3d ptInsert = asPnt3d(pt);
	
	// 创建块参照对象
	AcDbBlockReference *pBlkRef = new AcDbBlockReference(ptInsert, blkDefId);
	
	// 将块参照添加到模型空间
	CDwgDatabaseUtil::PostToModelSpace(pBlkRef);
}

