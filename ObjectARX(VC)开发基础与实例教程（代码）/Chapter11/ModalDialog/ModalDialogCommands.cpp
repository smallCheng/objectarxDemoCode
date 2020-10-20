//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "MfcDialog.h"
#include "ArxDialog.h"

// This is command 'MFCMODAL'
void ZffCHAP11MfcModal()
{
	// 显示MFC的模态对话框
	CMfcDialog theDialog;
	if (theDialog.DoModal() == IDOK)
	{
		AfxMessageBox(_T("关闭对话框！"));
	}	
}

// This is command 'ARXMODAL'
void ZffCHAP11ArxModal()
{
	// 防止资源冲突
	CAcModuleResourceOverride resOverride;
	
	// 显示ObjectARX的模态对话框
	CArxDialog theDialog;
	theDialog.DoModal();		
}

