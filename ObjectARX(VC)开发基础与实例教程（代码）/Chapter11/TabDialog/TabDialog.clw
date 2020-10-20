; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ResourceCount=3
ExtraDDXCount=33
ExtraDDX1=nMN;;Autodesk Control;CAdUiComboBox;;Control
ExtraDDX2=nMN;;AutoCAD Control;CAcUiComboBox;;Control
ExtraDDX3=nMN;;AutoCAD Control;CAcUiAngleComboBox;;Control
ExtraDDX4=nMN;;AutoCAD Control;CAcUiMRUComboBox;;Control
ExtraDDX5=nMN;;AutoCAD Control;CAcUiArrowHeadComboBox;;Control
ExtraDDX6=nMN;;AutoCAD Control;CAcUiColorComboBox;;Control
ExtraDDX7=nMN;;AutoCAD Control;CAcUiLineWeightComboBox;;Control
ExtraDDX8=nMN;;AutoCAD Control;CAcUiPlotStyleNamesComboBox;;Control
ExtraDDX9=nMN;;AutoCAD Control;CAcUiPlotStyleTableComboBox;;Control
ExtraDDX10=B;;Autodesk Control;CAdUiDropSite;;Control
ExtraDDX11=nMN;;AutoCAD Control;CAcUiStringComboBox;;Control
ExtraDDX12=nMN;;AutoCAD Control;CAcUiSymbolComboBox;;Control
ExtraDDX13=lL;;Autodesk Control;CAdUiListBox;;Control
ExtraDDX14=lL;;AutoCAD Control;CAcUiListBox;;Control
ExtraDDX15=lL;;AutoCAD Control;CAcUiMRUListBox;;Control
ExtraDDX16=B;;Autodesk Control;CAdUiOwnerDrawButton;;Control
ExtraDDX17=B;;Autodesk Control;CAdUiBitmapButton;;Control
ExtraDDX18=B;;Autodesk Control;CAdUiBitmapStatic;;Control
ExtraDDX10=B;;Autodesk Control;CAdUiDropSite;;Control
ExtraDDX20=B;;AutoCAD Control;CAcUiDropSite;;Control
ExtraDDX21=B;;AutoCAD Control;CAcUiBitmapStatic;;Control
ExtraDDX22=B;;Autodesk Control;CAdUiToolButton;;Control
ExtraDDX23=B;;AutoCAD Control;CAcUiToolButton;;Control
ExtraDDX24=B;;AutoCAD Control;CAcUiBitmapButton;;Control
ExtraDDX25=B;;AutoCAD Control;CAcUiPickButton;;Control
ExtraDDX26=B;;AutoCAD Control;CAcUiSelectButton;;Control
ExtraDDX27=B;;AutoCAD Control;CAcUiOwnerDrawButton;;Control
ExtraDDX28=E;;Autodesk Control;CAdUiEdit;;Control
ExtraDDX29=E;;AutoCAD Control;CAcUiEdit;;Control
ExtraDDX30=E;;AutoCAD Control;CAcUiAngleEdit;;Control
ExtraDDX31=E;;AutoCAD Control;CAcUiNumericEdit;;Control
ExtraDDX32=E;;AutoCAD Control;CAcUiStringEdit;;Control
ExtraDDX33=E;;AutoCAD Control;CAcUiSymbolEdit;;Control
;ExtraDDX34=X;;Autodesk Control;CAdUiListCtrl;;Control
;ExtraDDX35=X;;AutoCAD Control;CAcUiListCtrl;;Control
;ExtraDDX36=T;;Autodesk Control;CAdUiTab;;Control
;ExtraDDX37=T;;AutoCAD Control;CAcUiTab;;Control
;ExtraDDX38=H;;Autodesk Control;CAdUiHeaderCtrl;;Control
;ExtraDDX39=H;;AutoCAD Control;CAcUiHeaderCtrl;;Control
ClassCount=3
Class1=COptionSheet
Class2=CTextPage
Class3=CControlPage
LastClass=CControlPage
LastTemplate=CAcUiTabChildDialog
NewFileInclude1=#include "StdAfx.h"
NewFileInclude2=#include "resource.h"
ODLFile=TabDialog.idl
LastPage=0
Resource1=IDD_TEXT_PAGE
Resource2=IDD_OPTION_SHEET
Resource3=IDD_CONTROL_PAGE

[DLG:IDD_OPTION_SHEET]
Type=1
Class=COptionSheet
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TAB,SysTabControl32,1342177280

[CLS:COptionSheet]
Type=0
HeaderFile=OptionSheet.h
ImplementationFile=OptionSheet.cpp
BaseClass=CAcUiTabMainDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_TEXT_PAGE]
Type=1
Class=CTextPage
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_TEXT_HEIGHT,edit,1350631552
Control4=IDC_TEXT_SYTLE,combobox,1344340227

[CLS:CTextPage]
Type=0
HeaderFile=TextPage.h
ImplementationFile=TextPage.cpp
BaseClass=CAcUiTabChildDialog
Filter=D
LastObject=CTextPage
VirtualFilter=dWC

[DLG:IDD_CONTROL_PAGE]
Type=1
Class=CControlPage
ControlCount=4
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RADIO1,button,1342308361
Control3=IDC_RADIO2,button,1342177289
Control4=IDC_CHECK1,button,1342242819

[CLS:CControlPage]
Type=0
HeaderFile=ControlPage.h
ImplementationFile=ControlPage.cpp
BaseClass=CAcUiTabChildDialog
Filter=D
LastObject=CControlPage
VirtualFilter=dWC

