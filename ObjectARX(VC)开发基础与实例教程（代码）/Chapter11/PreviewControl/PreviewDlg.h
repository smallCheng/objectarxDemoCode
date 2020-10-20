//-----------------------------------------------------------------------------
#if !defined(ARX__PREVIEWDLG_H__20130504_110802)
#define ARX__PREVIEWDLG_H__20130504_110802

//-----------------------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "GsPreviewCtrl.h"

//-----------------------------------------------------------------------------
class CPreviewDlg : public CAcUiDialog 
{
	DECLARE_DYNAMIC (CPreviewDlg)

public:
	CPreviewDlg (CWnd* pParent =NULL, HINSTANCE hInstance =NULL) ;

	//{{AFX_DATA(CPreviewDlg)
	enum { IDD = IDD_PREVIEW };
	double	m_radius;
	CAcUiColorComboBox	m_cboColor;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPreviewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CPreviewDlg)
	afx_msg LRESULT OnAcadKeepFocus(WPARAM, LPARAM);
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusRadius();
	afx_msg void OnSelchangeColor();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void ShowPreview();

private:
	CGsPreviewCtrl m_gsPreviewCtrl;		// Ô¤ÀÀDWG¿Ø¼þ
} ;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //----- !defined(ARX__PREVIEWDLG_H__20130504_110802)
