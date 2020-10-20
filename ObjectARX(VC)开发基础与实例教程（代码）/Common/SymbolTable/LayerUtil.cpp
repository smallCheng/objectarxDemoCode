// LayerUtil.cpp: implementation of the CLayerUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LayerUtil.h"
#include <dbsymtb.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLayerUtil::CLayerUtil()
{

}

CLayerUtil::~CLayerUtil()
{

}

void CLayerUtil::Add( const TCHAR* layerName, int colorIndex )
{
	assert (layerName != NULL);
	assert (colorIndex >= 1 && colorIndex <= 255);			
	
	// 获得层表
	AcDbLayerTable *pLayerTbl = NULL;
	acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pLayerTbl, AcDb::kForWrite);

	// 是否已经存在同名的层
	if (!pLayerTbl->has(layerName))
	{
		AcDbLayerTableRecord *pLayerTblRcd = new AcDbLayerTableRecord();
		pLayerTblRcd->setName(layerName);
		AcCmColor color;
		color.setColorIndex(colorIndex);
		pLayerTblRcd->setColor(color);
		Acad::ErrorStatus es = pLayerTbl->add(pLayerTblRcd);
		pLayerTblRcd->close();
	}
	
	pLayerTbl->close();
}

AcDbObjectId CLayerUtil::GetLayerId( const TCHAR* layerName )
{
	assert (layerName != NULL);
	
	AcDbLayerTable *pLayerTbl;
	acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pLayerTbl, AcDb::kForRead);
	AcDbObjectId layerId = AcDbObjectId::kNull;
	if (pLayerTbl->has(layerName))
	{
		pLayerTbl->getAt(layerName, layerId); 
	}	
	pLayerTbl->close();	
	
	return layerId;
}

bool CLayerUtil::SetColor( const TCHAR* layerName, int colorIndex )
{
	AcDbObjectId layerId = GetLayerId(layerName);
	bool bRet = false;
	AcDbLayerTableRecord *pLayerTblRcd = NULL;
	if (acdbOpenObject(pLayerTblRcd, layerId, AcDb::kForWrite) == Acad::eOk)
	{
		AcCmColor color;
		color.setColorIndex(colorIndex);
		pLayerTblRcd->setColor(color);
		bRet = true;

		pLayerTblRcd->close();
	}

	return bRet;
}

void CLayerUtil::GetLayerList( AcDbObjectIdArray &layers )
{
	AcDbLayerTable *pLayerTbl = NULL;
	acdbHostApplicationServices()->workingDatabase()->getLayerTable(pLayerTbl, AcDb::kForRead);
	AcDbLayerTableIterator *it = NULL;
	pLayerTbl->newIterator(it);
	AcDbLayerTableRecord *pLayerTblRcd = NULL;
	for (it->start(); !it->done(); it->step())
	{
		if (it->getRecord(pLayerTblRcd, AcDb::kForRead) == Acad::eOk)
		{
			layers.append(pLayerTblRcd->objectId());
			
			pLayerTblRcd->close();
		}		
	}
	delete it;
	pLayerTbl->close();
}
