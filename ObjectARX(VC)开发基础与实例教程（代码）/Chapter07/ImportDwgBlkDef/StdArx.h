//
// StdArx.h : include file for ObjectARX/DBX include files
// this file is only included once by your stdafx.h

#if !defined(AFX_STDARX_H__2C608376_E451_48DA_AFAA_3077BACA6C22__INCLUDED_)
#define AFX_STDARX_H__2C608376_E451_48DA_AFAA_3077BACA6C22__INCLUDED_

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
void ZffChap7InsertBlkRefFromOtherDwg();
void ZffChap7InsertDwgBlockRef();
//}}AFX_ARX_FUNC

// TODO: Here you can add your own includes / declarations
#endif 
