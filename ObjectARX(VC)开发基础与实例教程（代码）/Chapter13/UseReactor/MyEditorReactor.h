// MyEditorReactor.h: interface for the CMyEditorReactor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYEDITORREACTOR_H__32F7D1CB_A24C_4B3A_8DC7_53928EEEB59E__INCLUDED_)
#define AFX_MYEDITORREACTOR_H__32F7D1CB_A24C_4B3A_8DC7_53928EEEB59E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyEditorReactor : public AcEditorReactor
{
public:
	CMyEditorReactor();
	virtual ~CMyEditorReactor();

	virtual void commandWillStart(const char* cmdStr);
	virtual void commandEnded(const TCHAR* cmdStr);
};

#endif // !defined(AFX_MYEDITORREACTOR_H__32F7D1CB_A24C_4B3A_8DC7_53928EEEB59E__INCLUDED_)
