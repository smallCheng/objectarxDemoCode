//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\SymbolTable\TextStyleUtil.h"

// This is command 'ADDTEXTSTYLE'
void ZffChap4AddTextStyle()
{
	CString textStyleName = TEXT("≤‚ ‘◊÷ÃÂ");
	AcDbObjectId textStyleId = CTextStyleUtil::GetAt(textStyleName);
	if (textStyleId.isNull())
	{
		CTextStyleUtil::Add(textStyleName, TEXT("txt.shx"), TEXT("hztxt.shx"));
	}
}

