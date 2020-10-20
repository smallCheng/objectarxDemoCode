// EntityUtil.cpp: implementation of the CEntityUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EntityUtil.h"
#include <gemat3d.h>
#include "..\Others\ConvertUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEntityUtil::CEntityUtil()
{

}

CEntityUtil::~CEntityUtil()
{

}

void CEntityUtil::SetColor( AcDbObjectId entId, int colorIndex )
{
	// 检测参数的有效性
	assert (colorIndex >= 0 && colorIndex <= 256);
	
	AcDbEntity *pEnt = NULL;
	if (acdbOpenObject(pEnt, entId, AcDb::kForWrite) == Acad::eOk)
	{
		pEnt->setColorIndex(colorIndex);
		pEnt->close();
	}
}

void CEntityUtil::SetLayer( AcDbObjectId entId, const TCHAR* layerName )
{
	AcDbEntity *pEnt = NULL;
	if (acdbOpenObject(pEnt, entId, AcDb::kForWrite) == Acad::eOk)
	{
		pEnt->setLayer(layerName);
		pEnt->close();
	}
}

void CEntityUtil::SetLinetype( AcDbObjectId entId, const TCHAR* linetype )
{
	AcDbEntity *pEnt = NULL;
	if (acdbOpenObject(pEnt, entId, AcDb::kForWrite) == Acad::eOk)
	{
		pEnt->setLinetype(linetype);
		pEnt->close();
	}
}

Acad::ErrorStatus CEntityUtil::Rotate( AcDbObjectId entId, const AcGePoint2d &ptBase, double rotation )
{
	AcGeMatrix3d xform;	
	AcGeVector3d vec(0, 0, 1);
	xform.setToRotation(rotation, vec, CConvertUtil::ToPoint3d(ptBase));	
	
	AcDbEntity *pEnt = NULL;
	Acad::ErrorStatus es = acdbOpenObject(pEnt, entId, AcDb::kForWrite, false);
	if (es == Acad::eOk)
	{
		es = pEnt->transformBy(xform);
		pEnt->close();
	}	
	
	return es;
}

Acad::ErrorStatus CEntityUtil::Move( AcDbObjectId entId, const AcGePoint3d &ptBase, const AcGePoint3d &ptDest )
{
	// 设置变换矩阵的参数
	AcGeMatrix3d xform;	
	AcGeVector3d vec(ptDest.x - ptBase.x, ptDest.y - ptBase.y, 
		ptDest.z - ptBase.z);
	xform.setToTranslation(vec);
	
	AcDbEntity *pEnt = NULL;
	Acad::ErrorStatus es = acdbOpenObject(pEnt, entId, AcDb::kForWrite, false);
	if (es == Acad::eOk)
	{
		es = pEnt->transformBy(xform);
		pEnt->close();
	}
	
	return es;
}

Acad::ErrorStatus CEntityUtil::Scale( AcDbObjectId entId, const AcGePoint3d &ptBase, double scaleFactor )
{
	// 设置变换矩阵的参数
	AcGeMatrix3d xform;		
	xform.setToScaling(scaleFactor, ptBase);
	
	AcDbEntity *pEnt = NULL;
	Acad::ErrorStatus es = acdbOpenObject(pEnt, entId, AcDb::kForWrite, false);
	if (es == Acad::eOk)
	{
		es = pEnt->transformBy(xform);
		pEnt->close();
	}
	
	return es;
}

void CEntityUtil::Erase( AcDbObjectId entId )
{
	AcDbEntity *pEnt = NULL;
	if (acdbOpenObject(pEnt, entId, AcDb::kForWrite) == Acad::eOk)
	{
		pEnt->erase();
		pEnt->close();
	}
}
