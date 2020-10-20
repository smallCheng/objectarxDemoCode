// (C) Copyright 2002-2005 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- MyPaletteChildDlg1.cpp : Implementation of CMyPaletteChildDlg1
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "MyPaletteChildDlg1.h"
#include "..\..\Common\Entity\LineUtil.h"

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CMyPaletteChildDlg1, CAcUiDialog)

BEGIN_MESSAGE_MAP(CMyPaletteChildDlg1, CAcUiDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	ON_BN_CLICKED(IDC_DRAW_LINE, &CMyPaletteChildDlg1::OnBnClickedDrawLine)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CMyPaletteChildDlg1::CMyPaletteChildDlg1 (CWnd *pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) 
	: CAcUiDialog (CMyPaletteChildDlg1::IDD, pParent, hInstance) 
{
}

//-----------------------------------------------------------------------------
void CMyPaletteChildDlg1::DoDataExchange (CDataExchange *pDX) {
	CAcUiDialog::DoDataExchange (pDX) ;
}

//-----------------------------------------------------------------------------
//----- Needed for modeless dialogs to keep focus.
//----- Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT CMyPaletteChildDlg1::OnAcadKeepFocus (WPARAM, LPARAM) {
	return (TRUE) ;
}

static AcDbObjectId PostToModelSpace( AcDbEntity *pEnt )
{
	if (pEnt == NULL)
	{
		return AcDbObjectId::kNull;
	}

	AcDbBlockTable *pBlkTbl;
	AcDbBlockTableRecord *pBlkTblRcd;
	Acad::ErrorStatus es = acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForRead);
	if (es != Acad::eOk)
	{
		return AcDbObjectId::kNull;
	}

	es = pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForWrite);
	if (es != Acad::eOk)
	{
		pBlkTbl->close();
		return AcDbObjectId::kNull;
	}
	pBlkTbl->close();

	AcDbObjectId entId;
	es = pBlkTblRcd->appendAcDbEntity(entId, pEnt);
	if (es != Acad::eOk)
	{
		pBlkTblRcd->close();
		delete pEnt;	// 添加失败时，要delete
		pEnt = NULL;

		return AcDbObjectId::kNull;
	}

	pBlkTblRcd->close();
	pEnt->close();

	return entId;	
}

void CMyPaletteChildDlg1::OnBnClickedDrawLine()
{
	// 类似非模态对话框，在修改图形数据库时必须锁定文档
	acDocManager->lockDocument(acDocManager->curDocument());

	// 绘制一条直线
	CLineUtil::Add(AcGePoint3d(0, 0, 0), AcGePoint3d(100, 100, 0));

	// 解锁文档
	acDocManager->unlockDocument(acDocManager->curDocument());
}
