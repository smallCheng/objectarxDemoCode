// EllipseUtil.h: interface for the CEllipseUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELLIPSEUTIL_H__160F02DF_ED73_43BA_A383_99B64A9F5FD5__INCLUDED_)
#define AFX_ELLIPSEUTIL_H__160F02DF_ED73_43BA_A383_99B64A9F5FD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEllipseUtil  
{
public:
	CEllipseUtil();
	virtual ~CEllipseUtil();

	// 创建椭圆
	static AcDbObjectId Add(const AcGePoint3d &ptCenter, const AcGeVector3d &vecNormal, 
		const AcGeVector3d &majorAxis, double ratio);
	// 根据外接矩形创建椭圆
	static AcDbObjectId Add(const AcGePoint2d &pt1, const AcGePoint2d &pt2);
};

#endif // !defined(AFX_ELLIPSEUTIL_H__160F02DF_ED73_43BA_A383_99B64A9F5FD5__INCLUDED_)
