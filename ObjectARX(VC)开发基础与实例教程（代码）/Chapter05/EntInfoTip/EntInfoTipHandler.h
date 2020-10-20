// EntInfoTipHandler.h: interface for the CEntInfoTipHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENTINFOTIPHANDLER_H__42D55ACC_95B2_4090_A8C4_F8969156387A__INCLUDED_)
#define AFX_ENTINFOTIPHANDLER_H__42D55ACC_95B2_4090_A8C4_F8969156387A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <acedinpt.h>

class CEntInfoTipHandler : public AcEdInputPointMonitor
{
public:
	CEntInfoTipHandler(const bool storeInDocVars = true, AcApDocument* pDoc = curDoc());
	virtual ~CEntInfoTipHandler();

	// 计算需要从自动捕捉中排除的实体
	virtual bool excludeFromOsnapCalculation(const AcArray<AcDbObjectId>& nestedEntity,
		int gsSelectionMark);

	// 监控输入点信息
	virtual Acad::ErrorStatus monitorInputPoint(
		bool& bAppendToTooltipStr,
		TCHAR*& pAdditionalTooltipString,
		AcGiViewportDraw* pDrawContext,
		AcApDocument* pDocument,
		bool pointComputed,
		int history,
		const AcGePoint3d& lastPoint,
		const AcGePoint3d& rawPoint,
		const AcGePoint3d& grippedPoint,
		const AcGePoint3d& cartesianSnappedPoint,
		const AcGePoint3d& osnappedPoint,
		AcDb::OsnapMask osnapMask,
		const AcArray<AcDbCustomOsnapMode*>& customOsnapModes,
		AcDb::OsnapMask osnapOverrides,
		const AcArray<AcDbCustomOsnapMode*>& customOsnapOverrides,
		const AcArray<AcDbObjectId>& apertureEntities,
		const AcArray< AcDbObjectIdArray,
		AcArrayObjectCopyReallocator< AcDbObjectIdArray > >& nestedApertureEntities,
		const AcArray<int>& gsSelectionMark,
		const AcArray<AcDbObjectId>& keyPointEntities,
		const AcArray< AcDbObjectIdArray,
		AcArrayObjectCopyReallocator< AcDbObjectIdArray > >& nestedKeyPointEntities,
		const AcArray<int>& keyPointGsSelectionMark,
		const AcArray<AcGeCurve3d*>& alignmentPaths,
		const AcGePoint3d& computedPoint,
	    const TCHAR* pTooltipString);

private:
	// 指向这个对象所属的文档
	AcApDocument* m_pDoc;
};

#endif // !defined(AFX_ENTINFOTIPHANDLER_H__42D55ACC_95B2_4090_A8C4_F8969156387A__INCLUDED_)
