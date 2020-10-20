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

// GsPreviewCtrl.cpp : implementation file
//

#include "stdafx.h"
//#include "..\stdarx.h"
//#include "resource.h"
#include "GsPreviewCtrl.h"
#include <acgs.h>
#include <dbsymtb.h>
//#include <Common\ObjectARX\DwgDatabaseUtil.h>
//#include "..\Dialog\SelectUserBlockDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CAcExtensionModule PreviewControlDLL;			//BlockView2002DLL;

/////////////////////////////////////////////////////////////////////////////
// CGsPreviewCtrl

BEGIN_MESSAGE_MAP(CGsPreviewCtrl, CStatic)
//{{AFX_MSG_MAP(CGsPreviewCtrl)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_NCHITTEST()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONUP()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGsPreviewCtrl message handlers

void CGsPreviewCtrl::OnPaint() 
{
	CPaintDC dc(this); 
	//update the gs view
	mpView->invalidate(); 
	mpView->update();
}

// Erase view and delete model
void CGsPreviewCtrl::erasePreview()
{
	if (mpView)
		mpView->eraseAll();
	if (mpManager && mpModel) {  
		mpManager->destroyAutoCADModel (mpModel);
		mpModel = NULL;
	}
}

void CGsPreviewCtrl::setModel(AcGsModel* pModel)
{
	erasePreview();
	mpModel = pModel;
	mbModelCreated =false;
}

void CGsPreviewCtrl::clearAll()
{
	if (mpView)  
	{
		mpView->eraseAll();
	}
	if (mpDevice)    
	{
		bool b = mpDevice->erase(mpView);
		RXASSERT(b);
	}
	
	if (mpFactory)    
	{
		if (mpView)  
		{
			mpFactory->deleteView(mpView);
			mpView = NULL;
		}
		if (mpGhostModel) 
		{
			mpFactory->deleteModel(mpGhostModel);
			mpGhostModel = NULL;
		}
		mpFactory = NULL;
	}
	
	if (mpManager)    
	{
		if (mpModel) 
		{
			if (mbModelCreated)
				mpManager->destroyAutoCADModel(mpModel);
			mpModel = NULL;
		}
    
		if (mpDevice)    
		{
			mpManager->destroyAutoCADDevice(mpDevice);
			mpDevice = NULL;
		}
		mpManager = NULL;
	}  
	
	if (m_pDb)
	{
		delete m_pDb;
		m_pDb = NULL;
	}
}

void CGsPreviewCtrl::Init(HMODULE hRes, bool bCreateModel)
{
	// 加载光标文件（根据需要决定是否使用）
// 	mhPanCursor = LoadCursor(hRes,MAKEINTRESOURCE(IDI_PAN));
// 	mhCrossCursor = LoadCursor(hRes,MAKEINTRESOURCE(IDI_CROSS));
// 	mhOrbitCursor = LoadCursor(hRes,MAKEINTRESOURCE(IDI_ORBIT));
	::SetClassLong(m_hWnd, GCL_HCURSOR, NULL);

	// 实例化视图、设备和模型对象
	CRect rect;
	if (!mpManager) 
	{
		// 获得AcGsManager对象
		mpManager = acgsGetGsManager();
		RXASSERT(mpManager);
		// get the GS class factory
		mpFactory = mpManager->getGSClassFactory();
		RXASSERT(mpFactory);
		// create an AcGsDevice object. The window handle passed in to this 
		// function is the display surface onto which the graphics system draws
		//a device with standard autocad color palette
		mpDevice = mpManager->createAutoCADDevice(m_hWnd);
		RXASSERT(mpDevice);
		
		// 获得我们将要绘制的窗口尺寸
		GetClientRect( &rect);
		// 确保gs设备知道窗口尺寸
		mpDevice->onSize(rect.Width(), rect.Height());   
		// 构造AcGsView对象
		mpView = mpFactory->createView();
		RXASSERT(mpView);
		if (bCreateModel)
		{
			RXASSERT(mpModel==NULL);
			// create an AcGsModel object with the AcGsModel::kMain RenderType 
			// (which is a hint to the graphics system that the geometry in this 
			// model should be rasterized into its main frame buffer). This 
			// AcGsModel is created with get and release functions that will open and close AcDb objects.
			mpModel = mpManager->createAutoCADModel();
			RXASSERT(mpModel);
			mbModelCreated = true;
		}
		//another model without open/close for the orbit gadget
		mpGhostModel = mpFactory->createModel(AcGsModel::kDirect,0,0,0);
		mpView->add(&mOrbitGadget,mpGhostModel);
		mOrbitGadget.setGsView(mpView);
		mpDevice->add(mpView);

		//////////////////////////////////////////////////////////////////////////
		AcColorSettings colourSettings; 
		// get the AutoCAD current colour settings
		acedGetCurrentColors(&colourSettings); 	
		DWORD colorDW; 
		// get the background colour
		colorDW = colourSettings.dwGfxModelBkColor; 
		// get the current device background colour	
		AcGsColor color = mpDevice->getBackgroundColor();
		// now update them to the new color
		color.m_red   = 0;
		color.m_green = 0;
		color.m_blue  = 0;
		color.m_filler = 255; // opaque background
		// 设置新的控件背景颜色
		mpDevice->setBackgroundColor(color);

		// 设置默认视图的显示方向
		ads_real height = 0.0, width = 0.0, viewTwist = 0.0;
		AcGePoint3d targetView(1, 1, 0);
		AcGeVector3d viewDir(0, 0, 1);
		mpView->setView(targetView + viewDir, targetView,
			AcGeVector3d(0.0, 1.0, 0.0),  // upvector
			1.0, 1.0);
	}
}


void CGsPreviewCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CRect rect;
	if (mpDevice) {
		GetClientRect( &rect);
		mpDevice->onSize(rect.Width(), rect.Height());
	}
}

BOOL CGsPreviewCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if (mpView)
	{
		if (zDelta<0)
			mpView->zoom(0.5);
		else
			mpView->zoom(1.5);
		Invalidate();
	}

	return TRUE;
}

void CGsPreviewCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
 	SetFocus();
}

void CGsPreviewCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//end orbit
// 	mbOrbiting = false;
// 	::SetClassLong(m_hWnd,GCL_HCURSOR,(long)mhCrossCursor);
// 	ReleaseCapture();
}

void CGsPreviewCtrl::OnMButtonDown(UINT nFlags, CPoint point) 
{
	//start pan
	mbPanning = true;
	SetCapture();
	//set up the proper cursor
	::SetClassLong(m_hWnd,GCL_HCURSOR,NULL);
	::SetCursor(mhPanCursor);
	//store the start point
	mStartPt = point;

	SetFocus();
}

void CGsPreviewCtrl::OnMButtonUp(UINT nFlags, CPoint point) 
{
	//end pan
	ReleaseCapture();
	mbPanning = false;
	::SetClassLong(m_hWnd,GCL_HCURSOR,(long)mhCrossCursor);
}

void CGsPreviewCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (mpView)
	{
		if (mbPanning)
		{
			//transform the point from device coordinates to
			//world coordinates
			AcGeVector3d pan_vec(-(point.x-mStartPt.x),point.y-mStartPt.y,0);
			pan_vec.transformBy(mpView->viewingMatrix() * mpView->worldToDeviceMatrix().inverse());
			mpView->dolly(pan_vec);
			Invalidate();
			mStartPt = point;
		}
		if (mbOrbiting)
		{
			const double Half_Pi =  1.570796326795;
			
			AcGsDCRect view_rect;
			mpView->getViewport (view_rect);
			
			int nViewportX = (view_rect.m_max.x - view_rect.m_min.x) + 1;
			int nViewportY = (view_rect.m_max.y - view_rect.m_min.y) + 1;
			
			int centerX = (int)(nViewportX / 2.0f + view_rect.m_min.x);
			int centerY = (int)(nViewportY / 2.0f + view_rect.m_min.y); 
      
			const double radius  = min (nViewportX, nViewportY) * 0.4f;
			
			// compute two vectors from last and new cursor positions:
			
			AcGeVector3d last_vector ((mStartPt.x - centerX) / radius,
				-(mStartPt.y - centerY) / radius,
				0.0);
			
			if (last_vector.lengthSqrd () > 1.0)     // outside the radius
				last_vector.normalize  ();
			else
				last_vector.z = sqrt (1.0 - last_vector.x * last_vector.x - last_vector.y * last_vector.y);
			
			AcGeVector3d new_vector((point.x - centerX) / radius,
				-(point.y - centerY) / radius,
				0.0);
			
			if (new_vector.lengthSqrd () > 1.0)     // outside the radius
				new_vector.normalize  ();
			else
				new_vector.z = sqrt (1.0 - new_vector.x * new_vector.x - new_vector.y * new_vector.y);
			
			// determine angles for proper sequence of camera manipulations:
			
			AcGeVector3d    rotation_vector (last_vector);
			rotation_vector = rotation_vector.crossProduct (new_vector);  // rotation_vector = last_vector x new_vector
			
			AcGeVector3d    work_vector (rotation_vector);
			work_vector.z = 0.0f;                      // projection of rotation_vector onto xy plane
			
			double          roll_angle      = atan2 (work_vector.x, 
				work_vector.y);        // assuming that the camera's up vector is "up",
			// this computes the angle between the up vector 
			// and the work vector, which is the roll required
			// to make the up vector coincident with the rotation_vector
			
			double length = rotation_vector.length ();
			double orbit_y_angle = (length != 0.0) ? acos (rotation_vector.z / length) + Half_Pi : Half_Pi;                   // represents inverse cosine of the dot product of the
			if (length > 1.0f)                                              // rotation_vector and the up_vector divided by the
				length = 1.0f;                                              // magnitude of both vectors.  We add pi/2 because we 
			// are making the up-vector parallel to the the rotation
			double          rotation_angle  = asin (length);                // vector ... up-vector is perpin. to the eye-vector.
			
			// perform view manipulations
			
			mpView->roll( roll_angle);               // 1: roll camera to make up vector coincident with rotation vector
			mpView->orbit( 0.0f,  orbit_y_angle);     // 2: orbit along y to make up vector parallel with rotation vector
			mpView->orbit( rotation_angle, 0.0f);     // 3: orbit along x by rotation angle
			mpView->orbit( 0.0f, -orbit_y_angle);     // 4: orbit along y by the negation of 2
			mpView->roll(-roll_angle);               // 5: roll camera by the negation of 1
			Invalidate();
			mStartPt = point;
		}
	}	
}

#if _MSC_VER <= 1310
UINT CGsPreviewCtrl::OnNcHitTest(CPoint point) 
{
	return HTCLIENT;
}
#else
LRESULT CGsPreviewCtrl::OnNcHitTest(CPoint point) 
{
	return HTCLIENT;
}
#endif


void CGsPreviewCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	::SetClassLong(m_hWnd,GCL_HCURSOR,(long)mhCrossCursor);	
}

void CGsPreviewCtrl::SetDwgFile( const TCHAR* fileName )
{
	// 完全清理GsView对象，重新开始构建新的环境
	if (mpView)
	{
		mpView->eraseAll();	
	}

	if (m_pDb)
	{
		delete m_pDb;
		m_pDb = NULL;
	}

	// 新建图形数据库，读取DWG文件，作为预览目标
	m_pDb = new AcDbDatabase (Adesk::kFalse);
	Acad::ErrorStatus es = Acad::eInvalidInput;
	if (fileName != NULL)
	{
		es = m_pDb->readDwgFile(fileName, _SH_DENYNO);
	}
	if (es != Acad::eOk)
	{
 		delete m_pDb;
 		m_pDb = NULL;
	}

	// 初始化预览控件
	InitDrawingControl();
	
	Invalidate();
}

static AcDbObjectIdArray GetAllEntityIds(AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase())
{
	AcDbObjectIdArray entIds;
	
	AcDbBlockTable *pBlkTbl = NULL;
	pDb->getBlockTable(pBlkTbl, AcDb::kForRead);
	
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForRead);
	pBlkTbl->close();
	
	AcDbBlockTableRecordIterator *it = NULL;
	pBlkTblRcd->newIterator(it);
	AcDbEntity *pEnt = NULL;
	for (it->start(); !it->done(); it->step())
	{
		if (it->getEntity(pEnt, AcDb::kForRead) == Acad::eOk)
		{
			entIds.append(pEnt->objectId());
			
			pEnt->close();
		}
	}
	delete it;
	pBlkTblRcd->close();
	
	return entIds;
}

static AcDbExtents GetModelSpaceExtent(AcDbDatabase *pDb)
{
	AcDbBlockTable *pBlkTbl = NULL;
	pDb->getBlockTable(pBlkTbl, AcDb::kForRead);
	
	// 获得模型空间的块表记录
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForRead);
	pBlkTbl->close();
	
	AcDbExtents extent;
	Acad::ErrorStatus es = extent.addBlockExt(pBlkTblRcd);
	pBlkTblRcd->close();
	
	// 如果图形数据库不是当前的工作数据库，有时候直接获取模型空间的范围会失败
	if (es != Acad::eOk)
	{
		AcDbObjectIdArray allEnts = GetAllEntityIds(pDb);
		for (int i = 0; i < allEnts.length(); i++)
		{
			AcDbEntity *pEnt = NULL;
			if (acdbOpenObject(pEnt, allEnts[i], AcDb::kForRead) == Acad::eOk)
			{
				AcDbExtents ext;
				if (pEnt->getGeomExtents(ext) == Acad::eOk)
				{
					extent.addExt(ext);
				}
				
				pEnt->close();
			}
		}
	}
	
	return extent;	
}

Acad::ErrorStatus CGsPreviewCtrl::InitDrawingControl( const TCHAR *space )
{
	// 检测是否设置有效图形数据库
	if (m_pDb == NULL)
		return Acad::eNullBlockName;
	
	// 获得块表
	AcDbBlockTable *pTab = NULL;
	Acad::ErrorStatus es = m_pDb->getBlockTable (pTab, AcDb::kForRead);
	if (es == Acad::eOk)
	{
		// 获得指定的块表记录（一般都是模型空间）
		AcDbBlockTableRecord *pRec = NULL;
		es = pTab->getAt (space, pRec, AcDb::kForRead);
		if (es == Acad::eOk)
		{
			pTab->close();

			// 初始化控件资源
			Init(PreviewControlDLL.ModuleResourceInstance(), true);
			
			// 计算图形数据库模型空间的大小
			AcDbExtents ext = GetModelSpaceExtent(m_pDb);
			AcGePoint3d extMax = ext.maxPoint();
			AcGePoint3d extMin = ext.minPoint();

			// 修正一下显示的范围，让整个图形都能显示出来
			double extHeight = extMax.y - extMin.y;
			double extWidth = extMax.x - extMin.x;
			double scale = 0.1;
			extMax.x += scale * extWidth;
			extMin.x -= scale * extWidth;
			extMax.y += scale * extHeight;
			extMin.y -= scale * extHeight;
			
			// get the view port information - see parameter list
			ads_real height = 0.0, width = 0.0, viewTwist = 0.0;
			AcGePoint3d targetView(1, 1, 0);
			AcGeVector3d viewDir(0, 0, 1);
			
			// 设置视图使用的是显示坐标系，因此需要进行坐标变换
			// Our view coordinate space consists of z direction 
			// get a perp vector off the z direction
			// Make sure its normalised
			AcGeVector3d viewXDir = viewDir.perpVector ().normal();
			// correct the x angle by applying the twist
			viewXDir = viewXDir.rotateBy (viewTwist, -viewDir);
			// now we can work out y, this is of course perp to the x and z directions. No need to normalise this, 
			// as we know that x and z are of unit length, and perpendicular, so their cross product must be on unit length
			AcGeVector3d viewYDir = viewDir.crossProduct (viewXDir);
			
			// find a nice point around which to transform the view. We'll use the same point as the center of the view.
			AcGePoint3d boxCenter = extMin + 0.5 * ( extMax - extMin );
			
			//**********************************************
			// create a transform from WCS to View space
			// this represents the transformation from WCS to the view space. (Actually not quite since 
			// we are keeping the fixed point as the center of the box for convenience )
			AcGeMatrix3d viewMat;
			viewMat = AcGeMatrix3d::alignCoordSys (boxCenter, AcGeVector3d::kXAxis, AcGeVector3d::kYAxis, AcGeVector3d::kZAxis,  
				boxCenter, viewXDir, viewYDir, viewDir).inverse();
			
			AcDbExtents wcsExtents(extMin, extMax);
			// now we have the view Extents
			AcDbExtents viewExtents = wcsExtents;
			// transforms the extents in WCS->view space
			viewExtents.transformBy (viewMat);
			
			//**********************************************
			// get the extents of the AutoCAD view
			double xMax = fabs(viewExtents.maxPoint ().x - viewExtents.minPoint ().x);
			double yMax = fabs(viewExtents.maxPoint ().y - viewExtents.minPoint ().y);
			
			//**********************************************
			// setup the view
			AcGsView *pView = view();	
			AcGePoint3d eye = boxCenter + viewDir;
			
			// 设置观察角度和范围
			pView->setView(eye, boxCenter, viewYDir, xMax, yMax);
			
			pView->add(pRec, model()); 
			
			pRec->close();
		}
	}
	
	return es;
}

bool CGsPreviewCtrl::GetActiveViewPortInfo( ads_real &height, ads_real &width, AcGePoint3d &target, AcGeVector3d &viewDir, ads_real &viewTwist, bool getViewCenter )
{
	// make sure the active view port is uptodate
	acedVports2VportTableRecords();
	
	// get the working db
	AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase(); 
	// if not ok
	if (pDb == NULL)
		return false;
	
	// open the view port records
	AcDbViewportTable *pVTable = NULL;
	Acad::ErrorStatus es = pDb->getViewportTable (pVTable, AcDb::kForRead);
	// if we opened them ok
	if (es == Acad::eOk)
	{
		AcDbViewportTableRecord *pViewPortRec = NULL;
		es = pVTable->getAt (TEXT("*Active"), pViewPortRec, AcDb::kForRead);
		if (es == Acad::eOk)
		{
			// get the height of the view
			height = pViewPortRec->height ();
			// get the width
			width = pViewPortRec->width ();
			// if the user wants the center of the viewport used
			if (getViewCenter == true)
			{
				struct resbuf rb;
				memset (&rb, 0, sizeof (struct resbuf));
				// get the system var VIEWCTR
				acedGetVar (TEXT("VIEWCTR"), &rb);
				// set that as the target
				target = AcGePoint3d (rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
			}
			// we want the viewports camera target setting
			else
			{
				// get the target of the view
				target = pViewPortRec->target ();
			}		
			
			// get the view direction
			viewDir = pViewPortRec->viewDirection ();
			// get the view twist of the viewport
			viewTwist = pViewPortRec->viewTwist ();
		}
		// close after use
		pVTable->close ();
		pViewPortRec->close();			
	}	
	
	return true;
}

void CGsPreviewCtrl::SetDatabase( AcDbDatabase *pDb )
{
	// 完全清理GsView对象，重新开始构建新的环境
	if (mpView)
	{
		mpView->eraseAll();	
	}
	
	if (m_pDb)
	{
		delete m_pDb;
		m_pDb = NULL;
	}

	m_pDb = pDb;
	
	// 初始化图形控件
	InitDrawingControl();
	
	Invalidate();
}
