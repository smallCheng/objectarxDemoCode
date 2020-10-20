// GridCellGroup.h: interface for the CTerminalCellGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELLGROUP_H__E9758CEB_6DAF_4431_8824_26DCFAD8C5C3__INCLUDED_)
#define AFX_GRIDCELLGROUP_H__E9758CEB_6DAF_4431_8824_26DCFAD8C5C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\GridCell.h"
#include <vector>	// 头文件中最好不要引入名称空间

class CTerminalCellInfo
{
public:
	
	long DstrTrmnlBoardLinkID;
	CString TopString;
	CString BottomString;
	bool IsNull;		
				
	CTerminalCellInfo();
};

class CGridCellTerminal : public CGridCell  
{
	friend class CGridCtrl;
    DECLARE_DYNCREATE(CGridCellTerminal)

public:
	CGridCellTerminal();
	virtual ~CGridCellTerminal();

public:
	void SetTerminalInfo(CTerminalCellInfo &groupInfo);
	CTerminalCellInfo GetTerminalInfo() const;

	// Operations
	virtual CSize GetCellExtent(CDC* pDC);
	virtual BOOL GetTextRect( LPRECT pRect);

protected:
    virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);

private:
	CTerminalCellInfo m_groupInfo;
	
};

#endif // !defined(AFX_GRIDCELLGROUP_H__E9758CEB_6DAF_4431_8824_26DCFAD8C5C3__INCLUDED_)
