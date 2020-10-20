//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "dbents.h"
#include "..\..\Common\Entity\LineUtil.h"
#include "..\..\Common\Entity\EntityUtil.h"

// 创建直线的函数
AcDbObjectId CreateLine()
{	
	AcGePoint3d ptStart(0, 0, 0);
	AcGePoint3d ptEnd(100, 100, 0);
	AcDbLine *pLine = new AcDbLine(ptStart, ptEnd);	
	
	AcDbBlockTable *pBlockTable;
	acdbHostApplicationServices()->workingDatabase()
		->getBlockTable(pBlockTable, AcDb::kForRead);	
	
	AcDbBlockTableRecord *pBlockTableRecord;
    pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
        AcDb::kForWrite);   	
	
	AcDbObjectId lineId;
    pBlockTableRecord->appendAcDbEntity(lineId, pLine);	
	
	pBlockTable->close();
    pBlockTableRecord->close();
    pLine->close();	

	return lineId;
}

// 修改指定实体的颜色
Acad::ErrorStatus ChangeColor(AcDbObjectId entId, Adesk::UInt16 colorIndex)
{
	AcDbEntity *pEntity;
	// 打开图形数据库中的对象
    acdbOpenObject(pEntity, entId, AcDb::kForWrite);
	
	// 修改实体的颜色
    pEntity->setColorIndex(colorIndex);
	
	// 用完之后，及时关闭
    pEntity->close();
	
    return Acad::eOk;	
}

// This is command 'CHANGECOLOR'
void ZffCHAP2ChangeColor()
{
	// 创建直线
	AcDbObjectId lineId;
	lineId = CreateLine();

	// 将直线的颜色修改为红色
	ChangeColor(lineId, 1);
}

// This is command 'CHANGECOLOR2'
void ZffCHAP2ChangeColor2()
{
	// 创建直线
	AcGePoint3d startPoint(0, 0, 0);
	AcGePoint3d endPoint(100, 100, 0);
	AcDbObjectId lineId = CLineUtil::Add(startPoint, endPoint);

	// 修改颜色为红色
	CEntityUtil::SetColor(lineId, 1);

	// 修改实体的图层和线型
	CEntityUtil::SetLayer(lineId, TEXT("中心线"));
	CEntityUtil::SetLinetype(lineId, TEXT("HIDDEN"));
}

