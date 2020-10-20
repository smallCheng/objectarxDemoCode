//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Document\DwgDatabaseUtil.h"
#include <dbents.h>

// This is command 'GETENTS'
void ZffChap2GetEnts()
{
	AcDbObjectIdArray allEntIds = CDwgDatabaseUtil::GetAllEntityIds(TEXT("≤‚À∆"));
	for (int i = 0; i < allEntIds.length(); i++)
	{
		AcDbLine *pLine = NULL;
		if (acdbOpenObject(pLine, allEntIds[i], AcDb::kForWrite) == Acad::eOk)
		{
			pLine->setColorIndex(1);
			pLine->close();
		}
	}
}

