//-----------------------------------------------------------------------------
#if !defined(ARX__ARXDIALOG_H__20050910_214331)
#define ARX__ARXDIALOG_H__20050910_214331

//-----------------------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//-----------------------------------------------------------------------------
class CArxDialog : public CAcUiDialog {
	DECLARE_DYNAMIC (CArxDialog)

public:
	void DisplayAngle();
	void DisplayPoint();
	CString m_strAngle;
	CString m_strZPt;
	CString m_strYPt;
	CString m_strXPt;
	CArxDialog (CWnd* pParent =NULL, HINSTANCE hInstance =NULL) ;

	//{{AFX_DATA(CArxDialog)
	enum { IDD = IDD_ARX_MODAL };
	CAcUiPickButton	m_btnAngle;
	CAcUiPickButton	m_btnPick;
	CAcUiAngleEdit	m_editAngle;
	CAcUiNumericEdit	m_editXPt;
	CAcUiNumericEdit	m_editYPt;
	CAcUiNumericEdit	m_editZPt;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CArxDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CArxDialog)
	afx_msg LONG OnAcadKeepFocus(UINT, UINT);
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAngle();
	afx_msg void OnButtonPoint();
	afx_msg void OnClose();
	afx_msg void OnKillfocusEditAngle();
	afx_msg void OnKillfocusEditXpt();
	afx_msg void OnKillfocusEditYpt();
	afx_msg void OnKillfocusEditZpt();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
} ;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //----- !defined(ARX__ARXDIALOG_H__20050910_214331)
