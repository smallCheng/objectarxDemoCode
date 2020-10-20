// TextFileUtil.h: interface for the CTextFileUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTFILEUTIL_H__50360F19_4F22_4CF2_8EA1_ABB4FCE2B72C__INCLUDED_)
#define AFX_TEXTFILEUTIL_H__50360F19_4F22_4CF2_8EA1_ABB4FCE2B72C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>

class CTextFileUtil  
{
public:
	CTextFileUtil();
	virtual ~CTextFileUtil();

	// 保存文本文件
	static void Save(const TCHAR* fileName, const std::vector<CString> &lines);

	// 加载文件
	static void Load(const TCHAR* fileName, std::vector<CString> &lines);
};

#endif // !defined(AFX_TEXTFILEUTIL_H__50360F19_4F22_4CF2_8EA1_ABB4FCE2B72C__INCLUDED_)
