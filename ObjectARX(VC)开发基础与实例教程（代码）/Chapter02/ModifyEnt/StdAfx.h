// StdAfx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__3FEEEAA0_D63B_49C3_9E64_889EA5692732__INCLUDED_)
#define AFX_STDAFX_H__3FEEEAA0_D63B_49C3_9E64_889EA5692732__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable: 4786)
//#pragma warning(disable: 4098)

#include <windows.h>

extern HINSTANCE _hdllInstance ;
#include "rxdebug.h"
// RX Includes
#include "acdb.h"               // acdb definitions
#include "rxregsvc.h"           // ARX linker
#include "dbapserv.h"           // Host application services
#include "aced.h"               // aced stuff
#include "adslib.h"             // RXADS definitions
#include "acdocman.h"           // MDI document manager


#ifdef _FULLDEBUG_
#pragma message ("Warning! You should better not run this application in a Standard AutoCAD release.")
#pragma message ("         Due to the memory managment constraints.")
#endif

#endif // !defined(AFX_STDAFX_H__3FEEEAA0_D63B_49C3_9E64_889EA5692732__INCLUDED)
