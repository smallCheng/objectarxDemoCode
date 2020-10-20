/////////////////////////////////////////////
// ZffDwgScale custom object.

#if !defined(ARX__ZFFDWGSCALE_H__20140205_113541)
#define ARX__ZFFDWGSCALE_H__20140205_113541

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dbmain.h"

#pragma warning(disable: 4275 4251)

#ifdef _CUSTOMOBJECTDB_
#define DLLIMPEXP __declspec(dllexport)
#else
#define DLLIMPEXP 
#endif

#ifndef ZFFCUSTOMOBJECTDB_DBXSERVICE
#define ZFFCUSTOMOBJECTDB_DBXSERVICE "ZFFCUSTOMOBJECTDB_DBXSERVICE"
#endif

class DLLIMPEXP ZffDwgScale : public AcDbObject
{
public:

	ACRX_DECLARE_MEMBERS(ZffDwgScale);

	// Constructor / Destructor
	ZffDwgScale();
	virtual ~ZffDwgScale();

	//{{AFX_ARX_METHODS(ZffDwgScale)
	virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
	virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
	virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
	virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
	//}}AFX_ARX_METHODS


	//{{AFX_ARX_DATA_ACCESS(ZffDwgScale)
	//}}AFX_ARX_DATA_ACCESS
	
	// 设置条件图比例和出图比例
	void Set(int infoScale, int lableScale);

	// 获得条件图比例和出图比例
	int GetInfoScale() const;
	int GetLabelScale() const;

private:
	//{{AFX_ARX_DATA(ZffDwgScale)
	//}}AFX_ARX_DATA
	Adesk::Int32 m_infoScale;		// 条件图比例
	Adesk::Int32 m_lableScale;		// 出图比例

private:

	void *operator new[](unsigned nSize) { return 0; }
	void operator delete[](void *p) {};
	void *operator new[](unsigned nSize, const char *file, int line) { return 0; }

};



#endif // !defined(ARX__ZFFDWGSCALE_H__20140205_113541)