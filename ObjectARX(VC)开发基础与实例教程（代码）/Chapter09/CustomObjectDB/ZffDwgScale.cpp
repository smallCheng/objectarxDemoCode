/////////////////////////////////////////////
// ZffDwgScale custom object.

#include "StdAfx.h"
#include "StdArx.h"
#include "dbproxy.h"
#include "geassign.h"
#include "acgi.h"

#define VERSION_ZFFDWGSCALE 1


//{{AFX_ARX_MACRO
ACRX_DXF_DEFINE_MEMBERS(ZffDwgScale, AcDbObject,
						 AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
                        AcDbProxyObject::kNoOperation,
						 ZFFDWGSCALE, ZffCustomObjectDB);
//}}AFX_ARX_MACRO


// Constructor / Destructor

ZffDwgScale::ZffDwgScale()
{
	//{{AFX_ARX_DATA_INIT(ZffDwgScale)
	//}}AFX_ARX_DATA_INIT

	m_infoScale = 0;
	m_lableScale = 0;
}

ZffDwgScale::~ZffDwgScale()
{
	// TODO: clean up.

}


Acad::ErrorStatus ZffDwgScale::dwgInFields(AcDbDwgFiler* pFiler)
{
	assertWriteEnabled();
	Acad::ErrorStatus es;

	// Call dwgInFields from AcDbObject
	if ((es = AcDbObject::dwgInFields(pFiler)) != Acad::eOk) {
		return es;
	}

	// Read version number.
	Adesk::UInt16 version;
	pFiler->readItem(&version);
	if (version > VERSION_ZFFDWGSCALE)
		return Acad::eMakeMeProxy;

	// Read the data members.
	switch (version)
	{
	case (1):
		// TODO: here you can file datamembers not
		//       created by the ObjectARX Add-In.
		pFiler->readItem(&m_infoScale);
		pFiler->readItem(&m_lableScale);

		break;
	}


	return pFiler->filerStatus();
}

Acad::ErrorStatus ZffDwgScale::dwgOutFields(AcDbDwgFiler* pFiler) const
{
	assertReadEnabled();
	Acad::ErrorStatus es;

	// Call dwgOutFields from AcDbObject
	if ((es = AcDbObject::dwgOutFields(pFiler)) != Acad::eOk) {
		return es;
	}

	// Write version number.
	pFiler->writeItem((Adesk::UInt16) VERSION_ZFFDWGSCALE);

	// Write the data members.
	// TODO: here you can file datamembers not
	//       created by the ObjectARX Add-In.
	pFiler->writeItem(m_infoScale);
	pFiler->writeItem(m_lableScale);

	return pFiler->filerStatus();
}

Acad::ErrorStatus ZffDwgScale::dxfInFields(AcDbDxfFiler* pFiler)
{
	assertWriteEnabled();
	struct resbuf rb;

	if ((AcDbObject::dxfInFields(pFiler) != Acad::eOk) ||
	    !pFiler->atSubclassData("ZffDwgScale"))
		return pFiler->filerStatus();

	// Read version number.
	pFiler->readItem(&rb);
	if (rb.restype != AcDb::kDxfInt16) {
		pFiler->pushBackItem();
		pFiler->setError(Acad::eInvalidDxfCode,
		                "nError: expected object version group code %d",
		                 AcDb::kDxfInt16);
		return pFiler->filerStatus();
	} else {
		Adesk::UInt16 version = rb.resval.rint;
		if (version > VERSION_ZFFDWGSCALE)
			return Acad::eMakeMeProxy;
	}

	// 读取条件图比例
	pFiler->readItem(&rb);
	if (rb.restype != AcDb::kDxfInt32) 
	{
		pFiler->pushBackItem();
		pFiler->setError(Acad::eInvalidDxfCode,
			"nError: expected object version group code %d",
			AcDb::kDxfInt32);
		return pFiler->filerStatus();
	} 
	else
	{
		m_infoScale = rb.resval.rlong;
	}

	// 读取出图比例
	pFiler->readItem(&rb);
	if (rb.restype != AcDb::kDxfInt32) 
	{
		pFiler->pushBackItem();
		pFiler->setError(Acad::eInvalidDxfCode,
			"nError: expected object version group code %d",
			AcDb::kDxfInt32);
		return pFiler->filerStatus();
	} 
	else
	{
		m_lableScale = rb.resval.rlong;
	}

	return pFiler->filerStatus();
}

Acad::ErrorStatus ZffDwgScale::dxfOutFields(AcDbDxfFiler* pFiler) const
{
	assertReadEnabled();
	Acad::ErrorStatus es;

	if ((es = AcDbObject::dxfOutFields(pFiler)) != Acad::eOk)
		return es;

	// Write subclass marker.
	pFiler->writeItem(AcDb::kDxfSubclass, "ZffDwgScale");

	// Write version number.
	pFiler->writeItem(AcDb::kDxfInt16, (Adesk::UInt16) VERSION_ZFFDWGSCALE);

	// 写入两个成员变量
	pFiler->writeItem(AcDb::kDxfInt32, m_infoScale);
	pFiler->writeItem(AcDb::kDxfInt32, m_lableScale);

	return es;
}

void ZffDwgScale::Set( int infoScale, int lableScale )
{
	assertWriteEnabled();

	m_infoScale = infoScale;
	m_lableScale = lableScale;
}

int ZffDwgScale::GetInfoScale() const
{
	assertReadEnabled();

	return m_infoScale;
}

int ZffDwgScale::GetLabelScale() const
{
	assertReadEnabled();

	return m_lableScale;
}

