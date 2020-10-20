//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "DrawSquareJig.h"
#include "..\..\Common\Interaction\GetInputUtil.h"
#include "..\..\Common\Entity\EntityUtil.h"

// This is command 'DRAWSEQUAREJIG'
void ZfgkBJDrawSequareJig()
{
	// 提示用户输入中心点
	AcGePoint3d centerPoint;
	if (CGetInputUtil::GetPoint(TEXT("\n指定正方形的中心点:"), centerPoint))
	{
		// 进入拖动状态
		CDrawSquareJig jig;
		AcDbObjectId polyId;
		if (jig.doIt(centerPoint, polyId))
		{
			// 成功创建之后，可以进行其他的修改
			CEntityUtil::SetColor(polyId, 1);
		}
		else
		{
			// 用户取消，删除已经创建的实体
			CEntityUtil::Erase(polyId);
		}
	}	
}

