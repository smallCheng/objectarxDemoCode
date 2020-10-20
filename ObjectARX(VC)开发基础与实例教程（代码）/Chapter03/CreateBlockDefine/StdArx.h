//
// StdArx.h : include file for ObjectARX/DBX include files
// this file is only included once by your stdafx.h

#if !defined(AFX_STDARX_H__95D8D0B1_71E2_4B6B_B6A6_DDBE029FE80D__INCLUDED_)
#define AFX_STDARX_H__95D8D0B1_71E2_4B6B_B6A6_DDBE029FE80D__INCLUDED_

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
void ZffChap3AddBlk();
//}}AFX_ARX_FUNC

// TODO: Here you can add your own includes / declarations
#endif 
