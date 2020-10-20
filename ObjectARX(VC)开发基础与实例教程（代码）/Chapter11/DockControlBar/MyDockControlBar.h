//-----------------------------------------------------------------------------
#if !defined(ARX__MYDOCKCONTROLBAR_H__20081001_112508)
#define ARX__MYDOCKCONTROLBAR_H__20081001_112508

//-----------------------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "resource.h"

#include "ChildDlg.h"

//-----------------------------------------------------------------------------
class CMyDockControlBar : public CAcUiDockControlBar {
	DECLARE_DYNAMIC(CMyDockControlBar)

public:
	CMyDockControlBar () ;

	//{{AFX_VIRTUAL(CMyDockControlBar)
	public:
	virtual BOOL Create(CWnd*pParent, LPCSTR lpszTitle);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CMyDockControlBar)
	afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual void SizeChanged (CRect *lpRect, BOOL bFloating, int flags);

private:
	CChildDlg* m_childDlg;
} ;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //----- !defined(ARX__MYDOCKCONTROLBAR_H__20081001_112508)
