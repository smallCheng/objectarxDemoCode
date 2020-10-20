//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Interaction\SelectUtil.h"
#include "..\..\Common\Interaction\GetInputUtil.h"
#include "ArcBlockJig.h"
#include <dbents.h>

// This is command 'ARCBLOCKJIG'
void ZffChap5ArcBlockJig()
{
	// 选择一个块参照，用于沿圆弧插入
	AcDbEntity *pEnt = NULL;
	AcDbObjectId blkDefId;
	AcGePoint3d pickPoint;
	if (CSelectUtil::PromptSelectEntity(TEXT("\n选择一个块参照用于沿圆弧插入:"), AcDbBlockReference::desc(), pEnt, pickPoint))
	{
		AcDbBlockReference *pBlkRef = AcDbBlockReference::cast(pEnt);
		blkDefId = pBlkRef->blockTableRecord();
		pEnt->close();
	}
	if (blkDefId.isNull())
	{
		return;
	}

	// 提示用户拾取第一点
	AcGePoint3d startPoint;
	if (!CGetInputUtil::GetPoint(TEXT("\n拾取第一点:"), startPoint))
	{
		return;
	}

	// 提示用户拾取第二点
	AcGePoint3d secondPoint;
	if (!CGetInputUtil::GetPoint(startPoint, TEXT("\n拾取第二点:"), secondPoint))
	{
		return;
	}

	// 开始拖动
	CArcBlockJig jig;
	int blockCount = 4;
	jig.doIt(startPoint, secondPoint, secondPoint, blkDefId, blockCount);
}

