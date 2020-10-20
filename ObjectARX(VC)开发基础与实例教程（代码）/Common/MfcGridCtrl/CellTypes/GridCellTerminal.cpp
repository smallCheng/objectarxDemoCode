// GridCellGroup.cpp: implementation of the CTerminalCellGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCellTerminal.h"
#include "../GridCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
CTerminalCellInfo::CTerminalCellInfo()
{
	DstrTrmnlBoardLinkID = -1;
	TopString = "";
	BottomString = "";
	IsNull = true;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CGridCellTerminal, CGridCell)

CGridCellTerminal::CGridCellTerminal()
{

}

CGridCellTerminal::~CGridCellTerminal()
{

}

CSize CGridCellTerminal::GetCellExtent( CDC* pDC )
{
	// 上边文字与下边文字取最大的宽度
	CSize tmpSize = GetTextExtent(m_groupInfo.TopString, pDC);
	CSize size = GetTextExtent(m_groupInfo.BottomString, pDC); 
	size.cy *= 2;
	size.cx = max(tmpSize.cx, size.cx);
    CSize ImageSize(0,0);    
    
    int nImage = GetImage();    
    if (nImage >= 0)    
    {        
        CGridCtrl* pGrid = GetGrid();        
        ASSERT(pGrid);        
        IMAGEINFO Info;        
        if (pGrid->GetImageList() && pGrid->GetImageList()->GetImageInfo(nImage, &Info))         
        {            
            ImageSize = CSize(Info.rcImage.right-Info.rcImage.left,                                 
                Info.rcImage.bottom-Info.rcImage.top);            
            if (size.cx > 2*(int)GetMargin ())                
                ImageSize.cx += GetMargin();            
            ImageSize.cy += 2*(int)GetMargin ();        
        }    
    }    
    size.cx += ImageSize.cx + 1;    
    size.cy = max(size.cy, ImageSize.cy) + 1;    
    if (IsFixed())    
    {        
        size.cx++;        
        size.cy++;    
    }    
	if (size.cx < 70)
	{
		size.cx = 70;
	}
	if (size.cy < 50)
	{
		size.cy = 50;
	}
    return size;
}

BOOL CGridCellTerminal::Draw( CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd /*= TRUE*/ )
{
	    // Note - all through this function we totally brutalise 'rect'. Do not
    // depend on it's value being that which was passed in.
	if (m_groupInfo.IsNull == true)
	{
		SetBackClr(RGB(34, 139, 34));
	}
	else
	{
		SetBackClr(CLR_DEFAULT);
	}

    CGridCtrl* pGrid = GetGrid();
    ASSERT(pGrid);

    if (!pGrid || !pDC)
        return FALSE;

    if( rect.Width() <= 0 || rect.Height() <= 0)  // prevents imagelist item from drawing even
        return FALSE;                             //  though cell is hidden

    //TRACE3("Drawing %scell %d, %d\n", IsFixed()? _T("Fixed ") : _T(""), nRow, nCol);

    int nSavedDC = pDC->SaveDC();
    pDC->SetBkMode(TRANSPARENT);

    // Get the default cell implementation for this kind of cell. We use it if this cell
    // has anything marked as "default"
    CGridDefaultCell *pDefaultCell = (CGridDefaultCell*) GetDefaultCell();
    if (!pDefaultCell)
        return FALSE;

    // Set up text and background colours
    COLORREF TextClr, TextBkClr;

    TextClr = (GetTextClr() == CLR_DEFAULT)? pDefaultCell->GetTextClr() : GetTextClr();
    if (GetBackClr() == CLR_DEFAULT)
        TextBkClr = pDefaultCell->GetBackClr();
    else
    {
        bEraseBkgnd = TRUE;
        TextBkClr = GetBackClr();
    }

    // Draw cell background and highlighting (if necessary)
    if ( IsFocused() || IsDropHighlighted() )
    {
        // Always draw even in list mode so that we can tell where the
        // cursor is at.  Use the highlight colors though.
        if(GetState() & GVIS_SELECTED)
        {
            TextBkClr = ::GetSysColor(COLOR_HIGHLIGHT);
            TextClr = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
            bEraseBkgnd = TRUE;
        }

        rect.right++; rect.bottom++;    // FillRect doesn't draw RHS or bottom
        if (bEraseBkgnd)
        {
            TRY 
            {
                CBrush brush(TextBkClr);
                pDC->FillRect(rect, &brush);
            } 
            CATCH(CResourceException, e)
            {
                //e->ReportError();
            }
            END_CATCH
        }

        // Don't adjust frame rect if no grid lines so that the
        // whole cell is enclosed.
        if(pGrid->GetGridLines() != GVL_NONE)
        {
            rect.right--;
            rect.bottom--;
        }

        if (pGrid->GetFrameFocusCell())
        {
                // Use same color as text to outline the cell so that it shows
                // up if the background is black.
            TRY 
            {
                CBrush brush(TextClr);
                pDC->FrameRect(rect, &brush);
            }
            CATCH(CResourceException, e)
            {
                //e->ReportError();
            }
            END_CATCH
        }
        pDC->SetTextColor(TextClr);

        // Adjust rect after frame draw if no grid lines
        if(pGrid->GetGridLines() == GVL_NONE)
        {
            rect.right--;
            rect.bottom--;
        }

		//rect.DeflateRect(0,1,1,1);  - Removed by Yogurt
    }
    else if ((GetState() & GVIS_SELECTED))
    {
        rect.right++; rect.bottom++;    // FillRect doesn't draw RHS or bottom
        pDC->FillSolidRect(rect, ::GetSysColor(COLOR_HIGHLIGHT));
        rect.right--; rect.bottom--;
        pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
    }
    else
    {
        if (bEraseBkgnd)
        {
            rect.right++; rect.bottom++;    // FillRect doesn't draw RHS or bottom
            CBrush brush(TextBkClr);
            pDC->FillRect(rect, &brush);
            rect.right--; rect.bottom--;
        }
        pDC->SetTextColor(TextClr);
    }

    // Draw lines only when wanted
    if (IsFixed() && pGrid->GetGridLines() != GVL_NONE)
    {
        CCellID FocusCell = pGrid->GetFocusCell();

        // As above, always show current location even in list mode so
        // that we know where the cursor is at.
        BOOL bHiliteFixed = pGrid->GetTrackFocusCell() && pGrid->IsValid(FocusCell) &&
                            (FocusCell.row == nRow || FocusCell.col == nCol);

        // If this fixed cell is on the same row/col as the focus cell,
        // highlight it.
        if (bHiliteFixed)
        {
            rect.right++; rect.bottom++;
            pDC->DrawEdge(rect, EDGE_RAISED/*EDGE_RAISED*/, BF_RECT);
            rect.DeflateRect(1,1);
        }
        else
        {
            CPen lightpen(PS_SOLID, 1,  ::GetSysColor(COLOR_3DHIGHLIGHT)),
                darkpen(PS_SOLID,  1, ::GetSysColor(COLOR_3DDKSHADOW)),
                *pOldPen = pDC->GetCurrentPen();

            pDC->SelectObject(&lightpen);
            pDC->MoveTo(rect.right, rect.top);
            pDC->LineTo(rect.left, rect.top);
            pDC->LineTo(rect.left, rect.bottom);

            pDC->SelectObject(&darkpen);
            pDC->MoveTo(rect.right, rect.top);
            pDC->LineTo(rect.right, rect.bottom);
            pDC->LineTo(rect.left, rect.bottom);

            pDC->SelectObject(pOldPen);
            rect.DeflateRect(1,1);
       }
    }

    // Draw Text and image
#if !defined(_WIN32_WCE_NO_PRINTING) && !defined(GRIDCONTROL_NO_PRINTING)
    if (!pDC->m_bPrinting)
#endif
    {
        CFont *pFont = GetFontObject();
		ASSERT(pFont);
        if (pFont)
            pDC->SelectObject(pFont);
    }

    //rect.DeflateRect(GetMargin(), 0); - changed by Yogurt
    rect.DeflateRect(GetMargin(), GetMargin());    
    rect.right++;    
    rect.bottom++;

    if (pGrid->GetImageList() && GetImage() >= 0)
    {
        IMAGEINFO Info;
        if (pGrid->GetImageList()->GetImageInfo(GetImage(), &Info))
        {
            //  would like to use a clipping region but seems to have issue
            //  working with CMemDC directly.  Instead, don't display image
            //  if any part of it cut-off
            //
            // CRgn rgn;
            // rgn.CreateRectRgnIndirect(rect);
            // pDC->SelectClipRgn(&rgn);
            // rgn.DeleteObject();

            /*
            // removed by Yogurt
            int nImageWidth = Info.rcImage.right-Info.rcImage.left+1;
            int nImageHeight = Info.rcImage.bottom-Info.rcImage.top+1;
            if( nImageWidth + rect.left <= rect.right + (int)(2*GetMargin())
                && nImageHeight + rect.top <= rect.bottom + (int)(2*GetMargin())  )
            {
                pGrid->GetImageList()->Draw(pDC, GetImage(), rect.TopLeft(), ILD_NORMAL);
            }
            */
            // Added by Yogurt
            int nImageWidth = Info.rcImage.right-Info.rcImage.left;            
            int nImageHeight = Info.rcImage.bottom-Info.rcImage.top;            
            if ((nImageWidth + rect.left <= rect.right) && (nImageHeight + rect.top <= rect.bottom))                
                pGrid->GetImageList()->Draw(pDC, GetImage(), rect.TopLeft(), ILD_NORMAL);

            //rect.left += nImageWidth+GetMargin();
        }
    }

    // Draw sort arrow
    if (pGrid->GetSortColumn() == nCol && nRow == 0)
    {
        CSize size = pDC->GetTextExtent(_T("M"));
        int nOffset = 2;

        // Base the size of the triangle on the smaller of the column
        // height or text height with a slight offset top and bottom.
        // Otherwise, it can get drawn outside the bounds of the cell.
        size.cy -= (nOffset * 2);

        if (size.cy >= rect.Height())
            size.cy = rect.Height() - (nOffset * 2);

        size.cx = size.cy;      // Make the dimensions square

        // Kludge for vertical text
        BOOL bVertical = (GetFont()->lfEscapement == 900);

        // Only draw if it'll fit!
        //if (size.cx + rect.left < rect.right + (int)(2*GetMargin())) - changed / Yogurt
        if (size.cx + rect.left < rect.right)
        {
            int nTriangleBase = rect.bottom - nOffset - size.cy;    // Triangle bottom right
            //int nTriangleBase = (rect.top + rect.bottom - size.cy)/2; // Triangle middle right
            //int nTriangleBase = rect.top + nOffset;                 // Triangle top right

            //int nTriangleLeft = rect.right - size.cx;                 // Triangle RHS
            //int nTriangleLeft = (rect.right + rect.left - size.cx)/2; // Triangle middle
            //int nTriangleLeft = rect.left;                            // Triangle LHS

            int nTriangleLeft;
            if (bVertical)
                nTriangleLeft = (rect.right + rect.left - size.cx)/2; // Triangle middle
            else
                nTriangleLeft = rect.right - size.cx;               // Triangle RHS

            CPen penShadow(PS_SOLID, 0, ::GetSysColor(COLOR_3DSHADOW));
            CPen penLight(PS_SOLID, 0, ::GetSysColor(COLOR_3DHILIGHT));
            if (pGrid->GetSortAscending())
            {
                // Draw triangle pointing upwards
                CPen *pOldPen = (CPen*) pDC->SelectObject(&penLight);
                pDC->MoveTo( nTriangleLeft + 1, nTriangleBase + size.cy + 1);
                pDC->LineTo( nTriangleLeft + (size.cx / 2) + 1, nTriangleBase + 1 );
                pDC->LineTo( nTriangleLeft + size.cx + 1, nTriangleBase + size.cy + 1);
                pDC->LineTo( nTriangleLeft + 1, nTriangleBase + size.cy + 1);

                pDC->SelectObject(&penShadow);
                pDC->MoveTo( nTriangleLeft, nTriangleBase + size.cy );
                pDC->LineTo( nTriangleLeft + (size.cx / 2), nTriangleBase );
                pDC->LineTo( nTriangleLeft + size.cx, nTriangleBase + size.cy );
                pDC->LineTo( nTriangleLeft, nTriangleBase + size.cy );
                pDC->SelectObject(pOldPen);
            }
            else
            {
                // Draw triangle pointing downwards
                CPen *pOldPen = (CPen*) pDC->SelectObject(&penLight);
                pDC->MoveTo( nTriangleLeft + 1, nTriangleBase + 1 );
                pDC->LineTo( nTriangleLeft + (size.cx / 2) + 1, nTriangleBase + size.cy + 1 );
                pDC->LineTo( nTriangleLeft + size.cx + 1, nTriangleBase + 1 );
                pDC->LineTo( nTriangleLeft + 1, nTriangleBase + 1 );
    
                pDC->SelectObject(&penShadow);
                pDC->MoveTo( nTriangleLeft, nTriangleBase );
                pDC->LineTo( nTriangleLeft + (size.cx / 2), nTriangleBase + size.cy );
                pDC->LineTo( nTriangleLeft + size.cx, nTriangleBase );
                pDC->LineTo( nTriangleLeft, nTriangleBase );
                pDC->SelectObject(pOldPen);
            }
            
            if (!bVertical)
                rect.right -= size.cy;
        }
    }

    // We want to see '&' characters so use DT_NOPREFIX
    GetTextRect(rect);
    rect.right++;    
    rect.bottom++;

	//DrawText(pDC->m_hDC, GetText(), -1, rect, GetFormat() | DT_NOPREFIX);
	if (IsFixed())
	{
		//DrawText(pDC->m_hDC, GetText(), -1, rect, GetFormat() | DT_NOPREFIX);
		DrawText(pDC->m_hDC, GetText(), -1, rect, GetFormat() | DT_NOPREFIX);
	}
    else
	{
// 		rect.right++;    
//		/rect.bottom++;
		
		//CString str = GetText();
		//CString str = GetCellData().EquipmentName;
		rect.bottom = rect.top + rect.Height() / 2;
		//DrawText(pDC->m_hDC, ExtractString(str, 0), -1, rect, GetFormat() | DT_NOPREFIX);
		DrawText(pDC->m_hDC, m_groupInfo.TopString, -1, rect, GetFormat() | DT_NOPREFIX | DT_TOP | DT_CENTER | DT_SINGLELINE);		// | DT_CENTER
		CRect rc = rect;
		rc.top = rect.bottom;
		rc.bottom = rc.top + rect.Height();
		//DrawText(pDC->m_hDC, ExtractString(str, 1), -1, rc, GetFormat() | DT_NOPREFIX);
		DrawText(pDC->m_hDC, m_groupInfo.BottomString, -1, rc, GetFormat() | DT_NOPREFIX | DT_TOP | DT_CENTER | DT_SINGLELINE);		// | DT_CENTER
		
		CPen newPen(PS_DOT, 1, ::GetSysColor(COLOR_GRAYTEXT));  
		CPen *pOldPen=pDC->SelectObject(&newPen);  
		pDC->MoveTo(rc.left, (rc.top + rect.bottom)/2);
		pDC->LineTo(rc.right, (rc.top + rect.bottom)/2);
		pDC->SelectObject(pOldPen);
		
		//DrawText(pDC->m_hDC, GetText(), -1, rect, GetFormat() | DT_NOPREFIX);
	}
    

    pDC->RestoreDC(nSavedDC);

	//////////////////////////////////////////////////////////////////////////
	

	
    return TRUE;
}

void CGridCellTerminal::SetTerminalInfo( CTerminalCellInfo &groupInfo )
{
	m_groupInfo = groupInfo;
}

CTerminalCellInfo CGridCellTerminal::GetTerminalInfo() const
{
	return m_groupInfo;
}

BOOL CGridCellTerminal::GetTextRect( LPRECT pRect )
{
	BOOL bResult = CGridCell::GetTextRect(pRect);
//     if (bResult)
//     {
//         int nWidth = GetSystemMetrics(SM_CXHSCROLL) + 2*GetMargin();
//         pRect->left += nWidth;
//         if (pRect->left > pRect->right)
//             pRect->left = pRect->right;
//     }
    return bResult;
}
