//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Entity\HatchUtil.h"

// This is command 'ADDHATCH'
void ZffChap2AddHatch()
{
	// 提示用户选择填充边界
	ads_name ss;
	int rt = acedSSGet(NULL, NULL, NULL, NULL, ss);
	AcDbObjectIdArray objIds;
	
	// 初始化填充边界的ID数组
	if (rt == RTNORM)
	{		
		long length;
		acedSSLength(ss, &length);
		for (int i = 0; i < length; i++)
		{
			ads_name ent;
			acedSSName(ss, i, ent);
			AcDbObjectId objId;
			acdbGetObjectId(objId, ent);
			
			objIds.append(objId);
		}
	}
	acedSSFree(ss);			// 释放选择集
	
	CHatchUtil::Add(objIds, TEXT("SOLID"), 1.0);	
}

