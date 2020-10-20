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
#include "MyPaletteSet.h"
#include "MyPalette.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("Zfgk")

// 工具选项板的生存周期与非模态对话框一致
CMyPaletteSet  *g_pPaletteSet = NULL;
CMyPalette *g_pPalette1 = NULL;
CAdUiPalette *g_pPalette2 = NULL;

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CCustomPaletteApp : public AcRxArxApp {

public:
	CCustomPaletteApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt)
	{
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) 
	{
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// 销毁选项板
		if (g_pPaletteSet != NULL)
		{
			g_pPaletteSet->DestroyWindow();
			delete g_pPaletteSet;
			g_pPaletteSet = NULL;
		}
		if (g_pPalette1 != NULL)
		{
			g_pPalette1->DestroyWindow();
			delete g_pPalette1;
			g_pPalette1 = NULL;
		}
		if (g_pPalette2 != NULL)
		{
			g_pPalette2->DestroyWindow();
			delete g_pPalette2;
			g_pPalette2 = NULL;
		}

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}


	// - ZfgkCustomPalette.AddPalette command (do not rename)
	static void ZfgkCustomPaletteAddPalette(void)
	{		
		if (!g_pPaletteSet)
		{
			// 创建palette set
			g_pPaletteSet = new CMyPaletteSet;
			CRect rect(0, 0, 400, 400);		// 初始大小
			g_pPaletteSet->Create(TEXT("自定义选项板"),
				WS_OVERLAPPED | WS_DLGFRAME, 
				rect, 
				acedGetAcadFrame(), 
				PSS_EDIT_NAME | 
				PSS_PROPERTIES_MENU | 
				PSS_AUTO_ROLLUP |
				PSS_CLOSE_BUTTON
				);


			// 创建Palette实例
			g_pPalette1 = new CMyPalette();  // 自定义的选项板
			g_pPalette2 = new CAdUiPalette();	// 系统默认的选项板，只是为了能显示标签名

			// 选项板1
			g_pPalette1->Create(WS_CHILD | WS_VISIBLE, TEXT("选项板1"), g_pPaletteSet, PS_EDIT_NAME);

			// 添加到选项板集合
			g_pPaletteSet->AddPalette(g_pPalette1);

			// 选项板2
			g_pPalette2->Create(WS_CHILD | WS_VISIBLE, TEXT("选项板2"), g_pPaletteSet, PS_EDIT_NAME);

			// 添加到选项板集合
			g_pPaletteSet->AddPalette(g_pPalette2);

			// 显示选项板集合
			g_pPaletteSet->EnableDocking(CBRS_ALIGN_ANY);
			g_pPaletteSet->RestoreControlBar();
		}

		acedGetAcadFrame()->ShowControlBar(g_pPaletteSet, TRUE, FALSE);

		// 设置透明度
		if (g_pPaletteSet->GetOpacity() != 100)
		{
			g_pPaletteSet->SetOpacity(100);
		}
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CCustomPaletteApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CCustomPaletteApp, ZfgkCustomPalette, AddPalette, AddPalette, ACRX_CMD_MODAL, NULL)
