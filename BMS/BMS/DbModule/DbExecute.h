﻿#ifndef DB_EXECUTE_H_
#define DB_EXECUTE_H_

#include "./Billiards/BilliardsType.h"
#include "./Billiards/Billiards.h"

// 数据库操作类...
class DbExecute {
public:
	DbExecute();
	~DbExecute();

public:
	static int InitDb();

	// 表 tableType
	static int InsertToTableType(BilliardsType& billiardsType);
	static int DeleteFromTableType(QString sqlWhere);
	static int QueryFromTableType(QVector<BilliardsType>& vecBilliardsType);

	// 表 billiardsTable
	static int InsertToBilliardsTable(Billiards& billiards);
	static int DeleteFromBilliardsTable(QString sqlWhere);
	static int QueryFromBilliardsTable(QVector<Billiards>& vecBilliards);

private:
	// 创建表 tableType
	static int CreateTableTableType();
	// 创建表 billiardsTable
	static int CreateTableBilliardsTable();

	// 判断表是否存在
	static bool IsExistTable(QString tableName);
};

#endif // !DB_EXECUTE_H_