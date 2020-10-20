// DwgDatabaseUtil.h: interface for the CDwgDatabaseUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DWGDATABASEUTIL_H__129CFB33_5499_4344_BA7B_815CB0DE76EF__INCLUDED_)
#define AFX_DWGDATABASEUTIL_H__129CFB33_5499_4344_BA7B_815CB0DE76EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDwgDatabaseUtil  
{
public:
	CDwgDatabaseUtil();
	virtual ~CDwgDatabaseUtil();

	// 将实体添加到模型空间
	static AcDbObjectId PostToModelSpace(AcDbEntity *pEnt, AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase());

	// 获得模型空间所有实体ID数组（可以将图层作为过滤条件）
	static AcDbObjectIdArray GetAllEntityIds(const TCHAR* layerName = NULL, 
		AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase());

	// 获得整个图形模型空间所有实体的包围框
	static AcDbExtents GetModelSpaceExtent(AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase());
};

#endif // !defined(AFX_DWGDATABASEUTIL_H__129CFB33_5499_4344_BA7B_815CB0DE76EF__INCLUDED_)
