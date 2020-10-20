// RegionUtil.h: interface for the CRegionUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGIONUTIL_H__8F210769_0CEC_413A_9572_1DD46FF4C030__INCLUDED_)
#define AFX_REGIONUTIL_H__8F210769_0CEC_413A_9572_1DD46FF4C030__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRegionUtil  
{
public:
	CRegionUtil();
	virtual ~CRegionUtil();

	// ¥¥Ω®√Ê”Ú
	static AcDbObjectIdArray Add(const AcDbObjectIdArray& curveIds);
};

#endif // !defined(AFX_REGIONUTIL_H__8F210769_0CEC_413A_9572_1DD46FF4C030__INCLUDED_)
