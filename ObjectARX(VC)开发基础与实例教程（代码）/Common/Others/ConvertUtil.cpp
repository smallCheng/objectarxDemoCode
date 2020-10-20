// ConvertUtil.cpp: implementation of the CConvertUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ConvertUtil.h"
#include "..\Geometry\MathUtil.h"
#include <geassign.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConvertUtil::CConvertUtil()
{

}

CConvertUtil::~CConvertUtil()
{

}

AcGePoint3d CConvertUtil::ToPoint3d( const AcGePoint2d &point2d, double z )
{
	return AcGePoint3d(point2d.x, point2d.y, z);
}

double CConvertUtil::AngleToRadian( double angle )
{
	return angle * CMathUtil::PI() / 180;
}

double CConvertUtil::RadianToAngle( double radian )
{
	return radian * 180 / CMathUtil::PI();
}

CString CConvertUtil::ToString( int val )
{
	CString str;
	str.Format(TEXT("%d"), val);
	return str;
}

CString CConvertUtil::ToString( double value, int precision /*= 2*/ )
{
	CString strFormat, str;
	strFormat.Format(TEXT("%%.%df"), precision);
	str.Format(strFormat, value);
	
	return str;
}

AcGePoint3d CConvertUtil::WcsToDcsPoint( const AcGePoint3d &point )
{
	// 转换成显示坐标	
	AcGePoint3d pt;
	struct resbuf rbFrom, rbTo;
	rbFrom.restype = RTSHORT;
	rbFrom.resval.rint = 0; // from WCS
	rbTo.restype = RTSHORT;
	rbTo.resval.rint = 2; // to DCS
	
	acedTrans(asDblArray(point), &rbFrom, &rbTo, Adesk::kFalse, asDblArray(pt));
	
	return pt;
}

AcGePoint2d CConvertUtil::ToPoint2d( const AcGePoint3d &point3d )
{
	return AcGePoint2d(point3d.x, point3d.y);
}

AcGePoint3d CConvertUtil::UcsToWcsPoint( const AcGePoint3d &point )
{
	// 转换成世界坐标	
	AcGePoint3d pt;
	struct resbuf rbFrom, rbTo;
	rbFrom.restype = RTSHORT;
	rbFrom.resval.rint = 1; // from UCS
	rbTo.restype = RTSHORT;
	rbTo.resval.rint = 0; // to WCS
	
	acedTrans(asDblArray(point), &rbFrom, &rbTo, Adesk::kFalse, asDblArray(pt));
	
	return pt;
}

AcGePoint3d CConvertUtil::WcsToUcsPoint( const AcGePoint3d &point )
{
	// 转换成世界坐标	
	AcGePoint3d pt;
	struct resbuf rbFrom, rbTo;
	rbFrom.restype = RTSHORT;
	rbFrom.resval.rint = 0; // from WCS
	rbTo.restype = RTSHORT;
	rbTo.resval.rint = 1; // to UCS
	
	acedTrans(asDblArray(point), &rbFrom, &rbTo, Adesk::kFalse, asDblArray(pt));
	
	return pt;
}

double CConvertUtil::ToDouble( const TCHAR* str )
{
	TCHAR* pszStop = NULL;
	return _tcstod(str, &pszStop);
}
