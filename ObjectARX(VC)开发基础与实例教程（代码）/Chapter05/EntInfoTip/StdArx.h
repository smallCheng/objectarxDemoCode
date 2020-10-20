//
// StdArx.h : include file for ObjectARX/DBX include files
// this file is only included once by your stdafx.h

#if !defined(AFX_STDARX_H__2F0862B2_878B_4A27_B518_D9EA50E2121F__INCLUDED_)
#define AFX_STDARX_H__2F0862B2_878B_4A27_B518_D9EA50E2121F__INCLUDED_

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
void ZffChap5EntTipOn();
void ZffChap5EntTipOff();
//}}AFX_ARX_FUNC

// TODO: Here you can add your own includes / declarations
#endif 
