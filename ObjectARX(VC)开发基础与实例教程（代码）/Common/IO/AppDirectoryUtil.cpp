// AppDirectoryUtil.cpp: implementation of the CAppDirectoryUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AppDirectoryUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAppDirectoryUtil::CAppDirectoryUtil()
{

}

CAppDirectoryUtil::~CAppDirectoryUtil()
{

}

CString CAppDirectoryUtil::GetCurrentDirectory( HMODULE hInstance )
{
	TCHAR szPath[256];
	GetModuleFileName(hInstance, szPath, sizeof(szPath));
	*(_tcsrchr(szPath, '\\')) = 0;		// 将最后一个\所在的位置修改为\0
	
	CString strResult = szPath;	
	return strResult;
}

CString CAppDirectoryUtil::GetParentDirectory( HMODULE hInstance )
{
	TCHAR szPath[256];
	GetModuleFileName(hInstance, szPath, sizeof(szPath));
	*(_tcsrchr(szPath, '\\')) = 0;		// 将最后一个\所在的位置设置为\0
	*(_tcsrchr(szPath, '\\')) = 0;		// 继续将最后一个\所在的位置设计为\0
	
	CString strResult = szPath;	
	return strResult;
}
