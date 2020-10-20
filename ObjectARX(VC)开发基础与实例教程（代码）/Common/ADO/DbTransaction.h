// DbTransaction.h: interface for the CDbTransaction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTRANSACTION_H__3952A420_3F06_4F11_85A4_B720C146A90E__INCLUDED_)
#define AFX_DBTRANSACTION_H__3952A420_3F06_4F11_85A4_B720C146A90E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined (_ZFGKCOMMONLIB_)
#define ZFGK_DLLIMPEXP __declspec(dllexport)
#else
#define ZFGK_DLLIMPEXP 
#endif

class ZFGK_DLLIMPEXP CDbTransaction  
{
public:
	CDbTransaction();
	virtual ~CDbTransaction();

};

#endif // !defined(AFX_DBTRANSACTION_H__3952A420_3F06_4F11_85A4_B720C146A90E__INCLUDED_)
