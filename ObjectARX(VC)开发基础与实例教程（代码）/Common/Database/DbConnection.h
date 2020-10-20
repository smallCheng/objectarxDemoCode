// DbConnection.h: interface for the CDbConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBCONNECTION_H__CD115B30_432E_4257_9541_CAB651F7D3F8__INCLUDED_)
#define AFX_DBCONNECTION_H__CD115B30_432E_4257_9541_CAB651F7D3F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined (_ZFGKCOMMONLIB_)
#define ZFGK_DLLIMPEXP __declspec(dllexport)
#else
#define ZFGK_DLLIMPEXP 
#endif

class ZFGK_DLLIMPEXP CDbConnection  
{
public:
	CDbConnection(const TCHAR* connectionString);
	virtual ~CDbConnection();

	// 打开连接
	bool Open();

	// 关闭连接
	void Close();

	// 是否是Access连接
	void SetIsAccessConnection(bool bAccessCon);

	// 开始事务处理
	void BeginTrans();

	// 提交事务
	void CommitTrans();
	
	// 回滚事务
	void RollbackTrans();

	// 释放数据库连接
	static void Release();

	// 是否存在某个表
	bool TableExist(const TCHAR *tableName);

	// 某个表中是否存在给定的字段
	bool FieldExist(const TCHAR* tableName, const TCHAR* fieldName);

protected:
	CDbConnection();

private:
	// 获得连接对象的Com指针
	_ConnectionPtr GetConnectionPtr();
	friend class CDbCommand;

	// 判断这个对象的COM是否已经关闭，防止关闭多次
	bool m_bClosed;
	bool m_bAccessConnection;		// 是否是Access数据库，如果是就不会在执行Close函数时真正关闭数据库连接，否则将关闭数据库连接

private:
	_ConnectionPtr m_pConnection;
	CString m_strConnectionString;
	
	static _ConnectionPtr m_pStConnection;
	static CString m_strStConString;
};

#endif // !defined(AFX_DBCONNECTION_H__CD115B30_432E_4257_9541_CAB651F7D3F8__INCLUDED_)
