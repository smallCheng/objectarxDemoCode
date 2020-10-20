//////////////////////////////////////////////////////////////////////////
// Hello.cpp
// by 张帆
//////////////////////////////////////////////////////////////////////////
// 包含头文件
#include <aced.h>
#include <rxregsvc.h>

// 声明初始化函数和卸载函数
void InitApp();
void UnloadApp();

// 声明命令的执行函数
void HelloWorld();

// 加载应用程序时被调用的函数
void InitApp()
{
	//使用AutoCAD命令机制注册一个新命令
	acedRegCmds->addCommand(TEXT("Hello1"),
		TEXT("Hello"),	//输入这两个命令名称均可以在
		TEXT("Hello"),	//AutoCAD中运行该程序
		ACRX_CMD_MODAL,
		HelloWorld);
}

// 卸载应用程序时被调用的函数
void UnloadApp()
{
	//删除命令组
	acedRegCmds->removeGroup(TEXT("Hello1"));
}

// 实现Hello命令的函数
void HelloWorld()
{
	acutPrintf(TEXT("\nHello, World!"));
}

// 入口点函数
extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch (msg) 
	{
	case AcRx::kInitAppMsg:
		acrxDynamicLinker->unlockApplication(pkt);
		acrxRegisterAppMDIAware(pkt);
		InitApp();
		break;
	case AcRx::kUnloadAppMsg:
		UnloadApp();
		break;
	default:
		break;
	}
	return AcRx::kRetOK;
}
