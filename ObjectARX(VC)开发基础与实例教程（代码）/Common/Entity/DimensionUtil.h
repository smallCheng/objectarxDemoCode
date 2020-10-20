// DimensionUtil.h: interface for the CDimensionUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIMENSIONUTIL_H__6F453D5C_040C_4656_AAD0_96598B73CC0B__INCLUDED_)
#define AFX_DIMENSIONUTIL_H__6F453D5C_040C_4656_AAD0_96598B73CC0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDimensionUtil  
{
public:
	CDimensionUtil();
	virtual ~CDimensionUtil();

	// 对齐标注
	static AcDbObjectId AddDimAligned(const AcGePoint3d& pt1, 
		const AcGePoint3d& pt2, const AcGePoint3d& ptLine, const TCHAR* dimText = NULL, 
		AcDbObjectId dimStyle = AcDbObjectId::kNull);
	static AcDbObjectId AddDimAligned(const AcGePoint3d& pt1, 
		const AcGePoint3d& pt2, const AcGePoint3d& ptLine, 
		const AcGeVector3d& vecOffset = AcGeVector3d::kIdentity, 
		const TCHAR* dimText = NULL);

	// 转角标注
	static AcDbObjectId AddDimRotated(const AcGePoint3d& pt1, 
		const AcGePoint3d& pt2, const AcGePoint3d& ptLine, 
		double rotation, const TCHAR* dimText = NULL, 
		AcDbObjectId dimStyle = AcDbObjectId::kNull);

	// 半径标注
	static AcDbObjectId AddDimRadial(const AcGePoint3d& ptCenter, 
		const AcGePoint3d& ptChord, double leaderLength, 
		const TCHAR* dimText = NULL, 
		AcDbObjectId dimStyle = AcDbObjectId::kNull);
	static AcDbObjectId AddDimRadial(const AcGePoint3d& ptCenter, 
		double radius, double angle, double leaderLength = 5);

	// 直径标注
	static AcDbObjectId AddDimDiametric (const AcGePoint3d& ptChord1, 
		const AcGePoint3d& ptChord2, double leaderLength, 
		const TCHAR* dimText = NULL, 
		AcDbObjectId dimStyle = AcDbObjectId::kNull);
	static AcDbObjectId AddDimDiametric(const AcGePoint3d& ptCenter, 
		double radius, double angle, double leaderLength = 5);

	// 角度标注
	static AcDbObjectId AddDim2LineAngular(const AcGePoint3d& ptStart1, 
		const AcGePoint3d& ptEnd1, const AcGePoint3d& ptStart2, 
		const AcGePoint3d& ptEnd2, const AcGePoint3d& ptArc, 
		const TCHAR* dimText = NULL, 
		AcDbObjectId dimStyle = AcDbObjectId::kNull);
	static AcDbObjectId AddDim3PtAngular(const AcGePoint3d& ptCenter, 
		const AcGePoint3d& ptEnd1, const AcGePoint3d& ptEnd2, 
		const AcGePoint3d& ptArc, const TCHAR* dimText = NULL, 
		AcDbObjectId dimStyle = AcDbObjectId::kNull);

	// 坐标标注
	static AcDbObjectId AddDimOrdinate(Adesk::Boolean xAxis, 
		const AcGePoint3d& ptStart, const AcGePoint3d& ptEnd, 
		const TCHAR* dimText = NULL, 
		AcDbObjectId dimStyle = AcDbObjectId::kNull);
	static AcDbObjectIdArray AddDimOrdinate(const AcGePoint3d& ptDef, 
		const AcGePoint3d& ptTextX, const AcGePoint3d& ptTextY);
	static AcDbObjectIdArray AddDimOrdinate(const AcGePoint3d& ptDef, 
		const AcGeVector3d& vecOffsetX, const AcGeVector3d& vecOffsetY);
};

#endif // !defined(AFX_DIMENSIONUTIL_H__6F453D5C_040C_4656_AAD0_96598B73CC0B__INCLUDED_)
