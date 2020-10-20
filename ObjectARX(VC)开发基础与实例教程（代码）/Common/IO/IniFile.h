// IniFile.h: interface for the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__D508DA87_D947_4FB1_9267_D79016C0BB55__INCLUDED_)
#define AFX_INIFILE_H__D508DA87_D947_4FB1_9267_D79016C0BB55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIniFile  
{
public:
	CIniFile(const TCHAR* fileName);
	virtual ~CIniFile();	
	
	// 指定字段名和键的名称，获得对应的键值
	bool GetValueOfKey(const TCHAR* strFieldName, const TCHAR* strKeyName, CString &strValue, int bufferLength = 1000) const;
	bool GetValueOfKey(const TCHAR* strFieldName, const TCHAR* strKeyName, int &nValue) const;	
	bool GetValueOfKey(const TCHAR* strFieldName, const TCHAR* strKeyName, byte &byteValue) const;	
	bool GetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, bool &bValue ) const;	
	bool GetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, double &dValue ) const;
	
	// 指定字段名和键的名称，写入对应的键值
	bool SetValueOfKey(const TCHAR* strFieldName, const TCHAR* strKeyName, const TCHAR* strValue);	
	bool SetValueOfKey(const TCHAR* strFieldName, const TCHAR* strKeyName, int nValue);	
	bool SetValueOfKey(const TCHAR* strFieldName, const TCHAR* strKeyName, byte byteValue);	
	bool SetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, bool bValue );	
	// decimalPlaces：小数点位数
	bool SetValueOfKey( const TCHAR* strFieldName, const TCHAR* strKeyName, double dValue, int decimalPlaces = 2 );
	
private:
	CString m_strFile;		// INI文件的保存位置
};

#endif // !defined(AFX_INIFILE_H__D508DA87_D947_4FB1_9267_D79016C0BB55__INCLUDED_)
