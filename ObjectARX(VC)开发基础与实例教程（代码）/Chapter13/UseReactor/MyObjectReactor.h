// MyObjectReactor.h: interface for the CMyObjectReactor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYOBJECTREACTOR_H__89798AC8_DB70_4D32_A5C1_44F934EF70BA__INCLUDED_)
#define AFX_MYOBJECTREACTOR_H__89798AC8_DB70_4D32_A5C1_44F934EF70BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyObjectReactor : public AcDbObject
{
public:
	// 如果没有用向导创建这个类一定记得加上这句话
	ACRX_DECLARE_MEMBERS(CMyObjectReactor);

	CMyObjectReactor();
	virtual ~CMyObjectReactor();

	Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
    Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;

	void modified(const AcDbObject* pObj);
	virtual void erased(const AcDbObject* dbObj, Adesk::Boolean pErasing = true);

	// 设置与其关联的实体
	void SetLinkEntId(AcDbObjectId entId);
    
private:
	AcDbObjectId m_entId;		// 与通知对象关联的实体ID
};

#endif // !defined(AFX_MYOBJECTREACTOR_H__89798AC8_DB70_4D32_A5C1_44F934EF70BA__INCLUDED_)
