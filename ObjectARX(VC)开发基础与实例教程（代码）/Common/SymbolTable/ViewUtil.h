// ViewUtil.h: interface for the CViewUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWUTIL_H__B066F34E_E9B5_4B50_9966_18A00967B85B__INCLUDED_)
#define AFX_VIEWUTIL_H__B066F34E_E9B5_4B50_9966_18A00967B85B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CViewUtil  
{
public:
	CViewUtil();
	virtual ~CViewUtil();

	// 获得当前的视图设置
	static void GetCurrentView(AcDbViewTableRecord &view);

	// 给定显示范围的最大、最小角点坐标和缩放比例，修改视图
	static void Set(const AcGePoint3d &ptMin, const AcGePoint3d &ptMax, double scale = 1.0);

	// 将视图移动到给定的中心点
	static void SetCenter(const AcGePoint3d &center);

	// 当前图形显示整个模型空间的实体
	static void ZoomExtent();

	// 后台创建的图形数据库，模型空间所有实体居中显示
	static void DwgZoomExtent(AcDbDatabase *pDb);
};

#endif // !defined(AFX_VIEWUTIL_H__B066F34E_E9B5_4B50_9966_18A00967B85B__INCLUDED_)
