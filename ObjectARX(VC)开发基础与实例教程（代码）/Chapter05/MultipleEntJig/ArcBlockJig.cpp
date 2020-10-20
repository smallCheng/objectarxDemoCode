// ArcBlockJig.cpp: implementation of the CArcBlockJig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ArcBlockJig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArcBlockJig::CArcBlockJig()
{
	m_pJigEnt = NULL;
}

CArcBlockJig::~CArcBlockJig()
{
	if (m_pJigEnt)
	{
		delete m_pJigEnt;
		m_pJigEnt = NULL;
	}
}

bool CArcBlockJig::doIt( const AcGePoint3d &startPoint, AcGePoint3d &thirdPoint, AcGePoint3d &endPoint, 
						AcDbObjectId blkDefId, int blockCount )
{
	// 拖动之前：创建自定义实体
	if (m_pJigEnt != NULL)
	{
		delete m_pJigEnt;
		m_pJigEnt = NULL;	
	}
	m_pJigEnt = new CArcBlockJigEntity(startPoint, thirdPoint, endPoint, blkDefId, blockCount);
	
	// 执行拖动绘制
	CString prompt = TEXT("\n指定下一点: ");
	setDispPrompt(prompt);
	AcEdJig::DragStatus stat = drag();
	
	// 拖动之后：根据需要确定自己的处理方式
	bool bRet = false;
	if (stat == kNormal)
	{
		// 添加子实体到模型空间
		m_pJigEnt->PostToModelSpace();	
		bRet = true;
	}
	
	m_blkRefIds = m_pJigEnt->GetBlkRefIds();
	delete m_pJigEnt;
	m_pJigEnt = NULL;
	
	return bRet;
}

AcEdJig::DragStatus CArcBlockJig::sampler()
{
	setUserInputControls((UserInputControls)
        (AcEdJig::kAccept3dCoordinates
		| AcEdJig::kNoNegativeResponseAccepted
		| AcEdJig::kNullResponseAccepted));	
	
	// 一定要判断一下点是否发生了变化，否则update函数不停地被调用，实体反而不能被绘制出来
	static AcGePoint3d pointTemp;
	DragStatus stat = acquirePoint(m_curPoint);
	if (pointTemp != m_curPoint)
	{
		pointTemp = m_curPoint;
	}
	else if (stat == AcEdJig::kNormal)
	{
		return AcEdJig::kNoChange;
	}
	
	return stat;
}

Adesk::Boolean CArcBlockJig::update()
{
	m_pJigEnt->SetEndPoint(m_curPoint);
	return Adesk::kTrue;
}

AcDbEntity* CArcBlockJig::entity() const
{
	return m_pJigEnt;
}

AcDbObjectIdArray CArcBlockJig::GetBlkRefIds()
{
	return m_blkRefIds;
}
