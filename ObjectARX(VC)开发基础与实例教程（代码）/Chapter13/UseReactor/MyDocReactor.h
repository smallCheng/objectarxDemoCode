// MyDocReactor.h: interface for the CMyDocReactor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDOCREACTOR_H__63605086_7719_4F74_9C1C_B6F55CC49639__INCLUDED_)
#define AFX_MYDOCREACTOR_H__63605086_7719_4F74_9C1C_B6F55CC49639__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyDocReactor : public AcApDocManagerReactor
{
public:
	CMyDocReactor();
	virtual ~CMyDocReactor();

	//”√”⁄Ω˚”√Line√¸¡Ó;
	virtual void documentLockModeChanged(AcApDocument* pDoc,
		AcAp::DocLockMode myPreviousMode,
		AcAp::DocLockMode myCurrentMode,
		AcAp::DocLockMode currentMode,
        const char* pGlobalCmdName);

	virtual void documentToBeDestroyed(AcApDocument* pDocToDestroy);
	virtual void documentCreated(AcApDocument* pDocCreating);
};

#endif // !defined(AFX_MYDOCREACTOR_H__63605086_7719_4F74_9C1C_B6F55CC49639__INCLUDED_)
