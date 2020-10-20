// ArcBlockJigEntity.h: interface for the CArcBlockJigEntity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARCBLOCKJIGENTITY_H__25911E45_B284_4A75_9FA3_86A86E7B2132__INCLUDED_)
#define AFX_ARCBLOCKJIGENTITY_H__25911E45_B284_4A75_9FA3_86A86E7B2132__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CArcBlockJigEntity : public AcDbEntity
{
public:
	// 参数startPoint:起始点; endPoint:终止点; thirdPoint:第三点; blockId:块的Id; 
	// count: 插入块的个数;
	CArcBlockJigEntity(const AcGePoint3d &startPoint, const AcGePoint3d &thirdPoint, const AcGePoint3d &endPoint, 
		AcDbObjectId blkDefId, int count);
	virtual ~CArcBlockJigEntity();

	// 自定义实体的绘制函数
	virtual Adesk::Boolean worldDraw(AcGiWorldDraw* mode);
	
	// 设置圆弧终点的位置
	void SetEndPoint(const AcGePoint3d &pt);

	// 将圆弧和块添加到模型空间
	void PostToModelSpace();

	// 获得添加的块参照集合
	AcDbObjectIdArray GetBlkRefIds();

private:
	// 绘制实体或添加到模型空间
	void DrawOrAddSubEnts(AcGiWorldDraw* mode);

private:
	AcGePoint3d m_startPoint, m_endPoint, m_thirdPoint;	// 圆弧的起点、终点和第三点（圆弧上位于起点和终点中间的一点）
	AcDbObjectId m_blkDefId;		// 块定义ID
	int m_blockCount;		// 要布置的块参照的数量
	AcDbObjectIdArray m_blkRefIds;		// 添加的块参照集合
};

#endif // !defined(AFX_ARCBLOCKJIGENTITY_H__25911E45_B284_4A75_9FA3_86A86E7B2132__INCLUDED_)
