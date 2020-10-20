// EntityUtil.h: interface for the CEntityUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENTITYUTIL_H__848573C8_AD29_4B2A_BFFB_6DF0EAFCB34F__INCLUDED_)
#define AFX_ENTITYUTIL_H__848573C8_AD29_4B2A_BFFB_6DF0EAFCB34F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEntityUtil  
{
public:
	CEntityUtil();
	virtual ~CEntityUtil();

	// 修改实体的属性/////////////////////////////////////////////////////
	// 设置实体的颜色
	static void SetColor(AcDbObjectId entId, int colorIndex);

	// 设置实体的图层
	static void SetLayer(AcDbObjectId entId, const TCHAR* layerName);

	// 设置实体的线型
	static void SetLinetype(AcDbObjectId entId, const TCHAR* linetype);

	// 删除一个实体
	static void Erase(AcDbObjectId entId);

	// 几何变换///////////////////////////////////////////////////////////
	// 二维旋转
	static Acad::ErrorStatus Rotate(AcDbObjectId entId, 
		const AcGePoint2d &ptBase, double rotation);

	// 移动
	static Acad::ErrorStatus Move(AcDbObjectId entId, const AcGePoint3d &ptBase, 
		const AcGePoint3d &ptDest);

	// 比例缩放
	static Acad::ErrorStatus Scale(AcDbObjectId entId, 
		const AcGePoint3d &ptBase, double scaleFactor);
};

#endif // !defined(AFX_ENTITYUTIL_H__848573C8_AD29_4B2A_BFFB_6DF0EAFCB34F__INCLUDED_)
