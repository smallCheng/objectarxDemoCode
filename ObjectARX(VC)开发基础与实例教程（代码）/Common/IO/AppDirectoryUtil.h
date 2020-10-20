// AppDirectoryUtil.h: interface for the CAppDirectoryUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPDIRECTORYUTIL_H__DD493023_982A_4370_8A6F_C271F5FD388F__INCLUDED_)
#define AFX_APPDIRECTORYUTIL_H__DD493023_982A_4370_8A6F_C271F5FD388F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAppDirectoryUtil  
{
public:
	CAppDirectoryUtil();
	virtual ~CAppDirectoryUtil();

	// 功能: 获得当前的ARX文件所在的路径
	static CString GetCurrentDirectory(HMODULE hInstance = _hdllInstance);

	// 功能: 获得当前的ARX文件所在的文件夹的上级目录
	static CString GetParentDirectory(HMODULE hInstance = _hdllInstance);
};

#endif // !defined(AFX_APPDIRECTORYUTIL_H__DD493023_982A_4370_8A6F_C271F5FD388F__INCLUDED_)
