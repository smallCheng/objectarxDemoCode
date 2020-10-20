// MathUtil.h: interface for the CMathUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATHUTIL_H__6942F157_F85E_4F55_B188_CB413C7BED7E__INCLUDED_)
#define AFX_MATHUTIL_H__6942F157_F85E_4F55_B188_CB413C7BED7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMathUtil  
{
public:
	CMathUtil();
	virtual ~CMathUtil();

	// 获得PI的值
	static double PI();

	// 判断两个数是否相等
	static bool IsEqual(double a, double b, double tol = 1.0E-7);

	// 获取两个整数之间的随机数
	// 注意调用之前，应该执行一次 srand((unsigned)time(NULL));
	static int GetRand(int minValue, int maxValue);

	// 对一个数按照指定的小数位数进行四舍五入
	static double Round(double a, int precision);
	static int Round(double a);
};

#endif // !defined(AFX_MATHUTIL_H__6942F157_F85E_4F55_B188_CB413C7BED7E__INCLUDED_)
