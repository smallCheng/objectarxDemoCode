// LayerUtil.h: interface for the CLayerUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAYERUTIL_H__001B5B7F_7ECE_40B0_8303_6E63AEA26C92__INCLUDED_)
#define AFX_LAYERUTIL_H__001B5B7F_7ECE_40B0_8303_6E63AEA26C92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLayerUtil  
{
public:
	CLayerUtil();
	virtual ~CLayerUtil();

	// 创建新图层，如果指定名称的图层已经存在，就不再创建新的图层
	static void Add(const TCHAR* layerName, int colorIndex = 7);

	// 获得图层ID
	static AcDbObjectId GetLayerId(const TCHAR* layerName);

	// 设置图层的颜色
	static bool SetColor(const TCHAR* layerName, int colorIndex);

	// 获得所有图层的列表
	static void GetLayerList(AcDbObjectIdArray &layers);
};

#endif // !defined(AFX_LAYERUTIL_H__001B5B7F_7ECE_40B0_8303_6E63AEA26C92__INCLUDED_)
