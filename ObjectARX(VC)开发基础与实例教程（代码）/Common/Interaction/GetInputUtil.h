// GetInputUtil.h: interface for the CGetInputUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GETINPUTUTIL_H__EDED7CA0_9516_44E8_A440_590BBD26C2C8__INCLUDED_)
#define AFX_GETINPUTUTIL_H__EDED7CA0_9516_44E8_A440_590BBD26C2C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGetInputUtil  
{
public:
	CGetInputUtil();
	virtual ~CGetInputUtil();

	// 提示用户选择一个点(无论当前是否在UCS中工作，直接返回该点的WCS坐标)
	// basePoint: 基于WCS的点坐标
	// 返回值：与acedGetPoint函数相同
	static int GetPointReturnCode(const AcGePoint3d &basePoint, const TCHAR* prompt, AcGePoint3d &point);
	static bool GetPoint(const AcGePoint3d &basePoint, const TCHAR* prompt, AcGePoint3d &point);
	static int GetPointReturnCode(const TCHAR* prompt, AcGePoint3d &point);
	static bool GetPoint(const TCHAR* prompt, AcGePoint3d &point);

	// 提示用户输入某个关键字对应的选项
	// firstDefault: 输入默认值显示内容，例如"是(Y)]"，如果输入NULL表示不使用默认值
	// defaultKeyIndex: 默认选项的索引
	static bool GetKeyword(const TCHAR* prompt, const TCHAR* keywords, const TCHAR* firstDefault, int defaultKeyIndex, int &nRet);

	// 提示用户输入实数
	// prompt:提示内容
	// defaultVal:默认值
	// precision:默认值显示时小数点后面的位数
	// ret:实际返回值
	// 例如 CGetInputUtil::GetReal(TEXT("\n输入新值"), 5, 0, newVal);
	static bool GetReal(const TCHAR* prompt, double defaultVal, int precision, double &ret);
};

#endif // !defined(AFX_GETINPUTUTIL_H__EDED7CA0_9516_44E8_A440_590BBD26C2C8__INCLUDED_)
