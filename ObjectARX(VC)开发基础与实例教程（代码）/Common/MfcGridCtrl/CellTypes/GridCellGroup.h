// GridCellGroup.h: interface for the CGridCellGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELLGROUP_H__E9758CEB_6DAF_4431_8824_26DCFAD8C5C3__INCLUDED_)
#define AFX_GRIDCELLGROUP_H__E9758CEB_6DAF_4431_8824_26DCFAD8C5C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\GridCell.h"
#include <vector>	// 头文件中最好不要引入名称空间

class CGroupCellInfo
{
public:
	CGroupCellInfo() : GroupType("")
	{
		IsNull = true;
	}
	
	bool operator == (const CGroupCellInfo &groupCell)
	{
		if (this->GroupIDs == groupCell.GroupIDs && 
			this->EquipmentNames == groupCell.EquipmentNames && 
			this->GroupType.Compare(groupCell.GroupType) == 0)
			return true;
		else
			return false;
	};
	
	bool operator != (const CGroupCellInfo &groupCell)
	{
		if (this->GroupIDs == groupCell.GroupIDs && 
			this->EquipmentNames == groupCell.EquipmentNames && 
			this->GroupType.Compare(groupCell.GroupType) == 0)
			return false;
		else
			return true;
	};
	
	CString GetEquipmentList()
	{
		CString strList;
		int nSize = EquipmentNames.size();
		for (int i = 0; i < nSize; i++)
		{
			strList += EquipmentNames[i];
			if (i < nSize - 1)
				strList += ",";
		}
		
		return strList;
	}
	
	void Clear()
	{
		GroupIDs.clear();
		EquipmentNames.clear();
		GroupType.Empty();
		DisplayName.Empty();
	}
	
	std::vector<long> GroupIDs;				// 
	std::vector<CString> EquipmentNames;		//
	CString GroupType;					//
	CString DisplayName;				//
	bool IsNull;						
};

class CGridCellGroup : public CGridCell  
{
	friend class CGridCtrl;
    DECLARE_DYNCREATE(CGridCellGroup)

public:
	CGridCellGroup();
	virtual ~CGridCellGroup();

public:
	void SetGroupInfo(CGroupCellInfo &groupInfo);
	CGroupCellInfo GetGroupInfo() const;

	// Operations
	virtual CSize GetCellExtent(CDC* pDC);
	virtual BOOL GetTextRect( LPRECT pRect);

protected:
    virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);

private:
	CGroupCellInfo m_groupInfo;
	
};

#endif // !defined(AFX_GRIDCELLGROUP_H__E9758CEB_6DAF_4431_8824_26DCFAD8C5C3__INCLUDED_)
