// GridCellButton.cpp: implementation of the CGridCellButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCellButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CGridCellButton, CGridCell)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridCellButton::CGridCellButton()
{

}

CGridCellButton::~CGridCellButton()
{

}

BOOL CGridCellButton::Draw( CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd /*= TRUE*/ )
{
	BOOL bResult = TRUE;//CGridCell::Draw(pDC, nRow, nCol, rect,  bEraseBkgnd);
	
#ifndef _WIN32_WCE	
    // Do the draw 
    pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);
#endif

    return bResult;
}

BOOL CGridCellButton::Edit( int nRow, int nCol, CRect rect, CPoint point, UINT nID, UINT nChar )
{
	return TRUE;
}

void CGridCellButton::EndEdit()
{
	
}
