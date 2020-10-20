// SelectionSet.cpp : Initialization functions
#include "StdAfx.h"
#include "StdArx.h"
#include "resource.h"
#include <afxdllx.h>

HINSTANCE _hdllInstance =NULL ;

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
AC_IMPLEMENT_EXTENSION_MODULE(SelectionSetDLL);

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
		SelectionSetDLL.AttachInstance(hInstance);
		InitAcUiDLL();
	} else if (dwReason == DLL_PROCESS_DETACH) {
		// Terminate the library before destructors are called
		SelectionSetDLL.DetachInstance();

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
	AddCommand("ZFFCHAP5", "CREATESSET", "CREATESSET", ACRX_CMD_MODAL, ZffChap5CreateSSet);
	AddCommand("ZFFCHAP5", "TEST", "TEST", ACRX_CMD_MODAL, ZffChap5Test);
	AddCommand("ZFFCHAP5", "SELECTENT", "SELECTENT", ACRX_CMD_MODAL, ZffChap5SelectEnt);
	AddCommand("ZFFCHAP5", "SELECTINPOLY", "SELECTINPOLY", ACRX_CMD_MODAL, ZffChap5SelectInPoly);
	AddCommand("ZFFCHAP5", "FILTER1", "FILTER1", ACRX_CMD_MODAL, ZffChap5Filter1);
	AddCommand("ZFFCHAP5", "FILTER2", "FILTER2", ACRX_CMD_MODAL, ZffChap5Filter2);
	AddCommand("ZFFCHAP5", "FILTER3", "FILTER3", ACRX_CMD_MODAL, ZffChap5Filter3);
	AddCommand("ZFFCHAP5", "FILTER4", "FILTER4", ACRX_CMD_MODAL, ZffChap5Filter4);
	AddCommand("ZFFCHAP5", "FILTER5", "FILTER5", ACRX_CMD_MODAL, ZffChap5Filter5);
	AddCommand("ZFFCHAP5", "TEST2", "TEST2", ACRX_CMD_MODAL, ZffChap5Test2);
	AddCommand("ZFFCHAP5", "ENTINFO", "ENTINFO", ACRX_CMD_MODAL, ZffChap5EntInfo);
	//}}AFX_ARX_INIT

	// TODO: add your initialization functions

}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_EXIT
	acedRegCmds->removeGroup("ZFFCHAP5");
	//}}AFX_ARX_EXIT

	// TODO: clean up your application
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
