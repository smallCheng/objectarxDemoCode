//
// StdArx.h : include file for ObjectARX/DBX include files
// this file is only included once by your stdafx.h

#if !defined(AFX_STDARX_H__BFCDA779_76A9_4448_836E_E69D9755303A__INCLUDED_)
#define AFX_STDARX_H__BFCDA779_76A9_4448_836E_E69D9755303A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//{{AFX_ARX_INC_SELECTED
//}}AFX_ARX_INC_SELECTED

//{{AFX_ARX_INC_OTHERS
#include "ArxMsgHandler.h"
//}}AFX_ARX_INC_OTHERS
#include "AdskDMgr.h"         // Utility class for document data
#include "docdata.h"          // Your document specific data

// Declare it as an extern here so that it
// becomes available in all modules
extern AsdkDataManager<CDocData> DocVars;
//{{AFX_ARX_FUNC
//}}AFX_ARX_FUNC

// TODO: Here you can add your own includes / declarations
#endif 
