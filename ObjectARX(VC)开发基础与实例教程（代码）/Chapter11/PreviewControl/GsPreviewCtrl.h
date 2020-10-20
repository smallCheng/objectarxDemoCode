//
// (C) Copyright 2002 by Autodesk, Inc. 
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

#if !defined(AFX_GSPREVIEWCTRL_H__7DC11025_C827_11D2_B89C_080009DCA551__INCLUDED_)
#define AFX_GSPREVIEWCTRL_H__7DC11025_C827_11D2_B89C_080009DCA551__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GsPreviewCtrl.h : header file
//
#include "acgi.h"
#include <math.h>
#include <gs.h>
#include <AcGsManager.h>
// Simple lighweight drawable to do orbit glyph
//
class OrbitGadget : public AcGiDrawable
{
    AcGsNode* m_pNode;
    AcGsView* m_pAcGsView;
public:
    
    OrbitGadget():m_pNode(NULL) {}
    void setGsView(AcGsView* pView) {m_pAcGsView=pView;}

#if _MSC_VER < 1500
	virtual Adesk::UInt32   setAttributes   (AcGiDrawableTraits * traits)
    {
        traits->setTrueColor (AcCmEntityColor(0,200,0));
        return kDrawableNone;
    }
    virtual Adesk::Boolean  worldDraw       (AcGiWorldDraw * wd)
    {
        return Adesk::kFalse;
    }
    virtual void            viewportDraw    (AcGiViewportDraw * pViewportDraw)
    {
        AcGsDCRect view_rect;
        m_pAcGsView->getViewport (view_rect);

        int nViewportX = (view_rect.m_max.x - view_rect.m_min.x) + 1;
        int nViewportY = (view_rect.m_max.y - view_rect.m_min.y) + 1;
        AcGeMatrix3d scale = m_pAcGsView->viewingMatrix() * m_pAcGsView->worldToDeviceMatrix().inverse();
        AcGeVector3d viewDir = m_pAcGsView->target()-m_pAcGsView->position();
        const double radius  = min (nViewportX, nViewportY) * 0.4f*scale.scale();

        pViewportDraw->geometry().circle(m_pAcGsView->target(),radius,viewDir);
        return;
    }
#endif	// _MSC_VER < 1500
    virtual Adesk::Boolean  isPersistent    (void) const
    { 
        return Adesk::kFalse;
    };                 
    virtual AcDbObjectId    id              (void) const
    {
        return AcDbObjectId::kNull;
    }
    virtual void            setGsNode       (AcGsNode * gsnode)
    {
        m_pNode = gsnode;
    }
    virtual AcGsNode*       gsNode          (void) const
    {
        return m_pNode;
    }

#if _MSC_VER >= 1500
	virtual Adesk::UInt32   subSetAttributes   (AcGiDrawableTraits * traits){ return 0; };

	virtual Adesk::Boolean  subWorldDraw       (AcGiWorldDraw * wd){ return Adesk::kTrue; };

	virtual void            subViewportDraw    (AcGiViewportDraw * vd){ };
#endif	// _MSC_VER >= 1500
};

/////////////////////////////////////////////////////////////////////////////
// CGsPreviewCtrl window

class CGsPreviewCtrl : public CStatic
{

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGsPreviewCtrl)
	//}}AFX_VIRTUAL


public:
	CGsPreviewCtrl() : CStatic(), 
		mpManager(NULL), mpFactory(NULL), mpDevice(NULL), mpView(NULL), 
		mpModel(NULL),mbModelCreated(false),mbPanning(false),mbOrbiting(false), 
		m_pDb(NULL) {} 
    
    virtual ~CGsPreviewCtrl() {clearAll();}

	// 初始化控件的资源
    void Init(HMODULE hRes, bool bCreateModel = true);
    void erasePreview();
    void clearAll();

	// 设置要预览的图形文件
	void SetDwgFile(const TCHAR* fileName);
	void SetDatabase(AcDbDatabase *pDb);

    AcGsView*   view()      { return mpView; }
    AcGsDevice* device()    { return mpDevice; }
    AcGsModel*  model()     { return mpModel; }
    void setModel(AcGsModel* pModel);
	// Generated message map functions

private:
	// 显示m_pDb图形数据库中某个块表记录的内容
	Acad::ErrorStatus InitDrawingControl (const TCHAR *space = ACDB_MODEL_SPACE);

	bool GetActiveViewPortInfo (ads_real &height, ads_real &width, AcGePoint3d &target, AcGeVector3d &viewDir, 
							ads_real &viewTwist, bool getViewCenter);

protected:
	//{{AFX_MSG(CGsPreviewCtrl)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
#if _MSC_VER <= 1310
	afx_msg UINT OnNcHitTest(CPoint point);
#else
	afx_msg LRESULT OnNcHitTest(CPoint point);
#endif
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	HCURSOR mhSavedCursor;
	HCURSOR mhPanCursor;
	HCURSOR mhCrossCursor;
	HCURSOR mhOrbitCursor;
	AcGsManager         *mpManager;
	AcGsClassFactory    *mpFactory;
	AcGsDevice          *mpDevice;
	AcGsView            *mpView;
	AcGsModel           *mpModel;
	AcGsModel           *mpGhostModel;
	OrbitGadget         mOrbitGadget;
	bool mbModelCreated;
	bool mbPanning;
	bool mbOrbiting;
	CPoint mStartPt;

	AcDbDatabase *m_pDb;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GSPREVIEWCTRL_H__7DC11025_C827_11D2_B89C_080009DCA551__INCLUDED_)
