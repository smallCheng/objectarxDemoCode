// StringUtil.h: interface for the CStringUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGUTIL_H__637019B0_219C_47FC_936B_866C88F308FD__INCLUDED_)
#define AFX_STRINGUTIL_H__637019B0_219C_47FC_936B_866C88F308FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

class CStringUtil  
{
public:
	CStringUtil();
	virtual ~CStringUtil();

	// 以一个字符串为分隔符对字符串进行分割
	// bAddEmptyItem: 是否添加空字符串元素
	static void Split(const CString &text, const TCHAR* separator, std::vector<CString> &result, bool bAddEmptyItem = true);

	// 通过分隔符合并字符串集合
	static CString Join(const std::vector<CString> &items, const TCHAR* separator);
};

#endif // !defined(AFX_STRINGUTIL_H__637019B0_219C_47FC_936B_866C88F308FD__INCLUDED_)
