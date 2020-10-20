//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\Document\DwgDatabaseUtil.h"
#include <dbents.h>
#include "..\..\Common\IO\AppDirectoryUtil.h"
#include "..\..\Common\Entity\LineUtil.h"
#include "..\..\Common\Entity\circleutil.h"

// 启动Excel程序
// 建议在调用程序的InitApplication函数中初始化COM动态链接库：::CoInitialize(NULL);
// 同时在UnloadApplication函数中关闭COM库的支持：::CoUninitialize();
static bool RunExcelApp(_Application &excelApp, bool bVisible = true, bool bUserControl = true);

// This is command 'SAVEFILE'
void ZffChap12SaveFile()
{
	// 获取直线、圆形集合
	AcDbObjectIdArray allEntIds = CDwgDatabaseUtil::GetAllEntityIds();
	AcDbObjectIdArray lineIds, circleIds;
	for (int i = 0; i < allEntIds.length(); i++)
	{
		AcDbEntity *pEnt = NULL;
		if (acdbOpenObject(pEnt, allEntIds[i], AcDb::kForRead) == Acad::eOk)
		{
			if (pEnt->isKindOf(AcDbLine::desc()))
			{
				lineIds.append(pEnt->objectId());
			}
			else if (pEnt->isKindOf(AcDbCircle::desc()))
			{
				circleIds.append(pEnt->objectId());
			}

			pEnt->close();
		}
	}

	// 写二进制文件
	CString fileName = CAppDirectoryUtil::GetCurrentDirectory() + TEXT("\\二进制文件.bnf");
	FILE *pFile = _tfopen(fileName, TEXT("wb"));
	if (pFile)
	{
		// 文件类型（文件类型识别字符串）4个字节的字符串
		char szFileDescription[4] = "bnf";
		fwrite(szFileDescription, sizeof(char), 4, pFile);

		// 文件版本
		int version = 1;		// 当前是第1版
		fwrite(&version, sizeof(int), 1, pFile);

		// 直线数据
		int lineCount = lineIds.length();
		fwrite(&lineCount, sizeof(int), 1, pFile);
		for (int i = 0; i < lineCount; i++)
		{
			AcDbLine *pLine = NULL;
			if (acdbOpenObject(pLine, lineIds[i], AcDb::kForRead) == Acad::eOk)
			{
				AcGePoint3d startPoint = pLine->startPoint();
				AcGePoint3d endPoint = pLine->endPoint();
				double stp[3];
				for (int j = 0; j < 3; j++)
				{
					stp[j] = startPoint[j];
				}
				fwrite(stp, sizeof(double), 3, pFile);
				double enp[3];
				for (j = 0; j < 3; j++)
				{
					enp[j] = endPoint[j];
				}
				fwrite(enp, sizeof(double), 3, pFile);

				pLine->close();
			}
		}

		// 圆数据
		int circleCount = circleIds.length();
		fwrite(&circleCount, sizeof(int), 1, pFile);
		for (i = 0; i < circleCount; i++)
		{
			AcDbCircle *pCircle = NULL;
			if (acdbOpenObject(pCircle, circleIds[i], AcDb::kForRead) == Acad::eOk)
			{
				AcGePoint3d centerPoint = pCircle->center();
				double radius = pCircle->radius();
				double cep[3];
				for (int j = 0; j < 3; j++)
				{
					cep[j] = centerPoint[j];
				}
				fwrite(cep, sizeof(double), 3, pFile);
				
				fwrite(&radius, sizeof(double), 1, pFile);
				
				pCircle->close();
			}
		}

		// 关闭文件
		fclose(pFile);
	}
}

// This is command 'LOADFILE'
void ZffCHAP12LoadFile()
{
	// 读二进制文件
	CString fileName = CAppDirectoryUtil::GetCurrentDirectory() + TEXT("\\二进制文件.bnf");
	FILE *pFile = _tfopen(fileName, TEXT("rb"));
	if (pFile)
	{
		// 文件类型（文件类型识别字符串）4个字节的字符串
		char szFileDescription[4] = {0};
		fread(szFileDescription, sizeof(char), 4, pFile);
		if (strcmp(szFileDescription, "bnf") != 0)
		{
			AfxMessageBox(TEXT("不是有效的BNF文件!"));
			fclose(pFile);
			return;
		}
		
		// 文件版本
		int version = 1;		// 当前是第1版
		fread(&version, sizeof(int), 1, pFile);
		
		// 直线数据
		int lineCount = 0;
		fread(&lineCount, sizeof(int), 1, pFile);
		for (int i = 0; i < lineCount; i++)
		{
			AcGePoint3d startPoint;
			double stp[3];
			fread(stp, sizeof(double), 3, pFile);
			for (int j = 0; j < 3; j++)
			{
				startPoint[j] = stp[j];
			}

			AcGePoint3d endPoint;
			double enp[3];
			fread(enp, sizeof(double), 3, pFile);
			for (j = 0; j < 3; j++)
			{
				endPoint[j] = enp[j];
			}

			CLineUtil::Add(startPoint, endPoint);
		}
		
		// 圆数据
		int circleCount = 0;
		fread(&circleCount, sizeof(int), 1, pFile);
		for (i = 0; i < circleCount; i++)
		{
			AcGePoint3d centerPoint;
			double cep[3];
			fread(cep, sizeof(double), 3, pFile);
			for (int j = 0; j < 3; j++)
			{
				centerPoint[j] = cep[j];
			}

			double radius = 0;			
			fread(&radius, sizeof(double), 1, pFile);
			
			CCircleUtil::Add(centerPoint, radius);
		}

		// 关闭文件
		fclose(pFile);
	}
}

public static List<Catalog> GetChildCatalogs(string number)
{
	try
	{
		List<Catalog> catalogs = new List<Catalog>();
		
		// 数据库连接
		OleDbConnection con = new OleDbConnection(DatabaseUtil.GetSysConnectionString());
		using (con)
		{
			con.Open();
			
			string sql = "SELECT * FROM [Catalog] WHERE Len([Number]) = " + (number.Length + 3) +
				" And [Number] Like '" + number + "%'";
			
			// 执行数据库查询命令
			OleDbCommand cmd = new OleDbCommand(sql, con);
			using (OleDbDataReader dr = cmd.ExecuteReader())
			{
				while (dr.Read())
				{
					Catalog c = new Catalog();
					c.name = dr["Name"].ToString();
					c.number = dr["Number"].ToString();
					c.catalogId = Convert.ToInt64(dr["CatalogId"]);
					catalogs.Add(c);
				}
			}
			
			return catalogs;
		}
	}
	catch (Exception ex)
	{
		MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
		return null;
	}
}