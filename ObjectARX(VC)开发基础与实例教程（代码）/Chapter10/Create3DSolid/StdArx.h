//
// StdArx.h : include file for ObjectARX/DBX include files
// this file is only included once by your stdafx.h

#if !defined(AFX_STDARX_H__9F44F5F0_FF68_4BB8_82C5_5846686D3AE0__INCLUDED_)
#define AFX_STDARX_H__9F44F5F0_FF68_4BB8_82C5_5846686D3AE0__INCLUDED_

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
void ZffChap10AddBox();
void ZffChap10AddCylinder();
void ZffChap10AddSpire();
void ZffChap10RevolveEnt();
void ZffChap10Boolean();
//}}AFX_ARX_FUNC

// TODO: Here you can add your own includes / declarations
#endif 
