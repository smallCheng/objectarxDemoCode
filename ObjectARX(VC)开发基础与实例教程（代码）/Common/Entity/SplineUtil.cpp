// SplineUtil.cpp: implementation of the CSplineUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SplineUtil.h"
#include <dbspline.h>
#include "..\Document\DwgDatabaseUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSplineUtil::CSplineUtil()
{

}

CSplineUtil::~CSplineUtil()
{

}

AcDbObjectId CSplineUtil::Add( const AcGePoint3dArray& points, int order, double fitTolerance )
{
	assert (order >= 2 && order <= 26);

	AcDbSpline *pSpline = new AcDbSpline(points, order, fitTolerance);	
	AcDbObjectId splineId = CDwgDatabaseUtil::PostToModelSpace(pSpline);
	
	return splineId;
}

AcDbObjectId CSplineUtil::Add( const AcGePoint3dArray& points, const AcGeVector3d& startTangent, 
							  const AcGeVector3d& endTangent, int order /*= 4*/, double fitTolerance /*= 0.0*/ )
{
	assert(order >= 2 && order <= 26);

	AcDbSpline *pSpline = new AcDbSpline(points, startTangent, endTangent, 
		order, fitTolerance);	
	return CDwgDatabaseUtil::PostToModelSpace(pSpline);
}
