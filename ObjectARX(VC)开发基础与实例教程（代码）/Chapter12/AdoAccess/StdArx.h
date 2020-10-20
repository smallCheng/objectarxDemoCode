//
// StdArx.h : include file for ObjectARX/DBX include files
// this file is only included once by your stdafx.h

#if !defined(AFX_STDARX_H__DBF7E52B_7747_493A_90F0_777AAF7DE2F5__INCLUDED_)
#define AFX_STDARX_H__DBF7E52B_7747_493A_90F0_777AAF7DE2F5__INCLUDED_

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
void ZffChap12AddBook();
void ZffChap12EditBook();
void ZffCHAP12DeleteBook();
void ZffCHAP12QueryBook();
//}}AFX_ARX_FUNC

// TODO: Here you can add your own includes / declarations
#endif 
