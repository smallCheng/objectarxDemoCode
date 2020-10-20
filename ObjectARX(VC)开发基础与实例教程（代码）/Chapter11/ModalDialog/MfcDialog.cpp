// MfcDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "resource.h"
#include "MfcDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcDialog dialog


CMfcDialog::CMfcDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMfcDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMfcDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMfcDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMfcDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMfcDialog, CDialog)
	//{{AFX_MSG_MAP(CMfcDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcDialog message handlers
