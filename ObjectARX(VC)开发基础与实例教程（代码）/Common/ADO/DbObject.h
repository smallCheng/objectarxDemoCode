// DbObject.h: interface for the CDbObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBOBJECT_H__21ED5A84_0F8E_4672_946A_5C47BA6F575B__INCLUDED_)
#define AFX_DBOBJECT_H__21ED5A84_0F8E_4672_946A_5C47BA6F575B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined (_ZFGKCOMMONLIB_)
#define ZFGK_DLLIMPEXP __declspec(dllexport)
#else
#define ZFGK_DLLIMPEXP 
#endif

class ZFGK_DLLIMPEXP CDbObject  
{
public:
	CDbObject();
	CDbObject(const COleVariant &variant);
	virtual ~CDbObject();

	// 使用一个COleVariant对象来初始化CDbObject对象
	void Set(const COleVariant &variant);

	// 转换为字符串
	CString ToString();

	// 转换为整数
	int ToInteger();

	// 转换为short
	short ToShort();
	
	// 转换为长整型
	long ToLong();

	// 转换为字节
	byte ToByte();

	// 是否为空
	bool IsNull();
	
	// 转换为bool
	bool ToBool();
	
	// 转换为double
	double ToDouble();

	// 转换为CTime
	CTime ToDateTime();

private:
	void SetNull();

private:
	COleVariant m_variant;
};

#endif // !defined(AFX_DBOBJECT_H__21ED5A84_0F8E_4672_946A_5C47BA6F575B__INCLUDED_)
