// MathUtil.cpp: implementation of the CMathUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MathUtil.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMathUtil::CMathUtil()
{

}

CMathUtil::~CMathUtil()
{

}

double CMathUtil::PI()
{
	return atan(1.0) * 4;
}

// 判断两个数是否相等
bool CMathUtil::IsEqual( double a, double b, double tol /*= 1.0E-7*/ )
{
	return (fabs(a - b) < tol);
}

// 获取两个整数之间的随机数
// 注意调用之前，应该执行一次 srand((unsigned)time(NULL));
int CMathUtil::GetRand( int minValue, int maxValue )
{
	assert (maxValue - minValue);
	
	int value = rand();			// 生成的随机数
	int rc = minValue + (int)CMathUtil::Round(((double)value) / RAND_MAX * (maxValue - minValue));
	
	return rc;
}

// 对一个数按照指定的小数位数进行四舍五入
double CMathUtil::Round( double a, int precision )
{
	return (floor(a * pow(10.0, precision) + 0.5)) / pow(10.0, precision);
}

// 对一个数进行四舍五入
int CMathUtil::Round( double a )
{
	return (int)(a + 0.5);
}
