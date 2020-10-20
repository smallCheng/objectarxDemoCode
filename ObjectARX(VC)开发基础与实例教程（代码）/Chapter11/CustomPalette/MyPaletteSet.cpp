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
//----- MyPaletteSet.cpp : Implementation of CMyPaletteSet
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "MyPaletteSet.h"

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CMyPaletteSet, CAdUiPaletteSet)

BEGIN_MESSAGE_MAP(CMyPaletteSet, CAdUiPaletteSet)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CMyPaletteSet::CMyPaletteSet () {
}

//-----------------------------------------------------------------------------
CMyPaletteSet::~CMyPaletteSet () {
}

//-----------------------------------------------------------------------------
#ifdef _DEBUG
//- Please uncomment the 2 following lines to avoid linker error when compiling
//- in release mode. But make sure to uncomment these lines only once per project
//- if you derive multiple times from CAdUiDockControlBar/CAcUiDockControlBar
//- classes.

//void CAdUiDockControlBar::AssertValid () const {
//}
#endif

//-----------------------------------------------------------------------------
//- Called by the palette set framework to determine size constraints.
//- Override these methods to provide minimum and maximum palette set sizes.
void CMyPaletteSet::GetMinimumSize (CSize &size) {
	// 面板的最小允许尺寸
	size.cx = 100;
	size.cy = 100;
}

//-----------------------------------------------------------------------------
void CMyPaletteSet::GetMaximumSize (CSize &size) {
	// 面板的最大允许尺寸（在AutoCAD中似乎无效）
	size.cx = 400;
	size.cy = 400;
}
