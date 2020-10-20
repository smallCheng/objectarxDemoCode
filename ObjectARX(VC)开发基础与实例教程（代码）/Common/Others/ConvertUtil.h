// ConvertUtil.h: interface for the CConvertUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONVERTUTIL_H__E2F2B2F9_52B8_4A46_A8BE_148DD9645A15__INCLUDED_)
#define AFX_CONVERTUTIL_H__E2F2B2F9_52B8_4A46_A8BE_148DD9645A15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConvertUtil  
{
public:
	CConvertUtil();
	virtual ~CConvertUtil();

	// 二维点和三维点之间的转换
	static AcGePoint3d ToPoint3d(const AcGePoint2d &point2d, double z = 0);
	static AcGePoint2d ToPoint2d(const AcGePoint3d &point3d);

	// 角度转换为弧度
	static double AngleToRadian(double angle);
	
	// 弧度转角度
	static double RadianToAngle(double radian);

	// 转换为字符串
	static CString ToString(int val);
	static CString ToString(double value, int precision = 2);

	// 字符串转换为特定的类型
	static double ToDouble(const TCHAR* str);

	// 将一个点从世界坐标系坐标转换到显示坐标系
	static AcGePoint3d WcsToDcsPoint(const AcGePoint3d &point);

	// 将一个点从用户坐标系坐标转换到世界坐标系
	static AcGePoint3d UcsToWcsPoint(const AcGePoint3d &point);

	// 将一个点从世界坐标系坐标转换到用户坐标系
	static AcGePoint3d WcsToUcsPoint(const AcGePoint3d &point);
};

#endif // !defined(AFX_CONVERTUTIL_H__E2F2B2F9_52B8_4A46_A8BE_148DD9645A15__INCLUDED_)
