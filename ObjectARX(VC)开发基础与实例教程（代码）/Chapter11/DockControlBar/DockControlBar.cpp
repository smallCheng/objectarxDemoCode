// DockControlBar.cpp : Initialization functions
#include "StdAfx.h"
#include "StdArx.h"
#include "resource.h"
#include <afxdllx.h>
#include "MyDockControlBar.h"

HINSTANCE _hdllInstance =NULL ;

CMyDockControlBar* g_pDlgBar = NULL;

// This command registers an ARX command.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal = -1);


// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_MSG
void InitApplication();
void UnloadApplication();
//}}AFX_ARX_MSG

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_ADDIN_FUNCS
//}}AFX_ARX_ADDIN_FUNCS


////////////////////////////////////////////////////////////////////////////
//
// Define the sole extension module object.
AC_IMPLEMENT_EXTENSION_MODULE(DockControlBarDLL);

// Now you can use the CAcModuleResourceOverride class in
// your application to switch to the correct resource instance.
// Please see the ObjectARX Documentation for more details

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
        _hdllInstance = hInstance;
		// Extension DLL one time initialization
		DockControlBarDLL.AttachInstance(hInstance);
		InitAcUiDLL();
	} else if (dwReason == DLL_PROCESS_DETACH) {
		// Terminate the library before destructors are called
		DockControlBarDLL.DetachInstance();

	}
	return TRUE;    // ok
}



/////////////////////////////////////////////////////////////////////////////
// ObjectARX EntryPoint
extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch (msg) {
	case AcRx::kInitAppMsg:
		// Comment out the following line if your
		// application should be locked into memory
		acrxDynamicLinker->unlockApplication(pkt);
		acrxDynamicLinker->registerAppMDIAware(pkt);
		InitApplication();
		break;
	case AcRx::kUnloadAppMsg:
		UnloadApplication();
		break;
	}
	return AcRx::kRetOK;
}

// Init this application. Register your
// commands, reactors...
void InitApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_INIT
	//}}AFX_ARX_INIT

	// 显示可停靠的窗体
	CAcModuleResourceOverride resOverride;	
	if (g_pDlgBar == NULL)
	{
		g_pDlgBar = new CMyDockControlBar();
		g_pDlgBar->Create(acedGetAcadFrame(), _T("DockBar"));
		g_pDlgBar->SetWindowText(_T("MyControlBar"));
		g_pDlgBar->EnableDocking(CBRS_ALIGN_ANY);		
	}
	
	acedGetAcadFrame()->FloatControlBar(g_pDlgBar, CPoint(100, 100), CBRS_ALIGN_TOP);		// 初始位置
	acedGetAcadFrame()->ShowControlBar(g_pDlgBar, TRUE, TRUE);
}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_EXIT
	//}}AFX_ARX_EXIT

	// 手动销毁可停靠窗体
	if (g_pDlgBar != NULL)
	{
		g_pDlgBar->DestroyWindow();
		delete g_pDlgBar;
		g_pDlgBar = NULL;
	}
}

// This functions registers an ARX command.
// It can be used to read the localized command name
// from a string table stored in the resources.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal)
{
	char cmdLocRes[65];

	// If idLocal is not -1, it's treated as an ID for
	// a string stored in the resources.
	if (idLocal != -1) {

		// Load strings from the string table and register the command.
		::LoadString(_hdllInstance, idLocal, cmdLocRes, 64);
		acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLocRes, cmdFlags, cmdProc);

	} else
		// idLocal is -1, so the 'hard coded'
		// localized function name is used.
		acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLoc, cmdFlags, cmdProc);
}
