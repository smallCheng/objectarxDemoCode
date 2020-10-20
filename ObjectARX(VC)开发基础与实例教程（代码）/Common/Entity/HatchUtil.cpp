// HatchUtil.cpp: implementation of the CHatchUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HatchUtil.h"
#include <dbhatch.h>
#include "..\Document\DwgDatabaseUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHatchUtil::CHatchUtil()
{

}

CHatchUtil::~CHatchUtil()
{

}

AcDbObjectId CHatchUtil::Add( const AcDbObjectIdArray &loopIds, const TCHAR* patName, double patternScale )
{
	Acad::ErrorStatus es;
	AcDbHatch *pHatch = new AcDbHatch();
	
	// 设置填充平面
	AcGeVector3d normal(0, 0, 1);
	pHatch->setNormal(normal);
	pHatch->setElevation(0);
	
	// 设置关联性
	pHatch->setAssociative(true);
	
	// 设置填充图案
	pHatch->setPattern(AcDbHatch::kPreDefined, patName);
	
	// 添加填充边界
	es = pHatch->appendLoop(AcDbHatch::kExternal, loopIds);
	
	// 显示填充对象
	es = pHatch->evaluateHatch();	
	
	// 添加到模型空间
	AcDbObjectId hatchId = CDwgDatabaseUtil::PostToModelSpace(pHatch);
	
	// 如果是关联性的填充，将填充对象与边界绑定，以便使其能获得边界对象修改的通知
	if (acdbOpenObject(pHatch, hatchId, AcDb::kForRead) == Acad::eOk)
	{
		AcDbObjectIdArray assocEntIds;
		pHatch->getAssocObjIds(assocEntIds);
		for (int i = 0; i < assocEntIds.length(); i++)
		{
			AcDbEntity *pEnt = NULL;
			if (acdbOpenObject(pEnt, assocEntIds[i], AcDb::kForWrite) == Acad::eOk)
			{
				// 添加一个永久反应器
				pEnt->addPersistentReactor(hatchId);
				pEnt->close();
			}
		}
		
		pHatch->close();
	}
	
	return hatchId;
}
