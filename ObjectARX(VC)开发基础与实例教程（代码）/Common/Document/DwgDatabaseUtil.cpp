// DwgDatabaseUtil.cpp: implementation of the CDwgDatabaseUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DwgDatabaseUtil.h"
#include <dbsymtb.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDwgDatabaseUtil::CDwgDatabaseUtil()
{

}

CDwgDatabaseUtil::~CDwgDatabaseUtil()
{

}

AcDbObjectId CDwgDatabaseUtil::PostToModelSpace( AcDbEntity *pEnt, AcDbDatabase *pDb )
{
	// 检查输入参数的有效性
	assert (pEnt);		// 等效于assert (pEnt != NULL);
	
	// 获得当前图形数据库的块表
	AcDbBlockTable *pBlkTbl = NULL;
	pDb->getBlockTable(pBlkTbl, AcDb::kForRead);
	
	// 获得模型空间对应的块表记录
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForWrite);
	pBlkTbl->close();
	
	// 将实体添加到模型空间的块表记录
	AcDbObjectId entId;
	Acad::ErrorStatus es = pBlkTblRcd->appendAcDbEntity(entId, pEnt);
	if (es != Acad::eOk)
	{
		pBlkTblRcd->close();
		delete pEnt;	// 添加失败时，要delete
		pEnt = NULL;
		
		return AcDbObjectId::kNull;
	}
	
	// 关闭模型空间块表记录和实体
	pBlkTblRcd->close();
	pEnt->close();
	
	return entId;
}

AcDbObjectIdArray CDwgDatabaseUtil::GetAllEntityIds( const TCHAR* layerName, AcDbDatabase *pDb )
{
	AcDbObjectIdArray entIds;		// 满足条件的实体集合
	bool bFilterLayer = false;			// 是否需要过滤图层
	AcDbObjectId layerId;
	// 获得指定图层的对象ID
	if (layerName != NULL)
	{
		AcDbLayerTable *pLayerTbl = NULL;
		acdbHostApplicationServices()->workingDatabase()
			->getSymbolTable(pLayerTbl, AcDb::kForRead);
		if (!pLayerTbl->has(layerName))
		{
			pLayerTbl->close();
			return entIds;
		}
		pLayerTbl->getAt(layerName, layerId);
		pLayerTbl->close();

		bFilterLayer = true;
	}
	
	// 获得块表
	AcDbBlockTable *pBlkTbl = NULL;
	pDb->getBlockTable(pBlkTbl, AcDb::kForRead);
	
	// 获得模型空间的块表记录
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForRead);
	pBlkTbl->close();
	
	// 创建遍历器，依次访问模型空间的每一个实体
	AcDbBlockTableRecordIterator *it = NULL;
	pBlkTblRcd->newIterator(it);
	for (it->start(); !it->done(); it->step())
	{
		AcDbEntity *pEnt = NULL;
		Acad::ErrorStatus es = it->getEntity(pEnt, AcDb::kForRead);
		if (es == Acad::eOk)
		{
			if (bFilterLayer)				// 过滤图层
			{
				if (pEnt->layerId() == layerId)
				{
					entIds.append(pEnt->objectId());
				}				
			}
			else
			{
				entIds.append(pEnt->objectId());
			}
			
			pEnt->close();
		}
		else
		{
			acutPrintf(TEXT("\nCDwgDatabaseUtil::GetAllEntityIds中打开实体失败(错误代码:%d)."), (int)es);
		}
	}
	delete it;
	pBlkTblRcd->close();
	
	return entIds;
}

AcDbExtents CDwgDatabaseUtil::GetModelSpaceExtent( AcDbDatabase *pDb )
{
	AcDbBlockTable *pBlkTbl = NULL;
	pDb->getBlockTable(pBlkTbl, AcDb::kForRead);
	
	// 获得模型空间的块表记录
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForRead);
	pBlkTbl->close();
	
	AcDbExtents extent;
	Acad::ErrorStatus es = extent.addBlockExt(pBlkTblRcd);
	pBlkTblRcd->close();
	
	// 如果图形数据库不是当前的工作数据库，有时候直接获取模型空间的范围会失败
	if (es != Acad::eOk)
	{
		AcDbObjectIdArray allEnts = GetAllEntityIds(NULL, pDb);
		for (int i = 0; i < allEnts.length(); i++)
		{
			AcDbEntity *pEnt = NULL;
			if (acdbOpenObject(pEnt, allEnts[i], AcDb::kForRead) == Acad::eOk)
			{
				AcDbExtents ext;
				if (pEnt->getGeomExtents(ext) == Acad::eOk)
				{
					extent.addExt(ext);
				}
				
				pEnt->close();
			}
		}
	}
	
	return extent;
}
