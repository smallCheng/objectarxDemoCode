// DbDataReader.h: interface for the CDbDataReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBDATAREADER_H__E380A51A_6B48_4D7C_9249_BE998F6DC941__INCLUDED_)
#define AFX_DBDATAREADER_H__E380A51A_6B48_4D7C_9249_BE998F6DC941__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DbObject.h"

#if defined (_ZFGKCOMMONLIB_)
#define ZFGK_DLLIMPEXP __declspec(dllexport)
#else
#define ZFGK_DLLIMPEXP 
#endif

class ZFGK_DLLIMPEXP CDbDataReader  
{
public:
	CDbDataReader();
	CDbDataReader(_RecordsetPtr pRecordset);
	virtual ~CDbDataReader();

	// 读取下一行的内容(返回值：是否读到了内容,返回false表示到达了表的结尾)
	bool Read();
	
	// 关闭读取器
	void Close();

	// 返回某个字段的值
	CDbObject operator[] (const TCHAR* field);

	// 读取Clob字段
	bool GetClobField(const TCHAR* field, CString &strResult);

private:
	_RecordsetPtr& GetRecordsetPtr();
	void SetRecordsetPtr(_RecordsetPtr &recordset);
	void SetFirstLine(bool bFirstLine);

private:
	_RecordsetPtr m_pRecordset;
	bool m_bFirstLine;
	friend class CDbCommand;
};

#endif // !defined(AFX_DBDATAREADER_H__E380A51A_6B48_4D7C_9249_BE998F6DC941__INCLUDED_)
