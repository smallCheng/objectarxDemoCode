# Microsoft Developer Studio Project File - Name="BinaryFile" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=BinaryFile - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BinaryFile.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BinaryFile.mak" CFG="BinaryFile - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BinaryFile - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BinaryFile - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BinaryFile - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 rxapi.lib acrx15.lib acdb15.lib acutil15.lib acge15.lib acgiapi.lib achapi15.lib acISMobj15.lib acad.lib acedapi.lib acsiobj.lib adui15.lib acui15.lib /nologo /subsystem:windows /dll /machine:I386 /out:"Release/ZffBinaryFile.arx"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "BinaryFile - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 rxapi.lib acrx15.lib acdb15.lib acutil15.lib acge15.lib acgiapi.lib achapi15.lib acISMobj15.lib acad.lib acedapi.lib acsiobj.lib adui15.lib acui15.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/ZffBinaryFile.arx" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "BinaryFile - Win32 Release"
# Name "BinaryFile - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BinaryFile.cpp
# End Source File
# Begin Source File

SOURCE=.\BinaryFile.def
# End Source File
# Begin Source File

SOURCE=.\BinaryFile.rc
# End Source File
# Begin Source File

SOURCE=.\BinaryFileCommands.cpp
# End Source File
# Begin Source File

SOURCE=.\DocData.cpp
# End Source File
# Begin Source File

SOURCE=.\rxdebug.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AdskDMgr.h
# End Source File
# Begin Source File

SOURCE=.\DocData.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\rxdebug.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StdArx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\BinaryFile.rc2
# End Source File
# End Group
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Group "Document"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Common\Document\DwgDatabaseUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Document\DwgDatabaseUtil.h
# End Source File
# End Group
# Begin Group "Entity"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Common\Entity\ArcUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\ArcUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\BlockUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\BlockUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\circleutil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\circleutil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\DimensionUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\DimensionUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\EllipseUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\EllipseUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\EntityUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\EntityUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\HatchUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\HatchUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\LineUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\LineUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\PolylineUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\PolylineUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\RegionUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\RegionUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\SplineUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\SplineUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\TextUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\TextUtil.h
# End Source File
# End Group
# Begin Group "Others"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Common\Others\ConvertUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Others\ConvertUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Others\StringUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Others\StringUtil.h
# End Source File
# End Group
# Begin Group "Geometry"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Common\Geometry\GePointUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Geometry\GePointUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Geometry\GeRectangleUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Geometry\GeRectangleUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Geometry\MathUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Geometry\MathUtil.h
# End Source File
# End Group
# Begin Group "SymbolTable"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Common\SymbolTable\LayerUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\SymbolTable\LayerUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\SymbolTable\TextStyleUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\SymbolTable\TextStyleUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\SymbolTable\ViewUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\SymbolTable\ViewUtil.h
# End Source File
# End Group
# Begin Group "IO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Common\IO\AppDirectoryUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\IO\AppDirectoryUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\IO\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\IO\IniFile.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\IO\TextFileUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\IO\TextFileUtil.h
# End Source File
# End Group
# Begin Group "Interaction"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Common\Interaction\GetInputUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Interaction\GetInputUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\Interaction\SelectUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Interaction\SelectUtil.h
# End Source File
# End Group
# Begin Group "MfcGridCtrl"

# PROP Default_Filter ""
# Begin Group "CellTypes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellTypes\GridCellButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellTypes\GridCellButton.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellTypes\GridCellCheck.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellTypes\GridCellCheck.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellTypes\GridCellCombo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellTypes\GridCellCombo.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellTypes\GridCellDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellTypes\GridCellDateTime.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellTypes\GridCellGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellTypes\GridCellGroup.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellTypes\GridCellNumeric.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellTypes\GridCellNumeric.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellTypes\GridCellTerminal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellTypes\GridCellTerminal.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellTypes\GridURLCell.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellTypes\GridURLCell.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\CellRange.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\GridCell.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\GridCell.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\GridCellBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\GridCellBase.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\GridCtrlUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\GridCtrlUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\GridDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\GridDropTarget.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\InPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\InPlaceEdit.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\MemDC.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\TitleTip.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\MfcGridCtrl\TitleTip.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\ObjectARX.prj
# End Source File
# End Target
# End Project
