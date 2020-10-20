// docdata.h : include file for document specific data
//      an instance of this class is automatically created
//      and managed by the AsdkDataManager class
//      see the AsdkDmgr.h DocData.cpp for more datail
#if !defined(AFX_DOCDATA_H__B9843CAE_C024_4E5F_8AD3_981E9D46E5A0__INCLUDED_)
#define AFX_DOCDATA_H__B9843CAE_C024_4E5F_8AD3_981E9D46E5A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////////////////////////////////////////
//
// Here you can store the document / database
// related data.
//
class CDocData
{
public:
	CDocData();
	CDocData(const CDocData &data) ;
	~CDocData();

	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_DATA(CDocData)
	//}}AFX_ARX_DATA

	// TODO: here you can add your variables
	//       which depends on a document / database.

};

#endif
