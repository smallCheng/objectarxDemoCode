// DbCommand.h: interface for the CDbCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBCOMMAND_H__1A146D13_AE69_4F1E_A4BF_6847C0B61A61__INCLUDED_)
#define AFX_DBCOMMAND_H__1A146D13_AE69_4F1E_A4BF_6847C0B61A61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DbConnection.h"
#include "DbObject.h"
#include "DbDataReader.h"
#include <set>

#if defined (_ZFGKCOMMONLIB_)
#define ZFGK_DLLIMPEXP __declspec(dllexport)
#else
#define ZFGK_DLLIMPEXP 
#endif

class ZFGK_DLLIMPEXP CDbCommand  
{
public:	
	CDbCommand(const TCHAR* sql, CDbConnection* pCon);
	CDbCommand(CDbConnection* pCon);
	CDbCommand();
	virtual ~CDbCommand();
	
	//************************************
	// 功能: 执行没有返回值的查询
	// 返回值:   int, 受影响的行数
	// 创建: 张帆 -- 2008-11-5 17:40
	//************************************
	int ExecuteNonQuery();

	// 返回一个结果集第一行第一列的查询
	CDbObject ExecuteScalar();

	// 返回一个Reader的查询(调用者不需要释放指针指向的内存)
	CDbDataReader* ExecuteReader();

	// 设置SQL字符串
	void SetCommandText(const TCHAR* sql);
	
	// 删除一个表的所有数据
	bool DeleteFromTable(const TCHAR* tableName);

	// 更新一个表中的二进制字段(对应SqlServer数据库的varbinary(MAX)字段)
	// tableName: 表名
	// pkName：主键名
	// fieldName：二进制字段名
	// pkId: 要更新的记录的主键ID
	// fileName：要更新的文件名
	bool UpdateBinaryField(const TCHAR* tableName, const TCHAR* pkName, const TCHAR* fieldName, int pkId, const TCHAR* fileName);

	// 获取一个表中的二进制字段(对应SqlServer数据库的varbinary(MAX)字段)，将其保存为一个文件
	// tableName: 表名
	// pkName：主键名
	// fieldName：二进制字段名
	// pkId: 要更新的记录的主键ID
	// fileName：要保存的文件名
	bool GetBinaryField(const TCHAR* tableName, const TCHAR* pkName, const TCHAR* fieldName, int pkId, const TCHAR* fileName);

	//*****************************************************
	// 功能: 为当前命令对象添加参数
	// 参数: const char * name, 参数名称
	// 参数: DataTypeEnum type, 参数类型(基本用于文本类型)
	// 参数: long size, 参数大小
	// 参数: long value, 参数值
	// 返回值: void, 
	// 创建: 首晓强，2008-12-16 18:27
	//*****************************************************
	//void AddParameter( const char* name, DataTypeEnum type, long size, long value );

	//*****************************************************
	// 功能: 为当前命令对象添加参数
	// 参数: const char * name, 参数名称
	// 参数: DataTypeEnum type, 参数类型(基本用于文本类型)
	// 参数: long size, 参数大小
	// 参数: const char * value, 参数值
	// 返回值: void, 无
	// 创建: 首晓强，2008-12-16 16:00
	//*****************************************************
	//void AddParameter( const char* name, DataTypeEnum type, long size, const char* value );

	// 添加字符串类型的命令参数
	void AddCharParameter(const TCHAR *name, const TCHAR *value, long size = 50);
	void AddVarcharParameter(const TCHAR *name, const TCHAR* value, long size = 50);

	// 添加字节类型的命令参数
	void AddByteParameter(const TCHAR *name, byte value);

	// 添加整型的命令参数
	// bool bZeroAsNull, 如果输入的参数是0，那么添加到数据库时是否将其指定为NULL值
	void AddIntParameter(const TCHAR *name, int value, bool bZeroAsNull = false);

	// 添加实数类型的命令参数
	void AddDoubleParameter(const TCHAR *name, double value);

	// 添加长整型的命令参数
	void AddLongParameter(const TCHAR *name, long value);

	// 添加布尔类型的命令参数
	void AddBoolParameter(const TCHAR* name, bool value);

	// 删除某个参数
	void DeleteParameter(const TCHAR *name);

private:
	//*****************************************************
	// 功能: 初始化命令对象
	// 返回值: void, 无
	// 创建: 首晓强，2008-12-16 17:42
	//*****************************************************
	void Init();	

private:
	CString m_sql;
	CDbConnection* m_pCon;
	CDbDataReader m_dataReader;
	_CommandPtr m_cmd;
	std::set<CString> m_paramSet;

	//_RecordsetPtr m_pRecordset;
};

#endif // !defined(AFX_DBCOMMAND_H__1A146D13_AE69_4F1E_A4BF_6847C0B61A61__INCLUDED_)
