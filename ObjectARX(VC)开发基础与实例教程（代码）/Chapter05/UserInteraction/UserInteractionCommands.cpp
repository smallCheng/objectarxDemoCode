//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Interaction\GetInputUtil.h"
#include "..\..\Common\Entity\PolylineUtil.h"
#include "..\..\Common\Others\ConvertUtil.h"
#include <dbpl.h>

// 提示用户输入线宽
ads_real GetWidth()
{
	ads_real width = 0;
	if (acedGetReal(TEXT("\n输入线宽:"), &width) == RTNORM)
	{
		return width;
	}
	else
	{
		return 0;
	}
}

// 提示用户输入颜色索引值
int GetColorIndex()
{
	int colorIndex = 0;
	if (acedGetInt(TEXT("\n输入颜色索引值(0~256):"), &colorIndex) != RTNORM)
	{
		return 0;
	}
	
	// 处理颜色索引值无效的情况
	while (colorIndex < 0 || colorIndex > 256)
	{
		acedPrompt(TEXT("\n输入了无效的颜色索引."));
		if (acedGetInt(TEXT("\n输入颜色索引值(0~256):"), &colorIndex) != RTNORM)
		{
			return 0;
		}
	}
	
	return colorIndex;
}

// This is command 'ADDPOLYBASIC'
void ZffChap5AddPolyBasic()
{
	int index = 2;				// 当前输入点的次数
	AcGePoint3d ptStart;			// 起点
	if (!CGetInputUtil::GetPoint(TEXT("\n输入第一点:"), ptStart))
	{
		return;
	}
	
	AcGePoint3d ptPrevious, ptCurrent;	// 前一个参考点，当前拾取的点
	ptPrevious = ptStart;
	AcDbObjectId polyId;				// 多段线的ID
	while (CGetInputUtil::GetPoint(ptPrevious, TEXT("\n输入下一点:"), ptCurrent))
	{
		if (index == 2)
		{
			// 创建多段线
			polyId = CPolylineUtil::Add(CConvertUtil::ToPoint2d(ptPrevious), CConvertUtil::ToPoint2d(ptCurrent));
		}
		else if (index > 2)
		{
			// 修改多段线，添加最后一个顶点
			AcDbPolyline *pPoly = NULL;
			if (acdbOpenObject(pPoly, polyId, AcDb::kForWrite) == Acad::eOk)
			{
				pPoly->addVertexAt(index - 1, CConvertUtil::ToPoint2d(ptCurrent));				
				pPoly->close();
			}
		}
		
		ptPrevious = ptCurrent;
		index++;
	}
}

// This is command 'GETPOINTKEYWORD'
void ZffChap5GetPointKeyword()
{
	int rc;		// 返回值
	TCHAR kword[20];		// 关键字
	AcGePoint3d pt;
	acedInitGet(RSG_NONULL, TEXT("K W"));
	rc = CGetInputUtil::GetPointReturnCode(TEXT("\n输入一个点或[Keyword1/keyWord2]:"), pt);
	
	switch (rc)
	{
	case RTKWORD:	// 输入了关键字
		if (acedGetInput(kword) != RTNORM)
		{
			return;
		}
		if (_tcscmp(kword, TEXT("K")) == 0)
		{
			acutPrintf(TEXT("\n选择的关键字是Keyword1!"));
		}
		else if (_tcscmp(kword, TEXT("W")) == 0)
		{
			acutPrintf(TEXT("\n选择的关键字是keyWord2!"));
		}
		break;
	case RTNORM:
		acutPrintf(TEXT("\n输入点的坐标是(%.2f, %.2f, %.2f)"), pt.x, pt.y, pt.z);
		break;
	default:
		break;
	}
}

// This is command 'ADDPOLY'
void ZffChap5AddPoly()
{
	int colorIndex = 0;			// 颜色索引值
	ads_real width = 0;			// 多段线的线宽	
	int index = 2;				// 当前输入点的次数	
	
	// 提示用户输入起点
	AcGePoint3d ptStart;			// 起点
	if (!CGetInputUtil::GetPoint(TEXT("\n输入第一点:"), ptStart))
	{
		return;
	}
	
	AcGePoint3d ptPrevious, ptCurrent;	// 前一个参考点，当前拾取的点
	ptPrevious = ptStart;
	AcDbObjectId polyId;				// 多段线的ID
	
	// 输入第二点
	acedInitGet(NULL, TEXT("W C O"));
	int rc = CGetInputUtil::GetPointReturnCode(ptPrevious, 
		TEXT("\n输入下一点[宽度(W)/颜色(C)]<完成(O)>:"), ptCurrent);
	while (rc == RTNORM || rc == RTKWORD)
	{
		if (rc == RTKWORD)		// 如果用户输入了关键字
		{
			TCHAR kword[20];
			if (acedGetInput(kword) != RTNORM)
				return;
			if (_tcscmp(kword, TEXT("W")) == 0)
			{
				width = GetWidth();				
			}
			else if (_tcscmp(kword, TEXT("C")) == 0)
			{
				colorIndex = GetColorIndex();
			}
			else if (_tcscmp(kword, TEXT("O")) == 0)
			{
				return;
			}
			else
			{
				acutPrintf(TEXT("\n无效的关键字."));
			}
		}
		else if (rc == RTNORM)	// 用户输入了点
		{
			if (index == 2)
			{
				// 创建多段线
				polyId = CPolylineUtil::Add(CConvertUtil::ToPoint2d(ptPrevious), CConvertUtil::ToPoint2d(ptCurrent));
				AcDbPolyline *pPoly = NULL;
				if (acdbOpenObject(pPoly, polyId, AcDb::kForWrite) == Acad::eOk)
				{
					// 修改多段线的颜色和线宽
					pPoly->setConstantWidth(width);
					pPoly->setColorIndex(colorIndex);
					pPoly->close();
				}
			}
			else if (index > 2)
			{
				// 修改多段线，添加最后一个顶点
				AcDbPolyline *pPoly = NULL;
				if (acdbOpenObject(pPoly, polyId, AcDb::kForWrite) == Acad::eOk)
				{
					pPoly->addVertexAt(index - 1, CConvertUtil::ToPoint2d(ptCurrent));	
					// 修改多段线的颜色和线宽
					pPoly->setConstantWidth(width);
					pPoly->setColorIndex(colorIndex);

					pPoly->close();
				}
			}
			
			ptPrevious = ptCurrent;
			index++;
		}
		
		// 提示用户输入新的节点
		acedInitGet(NULL, TEXT("W C O"));
		rc = CGetInputUtil::GetPointReturnCode(ptPrevious, TEXT("\n输入下一点 [宽度(W)/颜色(C)]<完成(O)>:"), ptCurrent);
	}
}

// This is command 'SELECTFILE'
void ZffChap5SelectFile()
{
	CString title = TEXT("选择图形文件");
	CString path = TEXT("C:\\");
	struct resbuf *fileName = acutNewRb(RTSTR);
	
	if (acedGetFileD(title, path, TEXT("dwg;dxf"), 0, fileName) == RTNORM)
	{
		acedAlert(fileName->resval.rstring);
	}
	
	acutRelRb(fileName);
}

