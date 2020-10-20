// (C) Copyright 2002-2005 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.h
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "ZfgkTriangle.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("Zfgk")
AC_DECLARE_EXTENSION_MODULE(TriangleEntityDBDLL) ;

static AcMgObjectFactoryBase __nogc * __nogc *g_PEs = NULL;

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CTriangleEntityDBApp : public AcRxDbxApp {

public:
	CTriangleEntityDBApp () : AcRxDbxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here
		TriangleEntityDBDLL.AttachInstance (_hdllInstance) ;

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxDbxApp::On_kInitAppMsg (pkt) ;

		RegisterManagedWrapperLink(); // 设置“托管-非托管”实体之间的关联		
		
		// TODO: Add your initialization code here
		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxDbxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here
		TriangleEntityDBDLL.DetachInstance () ;

		return (retCode) ;
	}

private:
	// 设置“托管-非托管”类的对应关系
	void RegisterManagedWrapperLink()
	{
		static AcMgObjectFactoryBase* PEs[] = 
		{
			new AcMgObjectFactory<Zfgk::TriangleEntityDB::MgTriangle, ZfgkTriangle>(), 
			// end the array with a NULL
			NULL
		};
		g_PEs = PEs;
	}

	virtual void RegisterServerComponents () {
	}

} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CTriangleEntityDBApp)

