# Microsoft Developer Studio Project File - Name="CreateText" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=CreateText - Win32 FullDebug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CreateText.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CreateText.mak" CFG="CreateText - Win32 FullDebug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CreateText - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CreateText - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CreateText - Win32 FullDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CreateText - Win32 Release"

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
# ADD LINK32 rxapi.lib acrx15.lib acdb15.lib acutil15.lib acge15.lib acgiapi.lib achapi15.lib acISMobj15.lib acad.lib acedapi.lib acsiobj.lib  adui15.lib acui15.lib /nologo /subsystem:windows /dll /machine:I386 /out:"Release/ZffCreateText.arx"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "CreateText - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ  /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /GZ  /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 rxapi.lib acrx15.lib acdb15.lib acutil15.lib acge15.lib acgiapi.lib achapi15.lib acISMobj15.lib acad.lib acedapi.lib acsiobj.lib  adui15.lib acui15.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/ZffCreateText.arx" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "CreateText - Win32 FullDebug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CreateText___Win32_FullDebug"
# PROP BASE Intermediate_Dir "CreateText___Win32_FullDebug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CreateText___Win32_FullDebug"
# PROP Intermediate_Dir "CreateText___Win32_FullDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /D "_FULLDEBUG_" /Fp"FullDebug/CreateText.pch" /YX /Fo"FullDebug/" /Fd"FullDebug/" /FD /GZ    /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /pdb:"FullDebug/ZffCreateText.pdb" /debug /machine:I386 /out:"FullDebug/ZffCreateText.arx" /implib:"FullDebug/ZffCreateText.lib" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 rxapi.lib acrx15.lib acdb15.lib acutil15.lib acge15d.lib acgiapi.lib achapi15.lib acISMobj15.lib acad.lib acedapi.lib acsiobj.lib  adui15.lib acui15.lib /nologo /subsystem:windows /dll /pdb:"FullDebug/ZffCreateText.pdb" /debug /machine:I386 /out:"FullDebug/ZffCreateText.arx" /implib:"FullDebug/ZffCreateText.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "CreateText - Win32 Release"
# Name "CreateText - Win32 Debug"
# Name "CreateText - Win32 FullDebug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CreateText.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateText.def
# End Source File
# Begin Source File

SOURCE=.\CreateText.rc
# End Source File
# Begin Source File

SOURCE=.\CreateTextCommands.cpp
# End Source File
# Begin Source File

SOURCE=.\DocData.cpp
# End Source File
# Begin Source File

SOURCE=.\rxdebug.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "CreateText - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "CreateText - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "CreateText - Win32 FullDebug"

!ENDIF 

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

SOURCE=.\res\CreateText.rc2
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

SOURCE=..\..\Common\Entity\circleutil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Entity\circleutil.h
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

SOURCE=..\..\Common\Geometry\MathUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Common\Geometry\MathUtil.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\ObjectARX.prj
# End Source File
# End Target
# End Project
