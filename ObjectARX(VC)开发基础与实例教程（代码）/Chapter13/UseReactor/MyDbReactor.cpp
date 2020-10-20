// MyDbReactor.cpp: implementation of the CMyDbReactor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyDbReactor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyDbReactor::CMyDbReactor()
{

}

CMyDbReactor::~CMyDbReactor()
{

}

void CMyDbReactor::objectAppended( const AcDbDatabase* dwg, const AcDbObject* dbObj )
{
	if (dbObj->isKindOf(AcDbEntity::desc()) && const_cast<AcDbObject*>(dbObj)->upgradeOpen() == Acad::eOk)
	{
		AcDbEntity *pEnt = AcDbEntity::cast(dbObj);
		pEnt->setColorIndex(1);
	}
}
