// BlockUtil.cpp: implementation of the CBlockUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BlockUtil.h"
#include <dbents.h>
#include "..\Document\DwgDatabaseUtil.h"
#include <acutmem.h>
#include <IO.H>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBlockUtil::CBlockUtil()
{

}

CBlockUtil::~CBlockUtil()
{

}

// 插入块参照
AcDbObjectId CBlockUtil::InsertBlockRef( AcDbObjectId blkDefId, const AcGePoint3d &insertPoint, double scale, 
										double rotation )
{
	// 设置图块的插入点、旋转角度、比例等等
	AcDbBlockReference *pBlkRef = new AcDbBlockReference(insertPoint, blkDefId);
	pBlkRef->setRotation(rotation);
	SetScaleFactor(pBlkRef, scale);
	
	// 把新建的图块参照实体加入到新建的块表记录中，并取得插入图块的实体Id，用于返回值
	return CDwgDatabaseUtil::PostToModelSpace(pBlkRef);
}

// 修改块参照的插入比例
void CBlockUtil::SetScaleFactor( AcDbBlockReference *pBlkRef, double scale )
{
	assert (pBlkRef);
	
	AcGeScale3d geScale(scale, scale, scale);
	pBlkRef->setScaleFactors(geScale);
}

// 获得指定名称的块定义
AcDbObjectId CBlockUtil::GetBlkDefId( const TCHAR* blkDefName, AcDbDatabase *pDb )
{
	AcDbBlockTable* pBlockTable = NULL;
	Acad::ErrorStatus es = pDb->getBlockTable(pBlockTable, AcDb::kForRead);
	AcDbObjectId blkDefId;
	es = pBlockTable->getAt(blkDefName, blkDefId);
	pBlockTable->close();
	
	if (es == Acad::eOk)
	{
		return blkDefId;
	}
	else
	{
		return AcDbObjectId::kNull;
	}
}

AcDbObjectId CBlockUtil::InsertBlockRefWithAttribute( const AcDbObjectId &blkDefId, const AcGePoint3d &insertPoint, 
													 double scale, double rotation )
{
	// 创建块参照对象
	AcDbBlockReference *pBlkRef = new AcDbBlockReference(insertPoint, blkDefId);
	SetScaleFactor(pBlkRef, scale);
	pBlkRef->setRotation(rotation);

	// 判断指定的块表记录是否包含属性定义
	AcDbBlockTableRecord *pBlkDefRcd = NULL;
	if (acdbOpenObject(pBlkDefRcd, pBlkRef->blockTableRecord(), AcDb::kForRead) == Acad::eOk)
	{
		if (pBlkDefRcd->hasAttributeDefinitions())
		{
			// 创建块表记录遍历器，用于访问块定义中的所有实体
			AcDbBlockTableRecordIterator *pItr = NULL;
			pBlkDefRcd->newIterator(pItr);
			
			for (pItr->start(); !pItr->done(); pItr->step())
			{
				AcDbEntity *pEnt = NULL;
				if (pItr->getEntity(pEnt, AcDb::kForRead) == Acad::eOk)
				{
					// 如果是属性定义，就向块参照添加属性
					AcDbAttributeDefinition *pAttDef = AcDbAttributeDefinition::cast(pEnt);
					if (pAttDef != NULL)
					{
						AppendAttributeToBlkRef(pBlkRef, pAttDef);
					}
					pEnt->close();
				}
			}
			delete pItr;
		}
		
		pBlkDefRcd->close();
	}

	// 将块参照添加到模型空间
	return CDwgDatabaseUtil::PostToModelSpace(pBlkRef);
}

bool CBlockUtil::SetBlockRefAttribute( AcDbBlockReference *pBlkRef, const TCHAR* tag, const TCHAR* val )
{	
	AcDbBlockTableRecord *pBlkDefRcd = NULL;
	bool bRet = true;
	if (acdbOpenObject(pBlkDefRcd, pBlkRef->blockTableRecord(), AcDb::kForRead) == Acad::eOk)
	{
		// 块定义中是否包含了对应的属性
		if (pBlkDefRcd->hasAttributeDefinitions())
		{
			AcDbBlockTableRecordIterator *pItr = NULL;
			pBlkDefRcd->newIterator(pItr);
			AcDbEntity *pEnt = NULL;
			
			for (pItr->start(); !pItr->done(); pItr->step())
			{
				pItr->getEntity(pEnt, AcDb::kForRead);
				
				// 检查是否是属性定义
				AcDbAttributeDefinition *pAttDef = AcDbAttributeDefinition::cast(pEnt);
				if (pAttDef != NULL)
				{
					TCHAR* pszTag = pAttDef->tag();
					CString strTag = pszTag;
					acutDelString(pszTag);
					if (strTag.CompareNoCase(tag) == 0)
					{
						// 遍历块参照的所有属性，判断是否包含了对应的属性
						bool bFound = false;
						AcDbObjectIterator *attIt = pBlkRef->attributeIterator();
						for(attIt->start(); !attIt->done(); attIt->step())
						{
							AcDbAttribute *pAtt = NULL;
							Acad::ErrorStatus es = acdbOpenObject(pAtt, attIt->objectId(), AcDb::kForWrite);
							if (es == Acad::eOk)
							{
								pszTag = pAtt->tag();
								strTag = pszTag;
								acutDelString(pszTag);
								if (strTag.CompareNoCase(tag) == 0)
								{
									pAtt->setTextString(val);
									bFound = true;
								}
								pAtt->close();
							}
						}
						delete attIt;
						
						// 如果没有找到给定名称的属性，就新建这个属性
						if (!bFound)
						{
							AppendAttributeToBlkRef(pBlkRef, pAttDef);
						}
					}										
				}
				pEnt->close();
			}
			delete pItr;
		}
		else
		{
			bRet = false;
		}
		
		pBlkDefRcd->close();
	}	
	
	return bRet;
}

void CBlockUtil::AppendAttributeToBlkRef( AcDbBlockReference * pBlkRef, AcDbAttributeDefinition * pAttDef )
{
	// 创建一个新的属性对象
	AcDbAttribute *pAtt = new AcDbAttribute();
	// 从属性定义获得属性对象的对象特性
	pAtt->setPropertiesFrom(pBlkRef);
	pAtt->setLayer(pBlkRef->layerId());
	// 设置属性对象的其他特性
	pAtt->setInvisible(pAttDef->isInvisible());
	pAtt->setPosition(pAttDef->position());
	pAtt->setHeight(pAttDef->height());
	pAtt->setWidthFactor(pAttDef->widthFactor());
	pAtt->setRotation(pAttDef->rotation());
	pAtt->setHorizontalMode(pAttDef->horizontalMode());
	pAtt->setVerticalMode(pAttDef->verticalMode());
	pAtt->setAlignmentPoint(pAttDef->alignmentPoint());
	pAtt->setTextStyle(pAttDef->textStyle());
	pAtt->setAttributeFromBlock(pBlkRef->blockTransform());
	
	// 获得属性对象的Tag、Prompt和TextString
	TCHAR *pStr = pAttDef->tag();
	pAtt->setTag(pStr);
	acutDelString(pStr);
	pAtt->setFieldLength(pAttDef->fieldLength());
	pAtt->setTextString(pAttDef->textString());
	
	// 向块参照追加属性对象
	pBlkRef->appendAttribute(pAtt);
	pAtt->close();
}

bool CBlockUtil::GetAttributeValue( AcDbBlockReference *pBlkRef, const TCHAR* tag, CString &value )
{
	// 创建块表记录的属性遍历器
	bool bFound = false;
	AcDbObjectIterator *pItr = pBlkRef->attributeIterator();
	if (pItr)
	{
		while (!pItr->done())
		{
			AcDbObjectId attId = pItr->objectId();
			AcDbAttribute *pAtt = NULL;
			if (pBlkRef->openAttribute(pAtt, attId, AcDb::kForRead) == Acad::eOk)
			{
				// 块参照中的属性Tag永远都会是大写字母，因此传入的参数需要进行换转
				TCHAR *szTag = pAtt->tag();
				CString strTag = tag;
				strTag.MakeUpper();
				if (_tcscmp(strTag, szTag) == 0)
				{
					TCHAR *szValue = pAtt->textString();	
					value = szValue;
					acutDelString(szValue);
					bFound = true;
				}
				acutDelString(szTag);
				
				pAtt->close();
			}			
			
			pItr->step();
		}
		delete pItr;
		
		return bFound;
	}
	else
	{
		return false;
	}
}

void CBlockUtil::IntersectWith( AcDbBlockReference *pBlkRef, AcDbEntity *pEnt, AcGePoint3dArray &intPoints, 
							   bool bIntersectWithText, bool bProjectToXOY, bool bExtendEntArg )
{
	assert(pBlkRef);
	assert(pEnt);
	
	// 获取块参照对应的变换矩阵
	AcGeMatrix3d xform = pBlkRef->blockTransform();
	
	AcDbObjectId blkTblId = pBlkRef->blockTableRecord();
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	if (acdbOpenObject(pBlkTblRcd, blkTblId, AcDb::kForRead) == Acad::eOk)
	{
		// 块表记录遍历器访问块定义中的每一个实体
		AcDbBlockTableRecordIterator *pIt = NULL;
		pBlkTblRcd->newIterator(pIt);
		for (pIt->start(); !pIt->done(); pIt->step())
		{
			AcDbEntity *pSubEnt = NULL;
			if (pIt->getEntity(pSubEnt, AcDb::kForRead) == Acad::eOk)
			{
				// 如果不与文字求交点，判断当前实体的类型，发现是文字就跳过去
				if ((!bIntersectWithText) && (pSubEnt->isKindOf(AcDbMText::desc()) || pSubEnt->isKindOf(AcDbMText::desc())))
				{
					pSubEnt->close();
					continue;
				}
				
				// 复制一个实体进行变换，避免修改块定义中的子实体
				AcDbEntity *pEntCopy = NULL;
				if (pSubEnt->getTransformedCopy(xform, pEntCopy) == Acad::eOk)
				{
					// 是否延长求交点
					AcDb::Intersect intMode = bExtendEntArg ? AcDb::kExtendArg : AcDb::kOnBothOperands;
					
					if (bProjectToXOY)
					{
						pEntCopy->intersectWith(pEnt, intMode, AcGePlane::kXYPlane, intPoints);
					}
					else
					{
						pEntCopy->intersectWith(pEnt, intMode, intPoints);
					}
					delete pEntCopy;
				}
				
				pSubEnt->close();
			}			
		}
		delete pIt;
		
		pBlkTblRcd->close();
	}
}

AcDbObjectId CBlockUtil::CopyBlockDefFromOtherDwg( const TCHAR* fileName, const TCHAR* blkDefName )
{
	AcDbObjectId blockRefId = AcDbObjectId::kNull;

	// 使用_SH_DENYNO参数打开图形(只读打开)，允许其它用户读写该文件
	AcDbDatabase* pSourceDwg = new AcDbDatabase(false);	
	Acad::ErrorStatus es = pSourceDwg->readDwgFile(fileName, _SH_DENYNO);
	if (es != Acad::eOk)
	{
		delete pSourceDwg;
		pSourceDwg = NULL;
		
		acutPrintf(TEXT("\n读入dwg图形错误, 图形名称: %s"), fileName);
		return blockRefId;
	}
	
	// 打开外部图形数据库的块表，寻找给定名称的块表记录
	AcDbBlockTable* pBlkTable = NULL;
	es = pSourceDwg->getBlockTable(pBlkTable, AcDb::kForRead);
	assert (es == Acad::eOk);
	bool bRet = false;
	if (pBlkTable->has(blkDefName))	// 不存在指定的图块
	{	
		AcDbObjectId destBlkDefId;		// 指定图块的块表记录Id
		es = pBlkTable->getAt(blkDefName, destBlkDefId);
		
		// 把指定的图块输出到一个临时图形数据库
		AcDbDatabase* pTempDb = NULL;	// 注意：这里千万不能new
		es = pSourceDwg->wblock(pTempDb, destBlkDefId);
		assert (es == Acad::eOk);		
		
		// 把该临时图形数据库作为块插入到当前dwg
		AcDbDatabase* pCurDb = acdbHostApplicationServices()->workingDatabase();
		es = pCurDb->insert(blockRefId, blkDefName, pTempDb);
		assert (es == Acad::eOk);
		delete pTempDb;
		pTempDb = NULL;
	}
	else
	{
		acutPrintf(TEXT("\n给定的DWG文件中, 不存在指定名称的块表记录."));
	}
	pBlkTable->close();
	
	delete pSourceDwg;
	pSourceDwg = NULL;
	
	return blockRefId;
}

AcDbObjectId CBlockUtil::InsertDwgBlockDef( const TCHAR* dwgFileName, const TCHAR* blkName, bool bOverwriteIfExist, 
										   AcDbDatabase *pDb )
{
	// 是否包含指定名称的块定义
	AcDbObjectId blkDefId = GetBlkDefId(blkName, pDb);
	if (blkDefId.isNull() || bOverwriteIfExist)
	{
		if (_taccess(dwgFileName, 0) != -1)
		{
			AcDbDatabase *pBlkDb = new AcDbDatabase(false);
			Acad::ErrorStatus es = pBlkDb->readDwgFile(dwgFileName, _SH_DENYNO);
			if (es == Acad::eOk)
			{
				es = pDb->insert(blkDefId, blkName, pBlkDb);
				if (es != Acad::eOk)
				{
					CString strMsg;
					strMsg.Format(TEXT("CBlockUtil::InsertDwgBlockDef函数, insert失败:%d."), (int)es);
					AfxMessageBox(strMsg);
				}
			}
			else
			{
				CString strMsg;
				strMsg.Format(TEXT("CBlockUtil::InsertDwgBlockDef函数, readDwgFile失败:%d."), (int)es);
				AfxMessageBox(strMsg);
			}
			delete pBlkDb;
		}
		else
		{
			AfxMessageBox(TEXT("CBlockUtil::InsertDwgBlockDef函数, 未找到指定的图块文件."));
		}
	}
	
	return blkDefId;
}
