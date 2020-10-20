// DrawSquareJig.h: interface for the CDrawSquareJig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWSQUAREJIG_H__709CE93B_B69C_473B_9073_7360D39855A3__INCLUDED_)
#define AFX_DRAWSQUAREJIG_H__709CE93B_B69C_473B_9073_7360D39855A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dbpl.h>

class CDrawSquareJig : AcEdJig
{
public:
	CDrawSquareJig();
	virtual ~CDrawSquareJig();

	// 外部调用的函数，一般用于Jig的初始化
	bool doIt(const AcGePoint3d &centerPoint, AcDbObjectId &polyId);
	
	// 此函数将被drag函数调用以获得用户输入
	virtual AcEdJig::DragStatus sampler();
	
	// 对需要在拖动过程中发生变化的实体进行修改
	virtual Adesk::Boolean update();
	
	// 指定了Jig所操作的对象
	virtual AcDbEntity* entity() const;

private:
	AcDbPolyline* m_pPoly;		// 拖动过程中动态变化的实体
	AcGePoint3d m_curPoint;		// 存储用户光标移动时点的临时位置
	AcGePoint3d m_centerPoint;	// 正方形的中心点
};

#endif // !defined(AFX_DRAWSQUAREJIG_H__709CE93B_B69C_473B_9073_7360D39855A3__INCLUDED_)
