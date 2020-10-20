// circleutil.h: interface for the CCircleUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCLEUTIL_H__2C82CD5A_BC5A_4E4B_A56F_7C41F8EAD5C6__INCLUDED_)
#define AFX_CIRCLEUTIL_H__2C82CD5A_BC5A_4E4B_A56F_7C41F8EAD5C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCircleUtil  
{
public:
	CCircleUtil();
	virtual ~CCircleUtil();

	// 添加圆
	static AcDbObjectId Add(const AcGePoint3d &centerPoint, const AcGeVector3d &normal, double radius, 
		AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase());
	static AcDbObjectId Add(const AcGePoint3d &centerPoint, double radius, 
		AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase());
	// 两点法
	static AcDbObjectId Add(const AcGePoint2d &point1, const AcGePoint2d &point2);
	// 三点法
	static AcDbObjectId Add(const AcGePoint2d &pt1, const AcGePoint2d &pt2, const AcGePoint2d &pt3);
};

#endif // !defined(AFX_CIRCLEUTIL_H__2C82CD5A_BC5A_4E4B_A56F_7C41F8EAD5C6__INCLUDED_)
