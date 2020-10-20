//
// StdArx.h : include file for ObjectARX/DBX include files
// this file is only included once by your stdafx.h

#if !defined(AFX_STDARX_H__2E7A1A09_11BC_4EF7_A014_01D2E69A3EB1__INCLUDED_)
#define AFX_STDARX_H__2E7A1A09_11BC_4EF7_A014_01D2E69A3EB1__INCLUDED_

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
void ZffChap2AddCircle();
//}}AFX_ARX_FUNC

// TODO: Here you can add your own includes / declarations
#endif 
