// StdAfx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__C02194E7_38C0_4FC8_BCB5_A4085EF12D01__INCLUDED_)
#define AFX_STDAFX_H__C02194E7_38C0_4FC8_BCB5_A4085EF12D01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable: 4786)
//#pragma warning(disable: 4098)

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

// 'DEBUG workaround' below prevents the MFC or ATL #include-s 
// from pulling in "afx.h" that would force the debug CRT through
// #pragma-s.
#if defined(_DEBUG) && !defined(_FULLDEBUG_)
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#pragma message ("     Compiling MFC header files in release mode.")
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>          // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>         // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>       // MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif


extern HINSTANCE _hdllInstance ;
#include "rxdebug.h"
// RX Includes
#include "acdb.h"               // acdb definitions
#include "rxregsvc.h"           // ARX linker
#include "dbapserv.h"           // Host application services
#include "AcExtensionModule.h"  // Utility class for extension dlls


#ifdef _FULLDEBUG_
#pragma message ("Warning! You should better not run this application in a Standard AutoCAD release.")
#pragma message ("         Due to the memory managment constraints.")
#endif

#endif // !defined(AFX_STDAFX_H__C02194E7_38C0_4FC8_BCB5_A4085EF12D01__INCLUDED)
