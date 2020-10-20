// (C) Copyright 2002-2005 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- ZfgkTriangle.cpp : Implementation of ZfgkTriangle
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "ZfgkTriangle.h"
#include "..\..\Common\Others\ConvertUtil.h"
#include "..\..\Common\Geometry\MathUtil.h"

//-----------------------------------------------------------------------------
Adesk::UInt32 ZfgkTriangle::kCurrentVersionNumber =1 ;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS (
						 ZfgkTriangle, AcDbEntity,
						 AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
						 AcDbProxyEntity::kNoOperation, ZFGKTRIANGLE,
						 "ZFGKTRIANGLEENTITYDBAPP"
						 "|Product Desc:     A description for your object"
						 "|Company:          Your company name"
						 "|WEB Address:      Your company WEB site address"
						 )

						 //-----------------------------------------------------------------------------
						 ZfgkTriangle::ZfgkTriangle () : AcDbEntity () {
}

ZfgkTriangle::ZfgkTriangle( const AcGePoint3d &pt1, const AcGePoint3d &pt2, const AcGePoint3d &pt3 )
{
	m_verts[0] = pt1;
	m_verts[1] = pt2;
	m_verts[2] = pt3;
}

ZfgkTriangle::~ZfgkTriangle () {
}

//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus ZfgkTriangle::dwgOutFields (AcDbDwgFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dwgOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (ZfgkTriangle::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	for (int i = 0; i < 3; i++)
	{
		pFiler->writeItem(m_verts[i]);
	}

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus ZfgkTriangle::dwgInFields (AcDbDwgFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dwgInFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be read first
	Adesk::UInt32 version =0 ;
	if ( (es =pFiler->readUInt32 (&version)) != Acad::eOk )
		return (es) ;
	if ( version > ZfgkTriangle::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < ZfgkTriangle::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params
	for (int i = 0; i < 3; i++)
	{
		pFiler->readItem(&m_verts[i]);
	}

	return (pFiler->filerStatus ()) ;
}

//-----------------------------------------------------------------------------
//----- AcDbEntity protocols
Adesk::Boolean ZfgkTriangle::worldDraw (AcGiWorldDraw *mode) {
	assertReadEnabled () ;

	// 绘制边
	for (int i = 0; i < 3; i++)
	{
		int nextIndex = i + 1;
		if (i == 2)
		{
			nextIndex = 0;
		}

		AcGePoint3d points[2];
		points[0] = m_verts[i];
		points[1] = m_verts[nextIndex];
		mode->geometry().polyline(2, points);
	}

	// 绘制内部的填充
	AcDbFace *pFace = GetFace();
	pFace->worldDraw(mode);
	delete pFace;

	return Adesk::kTrue;
}

//- Osnap points protocol
Acad::ErrorStatus ZfgkTriangle::getOsnapPoints (
	AcDb::OsnapMode osnapMode,
	int gsSelectionMark,
	const AcGePoint3d &pickPoint,
	const AcGePoint3d &lastPoint,
	const AcGeMatrix3d &viewXform,
	AcGePoint3dArray &snapPoints,
	AcDbIntArray &geomIds) const
{
	assertReadEnabled () ;

	AcDbPolyline *pPoly = GetPolyline();
	Acad::ErrorStatus es = pPoly->getOsnapPoints(osnapMode, gsSelectionMark, pickPoint, lastPoint, 
		viewXform, snapPoints, geomIds);
	delete pPoly;

	return es;
}

Acad::ErrorStatus ZfgkTriangle::getOsnapPoints (
	AcDb::OsnapMode osnapMode,
	int gsSelectionMark,
	const AcGePoint3d &pickPoint,
	const AcGePoint3d &lastPoint,
	const AcGeFastTransform &viewXform,
	AcGePoint3dArray &snapPoints,
	AcDbIntArray &geomIds) const
{
	assertReadEnabled () ;

	return AcDbEntity::getOsnapPoints(osnapMode, gsSelectionMark, pickPoint, lastPoint, 
		viewXform, snapPoints, geomIds);
}

Acad::ErrorStatus ZfgkTriangle::getOsnapPoints (
	AcDb::OsnapMode osnapMode,
	int gsSelectionMark,
	const AcGePoint3d &pickPoint,
	const AcGePoint3d &lastPoint,
	const AcGeMatrix3d &viewXform,
	AcGePoint3dArray &snapPoints,
	AcDbIntArray &geomIds,
	const AcGeMatrix3d &insertionMat) const
{
	assertReadEnabled () ;

	return AcDbEntity::getOsnapPoints(osnapMode, gsSelectionMark, pickPoint, lastPoint, 
		viewXform, snapPoints, geomIds, insertionMat);
}

Acad::ErrorStatus ZfgkTriangle::getOsnapPoints (
	AcDb::OsnapMode osnapMode,
	int gsSelectionMark,
	const AcGePoint3d & pickPoint,
	const AcGePoint3d & lastPoint,
	const AcGeFastTransform & viewXform,
	AcGePoint3dArray &snapPoints,
	AcDbIntArray &geomIds,
	const AcGeMatrix3d &insertionMat) const
{
	assertReadEnabled () ;

	return AcDbEntity::getOsnapPoints(osnapMode, gsSelectionMark, pickPoint, lastPoint, 
		viewXform, snapPoints, geomIds, insertionMat);
}

//- Grip points protocol
Acad::ErrorStatus ZfgkTriangle::getGripPoints (
	AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds
	) const {
		assertReadEnabled () ;

		for (int i = 0; i < 3; i++)
		{
			gripPoints.append(m_verts[i]);
		}

		return Acad::eOk;
}

Acad::ErrorStatus ZfgkTriangle::moveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset) {
	assertWriteEnabled () ;
	//----- This method is never called unless you return eNotImplemented 
	//----- from the new moveGripPointsAt() method below (which is the default implementation)

	m_verts[indices[0]] += offset;

	return Acad::eOk;
}

Acad::ErrorStatus ZfgkTriangle::getGripPoints (
	AcDbGripDataPtrArray &grips, const double curViewUnitSize, const int gripSize, 
	const AcGeVector3d &curViewDir, const int bitflags
	) const {
		assertReadEnabled () ;

		// 不实现

		//----- If you return eNotImplemented here, that will force AutoCAD to call
		//----- the older getGripPoints() implementation. The call below may return
		//----- eNotImplemented depending of your base class.
		return (AcDbEntity::getGripPoints (grips, curViewUnitSize, gripSize, curViewDir, bitflags)) ;
}

Acad::ErrorStatus ZfgkTriangle::moveGripPointsAt (
	const AcDbVoidPtrArray &gripAppData, const AcGeVector3d &offset,
	const int bitflags
	) {
		assertWriteEnabled () ;

		//----- If you return eNotImplemented here, that will force AutoCAD to call
		//----- the older getGripPoints() implementation. The call below may return
		//----- eNotImplemented depending of your base class.
		return (AcDbEntity::moveGripPointsAt (gripAppData, offset, bitflags)) ;
}

AcDbPolyline* ZfgkTriangle::GetPolyline() const
{
	AcDbPolyline *pPoly = new AcDbPolyline();
	for (int i = 0; i < 3; i++)
	{
		pPoly->addVertexAt(i, CConvertUtil::ToPoint2d(m_verts[i]));
	}
	pPoly->setClosed(Adesk::kTrue);

	return pPoly;
}

Acad::ErrorStatus ZfgkTriangle::transformBy( const AcGeMatrix3d& xform )
{
	for (int i = 0; i < 3; i++)
	{
		m_verts[i].transformBy(xform);
	}

	return Acad::eOk;
}

Acad::ErrorStatus ZfgkTriangle::getGeomExtents( AcDbExtents &extents ) const
{
	for (int i = 0; i < 3; i++)
	{
		extents.addPoint(m_verts[i]);
	}

	return Acad::eOk;
}

Acad::ErrorStatus ZfgkTriangle::explode( AcDbVoidPtrArray& entitySet ) const
{
	for (int i = 0; i < 3; i++)
	{
		int nextIndex = i + 1;
		if (i == 2)
		{
			nextIndex = 0;
		}

		AcDbLine *pLine = new AcDbLine(m_verts[i], m_verts[nextIndex]);
		pLine->setPropertiesFrom(this);
		entitySet.append(pLine);
	}

	return Acad::eOk;
}

void ZfgkTriangle::list() const
{
	AcDbEntity::list();

	for (int i = 0; i < 3; i++)
	{
		acutPrintf(TEXT("\n顶点%d:(%g, %g, %g)"), m_verts[i].x, m_verts[i].y, m_verts[i].z);
	}
}

void ZfgkTriangle::GetVerts( AcGePoint3dArray &verts ) const
{
	assertReadEnabled();

	verts.setLogicalLength(0);
	for (int i = 0; i < 3; i++)
	{
		verts.append(m_verts[i]);
	}
}

double ZfgkTriangle::GetArea() const
{
	AcDbPolyline *pPoly = GetPolyline();
	double area = 0;
	pPoly->getArea(area);
	delete pPoly;

	return area;
}

void ZfgkTriangle::SetVertAt( int index, const AcGePoint3d &point )
{
	assertWriteEnabled();

	if (index >= 0 && index <= 2)
	{
		m_verts[index] = point;
	}
}

#ifndef VCUSETRIANGLEENTITY_MODULE
void ZfgkTriangle::set_ManagedWrapper( gcroot<Zfgk::TriangleEntityDB::MgTriangle*> p )
{
	m_pManaged = p;
}
#endif

AcDbFace* ZfgkTriangle::GetFace() const
{
	AcDbFace *pFace = new AcDbFace(m_verts[0], m_verts[1], m_verts[2]);
	pFace->setColorIndex(this->colorIndex());
	return pFace;
}
