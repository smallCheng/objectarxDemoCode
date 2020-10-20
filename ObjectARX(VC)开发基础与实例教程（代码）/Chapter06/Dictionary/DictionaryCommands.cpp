//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Interaction\SelectUtil.h"
#include <dbxrecrd.h>
#include <dbdict.h>
#include <geassign.h>
#include <dbents.h>

// This is command 'ADDXRECORD'
void ZffChap6AddXRecord()
{
	// 提示用户选择所要添加扩展记录的图形对象
	AcDbEntity *pEnt = NULL;
	AcGePoint3d pickPoint;
	if (CSelectUtil::PromptSelectEntity(TEXT("\n选择所要添加扩展记录的实体:"), AcDbEntity::desc(), pEnt, pickPoint))
	{
		// 向实体中添加扩展字典
		pEnt->createExtensionDictionary();
		AcDbObjectId dictObjId = pEnt->extensionDictionary();
		pEnt->close();

		// 创建扩展记录实体
		AcDbXrecord *pXrec = new AcDbXrecord;
		
		// 向扩展字典中添加一条记录
		AcDbObjectId xRecObjId;
		AcDbDictionary *pDict = NULL;
		if (acdbOpenObject(pDict, dictObjId, AcDb::kForWrite) == Acad::eOk)
		{
			pDict->setAt(TEXT("XRecord"), pXrec, xRecObjId);
			pDict->close();
		}
		
		// 设置扩展记录的内容
		struct resbuf* pRb = acutBuildList(AcDb::kDxfText, TEXT("测试字符串数据"), 
			AcDb::kDxfInt32, 12, 
			AcDb::kDxfReal, 3.14, 
			AcDb::kDxfXCoord, asDblArray(pickPoint), 
			RTNONE);
		pXrec->setFromRbChain(*pRb);	// 扩展数据内容填充扩展记录对象
		pXrec->close();
		acutRelRb(pRb);
	}
}

// This is command 'VIEWXRECORD'
void ZffChap6ViewXRecord()
{
	// 提示用户选择所要查看扩展记录的图形对象
	AcDbEntity *pEnt = NULL;
	AcGePoint3d pickPoint;
	if (CSelectUtil::PromptSelectEntity(TEXT("\n选择所要查看扩展记录的实体:"), AcDbEntity::desc(), pEnt, pickPoint))
	{
		// 获得实体的扩展字典
		AcDbObjectId dictObjId = pEnt->extensionDictionary(); 
		pEnt->close();		
		if (dictObjId.isNull())
		{
			acutPrintf(TEXT("\n所选择的实体不包含扩展字典!"));
			return;
		}

		// 打开扩展字典，获得与关键字"XRecord"关联的扩展记录
		AcDbDictionary *pDict = NULL;
		AcDbXrecord *pXrec = NULL;
		struct resbuf *pRb = NULL;
		if (acdbOpenObject(pDict, dictObjId, AcDb::kForRead) == Acad::eOk)
		{
			pDict->getAt(TEXT("XRecord"), (AcDbObject*&)pXrec, AcDb::kForRead);
			
			// 获得扩展记录的数据链表并关闭扩展数据对象			
			pXrec->rbChain(&pRb);
			pXrec->close();

			pDict->close();
		}
		
		if (pRb != NULL)
		{
			// 在命令行显示扩展记录内容
			struct resbuf *pTemp = pRb;
			
			acutPrintf(TEXT("\n字符串类型的扩展数据是：%s"), pTemp->resval.rstring);
			
			pTemp = pTemp->rbnext;
			acutPrintf(TEXT("\n整数类型的扩展数据是：%d"), pTemp->resval.rint);
			
			pTemp = pTemp->rbnext;
			acutPrintf(TEXT("\n实数类型的扩展数据是：%.2f"), pTemp->resval.rreal);
			
			pTemp = pTemp->rbnext;
			acutPrintf(TEXT("\n点坐标类型的扩展数据是：(%.2f, %.2f, %.2f)"), 
				pTemp->resval.rpoint[X], pTemp->resval.rpoint[Y], 
				pTemp->resval.rpoint[Z]);
			
			acutRelRb(pRb);		
		}
	}	
}

// This is command 'ADDNAMEDICT'
void ZffChap6AddNameDict()
{
	// 获得有名对象字典，向其中添加指定的字典项
	AcDbDictionary *pNameObjDict = NULL;//, 
	acdbHostApplicationServices()->workingDatabase()
		->getNamedObjectsDictionary(pNameObjDict, AcDb::kForWrite);
	// 检查所要添加的字典项是否已经存在
	AcDbObjectId dictObjId;
	AcDbDictionary *pDict = NULL;
	if (pNameObjDict->getAt(TEXT("MyDict"), (AcDbObject*&)pDict, AcDb::kForWrite) == Acad::eKeyNotFound)
	{
		pDict = new AcDbDictionary;
		pNameObjDict->setAt(TEXT("MyDict"), pDict, dictObjId);
		pDict->close();
	}
	pNameObjDict->close();
	
	// 向新建的字典中添加一个图层对象
	if (acdbOpenObject(pDict, dictObjId, AcDb::kForWrite) == Acad::eOk)
	{
		AcDbLayerTableRecord *pLayer = new AcDbLayerTableRecord();		
		AcCmColor color;
		color.setColorIndex(20);
		pLayer->setColor(color);
		pLayer->setIsOff(true);
		pLayer->setIsFrozen(true);
		AcDbObjectId layerId;
		Acad::ErrorStatus es = pDict->setAt(TEXT("LayerKey"), pLayer, layerId);
		pLayer->close();
		pDict->close();
	}
}

// This is command 'VIEWNAMEDICT'
void ZffChap6ViewNameDict()
{
	// 获得对象有名字典中指定的字典项
	AcDbDictionary *pNameObjDict = NULL;
	Acad::ErrorStatus es;
	acdbHostApplicationServices()->workingDatabase()
		->getNamedObjectsDictionary(pNameObjDict, AcDb::kForRead);
	AcDbDictionary *pDict = NULL;
	es = pNameObjDict->getAt(TEXT("MyDict"), (AcDbObject*&)pDict, AcDb::kForRead);
	pNameObjDict->close();
	
	// 如果不存在指定的字典项，退出程序
	if (es == Acad::eKeyNotFound)
	{
		acutPrintf(TEXT("\n不存在字典项MyDict."));
		return;
	}
	
	// 获得指定的对象字典中的对象
	AcDbLayerTableRecord *pLayer = NULL;
	if (pDict->getAt(TEXT("LayerKey"), (AcDbObject*&)pLayer, AcDb::kForRead) == Acad::eOk)
	{
		// 获得实体的信息
		int colorIndex = pLayer->color().colorIndex();
		bool bOff = pLayer->isOff();
		bool bFrozen = pLayer->isFrozen();
		pLayer->close();

		// 在命令行打印实体信息
		acutPrintf(TEXT("\n字典中的图层颜色: %d"), colorIndex);
		acutPrintf(TEXT("\n字典中的图层是否是关闭状态: %s"), bOff ? TEXT("是") : TEXT("否"));
		acutPrintf(TEXT("\n字典中的图层是否是关闭状态: %s"), bFrozen ? TEXT("是") : TEXT("否"));
	}
	pDict->close();
}

