// DoubleClickCircle.h: interface for the CDoubleClickCircle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOUBLECLICKCIRCLE_H__1C4282DD_EA8C_4DF1_BA98_50413B6912BC__INCLUDED_)
#define AFX_DOUBLECLICKCIRCLE_H__1C4282DD_EA8C_4DF1_BA98_50413B6912BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <AcDblClkEdit.h>

class CDoubleClickCircle : public AcDbDoubleClickEdit
{
public:
	CDoubleClickCircle();
	virtual ~CDoubleClickCircle();

	// 开始编辑时调用的函数
	void startEdit(AcDbEntity *pEnt, AcGePoint3d pt);

	// 完成编辑之后调用的函数
	void finishEdit(void);	
};

#endif // !defined(AFX_DOUBLECLICKCIRCLE_H__1C4282DD_EA8C_4DF1_BA98_50413B6912BC__INCLUDED_)
