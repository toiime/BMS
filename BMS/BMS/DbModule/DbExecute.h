#ifndef DB_EXECUTE_H_
#define DB_EXECUTE_H_

#include "./Billiards/BilliardsType.h"
#include "./Billiards/Billiards.h"
#include "./Bill/Bill.h"

// 数据库操作类...
class DbExecute {
public:
	DbExecute();
	~DbExecute();

public:
	static int InitDb();

	// 表 tableType
	static int InsertToTableType(BilliardsType*& billiardsType);
	static int DeleteFromTableType(QString sqlWhere);
	static int UpdateToTableType(BilliardsType* billiardsType);
	static int QueryFromTableType(QVector<BilliardsType*>& vecBilliardsType);

	// 表 billiardsTable
	static int InsertToBilliardsTable(Billiards* billiards);
	static int DeleteFromBilliardsTable(QString sqlWhere);
	static int UpdateToBilliardsTable(Billiards* billiards);
	static int QueryFromBilliardsTable(QVector<Billiards*>& vecBilliards);

	// 表 bill
	static int InsertToBill(Bill& bill);
	static int QueryFromBill(QVector<Bill>& vecBill);

private:
	// 创建表 tableType
	static int CreateTableTableType();
	// 创建表 billiardsTable
	static int CreateTableBilliardsTable();
	// 创建表 bill
	static int CreateBill();

	// 判断表是否存在
	static bool IsExistTable(QString tableName);
};

#endif // !DB_EXECUTE_H_