//-----------------------------------------------------------------------------
#ifndef ARX__ARXMSGHANDLER_H__20081010_150116
#define ARX__ARXMSGHANDLER_H__20081010_150116

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcToolBar.h"

class CArxMsgHandler : public CWnd {
	DECLARE_DYNAMIC (CArxMsgHandler)

public:
	CArxMsgHandler () ;

public:
	//{{AFX_VIRTUAL(CArxMsgHandler)
	//}}AFX_VIRTUAL

public:
	virtual ~CArxMsgHandler () ;

protected:
	//{{AFX_MSG(CArxMsgHandler)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnButtonFirst();
	afx_msg void OnButtonSecond();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP ()

private:
	CAcToolBar* m_pToolbar;
} ;

BOOL CreateArxMsgHandler () ;
void DestroyArxMsgHandler () ;
CArxMsgHandler *GetArxMsgHandler () ;

#endif //----- ARX__ARXMSGHANDLER_H__20081010_150116
