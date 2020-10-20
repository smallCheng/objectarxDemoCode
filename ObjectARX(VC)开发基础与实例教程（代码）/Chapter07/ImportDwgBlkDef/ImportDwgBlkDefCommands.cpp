//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Entity\BlockUtil.h"
#include <IO.H>

// This is command 'INSERTBLKREFFROMOTHERDWG'
void ZffChap7InsertBlkRefFromOtherDwg()
{
	CString fileName = TEXT("C:\\包含图块.dwg");
	if (_taccess(fileName, 0) != -1)
	{
		AcDbObjectId blkDefId = CBlockUtil::CopyBlockDefFromOtherDwg(fileName, TEXT("测试图块"));
		if (blkDefId.isValid())
		{
			CBlockUtil::InsertBlockRef(blkDefId, AcGePoint3d(100, 100, 0), 1, 0);
		}
	}
	else
	{
		acutPrintf(TEXT("\n指定的图形文件不存在."));
	}
}

// This is command 'INSERTDWGBLOCKREF'
void ZffChap7InsertDwgBlockRef()
{
	CString fileName = TEXT("C:\\作为图块的文件.dwg");
	if (_taccess(fileName, 0) != -1)
	{
		AcDbObjectId blkDefId = CBlockUtil::InsertDwgBlockDef(fileName, TEXT("外部DWG图块"), true);
		if (blkDefId.isValid())
		{
			CBlockUtil::InsertBlockRef(blkDefId, AcGePoint3d(200, 100, 0), 1, 0);
		}
	}
	else
	{
		acutPrintf(TEXT("\n指定的图形文件不存在."));
	}
}

