//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"

// This is command 'ADDCIRCLE1'
void ZffChap5AddCircle1()
{
	// 声明ADS变量
	ads_point ptCenter = {0, 0, 0};		// 圆心
	ads_real radius = 10;				// 半径
	
	// 调用acedCommand函数创建圆
	acedCommand(RTSTR, TEXT("Circle"),		// 命令
		RTPOINT, ptCenter,	// 圆心
		RTREAL, radius,		// 半径
		RTNONE);			// 结束命令
}

// This is command 'ADDCIRCLE2'
void ZffChap5AddCircle2()
{
	struct resbuf *rb;	// 结果缓冲区
	int rc = RTNORM;	// 返回值
	
	// 创建结果缓冲区链表
	ads_point ptCenter = {30, 0, 0};
	ads_real radius = 10;
	rb = acutBuildList(RTSTR, TEXT("Circle"), 
		RTPOINT, ptCenter, 
		RTREAL, radius, 
		RTNONE);
	
	// 创建圆
	if (rb != NULL)
	{
		rc = acedCmd(rb);
	}
	
	// 检验返回值
	if (rc != RTNORM)
	{
		acutPrintf(TEXT("\n创建圆失败!"));
	}
	
	acutRelRb(rb);
	
	// 进行缩放
	acedCommand(RTSTR, TEXT("Zoom"), RTSTR, TEXT("E"), RTNONE);
}

// This is command 'ENTINFO'
void ZffChap5EntInfo()
{
	// 提示用户选择实体
	ads_name entName;
	ads_point pt;
	if (acedEntSel(TEXT("\n选择实体:"), entName, pt) != RTNORM)
		return;
	
	struct resbuf *rbEnt;	// 保存实体数据的结果缓冲区
	struct resbuf *rb;		// 用于遍历rbEnt的结果缓冲区
	
	// 从entName获得保存实体数据的结果缓冲区
	rbEnt = acdbEntGet(entName);
	rb = rbEnt;
	
	while (rb != NULL)
	{
		switch (rb->restype) 
		{
		case -1:	// 图元名
			acutPrintf(TEXT("\n图元名: %x"), rb->resval.rstring);
			break;
		case 0:		// 图元类型
			acutPrintf(TEXT("\n图元类型: %s"), rb->resval.rstring);
			break;
		case 8:		// 图层
			acutPrintf(TEXT("\n图层:%s"), rb->resval.rstring);
			break;
		case 10:	// 圆心
			acutPrintf(TEXT("\n圆心:(%.2f, %.2f, %.2f)"), 
				rb->resval.rpoint[X], 
				rb->resval.rpoint[Y], 
				rb->resval.rpoint[Z]);
			break;
		case 40:	// 半径
			acutPrintf(TEXT("\n半径:%.4f"), rb->resval.rreal);
			break;
		case 210:	// 圆所在平面的法向矢量
			acutPrintf(TEXT("\n平面的法向矢量:(%.2f, %.2f, %.2f)"), 
				rb->resval.rpoint[X], 
				rb->resval.rpoint[Y], 
				rb->resval.rpoint[Z]);
			break;
		default:
			break;
		}	// switch
		
		rb = rb->rbnext;		// 切换到下一个节点
	}	// while
	
	if (rbEnt != NULL)
	{
		acutRelRb(rbEnt);
	}
}

