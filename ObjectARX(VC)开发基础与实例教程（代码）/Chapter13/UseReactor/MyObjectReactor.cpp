// MyObjectReactor.cpp: implementation of the CMyObjectReactor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyObjectReactor.h"
#include <dbents.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// 如果没用向导创建，一定记得加上这句话
ACRX_DXF_DEFINE_MEMBERS(CMyObjectReactor, AcDbObject, 
						AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
						0, MYOBJECTREACTOR, UseReactor);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyObjectReactor::CMyObjectReactor()
{

}

CMyObjectReactor::~CMyObjectReactor()
{

}

Acad::ErrorStatus CMyObjectReactor::dwgInFields( AcDbDwgFiler* pFiler )
{
	assertWriteEnabled();
    AcDbObject::dwgInFields(pFiler);
	
    pFiler->readItem((AcDbSoftPointerId*) &m_entId);
    return pFiler->filerStatus();
}

Acad::ErrorStatus CMyObjectReactor::dwgOutFields( AcDbDwgFiler* pFiler ) const
{
	assertReadEnabled();
    AcDbObject::dwgOutFields(pFiler);
    pFiler->writeItem((AcDbSoftPointerId&)m_entId);
    return pFiler->filerStatus();
}

void CMyObjectReactor::modified( const AcDbObject* pObj )
{
	AcDbCircle *pCircle = AcDbCircle::cast(pObj);
	if (pCircle != NULL)
	{
		double radius = pCircle->radius();

		AcDbCircle *pLinkCircle = NULL;
		if (acdbOpenObject(pLinkCircle, m_entId, AcDb::kForWrite) == Acad::eOk)
		{
			pLinkCircle->setRadius(radius);

			pLinkCircle->close();
		}
	}
}

void CMyObjectReactor::erased( const AcDbObject* dbObj, Adesk::Boolean pErasing /*= true*/ )
{
	AcDbCircle *pCircle = AcDbCircle::cast(dbObj);
	if (pCircle != NULL && pErasing)
	{
		AcDbCircle *pLinkCircle = NULL;
		if (acdbOpenObject(pLinkCircle, m_entId, AcDb::kForWrite) == Acad::eOk)
		{
			pLinkCircle->erase();
			
			pLinkCircle->close();
		}
	}
}

void CMyObjectReactor::SetLinkEntId( AcDbObjectId entId )
{
	assertWriteEnabled();

	m_entId = entId;
}
