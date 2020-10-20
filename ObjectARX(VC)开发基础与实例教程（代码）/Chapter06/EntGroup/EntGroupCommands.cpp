//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Interaction\SelectUtil.h"
#include <dbgroup.h>
#include <dbdict.h>

// This is command 'ADDGROUP'
void ZffChap6AddGroup()
{
	// 提示用户选择多个实体
	AcDbObjectIdArray entIds;
	if (CSelectUtil::PromptSelectEnts(TEXT("\n选择要成组的实体:"), AcDbEntity::desc(), entIds))
	{
		// 创建组
		AcDbGroup *pGroup = new AcDbGroup();
		for (int i = 0; i < entIds.length(); i++) 
		{
			pGroup->append(entIds[i]);
		}
		
		// 将组添加到有名对象字典的组字典中
		AcDbDictionary *pGroupDict = NULL;
		acdbHostApplicationServices()->workingDatabase()
			->getGroupDictionary(pGroupDict, AcDb::kForWrite);
		
		// （如果组名为*，会创建匿名组)
		CString groupName = TEXT("*");
		AcDbObjectId groupId;
		pGroupDict->setAt(groupName, pGroup, groupId);
		pGroupDict->close();
		pGroup->close();
	}
}

// This is command 'DELETEGROUP'
void ZffChap6DeleteGroup()
{
	AcDbObjectIdArray entIds;
	if (CSelectUtil::PromptSelectEnts(TEXT("\n选择要分解的组中的实体:"), AcDbEntity::desc(), entIds))
	{
		// 遍历组字典，判断是否包含了给定的实体
		AcDbDictionary *pGroupDict = NULL;
		acdbHostApplicationServices()->workingDatabase()->getGroupDictionary(pGroupDict, AcDb::kForWrite);
		AcDbDictionaryIterator *it = pGroupDict->newIterator();
		for (; !it->done(); it->next())
		{
			AcDbGroup *pGroup = NULL;
			if (it->getObject((AcDbObject*&)pGroup, AcDb::kForWrite) == Acad::eOk)
			{
				AcDbObjectIdArray groupEntIds;
				pGroup->allEntityIds(groupEntIds);
				bool bFound = false;
				for (int i = 0; i < entIds.length(); i++)
				{
					if (groupEntIds.contains(entIds[i]))
					{
						bFound = true;
						break;
					}
				}
				// 删除包含选择集中实体的组
				if (bFound)
				{
					pGroup->erase();
				}
				
				pGroup->close();
			}
		}		
		pGroupDict->close();
	}
}

