// DbConnection.cpp: implementation of the CDbConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DbConnection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDbConnection::CDbConnection(const TCHAR* connectionString) : m_pConnection(NULL), m_bClosed(false)
{
	// 初始化COM动态链接库
	::CoInitialize(NULL);
	// 创建ADO连接对象
	//m_pConnection.CreateInstance(__uuidof(Connection));

	m_strConnectionString = connectionString;
	m_bAccessConnection = true;
}

CDbConnection::CDbConnection() : m_pConnection(NULL), m_bClosed(true)
{
}

CDbConnection::~CDbConnection()
{
	Close();
}
//////////////////////////////////////////////////////////////////////////
_ConnectionPtr CDbConnection::m_pStConnection = NULL;
CString CDbConnection::m_strStConString = "";

bool CDbConnection::Open()
{
	try
	{
		if (m_pStConnection == NULL/* || m_pStConnection->State == 0*/)
		{
			m_strStConString = m_strConnectionString;
			m_pStConnection.CreateInstance(__uuidof(Connection));
			m_pStConnection->CursorLocation = adUseClient;	// 设置好客户端游标，否则CDbDataReader::Read函数m_pRecordset->MoveFirst();会出错
			m_pStConnection->Open(m_strStConString.GetBuffer(500), "", "", adModeUnknown);
			m_strStConString.ReleaseBuffer();
		}
		else
		{			
			if (m_strConnectionString.CompareNoCase(m_strStConString) != 0)
			{
				if (m_pStConnection->State)
				{
					m_pStConnection->Close();
					//m_pStConnection = NULL;		// 不能置为NULL，否则Access连接时m_pStConnection将会无效
				}

				m_strStConString = m_strConnectionString;
				m_pStConnection->Open(m_strStConString.GetBuffer(500), "", "", adModeUnknown);
				m_strStConString.ReleaseBuffer();
			}
		}
		//m_pConnection->Open(m_strConnectionString.GetBuffer(200), "", "", adModeUnknown);
		//m_strConnectionString.ReleaseBuffer();

		return true;
	}
	catch (_com_error e)
	{
		CString strErrMsg;
		strErrMsg.Format(TEXT("打开数据库连接失败!详细信息: %s。"), e.ErrorMessage());
		AfxMessageBox(strErrMsg);
		m_pStConnection = NULL;		// 智能指针的对象，这里不能进行Close

		return false;
	}
}

void CDbConnection::Close()
{
// 	if (m_pStConnection != NULL && m_pStConnection->State)
// 		m_pStConnection->Close();

	if (!m_bAccessConnection)
	{
		Release();
	}

	// 关闭COM库的支持
	if (!m_bClosed)
	{
		::CoUninitialize();
		m_bClosed = true;
	}
}

_ConnectionPtr CDbConnection::GetConnectionPtr()
{
	return m_pStConnection;	
}

void CDbConnection::BeginTrans()
{
	m_pStConnection->BeginTrans();
}

void CDbConnection::CommitTrans()
{
	m_pStConnection->CommitTrans();
}

void CDbConnection::Release()
{
	if (m_pStConnection == NULL)
	{
		return;
	}

	if (m_pStConnection->State)
	{	
		m_pStConnection->Close();
		m_pStConnection = NULL;
	}
}

void CDbConnection::RollbackTrans()
{
	m_pStConnection->RollbackTrans();	
}

bool CDbConnection::TableExist( const TCHAR *tableName )
{
	_variant_t varSchema;
	_RecordsetPtr pRstSchema = m_pStConnection->OpenSchema(adSchemaTables, &varSchema);
	bool bFound = false;
	pRstSchema->MoveFirst();
	while (pRstSchema->EndOfFile == VARIANT_FALSE)
	{
		COleVariant vaHolder = pRstSchema->GetCollect(TEXT("TABLE_TYPE"));
		CString strType = (LPCWSTR)_bstr_t(vaHolder);
		
		if (strType.CompareNoCase(TEXT("TABLE")) == 0)
		{
			vaHolder = pRstSchema->GetCollect(TEXT("TABLE_NAME"));
			CString strName = (LPCWSTR)_bstr_t(vaHolder);
			if (strName.CompareNoCase(tableName) == 0)
			{
				bFound = true;
				break;
			}
		}
		
		pRstSchema->MoveNext();
	}
	pRstSchema->Close();
	
	return bFound;
}

void CDbConnection::SetIsAccessConnection( bool bAccessCon )
{
	m_bAccessConnection = bAccessCon;
}

bool CDbConnection::FieldExist( const TCHAR* tableName, const TCHAR* fieldName )
{
	_variant_t varSchema;
	_RecordsetPtr pRstSchema = m_pStConnection->OpenSchema(adSchemaColumns, &varSchema);
	bool bFound = false;
	pRstSchema->MoveFirst();
	while (pRstSchema->EndOfFile == VARIANT_FALSE)
	{
		COleVariant vaHolder = pRstSchema->GetCollect(TEXT("TABLE_NAME"));
		CString strTableName = (LPCWSTR)_bstr_t(vaHolder);
		
		if (strTableName.CompareNoCase(tableName) == 0)
		{
			vaHolder = pRstSchema->GetCollect(TEXT("COLUMN_NAME"));
			CString strColumnName = (LPCWSTR)_bstr_t(vaHolder);
			if (strColumnName.CompareNoCase(fieldName) == 0)
			{
				bFound = true;
				break;
			}
		}
		
		pRstSchema->MoveNext();
	}
	pRstSchema->Close();
	
	return bFound;
}
