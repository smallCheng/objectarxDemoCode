#if !defined(RXTRACE_H__35A69BA3_C12C_11D2_B89B_080009DCA551__INCLUDED_)
#define RXTRACE_H__35A69BA3_C12C_11D2_B89B_080009DCA551__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <tchar.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

void _cdecl RxTrace(const TCHAR* lpszFormat, ...);

#ifdef _DEBUG
#define RXTRACE         ::RxTrace
#define RXASSERT(f)     assert(f)
#else
#define RXTRACE         1?(void)0: ::RxTrace
#define RXASSERT(f)     ((void)0)
#endif


#endif // !defined(RXTRACE_H__35A69BA3_C12C_11D2_B89B_080009DCA551__INCLUDED_)
