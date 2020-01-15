#ifndef DB_EXECUTE_H_
#define DB_EXECUTE_H_

#include "./DbModule/DbStructDef.h"

// 数据库操作类...
class DbExecute {
public:
    DbExecute();
    ~DbExecute();

public:
    static int InitDb();

    // 表 tableType
    static int InsertToTableType(const TableTypeDef& tableTypeDef);
    static int DeleteFromTableType(QString sqlWhere);
    static int UpdateToTableType(const TableTypeDef& tableTypeDef);
    static int QueryFromTableType(QVector<TableTypeDef>& vecTableTypeDef);

    // 表 billiardsTable
    static int InsertToBilliardsTable(const BilliardsTableDef& billiardsTableDef);
    static int DeleteFromBilliardsTable(QString sqlWhere);
    static int UpdateToBilliardsTable(const BilliardsTableDef& billiardsTableDef);
    static int QueryFromBilliardsTable(QVector<BilliardsTableDef>& vecBilliardsTableDef);

    // 表 bill
    static int InsertToBill(const BillDef& billDef);
    static int DeleteFromBill(QString sqlWhere);
    static int UpdateToBill(const BillDef& billDef);
    static int QueryFromBill(QVector<BillDef>& vecBillDef);

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