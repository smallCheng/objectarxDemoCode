//
// StdArx.h : include file for ObjectARX/DBX include files
// this file is only included once by your stdafx.h

#if !defined(AFX_STDARX_H__4EDC26D5_929F_4E5D_AB7C_698E4C8C2581__INCLUDED_)
#define AFX_STDARX_H__4EDC26D5_929F_4E5D_AB7C_698E4C8C2581__INCLUDED_

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
void ZffChap4NewLayer();
void ZffCHAP4LayerColor();
void ZffCHAP4DeleteLayer();
void ZffCHAP4ExportLayer();
void ZffCHAP4ImportLayer();
//}}AFX_ARX_FUNC

// TODO: Here you can add your own includes / declarations
#endif 
