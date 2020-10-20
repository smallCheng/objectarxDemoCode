//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include <dbpl.h>
#include <gecomp2d.h>

// 根据多段线构建二维几何曲线
static bool PolyToGeCurve(AcDbPolyline *pPline, AcGeCurve2d *&pGeCurve)
{	
	int nSegs;							// 多段线的段数
	AcGeLineSeg2d line, *pLine;			// 几何曲线的直线段部分
	AcGeCircArc2d arc, *pArc;			// 几何曲线的圆弧部分
	AcGeVoidPointerArray geCurves;		// 指向组成几何曲线各分段的指针数组										
	
	nSegs = pPline->numVerts() - 1;
	
	// 根据多段线创建对应的分段几何曲线
	for (int i = 0; i < nSegs; i++)
	{
		if (pPline->segType(i) == AcDbPolyline::kLine)
		{
			pPline->getLineSegAt(i, line);
			pLine = new AcGeLineSeg2d(line);
			geCurves.append(pLine);
		}
		else if (pPline->segType(i) == AcDbPolyline::kArc)
		{
			pPline->getArcSegAt(i, arc);
			pArc = new AcGeCircArc2d(arc);
			geCurves.append(pArc);
		}		
	}
	
	// 处理闭合多段线最后一段是圆弧的情况
	if (pPline->isClosed() && pPline->segType(nSegs) == AcDbPolyline::kArc)
	{
		pPline->getArcSegAt(nSegs, arc);
		pArc = new AcGeCircArc2d(arc);
		pArc->setAngles(arc.startAng(), arc.endAng() - 
			(arc.endAng() - arc.startAng()) / 100);
		geCurves.append(pArc);
	}
	
	// 根据分段的几何曲线创建对应的复合曲线
	if (geCurves.length() == 1)
	{
		pGeCurve = (AcGeCurve2d *)geCurves[0];
	}
	else
	{
		pGeCurve = new AcGeCompositeCurve2d(geCurves);
	}	
	
	// 释放动态分配的内存
	if (geCurves.length() > 1)		
	{
		for (i = 0; i < geCurves.length(); i++)
		{
			delete geCurves[i];
		}
	}
	
	return true;
}

// 根据指定的一组点创建一个结果缓冲区链表
struct resbuf* BuildRbFromPtArray(const AcGePoint2dArray &arrPoints)
{
	struct resbuf *retRb = NULL;
	int count = arrPoints.length();
	if (count <= 1)
	{
		acedAlert(TEXT("函数BuildBbFromPtArray中, 点数组包含元素个数不足!"));
		return retRb;
	}
	
	// 使用第一个点来构建结果缓冲区链表的头节点
	ads_point adsPt;
	adsPt[X] = arrPoints[0].x;
	adsPt[Y] = arrPoints[0].y;
	retRb = acutBuildList(RTPOINT, adsPt, RTNONE);
	
	struct resbuf *nextRb = retRb;		// 辅助指针
	
	for (int i = 1; i < count; i++)			// 注意：不考虑第一个元素，因此i从1开始
	{
		adsPt[X] = arrPoints[i].x;
		adsPt[Y] = arrPoints[i].y;
		// 动态创建新的节点，并将其链接到原来的链表尾部
		nextRb->rbnext = acutBuildList(RTPOINT, adsPt, RTNONE);		
		nextRb = nextRb->rbnext;		
	}	
	
	return retRb;
}

// 选择位于多段线内部的所有实体
static bool SelectEntInPoly(AcDbPolyline *pPline, 
								   AcDbObjectIdArray &ObjectIdArray, const char *selectMode, double approxEps)
{
	// 判断selectMode的有效性
	if (_tcscmp(selectMode, TEXT("CP")) != 0 && _tcscmp(selectMode, TEXT("WP")) != 0)
	{
		acedAlert(TEXT("函数SelectEntInPline中, 指定了无效的选择模式!"));
		return false;
	}	
	
	// 清除数组中所有的ObjectId
	for (int i = 0; i < ObjectIdArray.length(); i++)
	{
		ObjectIdArray.removeAt(i);
	}
	
	AcGeCurve2d *pGeCurve;						// 多段线对应的几何曲线
	Adesk::Boolean bClosed = pPline->isClosed();	// 多段线是否闭合
	if (bClosed != Adesk::kTrue)				// 确保多段线作为选择边界时是闭合的
	{
		pPline->setClosed(!bClosed);
	}	
	
	// 创建对应的几何类曲线
	PolyToGeCurve(pPline, pGeCurve);
	
	// 获得几何曲线的样本点
	AcGePoint2dArray SamplePtArray;				// 存储曲线的样本点
	AcGeDoubleArray ParamArray;					// 存储样本点对应的参数值
	AcGePoint2d ptStart, ptEnd;			// 几何曲线的起点和终点
	Adesk::Boolean bRet = pGeCurve->hasStartPoint(ptStart);
	bRet = pGeCurve->hasEndPoint(ptEnd);
	double valueSt = pGeCurve->paramOf(ptStart);
	double valueEn = pGeCurve->paramOf(ptEnd);
	pGeCurve->getSamplePoints(valueSt, valueEn, approxEps, 
		SamplePtArray, ParamArray);
	
	delete pGeCurve;		// 在函数PolyToGeCurve中分配了内存	
	
	// 确保样本点的起点和终点不重合
	AcGeTol tol;
	tol.setEqualPoint(0.01);
	AcGePoint2d ptFirst = SamplePtArray[0];
	AcGePoint2d ptLast = SamplePtArray[SamplePtArray.length() - 1];	
	if (ptFirst.isEqualTo(ptLast))
	{
		SamplePtArray.removeLast();
	}	
	
	// 根据样本点创建结果缓冲区链表
	struct resbuf *rb;
	rb = BuildRbFromPtArray(SamplePtArray);	
	
	// 使用acedSSGet函数创建选择集
	ads_name ssName;			// 选择集名称
	int rt = acedSSGet(selectMode, rb, NULL, NULL, ssName);	
	if (rt != RTNORM)
	{		
		acutRelRb(rb);			// 释放结果缓冲区链表
		return false;
	}
	
	// 将选择集中所有的对象添加到ObjectIdArray
	long length;	
	acedSSLength(ssName, &length);
	for (i = 0; i < length; i++)
	{
		// 获得指定元素的ObjectId
		ads_name ent;
		acedSSName(ssName, i, ent);
		AcDbObjectId objId;
		acdbGetObjectId(objId, ent);
		
		// 获得指向当前元素的指针
		AcDbEntity *pEnt;
		Acad::ErrorStatus es = acdbOpenAcDbEntity(pEnt, objId, AcDb::kForRead);
		
		// 选择到作为边界的多段线了，直接跳过该次循环
		if (es == Acad::eWasOpenForWrite)		
		{
			continue;
		}
		
		ObjectIdArray.append(pEnt->objectId());
		
		pEnt->close();
	}	
	
	// 释放内存
	acutRelRb(rb);								// 释放结果缓冲区链表
	acedSSFree(ssName);							// 删除选择集
	
	return true;
}

// This is command 'CREATESSET'
void ZffChap5CreateSSet()
{
	ads_name sset;	// 选择集名称
	// 选择图形数据库中所有的实体
	acedSSGet(TEXT("A"), NULL, NULL, NULL, sset);
	long length;
	acedSSLength(sset, &length);
	acutPrintf(TEXT("\n实体数:%d"), length);
	
	// 进行其他操作
	
	acedSSFree(sset);
}

// This is command 'TEST'
void ZffChap5Test()
{
	struct resbuf *rb;	// 结果缓冲区链表	
	ads_name ssname;	
	
	rb = acutBuildList(RTDXF0, TEXT("LINE"),		// 实体类型
		8, TEXT("0"),							// 图层
		RTNONE);
	
	// 选择图形中位于0层上的所有直线
	acedSSGet(TEXT("X"), NULL, NULL, rb, ssname); 
	
	acutRelRb(rb);	
	acedSSFree(ssname);
}

// This is command 'SELECTENT'
void ZffChap5SelectEnt()
{
	ads_point pt1, pt2, pt3, pt4; 
	struct resbuf *pointlist;		// 结果缓冲区链表
	ads_name ssname;				// 选择集的图元名
	pt1[X] = pt1[Y] = pt1[Z] = 0.0; 
	pt2[X] = pt2[Y] = 5.0; pt2[Z] = 0.0; 
	
	// 如果已经选择到了实体，就获得当前的PICKFIRST选择集
	// 否则提示用户选择实体
	acedSSGet(NULL, NULL, NULL, NULL, ssname); 
	
	// 如果存在，就获得当前的PickFirst选择集 
	acedSSGet(TEXT("I"), NULL, NULL, NULL, ssname); 
	
	// 选择最近创建的选择集 
	acedSSGet(TEXT("P"), NULL, NULL, NULL, ssname); 
	
	// 选择最后一次创建的可见实体
	acedSSGet(TEXT("L"), NULL, NULL, NULL, ssname); 
	
	// 选择通过点(5,5)的所有实体
	acedSSGet(NULL, pt2, NULL, NULL, ssname); 
	
	// 选择位于角点(0,0)和(5,5)组成的窗口内所有的实体
	acedSSGet(TEXT("W"), pt1, pt2, NULL, ssname); 
	
	// 选择被指定的多边形包围的所有实体 
	pt3[X] = 10.0; pt3[Y] = 5.0; pt3[Z] = 0.0; 
	pt4[X] = 5.0; pt4[Y] = pt4[Z] = 0.0; 
	pointlist = acutBuildList(RTPOINT, pt1, RTPOINT, pt2, 
		RTPOINT, pt3, RTPOINT, pt4, 0); 
	acedSSGet(TEXT("WP"), pointlist, NULL, NULL, ssname); 
	
	// 选择与角点(0,0)和(5,5)组成的区域相交的所有实体 
	acedSSGet(TEXT("C"), pt1, pt2, NULL, ssname); 
	
	// 选择与指定多边形区域相交的所有实体 
	acedSSGet(TEXT("CP"), pointlist, NULL, NULL, ssname); 
	acutRelRb(pointlist); 
	
	// 选择与选择栏相交的所有对象
	pt4[Y] = 15.0; pt4[Z] = 0.0; 
	pointlist = acutBuildList(RTPOINT, pt1, RTPOINT, pt2, 
		RTPOINT, pt3, RTPOINT, pt4, 0); 
	acedSSGet(TEXT("F"), pointlist, NULL, NULL, ssname); 
	
	acutRelRb(pointlist);
	acedSSFree(ssname);
}

// This is command 'SELECTINPOLY'
void ZffChap5SelectInPoly()
{
	// 提示用户选择多段线
	ads_name entName;
	ads_point pt;
	if (acedEntSel(TEXT("\n选择多段线:"), entName, pt) != RTNORM)
		return;
	
	AcDbObjectId entId;
	acdbGetObjectId(entId, entName);
	
	// 判断选择的实体是否是多段线
	AcDbEntity *pEnt;
	acdbOpenObject(pEnt, entId, AcDb::kForWrite);
	if (pEnt->isKindOf(AcDbPolyline::desc()))
	{
		AcDbPolyline *pPoly = AcDbPolyline::cast(pEnt);
		
		AcDbObjectIdArray ObjectIdArray;	// 选择到的实体ID集合
		SelectEntInPoly(pPoly, ObjectIdArray, "CP", 1);
		acutPrintf(TEXT("\n选择到%d个实体."), ObjectIdArray.length());
	}
	
	pEnt->close();
}

// This is command 'FILTER1'
void ZffChap5Filter1()
{
	struct resbuf *rb;	// 结果缓冲区链表	
	ads_name ssname;	
	
	rb = acutBuildList(RTDXF0, TEXT("TEXT"),		// 实体类型
		8, TEXT("0,图层1"),							// 图层
		1, TEXT("*cadhelp*"),						// 包含的字符串
		RTNONE);
	
	// 选择复合要求的文字
	acedSSGet(TEXT("X"), NULL, NULL, rb, ssname); 
	long length;
	acedSSLength(ssname, &length);
	acutPrintf(TEXT("\n实体数:%d"), length);
	
	acutRelRb(rb);	
	acedSSFree(ssname);
}

// This is command 'FILTER2'
void ZffChap5Filter2()
{
	struct resbuf *rb;	// 结果缓冲区链表	
	ads_name ssname;	
	
	rb = acutBuildList(-4, TEXT("<OR"),		// 逻辑运算符开始
		RTDXF0, TEXT("TEXT"),					// 一个条件
		RTDXF0, TEXT("MTEXT"),				// 另一个条件
		-4, TEXT("OR>"),						// 逻辑运算符结束
		RTNONE);
	
	// 选择复合要求的文字
	acedSSGet(TEXT("A"), NULL, NULL, rb, ssname); 
	long length;
	acedSSLength(ssname, &length);
	acutPrintf(TEXT("\n实体数:%d"), length);
	
	acutRelRb(rb);	
	acedSSFree(ssname);
}

// This is command 'FILTER3'
void ZffChap5Filter3()
{
	struct resbuf *rb;	// 结果缓冲区链表	
	ads_name ssname;	
	
	rb = acutBuildList(RTDXF0, TEXT("CIRCLE"),	// 实体类型
		-4, TEXT(">="),							// 关系运算符
		40, 30,								// 半径
		RTNONE);
	
	// 选择复合要求的实体
	acedSSGet(TEXT("A"), NULL, NULL, rb, ssname); 
	long length;
	acedSSLength(ssname, &length);
	acutPrintf(TEXT("\n实体数:%d"), length);
	
	acutRelRb(rb);	
	acedSSFree(ssname);
}

// This is command 'FILTER4'
void ZffChap5Filter4()
{
	struct resbuf *rb;	// 结果缓冲区链表	
	ads_name ssname;	
	
	ads_point pt1, pt2;
	pt1[X] = pt1[Y] = pt1[Z] = 0;
	pt2[X] = pt2[Y] = 100;
	pt2[Z] = 0;
	
	rb = acutBuildList(RTDXF0, TEXT("CIRCLE"),	// 实体类型
		-4, TEXT(">,>,*"),						// 关系运算符和通配符
		10, pt1,							// 圆心
		-4, TEXT("<,<,*"),						// 关系运算符和通配符
		10, pt2,							// 圆心
		RTNONE);
	
	// 选择复合要求的实体
	acedSSGet(TEXT("A"), NULL, NULL, rb, ssname); 
	long length;
	acedSSLength(ssname, &length);
	acutPrintf(TEXT("\n实体数:%d"), length);
	
	acutRelRb(rb);	
	acedSSFree(ssname);
}

// This is command 'FILTER5'
void ZffChap5Filter5()
{
	struct resbuf *rb;	// 结果缓冲区链表	
	ads_name ssname;	
	
	ads_point pt1, pt2;
	pt1[X] = pt1[Y] = pt1[Z] = 0;
	pt2[X] = pt2[Y] = 100;
	pt2[Z] = 0;
	
// 	rb = acutBuildList(1001, TEXT("XData"),	// 扩展数据的应用程序名		
// 		RTNONE);

	rb = acutBuildList(1000, TEXT("Road"),	// 扩展数据中的ASCII字符串	
		RTNONE);
	
	// 选择复合要求的实体
	acedSSGet(TEXT("A"), NULL, NULL, rb, ssname); 
	long length;
	acedSSLength(ssname, &length);
	acutPrintf(TEXT("\n实体数:%d"), length);
	
	acutRelRb(rb);	
	acedSSFree(ssname);
}

// This is command 'TEST2'
void ZffChap5Test2()
{
	ads_name ssname;	
	ads_point pt1, pt2;
	pt1[X] = pt1[Y] = pt1[Z] = 0;
	pt2[X] = pt2[Y] = 100;
	pt2[Z] = 0;	
	
	// 选择图形中与pt1和pt2组成的窗口相交的所有对象
	acedSSGet(TEXT("C"), pt1, pt2, NULL, ssname); 
	long length;
	acedSSLength(ssname, &length);
	acutPrintf(TEXT("\n实体数:%d"), length);
	
	acedSSFree(ssname);
}

// This is command 'ENTINFO'
void ZffChap5EntInfo()
{
	acDocManager->sendStringToExecute(acDocManager->curDocument(), 
		TEXT("(entget(car(entsel))) "));	// 字符串的末尾包含一个空字符
}

