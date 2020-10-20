// IniFile.cpp: implementation of the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIniFile::CIniFile(const TCHAR* fileName)
{
	m_strFile = fileName;
}

CIniFile::~CIniFile()
{

}

bool CIniFile::GetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, CString &strValue, int bufferLength ) const
{
	assert (m_strFile.GetLength() > 0);
	
	CString strDefault = TEXT("NotExist");		// 如果找不到对应的键，则返回该值
	CString strTemp;
	
	DWORD dwCharacters = ::GetPrivateProfileString(strFieldName, 
		strKeyName, 
		strDefault, 
		strTemp.GetBuffer(bufferLength), 
		bufferLength, 
		m_strFile);
	strTemp.ReleaseBuffer();
	
	// 注意GetPrivateProfileString函数返回错误的形式
	if (strTemp.Compare(strDefault) == 0)
	{
		return false;
	}
	else
	{
		strValue = strTemp;
		return true;
	}
}

bool CIniFile::GetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, int &nValue ) const
{
	CString strValue = TEXT("");
	if (GetValueOfKey(strFieldName, strKeyName, strValue))
	{
		nValue = _ttoi(strValue);
		return true;
	}
	else
	{
		return false;
	}
}

bool CIniFile::GetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, byte &byteValue ) const
{
	CString strValue = TEXT("");
	if (GetValueOfKey(strFieldName, strKeyName, strValue))
	{
		byteValue = (byte)(_ttoi(strValue));
		return true;
	}
	else
	{
		return false;
	}
}

bool CIniFile::GetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, bool &bValue ) const
{
	CString strValue = TEXT("");
	if (GetValueOfKey(strFieldName, strKeyName, strValue))
	{
		bValue = bool(_ttoi(strValue) == 1);
		return true;
	}
	else
	{
		return false;
	}
}

bool CIniFile::GetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, double &dValue ) const
{
	CString strValue = TEXT("");
	if (GetValueOfKey(strFieldName, strKeyName, strValue))
	{
		//dValue = _tstof(strValue);
		TCHAR* szStop = NULL;
		dValue = _tcstod(strValue, &szStop);
		return true;
	}
	else
	{
		return false;
	}
}

bool CIniFile::SetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, const TCHAR* strValue )
{
	// 防止在调用函数之前m_strFile未被初始化
	if (m_strFile.IsEmpty())
	{
		AfxMessageBox(TEXT("在调用函数SetValueOfKey时，m_strFile未被赋值，异常退出！"));		
		return false;
	}
	
	BOOL bRet = ::WritePrivateProfileString(strFieldName, 
		strKeyName, 
		strValue, 
		m_strFile);	
	
	if (bRet)
		return true;
	else
		return false;
}

bool CIniFile::SetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, int nValue )
{
	CString strValue = TEXT("");
	strValue.Format(TEXT("%d"), nValue);
	return SetValueOfKey(strFieldName, strKeyName, strValue);
}

bool CIniFile::SetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, byte byteValue )
{
	CString strValue = TEXT("");
	strValue.Format(TEXT("%u"), byteValue);
	return SetValueOfKey(strFieldName, strKeyName, strValue);
}

bool CIniFile::SetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, bool bValue )
{
	CString strValue = TEXT("");
	strValue.Format(TEXT("%d"), bValue);
	return SetValueOfKey(strFieldName, strKeyName, strValue);
}

bool CIniFile::SetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, double dValue, int decimalPlaces /*= 2 */ )
{
	assert(decimalPlaces >= 0);
	
	CString strFormat = TEXT("");
	strFormat.Format(TEXT("%%0.%df"), decimalPlaces);
	
	CString strValue = TEXT("");
	strValue.Format(strFormat, dValue);
	return SetValueOfKey(strFieldName, strKeyName, strValue);
}
