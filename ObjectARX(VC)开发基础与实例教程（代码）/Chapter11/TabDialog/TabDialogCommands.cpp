//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "OptionSheet.h"

// This is command 'SHOWTABDLG'
void ZffChap11ShowTabDlg()
{
	CAcModuleResourceOverride myResource;
	COptionSheet dlg;
	dlg.DoModal();
}

