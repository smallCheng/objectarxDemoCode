// TextFileUtil.cpp: implementation of the CTextFileUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TextFileUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextFileUtil::CTextFileUtil()
{

}

CTextFileUtil::~CTextFileUtil()
{

}

void CTextFileUtil::Save( const TCHAR* fileName, const std::vector<CString> &lines )
{
	CStdioFile file(fileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
	for (int i = 0; i < lines.size(); i++)
	{
		file.WriteString(lines[i]);
		file.WriteString(TEXT("\n"));
	}
	file.Close();
}

void CTextFileUtil::Load( const TCHAR* fileName, std::vector<CString> &lines )
{
	lines.clear();

	CStdioFile file(fileName, CFile::modeRead | CFile::typeText);
	CString strLine;
	while (file.ReadString(strLine))
	{
		lines.push_back(strLine);
	}
}
