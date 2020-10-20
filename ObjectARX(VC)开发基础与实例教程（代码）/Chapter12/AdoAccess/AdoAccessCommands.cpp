//
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "..\..\Common\IO\AppDirectoryUtil.h"
#include "..\..\Common\Database\DbConnection.h"
#include "..\..\Common\Database\DbCommand.h"
#include "..\..\Common\Database\DbDataReader.h"

// 获得数据库连接字符串
static CString GetConnectionString()
{
	CString mdbFileName = CAppDirectoryUtil::GetParentDirectory() + TEXT("\\Book.mdb");
	return TEXT("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=") + mdbFileName;		
}

// This is command 'ADDBOOK'
void ZffChap12AddBook()
{
	// 打开数据库连接
	CDbConnection con(GetConnectionString());
	con.Open();

	// 定义查询命令
	CString sql;
	sql.Format(TEXT("Insert Into Book(Name, Author, Press, Price) Values('%s', '%s', '%s', %f)"), 
		TEXT("AutoCAD 2002开发教程"), TEXT("唐亮 张帆 卫朝富"), TEXT("北京希望电子出版社"), 32.0);
	CDbCommand cmd(sql, &con);
	int rows = cmd.ExecuteNonQuery();

	CDbCommand cmd2(TEXT("Select @@Identity"), &con);
	int bookId = cmd2.ExecuteScalar().ToInteger();
	acutPrintf(TEXT("\n新建的Book表记录主键:%d"), bookId);

	// 关闭数据库连接
	con.Close();
}

// This is command 'EDITBOOK'
void ZffChap12EditBook()
{
	// 打开数据库连接
	CDbConnection con(GetConnectionString());
	con.Open();
	
	// 定义查询命令
	CString sql = TEXT("Update Book Set Name = @Name, Author = @Author, Press = @Press, Price = @Price Where BookID = @BookID");
	CDbCommand cmd(sql, &con);
	cmd.AddCharParameter(TEXT("@Name"), TEXT("测试图书"));
	cmd.AddCharParameter(TEXT("@Author"), TEXT("测试作者"));
	cmd.AddCharParameter(TEXT("@Press"), TEXT("测试出版社"));
	cmd.AddDoubleParameter(TEXT("@Price"), 10.0);
	cmd.AddLongParameter(TEXT("@BookID"), 4);
	int rows = cmd.ExecuteNonQuery();
	if (rows > 0)
	{
		acutPrintf(TEXT("\n修改记录成功."));
	}
	
	// 关闭数据库连接
	con.Close();
}

// This is command 'DELETEBOOK'
void ZffCHAP12DeleteBook()
{
	// 打开数据库连接
	CDbConnection con(GetConnectionString());
	con.Open();
	
	// 定义查询命令
	CString sql = TEXT("Delete From Book Where BookID = @BookID");
	CDbCommand cmd(sql, &con);
	cmd.AddLongParameter(TEXT("@BookID"), 4);
	int rows = cmd.ExecuteNonQuery();
	if (rows > 0)
	{
		acutPrintf(TEXT("\n删除记录成功."));
	}
	
	// 关闭数据库连接
	con.Close();
}

// This is command 'QUERYBOOK'
void ZffCHAP12QueryBook()
{
	// 打开数据库连接
	CDbConnection con(GetConnectionString());
	con.Open();
	
	// 定义查询命令
	CString sql = TEXT("Select * From Book Where Price > 20.0");
	CDbCommand cmd(sql, &con);
	CDbDataReader *dr = cmd.ExecuteReader();
	while (dr->Read())
	{
		long bookId = (*dr)[TEXT("BookID")].ToLong();
		CString name = (*dr)[TEXT("Name")].ToString();
		CString author = (*dr)[TEXT("Author")].ToString();
		CString press = (*dr)[TEXT("Press")].ToString();
		double price = (*dr)[TEXT("Price")].ToDouble();
		acutPrintf(TEXT("\nBookId:%d, Name:%s, Author:%s, Press:%s, Price:%.2f"), bookId, 
			name, author, press, price);
	}
	dr->Close();
	
	// 关闭数据库连接
	con.Close();
}

