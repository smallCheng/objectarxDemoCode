//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\SymbolTable\LayerUtil.h"
#include <dbsymtb.h>
#include <vector>
#include <acutmem.h>
#include "..\..\Common\Others\ConvertUtil.h"
#include "..\..\Common\Others\StringUtil.h"
#include "..\..\Common\IO\TextFileUtil.h"
#include <IO.H>

// This is command 'NEWLAYER'
void ZffChap4NewLayer()
{
	// 提示用户输入图层名称
	TCHAR layerName[100];
	if (acedGetString(Adesk::kFalse, TEXT("\n输入图层的名称:"), layerName) != RTNORM)
	{
		return;
	}

	// 新建图层
	AcDbObjectId layerId = CLayerUtil::GetLayerId(layerName);
	if (layerId.isValid())
	{
		acutPrintf(TEXT("\n图形中已经存在同名的图层."));
	}
	else
	{
		CLayerUtil::Add(layerName);
		acutPrintf(TEXT("\n成功创建图层."));
	}
}

// This is command 'LAYERCOLOR'
void ZffCHAP4LayerColor()
{
	// 提示用户输入图层名称
	TCHAR layerName[100];
	if (acedGetString(Adesk::kFalse, TEXT("\n输入图层的名称:"), layerName) != RTNORM)
	{
		return;
	}
	
	// 新建图层
	AcDbObjectId layerId = CLayerUtil::GetLayerId(layerName);
	if (layerId.isValid())
	{
		// 获取图层当前的颜色
		AcCmColor oldColor;
		AcDbLayerTableRecord *pLayerTblRcd = NULL;
		if (acdbOpenObject(pLayerTblRcd, layerId, AcDb::kForRead) == Acad::eOk)
		{
			oldColor = pLayerTblRcd->color();
			pLayerTblRcd->close();
		}
		int nCurColor = oldColor.colorIndex();		// 图层修改前的颜色
		int nNewColor = oldColor.colorIndex();		// 用户选择的颜色

		// 弹出"颜色"对话框
		if (acedSetColorDialog(nNewColor, Adesk::kFalse, nCurColor))
		{
			CLayerUtil::SetColor(layerName, nNewColor);
		}
	}
	else
	{
		acutPrintf(TEXT("\n图形中不存在指定名称的图层."));
	}
}

// This is command 'DELETELAYER'
void ZffCHAP4DeleteLayer()
{
	// 提示用户输入图层名称
	TCHAR layerName[100];
	if (acedGetString(Adesk::kFalse, TEXT("\n输入图层的名称:"), layerName) != RTNORM)
	{
		return;
	}
	
	AcDbObjectId layerId = CLayerUtil::GetLayerId(layerName);
	if (layerId.isValid())
	{
		// 删除图层
		AcDbLayerTableRecord *pLayerTblRcd = NULL;
		if (acdbOpenObject(pLayerTblRcd, layerId, AcDb::kForWrite) == Acad::eOk)
		{
			pLayerTblRcd->erase();
			pLayerTblRcd->close();
		}
	}
	else
	{
		acutPrintf(TEXT("\n图形中不存在指定名称的图层."));
	}
}

// This is command 'EXPORTLAYER'
void ZffCHAP4ExportLayer()
{
	// 获得图层列表
	AcDbObjectIdArray layerIds;
	CLayerUtil::GetLayerList(layerIds);

	// 遍历图层列表，构建需要写入到文本文件的字符串集合
	std::vector<CString> lines;
	for (int i = 0; i < layerIds.length(); i++)
	{
		AcDbLayerTableRecord *pLayerTblRcd = NULL;
		if (acdbOpenObject(pLayerTblRcd, layerIds[i], AcDb::kForRead) == Acad::eOk)
		{
			// 输出图层的信息
			std::vector<CString> layerInfos;
			TCHAR *szLayerName;		// 图层名称
			pLayerTblRcd->getName(szLayerName);
			layerInfos.push_back(szLayerName);
			acutDelString(szLayerName);			
											
			AcCmColor color = pLayerTblRcd->color();	// 图层颜色	
			layerInfos.push_back(CConvertUtil::ToString(color.colorIndex()));
								
			AcDbLinetypeTableRecord *pLinetypeTblRcd = NULL;	// 图层线型
			acdbOpenObject(pLinetypeTblRcd, pLayerTblRcd->linetypeObjectId(), AcDb::kForRead);
			TCHAR *szLinetypeName;
			pLinetypeTblRcd->getName(szLinetypeName);
			pLinetypeTblRcd->close();
			layerInfos.push_back(szLinetypeName);
			acutDelString(szLinetypeName);
								
			AcDb::LineWeight lineWeight = pLayerTblRcd->lineWeight();	// 图层的线宽
			int nVal = (int)lineWeight;		// 枚举转换为整型
			layerInfos.push_back(CConvertUtil::ToString(nVal));

			CString strLayerInfo = CStringUtil::Join(layerInfos, TEXT(","));		// 要输出的图层汇总信息
			lines.push_back(strLayerInfo);

			pLayerTblRcd->close();
		}
	}

	// 写入文本文件
	CString fileName = TEXT("C:\\layers.txt");
	CTextFileUtil::Save(fileName, lines);
}

// This is command 'IMPORTLAYER'
void ZffCHAP4ImportLayer()
{
	// 读取文件中的内容
	CString fileName = TEXT("C:\\layers.txt");
	if (_taccess(fileName, 0) != -1)
	{		
		std::vector<CString> lines;
		CTextFileUtil::Load(fileName, lines);

		// 遍历每一个字符串，处理当前图形中的图层
		for (int i = 0; i < lines.size(); i++)
		{
			std::vector<CString> layerInfos;
			CStringUtil::Split(lines[i], TEXT(","), layerInfos, false);
			if (layerInfos.size() == 4)
			{
				CString layerName = layerInfos[0];
				AcDbObjectId layerId = CLayerUtil::GetLayerId(layerName);
				if (layerId.isNull())
				{
					CLayerUtil::Add(layerName);
					layerId = CLayerUtil::GetLayerId(layerName);
				}

				AcDbLayerTableRecord *pLayerTblRcd = NULL;
				if (acdbOpenObject(pLayerTblRcd, layerId, AcDb::kForWrite) == Acad::eOk)
				{
					// 设置颜色
					AcCmColor color;
					Adesk::UInt16 colorIndex = _ttoi(layerInfos[1]);
					color.setColorIndex(colorIndex);
					pLayerTblRcd->setColor(color);
					
					// 设置线型
					AcDbLinetypeTable *pLinetypeTbl = NULL;
					AcDbObjectId linetypeId;
					acdbHostApplicationServices()->workingDatabase()
						->getLinetypeTable(pLinetypeTbl, AcDb::kForRead);
					if (pLinetypeTbl->has(layerInfos[2]))
					{
						pLinetypeTbl->getAt(layerInfos[2], linetypeId);	
						pLayerTblRcd->setLinetypeObjectId(linetypeId);
					}					
					pLinetypeTbl->close();
					
					// 设置线宽
					AcDb::LineWeight lineWeight = (AcDb::LineWeight)_ttoi(layerInfos[3]);		
					pLayerTblRcd->setLineWeight(lineWeight);
					
					pLayerTblRcd->close();
				}				
			}
		}
	}
	else
	{
		acutPrintf(TEXT("\n未找到指定的文件."));
	}
}

