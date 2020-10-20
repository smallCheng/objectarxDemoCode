// SelectUtil.h: interface for the CSelectUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SELECTUTIL_H__73F892C8_D07B_4446_97D2_BB31119A85DD__INCLUDED_)
#define AFX_SELECTUTIL_H__73F892C8_D07B_4446_97D2_BB31119A85DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>

class CSelectUtil  
{
public:
	CSelectUtil();
	virtual ~CSelectUtil();

	// 功能: 获得当前图形中位于给定矩形范围内的所有实体（以实体的包围框进行判断）
	// 参数: const AcGePoint2d & firstPoint, 矩形的第一个角点
	// 参数: const AcGePoint2d & secondPoint, 矩形的第二个角点
	// 参数: AcDbObjectIdArray & entIds, 满足条件的实体数组
	// 返回值:   void, 无
	//************************************
	static void GetEntityInRectangle(const AcGePoint2d &firstPoint, const AcGePoint2d &secondPoint, AcDbObjectIdArray &entIds);

	// 提示用户选择多个实体
	static bool PromptSelectEnts(const TCHAR* prompt, struct resbuf *rb, AcDbObjectIdArray &entIds);
	static bool PromptSelectEnts(const TCHAR* prompt, AcRxClass* classDesc, AcDbObjectIdArray &entIds);
	static bool PromptSelectEnts(const TCHAR* prompt, const std::vector<AcRxClass*> &classDescs, AcDbObjectIdArray &entIds);

	// 提示用户选择某个类型的实体
	// 注意：调用者必须关闭实体	
	static bool PromptSelectEntity(const TCHAR* prompt, AcRxClass* classDesc, AcDbEntity *&pEnt, AcGePoint3d &pickPoint, 
		bool bOpenForWrite = true);
	static bool PromptSelectEntity(const TCHAR* prompt, const std::vector<AcRxClass*> &classDescs, AcDbEntity *&pEnt, 
		AcGePoint3d &pickPoint, bool bOpenForWrite = true);
};

#endif // !defined(AFX_SELECTUTIL_H__73F892C8_D07B_4446_97D2_BB31119A85DD__INCLUDED_)
