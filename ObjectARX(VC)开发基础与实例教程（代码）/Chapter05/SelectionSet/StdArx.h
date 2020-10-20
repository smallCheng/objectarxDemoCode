//
// StdArx.h : include file for ObjectARX/DBX include files
// this file is only included once by your stdafx.h

#if !defined(AFX_STDARX_H__32456FA1_5030_4C25_994B_D48B2F0EB412__INCLUDED_)
#define AFX_STDARX_H__32456FA1_5030_4C25_994B_D48B2F0EB412__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//{{AFX_ARX_INC_SELECTED
//}}AFX_ARX_INC_SELECTED

//{{AFX_ARX_INC_OTHERS
//}}AFX_ARX_INC_OTHERS
#include "AdskDMgr.h"         // Utility class for document data
#include "docdata.h"          // Your document specific data

// Declare it as an extern here so that it
// becomes available in all modules
extern AsdkDataManager<CDocData> DocVars;
//{{AFX_ARX_FUNC
void ZffChap5CreateSSet();
void ZffChap5Test();
void ZffChap5SelectEnt();
void ZffChap5SelectInPoly();
void ZffChap5Filter1();
void ZffChap5Filter2();
void ZffChap5Filter3();
void ZffChap5Filter4();
void ZffChap5Filter5();
void ZffChap5Test2();
void ZffChap5EntInfo();
//}}AFX_ARX_FUNC

// TODO: Here you can add your own includes / declarations
#endif 
