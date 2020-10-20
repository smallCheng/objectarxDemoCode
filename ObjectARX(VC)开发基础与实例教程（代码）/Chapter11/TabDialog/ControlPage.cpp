//-----------------------------------------------------------------------------
//----- ControlPage.cpp : implementation file
#include "StdAfx.h"
#include "ControlPage.h"
#include "..\..\Common\IO\IniFile.h"
#include "..\..\Common\IO\AppDirectoryUtil.h"

//-----------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CControlPage, CAcUiTabChildDialog)

BEGIN_MESSAGE_MAP(CControlPage, CAcUiTabChildDialog)
	//{{AFX_MSG_MAP(CControlPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CControlPage::CControlPage (CWnd* pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiTabChildDialog (pParent, hInstance) {
	//{{AFX_DATA_INIT(CControlPage)
	m_bCheck1 = FALSE;
	m_nRadio1 = 0;
	//}}AFX_DATA_INIT
}

void CControlPage::DoDataExchange (CDataExchange *pDX) {
	CAcUiTabChildDialog::DoDataExchange (pDX) ;
	//{{AFX_DATA_MAP(CControlPage)
	DDX_Check(pDX, IDC_CHECK1, m_bCheck1);
	DDX_Radio(pDX, IDC_RADIO1, m_nRadio1);
	//}}AFX_DATA_MAP
}

//-----------------------------------------------------------------------------
void CControlPage::OnTabActivation (BOOL bActivate) {
	//----- TODO: Add your code here
}

BOOL CControlPage::OnTabChanging () {
	//----- TODO: Add your code here

	return (TRUE) ;
}

//-----------------------------------------------------------------------------

BOOL CControlPage::OnInitDialog() 
{
	CAcUiTabChildDialog::OnInitDialog();
	
	// 从INI文件中加载参数值
	CIniFile iniFile(CAppDirectoryUtil::GetCurrentDirectory() + TEXT("\\OptionSheet.ini"));
	CString field = TEXT("OptionSheet");
	iniFile.GetValueOfKey(field, TEXT("nRadio1"), m_nRadio1);
	iniFile.GetValueOfKey(field, TEXT("bCheck1"), m_bCheck1);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CControlPage::SaveProfiles()
{
	if (!UpdateData())
	{
		return false;
	}

	// 保存参数值
	CIniFile iniFile(CAppDirectoryUtil::GetCurrentDirectory() + TEXT("\\OptionSheet.ini"));
	CString field = TEXT("OptionSheet");
	iniFile.SetValueOfKey(field, TEXT("nRadio1"), m_nRadio1);
	iniFile.SetValueOfKey(field, TEXT("bCheck1"), m_bCheck1);

	return true;
}
