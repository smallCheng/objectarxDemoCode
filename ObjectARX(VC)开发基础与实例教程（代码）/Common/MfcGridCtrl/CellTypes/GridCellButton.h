// GridCellButton.h: interface for the CGridCellButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELLBUTTON_H__A24B115D_6DA5_4D32_9C04_0CCC48343A11__INCLUDED_)
#define AFX_GRIDCELLBUTTON_H__A24B115D_6DA5_4D32_9C04_0CCC48343A11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\GridCell.h"

#if defined (_ZFGKCOMMONLIB_)
#define ZFGK_DLLIMPEXP __declspec(dllexport)
#else
#define ZFGK_DLLIMPEXP 
#endif

class ZFGK_DLLIMPEXP CGridCellButton : public CGridCell
{
	friend class CGridCtrl;
    DECLARE_DYNCREATE(CGridCellButton)

public:
	CGridCellButton();
	virtual ~CGridCellButton();

	// editing cells
public:
    virtual BOOL  Edit(int nRow, int nCol, CRect rect, CPoint point, UINT nID, UINT nChar);
    //virtual CWnd* GetEditWnd() const;
    virtual void  EndEdit();

protected:
	virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);
};

#endif // !defined(AFX_GRIDCELLBUTTON_H__A24B115D_6DA5_4D32_9C04_0CCC48343A11__INCLUDED_)
