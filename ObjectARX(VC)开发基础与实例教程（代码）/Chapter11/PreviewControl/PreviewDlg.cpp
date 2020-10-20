//-----------------------------------------------------------------------------
//----- PreviewDlg.cpp : implementation file
#include "StdAfx.h"
#include "PreviewDlg.h"
#include <dbsymtb.h>
#include <dbents.h>
#include "..\..\Common\Document\DwgDatabaseUtil.h"

//-----------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CAcExtensionModule PreviewControlDLL;

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CPreviewDlg, CAcUiDialog)

BEGIN_MESSAGE_MAP(CPreviewDlg, CAcUiDialog)
	//{{AFX_MSG_MAP(CPreviewDlg)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)    // Needed for modeless dialog.
	ON_EN_KILLFOCUS(IDC_RADIUS, OnKillfocusRadius)
	ON_CBN_SELCHANGE(IDC_COLOR, OnSelchangeColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CPreviewDlg::CPreviewDlg (CWnd* pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiDialog (CPreviewDlg::IDD, pParent, hInstance) {
	//{{AFX_DATA_INIT(CPreviewDlg)
	m_radius = 50.0;
	//}}AFX_DATA_INIT
}

void CPreviewDlg::DoDataExchange (CDataExchange *pDX) {
	CAcUiDialog::DoDataExchange (pDX) ;
	//{{AFX_DATA_MAP(CPreviewDlg)
	DDX_Text(pDX, IDC_RADIUS, m_radius);
	DDV_MinMaxDouble(pDX, m_radius, 1.e-004, 100000.);
	DDX_Control(pDX, IDC_COLOR, m_cboColor);
	//}}AFX_DATA_MAP
}

// Needed for modeless dialogs to keep focus.
// Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT CPreviewDlg::OnAcadKeepFocus(WPARAM, LPARAM)
{
  return TRUE;
}

//-----------------------------------------------------------------------------

BOOL CPreviewDlg::OnInitDialog() 
{
	CAcUiDialog::OnInitDialog();
	
	// 预览DWG文件的控件初始化
	m_gsPreviewCtrl.SubclassDlgItem(IDC_PREVIEW, this);		// 控件和资源的关联
	m_gsPreviewCtrl.Init(PreviewControlDLL.ModuleResourceInstance(), true);
	ShowPreview();

	m_cboColor.SetCurSel(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPreviewDlg::OnKillfocusRadius() 
{
	if (UpdateData())
	{
		ShowPreview();
	}
}

void CPreviewDlg::OnSelchangeColor() 
{
	if (UpdateData())
	{
		ShowPreview();
	}
}

static AcDbPolyline* NewPolyline( const AcGePoint2dArray &verts, bool bClosed /*= false*/ )
{
	AcDbPolyline* pPoly = new AcDbPolyline();
	for (int i = 0; i < verts.length(); i++)
	{
		pPoly->addVertexAt(i, verts[i], 0);
	}
	
	if (bClosed)
	{
		pPoly->setClosed(Adesk::kTrue);
	}
	
	return pPoly;
}

void CPreviewDlg::ShowPreview()
{
	AcDbDatabase *pDatabase = new AcDbDatabase();

	// 参照矩形
	AcGePoint2dArray verts;
	verts.append(AcGePoint2d(50, 50));
	verts.append(AcGePoint2d(-50, 50));
	verts.append(AcGePoint2d(-50, -50));
	verts.append(AcGePoint2d(50, -50));
	AcDbPolyline *pPoly = NewPolyline(verts, true);
	pPoly->setColorIndex(1);
	CDwgDatabaseUtil::PostToModelSpace(pPoly, pDatabase);

	AcDbCircle *pCircle = new AcDbCircle(AcGePoint3d::kOrigin, AcGeVector3d::kZAxis, m_radius);
	int colorIndex = m_cboColor.GetCurrentItemColorIndex();
	if (colorIndex >= 0 && colorIndex <= 256)
	{
		pCircle->setColorIndex(colorIndex);
	}
	CDwgDatabaseUtil::PostToModelSpace(pCircle, pDatabase);

	m_gsPreviewCtrl.SetDatabase(pDatabase);
}
