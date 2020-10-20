// BlockUtil.h: interface for the CBlockUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLOCKUTIL_H__7ADDDF39_6E25_4316_A6B7_0B99ECBE3CEB__INCLUDED_)
#define AFX_BLOCKUTIL_H__7ADDDF39_6E25_4316_A6B7_0B99ECBE3CEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <dbents.h>

class CBlockUtil  
{
public:
	CBlockUtil();
	virtual ~CBlockUtil();

	// 获得指定名称的块定义
	static AcDbObjectId GetBlkDefId(const TCHAR* blkDefName, AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase());

	// 插入块参照
	static AcDbObjectId InsertBlockRef(AcDbObjectId blkDefId, const AcGePoint3d &insertPoint, double scale = 1, double rotation = 0);

	// 插入属性块（属性值全部使用默认值）
	static AcDbObjectId InsertBlockRefWithAttribute(const AcDbObjectId &blkDefId, const AcGePoint3d &insertPoint, 
		double scale = 1, double rotation = 0);
	
	// 向块参照中添加某种属性
	static void AppendAttributeToBlkRef( AcDbBlockReference * pBlkRef, AcDbAttributeDefinition * pAttDef );

	// 设置属性块的某个属性值
	static bool SetBlockRefAttribute(AcDbBlockReference *pBlkRef, const TCHAR* tag, const TCHAR* val);

	// 获得块参照中某个属性的内容
	static bool GetAttributeValue(AcDbBlockReference *pBlkRef, const TCHAR* tag, CString &value);

	// 设置块参照的缩放比例
	static void SetScaleFactor(AcDbBlockReference *pBlkRef, double scale);

	// 计算块参照与其他实体的真实交点（否则获得的是块参照包围框与实体的交点）
	static void IntersectWith(AcDbBlockReference *pBlkRef, AcDbEntity *pEnt, AcGePoint3dArray &intPoints, 
		bool bIntersectWithText = true, bool bProjectToXOY = false, bool bExtendEntArg = false);

	// 功能: 从其他的DWG图形复制一个块定义到当前图形
	// 参数: const TCHAR * fileName, Dwg文件名（全路径）
	// 参数: const TCHAR * blkDefName, 块定义的名称
	// 返回值:   AcDbObjectId, 复制到当前图形中对应的块定义ID(如果当前图形中存在同名的块定义，直接返回当前图形中同名的块定义的ID)
	static AcDbObjectId CopyBlockDefFromOtherDwg(const TCHAR* fileName, const TCHAR* blkDefName);

	// 将DWG文件作为块定义加入到指定的图形数据库
	// bOverwriteIfExist: 如果指定的图形数据库中已经定义了同名的块，是否覆盖原有的定义
	static AcDbObjectId InsertDwgBlockDef(const TCHAR* dwgFileName, const TCHAR* blkName, bool bOverwriteIfExist, 
		AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase());
};

#endif // !defined(AFX_BLOCKUTIL_H__7ADDDF39_6E25_4316_A6B7_0B99ECBE3CEB__INCLUDED_)
