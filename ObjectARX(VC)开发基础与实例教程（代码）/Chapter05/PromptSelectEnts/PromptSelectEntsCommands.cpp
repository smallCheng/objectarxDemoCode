//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Interaction\SelectUtil.h"
#include <dbents.h>

// This is command 'SELECTENT'
void ZffChap5SelectEnt()
{
	// 提示用户选择一个圆，将其颜色修改为红色
	AcDbEntity *pEnt = NULL;
	AcGePoint3d pickPoint;
	if (CSelectUtil::PromptSelectEntity(TEXT("\n选择圆:"), AcDbCircle::desc(), pEnt, pickPoint))
	{
		pEnt->setColorIndex(1);
		pEnt->close();
	}
}

// This is command 'SELECTENTS'
void ZffChap5SelectEnts()
{
	// 提示用户选择多个圆或直线，将其颜色修改为红色
	std::vector<AcRxClass*> descs;
	descs.push_back(AcDbLine::desc());
	descs.push_back(AcDbCircle::desc());
	AcDbObjectIdArray entIds;
	if (CSelectUtil::PromptSelectEnts(TEXT("\n选择圆和直线:"), descs, entIds))
	{
		for (int i = 0; i < entIds.length(); i++)
		{
			AcDbEntity *pEnt = NULL;
			if (acdbOpenObject(pEnt, entIds[i], AcDb::kForWrite) == Acad::eOk)
			{
				pEnt->setColorIndex(1);
				pEnt->close();
			}
		}
	}
}

