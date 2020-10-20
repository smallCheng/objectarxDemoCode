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
//----- MyPalette.h : Declaration of the CMyPalette
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "adui.h"
#include "MyPaletteChildDlg1.h"

//-----------------------------------------------------------------------------
class CMyPalette : public CAdUiPalette 
{
	DECLARE_DYNAMIC (CMyPalette)//是为了确定运行时对象属于哪一个类而定义的宏。 

public:

public:
	CMyPalette (HINSTANCE hInstance =NULL) ;
	virtual ~CMyPalette () ;

	//- Load the data from xml.
	virtual BOOL Load (IUnknown *pUnk) ;
	//- Save the data to xml.
	virtual BOOL Save (IUnknown *pUnk) ;
	//- Called by the palette set when the palette is made active
	virtual void OnSetActive () ;
	//- Called by AutoCAD to steal focus from the palette
	virtual bool CanFrameworkTakeFocus () ;

protected:
	afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct) ;
	afx_msg void OnSize (UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
	
private:
	CMyPaletteChildDlg1 mChildDlg;
} ;
