//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\CustomObjectDB\ZffDwgScale.h"
#include <dbdict.h>

const CString DWG_SCALE_KEY = TEXT("DwgScale");

// This is command 'SETDWGSCALE'
void ZffChap9SetDwgScale()
{
	// 获得有名对象字典
	AcDbDictionary *pNameObjDict = NULL;
	acdbHostApplicationServices()->workingDatabase()
		->getNamedObjectsDictionary(pNameObjDict, AcDb::kForWrite);

	// 想根字典中添加ZffDwgScale对象
	AcDbObjectId dictObjId;
	ZffDwgScale *pDwgScale = new ZffDwgScale();
	pDwgScale->Set(1, 100);
	pNameObjDict->setAt(DWG_SCALE_KEY, pDwgScale, dictObjId);
	pDwgScale->close();
	pNameObjDict->close();
}

// This is command 'GETDWGSCALE'
void ZffChap9GetDwgScale()
{
	// 获得对象有名字典中指定的字典项
	AcDbDictionary *pNameObjDict = NULL;
	Acad::ErrorStatus es;
	acdbHostApplicationServices()->workingDatabase()
		->getNamedObjectsDictionary(pNameObjDict, AcDb::kForRead);
	ZffDwgScale *pDwgScale = NULL;
	es = pNameObjDict->getAt(DWG_SCALE_KEY, (AcDbObject*&)pDwgScale, AcDb::kForRead);
	pNameObjDict->close();
	
	// 如果不存在指定的字典项，退出程序
	if (es == Acad::eKeyNotFound)
	{
		acutPrintf(TEXT("\n不存在字典项%s."), DWG_SCALE_KEY);
		return;
	}
	
	// 获得指定的对象字典中的对象
	acutPrintf(TEXT("\n当前图形条件图比例:%d, 出图比例:%d"), pDwgScale->GetInfoScale(), pDwgScale->GetLabelScale());
	pDwgScale->close();
}

