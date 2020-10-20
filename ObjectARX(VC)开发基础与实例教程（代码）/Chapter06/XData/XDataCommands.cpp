//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Interaction\SelectUtil.h"
#include <geassign.h>

// This is command 'ADDXDATA'
void ZffChap6AddXData()
{
	// 提示用户选择所要添加扩展数据的图形对象
	AcDbEntity *pEnt = NULL;
	AcGePoint3d pickPoint;
	if (CSelectUtil::PromptSelectEntity(TEXT("\n选择所要添加扩展数据的实体:"), AcDbEntity::desc(), pEnt, pickPoint))
	{
		CString appName = TEXT("XDataApp");
		
		// 注册应用程序名称
		acdbRegApp(appName);

		// 创建结果缓冲区链表
		struct resbuf* rb = acutBuildList(AcDb::kDxfRegAppName, appName,		// 应用程序名称
			AcDb::kDxfXdAsciiString, TEXT("字符串测试数据"),	// 字符串
			AcDb::kDxfXdInteger32, 2,							// 整数
			AcDb::kDxfXdReal, 3.14,								// 实数
			AcDb::kDxfXdWorldXCoord, asDblArray(pickPoint),						// 点坐标值
			RTNONE);
		
		// 为选择的实体添加扩展数据
		pEnt->setXData(rb);
		acutRelRb(rb);

		acutPrintf(TEXT("\n成功为实体添加了扩展数据."));

		pEnt->close();
	}
}

// This is command 'VIEWXDATA'
void ZffChap6ViewXData()
{
	// 提示用户选择所要查看扩展数据的图形对象
	AcDbEntity *pEnt = NULL;
	AcGePoint3d pickPoint;
	if (CSelectUtil::PromptSelectEntity(TEXT("\n选择所要添加扩展数据的实体:"), AcDbEntity::desc(), pEnt, pickPoint))
	{
		CString appName = TEXT("XDataApp");
		
		// 获取实体的扩展数据
		struct resbuf *pRb = pEnt->xData(appName);		
		if (pRb != NULL)
		{
			// 在命令行显示所有的扩展数据
			struct resbuf *pTemp = pRb;		// 使用临时的结果缓冲区指针进行遍历，pRb不修改便于释放
			
			// 首先要跳过应用程序的名称这一项
			pTemp = pTemp->rbnext;
			acutPrintf("\n字符串类型的扩展数据是: %s", pTemp->resval.rstring);
			
			pTemp = pTemp->rbnext;
			acutPrintf("\n整数类型的扩展数据是: %d", pTemp->resval.rint);
			
			pTemp = pTemp->rbnext;
			acutPrintf("\n实数类型的扩展数据是: %.2f", pTemp->resval.rreal);
			
			pTemp = pTemp->rbnext;
			acutPrintf("\n点坐标类型的扩展数据是: (%.2f, %.2f, %.2f)", 
				pTemp->resval.rpoint[X], pTemp->resval.rpoint[Y], 
				pTemp->resval.rpoint[Z]);
			
			acutRelRb(pRb);		
		}
		else
		{
			acutPrintf("\n所选择的实体不包含任何的扩展数据!");
		}
		
		pEnt->close();
	}
}

// This is command 'DELETEXDATA'
void ZffCHAP6DeleteXData()
{
	// 提示用户选择所要删除扩展数据的图形对象
	AcDbEntity *pEnt = NULL;
	AcGePoint3d pickPoint;
	if (CSelectUtil::PromptSelectEntity(TEXT("\n选择所要删除扩展数据的实体:"), AcDbEntity::desc(), pEnt, pickPoint))
	{
		CString appName = TEXT("XDataApp");
		
		// 注册应用程序名称
		acdbRegApp(appName);
		
		// 创建结果缓冲区链表
		struct resbuf* rb = acutBuildList(AcDb::kDxfRegAppName, appName,		// 应用程序名称			
			RTNONE);
		
		// 设置内容为空的结果缓冲区链表就是删除扩展数据
		pEnt->setXData(rb);
		acutRelRb(rb);

		acutPrintf(TEXT("\n成功为实体删除了扩展数据."));
		
		pEnt->close();
	}
}

