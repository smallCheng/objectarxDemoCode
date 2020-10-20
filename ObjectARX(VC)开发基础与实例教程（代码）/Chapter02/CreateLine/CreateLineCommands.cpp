//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "dbents.h"
//#include "dbapserv.h"

// This is command 'CREATELINE'
void ZffCHAP2CreateLine()
{
	// 在内存上创建一个新的AcDbLine对象
	AcGePoint3d ptStart(0, 0, 0);
	AcGePoint3d ptEnd(100, 100, 0);
	AcDbLine *pLine = new AcDbLine(ptStart, ptEnd);
	
	// 获得指向块表的指针
	AcDbBlockTable *pBlockTable = NULL;
	acdbHostApplicationServices()->workingDatabase()
		->getBlockTable(pBlockTable, AcDb::kForRead);

	// 获得指向特定的块表记录（模型空间）的指针
	AcDbBlockTableRecord *pBlockTableRecord = NULL;
    pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
        AcDb::kForWrite);    
	
	// 将AcDbLine类的对象添加到块表记录中
	AcDbObjectId lineId;
    pBlockTableRecord->appendAcDbEntity(lineId, pLine);
	
	// 关闭图形数据库的各种对象
	pBlockTable->close();
    pBlockTableRecord->close();
    pLine->close();	
}






















