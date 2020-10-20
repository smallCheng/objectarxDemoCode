//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"

// 声明这个全局函数的定义在其他的obj中
extern AsdkDataManager<CDocData> DocVars;

// This is command 'ENTTIPON'
void ZffChap5EntTipOn()
{
	if (!DocVars.docData().m_pIPM)
	{
		new CEntInfoTipHandler;
	}
}

// This is command 'ENTTIPOFF'
void ZffChap5EntTipOff()
{
	if (DocVars.docData().m_pIPM)
	{
		delete DocVars.docData().m_pIPM;
		DocVars.docData().m_pIPM = NULL;
	}
}

