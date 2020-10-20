// MyDocReactor.cpp: implementation of the CMyDocReactor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyDocReactor.h"
#include "MyDbReactor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CMyDbReactor *g_dbReactor;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyDocReactor::CMyDocReactor()
{

}

CMyDocReactor::~CMyDocReactor()
{

}

void CMyDocReactor::documentLockModeChanged( AcApDocument* pDoc, AcAp::DocLockMode myPreviousMode, 
											AcAp::DocLockMode myCurrentMode, AcAp::DocLockMode currentMode, 
											const char* pGlobalCmdName )
{
	if (strcmp(pGlobalCmdName, "LINE") == 0)
	{
		acutPrintf(TEXT("\nLine命令被当前软件禁止."));
		veto();
	}
}

void CMyDocReactor::documentToBeDestroyed( AcApDocument* pDocToDestroy )
{
	pDocToDestroy->database()->removeReactor(g_dbReactor);
}

void CMyDocReactor::documentCreated( AcApDocument* pDocCreating )
{
	pDocCreating->database()->addReactor(g_dbReactor);
}
