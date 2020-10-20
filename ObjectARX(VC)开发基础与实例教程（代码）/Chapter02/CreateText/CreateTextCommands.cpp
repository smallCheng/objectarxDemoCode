//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Entity\TextUtil.h"

// This is command 'ADDTEXT'
void ZffChap2AddText()
{
	// 创建单行文字
	AcGePoint3d ptInsert(0, 18, 0);
	CTextUtil::AddText(ptInsert, TEXT("北京智帆高科"));
	
	// 创建多行文字
	ptInsert.set(0, 0, 0);
	CTextUtil::AddMText(ptInsert, TEXT("学习和使用ObjectARX需要付出你的努力."));
}

