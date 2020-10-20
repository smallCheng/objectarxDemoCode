//-----------------------------------------------------------------------------
//----- TextPage.cpp : implementation file
#include "StdAfx.h"
#include "TextPage.h"
#include <vector>
#include "..\..\Common\SymbolTable\TextStyleUtil.h"
#include "..\..\Common\IO\IniFile.h"
#include "..\..\Common\IO\AppDirectoryUtil.h"

//-----------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CTextPage, CAcUiTabChildDialog)

BEGIN_MESSAGE_MAP(CTextPage, CAcUiTabChildDialog)
	//{{AFX_MSG_MAP(CTextPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CTextPage::CTextPage (CWnd* pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiTabChildDialog (pParent, hInstance) {
	//{{AFX_DATA_INIT(CTextPage)
	m_textHeight = 3.5;
	//}}AFX_DATA_INIT
}

void CTextPage::DoDataExchange (CDataExchange *pDX) {
	CAcUiTabChildDialog::DoDataExchange (pDX) ;
	//{{AFX_DATA_MAP(CTextPage)
	DDX_Control(pDX, IDC_TEXT_SYTLE, m_cboTextStyle);
	DDX_Text(pDX, IDC_TEXT_HEIGHT, m_textHeight);
	DDV_MinMaxDouble(pDX, m_textHeight, 1.e-003, 100000.);
	//}}AFX_DATA_MAP
}

//-----------------------------------------------------------------------------
void CTextPage::OnTabActivation (BOOL bActivate) {
	//----- TODO: Add your code here
}

BOOL CTextPage::OnTabChanging () {
	//----- TODO: Add your code here

	return (TRUE) ;
}

//-----------------------------------------------------------------------------

BOOL CTextPage::OnInitDialog() 
{
	CAcUiTabChildDialog::OnInitDialog();

	// 填充文字样式组合框
	std::vector<CString> textStyles;
	CTextStyleUtil::GetAll(textStyles);
	for (int i = 0; i < textStyles.size(); i++)
	{
		m_cboTextStyle.AddString(textStyles[i]);
	}
	if (m_cboTextStyle.GetCount() > 0)
	{
		m_cboTextStyle.SetCurSel(0);
	}
	
	// 从INI文件中加载参数值
	CIniFile iniFile(CAppDirectoryUtil::GetCurrentDirectory() + TEXT("\\OptionSheet.ini"));
	CString field = TEXT("OptionSheet");
	iniFile.GetValueOfKey(field, TEXT("textHeight"), m_textHeight);
	CString strTextStyle;
	iniFile.GetValueOfKey(field, TEXT("textStyle"), strTextStyle);
	
	// 设置组合框的当前选择项
	for (i = 0; i < m_cboTextStyle.GetCount(); i++)
	{
		CString strItem;
		m_cboTextStyle.GetLBText(i, strItem);
		if (strItem.CompareNoCase(strTextStyle) == 0)
		{
			m_cboTextStyle.SetCurSel(i);
			break;
		}
	}

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CTextPage::SaveProfiles()
{
	if (!UpdateData())
	{
		return false;
	}

	// 保存参数值
	CIniFile iniFile(CAppDirectoryUtil::GetCurrentDirectory() + TEXT("\\OptionSheet.ini"));
	CString field = TEXT("OptionSheet");
	iniFile.SetValueOfKey(field, TEXT("textHeight"), m_textHeight);
	CString strTextStyle;
	m_cboTextStyle.GetLBText(m_cboTextStyle.GetCurSel(), strTextStyle);
	iniFile.SetValueOfKey(field, TEXT("textStyle"), strTextStyle);

	return true;
}
