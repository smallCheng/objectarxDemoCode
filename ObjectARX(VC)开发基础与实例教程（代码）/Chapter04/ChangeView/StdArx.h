//
// StdArx.h : include file for ObjectARX/DBX include files
// this file is only included once by your stdafx.h

#if !defined(AFX_STDARX_H__9471CAC1_6230_461E_9E59_1240873D694E__INCLUDED_)
#define AFX_STDARX_H__9471CAC1_6230_461E_9E59_1240873D694E__INCLUDED_

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
void ZffChap4ZoomWindow();
void ZffCHAP4ZoomExtent();
void ZffCHAP4ZoomEntity();
//}}AFX_ARX_FUNC

// TODO: Here you can add your own includes / declarations
#endif 
