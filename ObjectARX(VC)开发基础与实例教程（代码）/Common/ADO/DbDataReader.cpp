// DbDataReader.cpp: implementation of the CDbDataReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DbDataReader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDbDataReader::CDbDataReader() : m_pRecordset(NULL), m_bFirstLine(true)
{
	m_pRecordset.CreateInstance(__uuidof(Recordset));
}

CDbDataReader::CDbDataReader( _RecordsetPtr pRecordset )
{
	m_pRecordset = pRecordset->Clone(adLockOptimistic);
}
CDbDataReader::~CDbDataReader()
{
	if (m_pRecordset != NULL && m_pRecordset->State)
		m_pRecordset->Close();
}
//////////////////////////////////////////////////////////////////////////
CDbObject CDbDataReader::operator[]( const TCHAR* field )
{
	CDbObject result;
	try
	{
		COleVariant vaHolder = m_pRecordset->GetCollect(field);
		result.Set(vaHolder);
		return result;
	}
	catch (_com_error e)
	{
		assert(false);
		CString strErrMsg;
		strErrMsg.Format(TEXT("获得字段内容失败!详细信息: %s"), e.ErrorMessage());
		AfxMessageBox(strErrMsg);
		
		return result;
	}
}

bool CDbDataReader::Read()
{	
	try
	{
		if (m_pRecordset->EndOfFile == VARIANT_FALSE)
		{
			if (m_bFirstLine)
			{
				m_pRecordset->MoveFirst();
				m_bFirstLine = false;
			}
			else
			{
				m_pRecordset->MoveNext();
			}
			
			if (m_pRecordset->EndOfFile == VARIANT_TRUE)
			{
				m_bFirstLine = true;
				return false;
			}
			else
			{
				return true;
			}
		}
		else		// 这个分支实际上不会访问到
		{
			m_bFirstLine = true;
			return false;
		}
	}
	catch (_com_error e)
	{
		CString strErrMsg;
		strErrMsg.Format(TEXT("读取下一行内容失败!详细信息: %s"), e.ErrorMessage());
		_bstr_t   bstrSource(e.Source()); 
		_bstr_t   bstrDescription(e.Description()); 
		CString str1, str2;
		str1.Format(TEXT("%s"), (LPCTSTR)bstrSource);
		str2.Format(TEXT("%s"), (LPCTSTR)bstrDescription);
		AfxMessageBox(strErrMsg);
		
		m_bFirstLine = true;
		return false;
	}
}

_RecordsetPtr& CDbDataReader::GetRecordsetPtr()
{
	return m_pRecordset;	
}

void CDbDataReader::SetRecordsetPtr(_RecordsetPtr &recordset)
{
	m_pRecordset = recordset;
}

void CDbDataReader::Close()
{
	if (m_pRecordset != NULL && m_pRecordset->State)
		m_pRecordset->Close();
}

void CDbDataReader::SetFirstLine( bool bFirstLine )
{
	m_bFirstLine = bFirstLine;
}

bool CDbDataReader::GetClobField( const TCHAR* field, CString &strResult )
{
	long lDataLength = this->GetRecordsetPtr()->Fields->Item[field]->ActualSize;
	if (lDataLength > 0)		
	{		
		_variant_t varBLOB = this->GetRecordsetPtr()->GetFields()->GetItem(_variant_t(field))->GetChunk(lDataLength); 
		
		if (varBLOB.vt== VT_BSTR && varBLOB.vt != VT_EMPTY && varBLOB.vt != VT_NULL)			
		{
			strResult = varBLOB.bstrVal;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		strResult = TEXT("");
		return true;
	}
}
