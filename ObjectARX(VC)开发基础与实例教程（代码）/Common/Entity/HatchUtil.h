// HatchUtil.h: interface for the CHatchUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HATCHUTIL_H__CD5BAECA_C785_40E9_A967_60179A51BE79__INCLUDED_)
#define AFX_HATCHUTIL_H__CD5BAECA_C785_40E9_A967_60179A51BE79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHatchUtil  
{
public:
	CHatchUtil();
	virtual ~CHatchUtil();

	// ´´½¨Ìî³ä
	static AcDbObjectId Add(const AcDbObjectIdArray &loopIds, const TCHAR* patName, double patternScale = 1.0);
};

#endif // !defined(AFX_HATCHUTIL_H__CD5BAECA_C785_40E9_A967_60179A51BE79__INCLUDED_)
