// MyDbReactor.h: interface for the CMyDbReactor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDBREACTOR_H__2289705F_C4DA_4C58_9910_D8AECE597D96__INCLUDED_)
#define AFX_MYDBREACTOR_H__2289705F_C4DA_4C58_9910_D8AECE597D96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyDbReactor : public AcDbDatabaseReactor
{
public:
	CMyDbReactor();
	virtual ~CMyDbReactor();

	virtual void objectAppended (const AcDbDatabase* dwg, const AcDbObject* dbObj);
};

#endif // !defined(AFX_MYDBREACTOR_H__2289705F_C4DA_4C58_9910_D8AECE597D96__INCLUDED_)
