// SelectUtil.cpp: implementation of the CSelectUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SelectUtil.h"
#include <math.h>
#include "..\Document\DwgDatabaseUtil.h"
#include "..\Geometry\GeRectangleUtil.h"
#include "..\Others\ConvertUtil.h"
#include <geassign.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSelectUtil::CSelectUtil()
{

}

CSelectUtil::~CSelectUtil()
{

}

void CSelectUtil::GetEntityInRectangle( const AcGePoint2d &firstPoint, const AcGePoint2d &secondPoint, AcDbObjectIdArray &entIds )
{
	// 1.参数有效性检查
	// 1.1 点不能构成一条直线或重合
	assert (fabs(firstPoint.x - secondPoint.x) > 1.0E-7 || fabs(firstPoint.y - secondPoint.y) > 1.0E-7);
	
	// 2.遍历模型空间获得满足条件的实体
	AcDbObjectIdArray allEntIds = CDwgDatabaseUtil::GetAllEntityIds();
	for (int i = 0; i < allEntIds.length(); i++)
	{
		// 利用遍历器获得每一个实体
		AcDbEntity *pEnt = NULL;
		if (acdbOpenObject(pEnt, allEntIds[i], AcDb::kForRead) == Acad::eOk)
		{
			AcDbExtents extent;
			pEnt->getGeomExtents(extent);
			
			// 如果实体的外包围框和给定矩形相交，就将这个实体添加到数组中
			AcGePoint2d extMinPoint = CConvertUtil::ToPoint2d(extent.minPoint());
			AcGePoint2d extMaxPoint = CConvertUtil::ToPoint2d(extent.maxPoint());
			if (CGeRectangleUtil::IntersectWithRectangle(extMinPoint, extMaxPoint, firstPoint, secondPoint))
			{
				entIds.append(pEnt->objectId());
			}			
			
			pEnt->close();
		}
	}
}

bool CSelectUtil::PromptSelectEnts( const TCHAR* prompt, struct resbuf *rb, AcDbObjectIdArray &entIds )
{
	entIds.setLogicalLength(0);

	bool bRet = false;
	ads_name sset;
	acutPrintf(prompt);
	int rc = acedSSGet(NULL, NULL, NULL, rb, sset);
	
	if (rc == RTNORM)
	{		
		long length = 0;
		acedSSLength(sset, &length);
		
		for (int i = 0; i < length; i++)
		{
			ads_name ename;
			acedSSName(sset, i, ename);
			
			AcDbObjectId entId;
			acdbGetObjectId(entId, ename);
			entIds.append(entId);
		}
		
		bRet = true;
	}
	
	acedSSFree(sset);
	
	return bRet;
}

bool CSelectUtil::PromptSelectEnts( const TCHAR* prompt, AcRxClass* classDesc, AcDbObjectIdArray &entIds )
{
	std::vector<AcRxClass*> vecClassDesc;
	vecClassDesc.push_back(classDesc);
	
	return PromptSelectEnts(prompt, vecClassDesc, entIds);
}

bool CSelectUtil::PromptSelectEnts( const TCHAR* prompt, const std::vector<AcRxClass*> &classDescs, AcDbObjectIdArray &entIds )
{
	// 初始化
	entIds.setLogicalLength(0);
	
	// 提示用户选择实体
	ads_name sset;
	int result = 0;
	acutPrintf(prompt);
	result = acedSSGet(NULL, NULL, NULL, NULL, sset);
	
	if (result != RTNORM)
	{
		return false;
	}
	
	// 取得选择集的长度
	long length = 0;
	acedSSLength(sset, &length);
	
	// 遍历选择集
	Acad::ErrorStatus es;
	AcDbEntity* pEnt = NULL;
	for (long i = 0; i < length; i++)
	{
		ads_name ename;
		acedSSName(sset, i, ename);
		
		AcDbObjectId curEntId;
		es = acdbGetObjectId(curEntId, ename);
		if (es != Acad::eOk)
		{
			continue;
		}
		
		// 打开实体
		es = acdbOpenObject(pEnt, curEntId, AcDb::kForRead);
		if (es != Acad::eOk)
		{
			continue;
		}
		
		// 判断当前实体是否是指定的实体类型
		for (int j = 0; j < (int)classDescs.size(); j++)
		{
			if (pEnt->isKindOf(classDescs[j]))
			{
				entIds.append(pEnt->objectId());				
				break;
			}
		}
		
		pEnt->close();	// 关闭实体
	}
	acedSSFree(sset);	// 释放选择集

	return (entIds.length() > 0);
}

bool CSelectUtil::PromptSelectEntity( const TCHAR* prompt, AcRxClass* classDesc, AcDbEntity *&pEnt, 
									 AcGePoint3d &pickPoint, bool bOpenForWrite /*= true*/ )
{
	std::vector<AcRxClass*> descs;
	descs.push_back(classDesc);

	return PromptSelectEntity(prompt, descs, pEnt, pickPoint, bOpenForWrite);
}

bool CSelectUtil::PromptSelectEntity( const TCHAR* prompt, const std::vector<AcRxClass*> &classDescs, AcDbEntity *&pEnt, 
									 AcGePoint3d &pickPoint, bool bOpenForWrite /*= true*/ )
{
	ads_name ename;
RETRY:
	if (acedEntSel(prompt, ename, asDblArray(pickPoint)) != RTNORM)
	{
		pEnt = NULL;
		return false;
	}
	
	AcDbObjectId entId;
	acdbGetObjectId(entId, ename);
	
	// 判断选择的实体是否是指定类型的实体
	Acad::ErrorStatus es;
	if (bOpenForWrite)
	{
		es = acdbOpenObject(pEnt, entId, AcDb::kForWrite);
	}
	else
	{
		es = acdbOpenObject(pEnt, entId, AcDb::kForRead);
	}
	assert (es == Acad::eOk);
	bool bRet = false;
	for (int i = 0; i < (int)classDescs.size(); i++)
	{
		if (pEnt->isKindOf(classDescs[i]))
		{			
			bRet = true;
			break;
		}
	}
	
	if (bRet)
	{
		return true;
	}
	else
	{
		pEnt->close();
		acutPrintf(TEXT("\n选择的实体类型不合要求, 请再次选择..."));
		goto RETRY;
	}
}
