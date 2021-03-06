//
// StdArx.h : include file for ObjectARX/DBX include files
// this file is only included once by your stdafx.h

#if !defined(AFX_STDARX_H__B308660F_3FB2_412D_9829_329FA8385055__INCLUDED_)
#define AFX_STDARX_H__B308660F_3FB2_412D_9829_329FA8385055__INCLUDED_

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
void ZffChap10GetCylinderInfo();
void ZffChap10GetBoundayCurves();
//}}AFX_ARX_FUNC

// TODO: Here you can add your own includes / declarations
#endif 
