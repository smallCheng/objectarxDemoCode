// ArcBlockJig.h: interface for the CArcBlockJig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARCBLOCKJIG_H__C0A05BEA_FABF_41C9_9F06_A11DF104871D__INCLUDED_)
#define AFX_ARCBLOCKJIG_H__C0A05BEA_FABF_41C9_9F06_A11DF104871D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ArcBlockJigEntity.h"

class CArcBlockJig  : AcEdJig
{
public:
	CArcBlockJig();
	virtual ~CArcBlockJig();

	// 参数startPoint:起始点; endPoint:终止点; thirdPoint:第三点; blkDefId:块的Id; 
	// blockCount: 插入块的个数;
	bool doIt(const AcGePoint3d &startPoint, AcGePoint3d &thirdPoint, AcGePoint3d &endPoint, 
		AcDbObjectId blkDefId, int blockCount);
	virtual AcEdJig::DragStatus sampler();		// 此函数将被drag函数调用以获得一个输入
	virtual Adesk::Boolean update();
	virtual AcDbEntity* entity() const;			// 指定了Jig所操作的对象

	// 获取Jig操作成功后插入的块参照集合
	AcDbObjectIdArray GetBlkRefIds();
	
private:
	CArcBlockJigEntity* m_pJigEnt;
	AcGePoint3d m_curPoint;
	AcDbObjectIdArray m_blkRefIds;
};

#endif // !defined(AFX_ARCBLOCKJIG_H__C0A05BEA_FABF_41C9_9F06_A11DF104871D__INCLUDED_)
