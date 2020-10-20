// DbObject.cpp: implementation of the CDbObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DbObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDbObject::CDbObject()
{
	SetNull();
}

CDbObject::CDbObject( const COleVariant &variant )
{
	m_variant = variant;
	//SetNull();
}

CDbObject::~CDbObject()
{

}

void CDbObject::Set( const COleVariant &variant )
{
	m_variant = variant;	
	if (m_variant.vt == VT_EMPTY)
		SetNull();
}

CString CDbObject::ToString()
{
	if (IsNull())
	{
		return "";
	}
	else
	{
		return (LPCWSTR)_bstr_t(m_variant);
	}
}

bool CDbObject::IsNull()
{
	return m_variant.vt == VT_NULL;	
}

void CDbObject::SetNull()
{
	if (!IsNull())	
		m_variant.vt = VT_NULL;
}

int CDbObject::ToInteger()
{
	if (IsNull())
	{
		return 0;
	}
	else
	{
		if (m_variant.vt == VT_I2)
		{
			return (int)m_variant.iVal;
		}
		else if (m_variant.vt == VT_DECIMAL)
		{
			return (int)((long)_variant_t(m_variant));
		}
// 		else if (m_variant.vt == VT_I4)
// 		{
// 			return (int)m_variant.lVal;
// 		}
		else
		{
			return (int)m_variant.lVal;
		}
	}
}

long CDbObject::ToLong()
{
	if (IsNull())
	{
		return 0;
	}
	else
	{
		// 2011-11-28：如果是SqlServer数据库，使用Select @@Identity返回值实际上是VT_DECIMAL，因此需要将默认的返回值设置为(long)m_variant.lVal;
		if (m_variant.vt == VT_I2)
		{
			return (long)m_variant.iVal;
		}
		else if (m_variant.vt == VT_DECIMAL)
		{
			return (long)_variant_t(m_variant);
		}
// 		else if (m_variant.vt == VT_I4)
// 		{
// 			return (long)m_variant.lVal;
// 		}
		else
		{
			return (long)m_variant.lVal;
		}
	}
}

byte CDbObject::ToByte()
{
	if (IsNull())
	{
		return 0;
	}
	else
	{
		return (byte)m_variant.bVal;
	}
}

bool CDbObject::ToBool()
{
	return (m_variant.boolVal != false);
}

double CDbObject::ToDouble()
{
	if (m_variant.vt == VT_R8)
	{
		return (double)m_variant.dblVal;
	}
	else if (m_variant.vt == VT_I4)
	{
		return (double)m_variant.intVal;
	}
	else if (m_variant.vt == VT_DECIMAL)
	{
		return (double)_variant_t(m_variant);
	}
	else
	{
		return 0;
	}
}

short CDbObject::ToShort()
{
	return (short)m_variant.iVal;
}

CTime CDbObject::ToDateTime()
{
	COleDateTime dt(m_variant.date);
	SYSTEMTIME   systime; 
	VariantTimeToSystemTime(dt, &systime); 
	return CTime(systime);
}
