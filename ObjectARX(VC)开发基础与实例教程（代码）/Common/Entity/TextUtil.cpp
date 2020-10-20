// TextUtil.cpp: implementation of the CTextUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TextUtil.h"
#include <dbents.h>
#include "..\Document\DwgDatabaseUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextUtil::CTextUtil()
{

}

CTextUtil::~CTextUtil()
{

}

AcDbObjectId CTextUtil::AddText( const AcGePoint3d& ptInsert, const TCHAR* text, 
								AcDbObjectId style, double height, double rotation )
{
	AcDbText *pText = new AcDbText(ptInsert, text, style, height, rotation);
	
	return CDwgDatabaseUtil::PostToModelSpace(pText);
}

AcDbObjectId CTextUtil::AddMText( const AcGePoint3d& ptInsert, const TCHAR* text, 
								 AcDbObjectId style, double height, double width )
{
	AcDbMText *pMText = new AcDbMText();
	
	// 设置多行文字的特性
	pMText->setTextStyle(style);
	pMText->setContents(text);
	pMText->setLocation(ptInsert);
	pMText->setTextHeight(height);
	pMText->setWidth(width);
	pMText->setAttachment(AcDbMText::kBottomLeft);
	
	return CDwgDatabaseUtil::PostToModelSpace(pMText);
}
