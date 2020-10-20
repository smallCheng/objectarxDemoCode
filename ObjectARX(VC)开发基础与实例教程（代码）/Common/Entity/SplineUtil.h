// SplineUtil.h: interface for the CSplineUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINEUTIL_H__8EFD2D3B_F46F_4C41_9340_2E477895D144__INCLUDED_)
#define AFX_SPLINEUTIL_H__8EFD2D3B_F46F_4C41_9340_2E477895D144__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSplineUtil  
{
public:
	CSplineUtil();
	virtual ~CSplineUtil();

	// 添加样条曲线
	static AcDbObjectId Add(const AcGePoint3dArray& points, int order = 4, double fitTolerance = 0.0);
	static AcDbObjectId Add(const AcGePoint3dArray& points, const AcGeVector3d& startTangent, 
		const AcGeVector3d& endTangent, int order = 4, double fitTolerance = 0.0);
};

#endif // !defined(AFX_SPLINEUTIL_H__8EFD2D3B_F46F_4C41_9340_2E477895D144__INCLUDED_)
