//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Interaction\SelectUtil.h"
#include <dbents.h>
#include "MyObjectReactor.h"

// This is command 'SETLINKENTS'
void ZffChap13SetLinkEnts()
{
	// 提示用户选择两个圆
	AcDbObjectIdArray circleIds;
	if (CSelectUtil::PromptSelectEnts(TEXT("\n选择两个圆:"), AcDbCircle::desc(), circleIds))
	{
		if (circleIds.length() != 2)
		{
			acutPrintf(TEXT("\n必须选择两个圆."));
			return;
		}

		// 第一个圆的反应器
		AcDbDictionary *pNamedDict = NULL;
		CMyObjectReactor *pObjReactorA = new CMyObjectReactor();
		pObjReactorA->SetLinkEntId(circleIds[1]);
		AcDbObjectId objReactorAId;
		Acad::ErrorStatus es = acdbHostApplicationServices()->workingDatabase()->
			getNamedObjectsDictionary(pNamedDict, AcDb::kForWrite);
		pNamedDict->setAt(TEXT("CircleA"), pObjReactorA, objReactorAId);
		AcDbCircle *pCircleA = NULL;
		if (acdbOpenObject(pCircleA, circleIds[0], AcDb::kForWrite) == Acad::eOk)
		{
			pCircleA->addPersistentReactor(objReactorAId);
			pCircleA->close();
		}

		// 第二个圆的反应器
		CMyObjectReactor *pObjReactorB = new CMyObjectReactor();
		pObjReactorB->SetLinkEntId(circleIds[0]);
		AcDbObjectId objReactorBId;
		pNamedDict->setAt(TEXT("CircleB"), pObjReactorB, objReactorBId);
		AcDbCircle *pCircleB = NULL;
		if (acdbOpenObject(pCircleB, circleIds[1], AcDb::kForWrite) == Acad::eOk)
		{
			pCircleB->addPersistentReactor(objReactorBId);
			pCircleB->close();
		}
		pNamedDict->close();
	}
}

