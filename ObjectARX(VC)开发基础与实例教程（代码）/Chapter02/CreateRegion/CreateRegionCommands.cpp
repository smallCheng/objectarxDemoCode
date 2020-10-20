//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Entity\RegionUtil.h"

// This is command 'ADDREGION'
void ZffChap2AddRegion()
{
	// 使用选择集，提示用户选择作为面域边界的对象
	ads_name ss;
	int rt = acedSSGet(NULL, NULL, NULL, NULL, ss);		// 提示用户选择对象	
	
	// 根据选择集中的对象构建边界曲线的ID数组
	AcDbObjectIdArray objIds;
	if (rt == RTNORM)
	{		
		long length;
		acedSSLength(ss, &length);		// 获得选择集中的对象个数
		for (int i = 0; i < length; i++)
		{
			ads_name ent;
			acedSSName(ss, i, ent);
			AcDbObjectId objId;
			acdbGetObjectId(objId, ent);
			
			objIds.append(objId);
		}
	}
	acedSSFree(ss);			// 及时释放选择集
	
	AcDbObjectIdArray regionIds;
	regionIds = CRegionUtil::Add(objIds);
	
	int number = regionIds.length();
	acutPrintf("\n已经创建%d个面域.", number);
}

