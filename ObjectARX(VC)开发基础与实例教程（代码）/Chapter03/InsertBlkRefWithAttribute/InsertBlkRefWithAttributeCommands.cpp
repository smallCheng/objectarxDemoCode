//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include <dbsymtb.h>
#include <geassign.h>
#include <dbents.h>
#include "..\..\Common\Document\DwgDatabaseUtil.h"
#include <acutmem.h>
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

	// 插入块参照（属性值使用默认值）
	AcDbObjectId blkRefId = CBlockUtil::InsertBlockRefWithAttribute(blkDefId, ptInsert, 1, 0);

	// 设置参数值
	AcDbBlockReference *pBlkRef = NULL;
	if (acdbOpenObject(pBlkRef, blkRefId, AcDb::kForWrite) == Acad::eOk)
	{
		CBlockUtil::SetBlockRefAttribute(pBlkRef, TEXT("名称"), TEXT("矩形板"));
		CBlockUtil::SetBlockRefAttribute(pBlkRef, TEXT("重量"), TEXT("2.3Kg"));
		pBlkRef->close();
	}
}

