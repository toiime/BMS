#include "DbExecute.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "./Global/GlobalDefine.h"

DbExecute::DbExecute() {

}

DbExecute::~DbExecute() {

}

int DbExecute::InitDb() {
	QSqlDatabase db = QSqlDatabase::addDatabase(gDbType, gConnectionName);
	if (!db.isValid()) return -1;
	db.setDatabaseName(gDbName);
	bool ok = db.open();
	if (!ok) return -1;

	CreateTableTableType();
	CreateTableBilliardsTable();
	CreateBill();

	return 0;
}

int DbExecute::InsertToTableType(const TableTypeDef& tableTypeDef) {
	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("insert into tableType(uuid, typeName, pricePerHour) values('%1', '%2', %3)")
		.arg(tableTypeDef.uuid_)
		.arg(tableTypeDef.typeName_)
		.arg(tableTypeDef.pricePerHour_);
	query.prepare(sql);
	bool isOk = query.exec();

	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::InsertToTableType sql is " << sql;
		qDebug() << "\n Sql Error " << query.lastError();
		return -1;
	}
	return 0;
}

int DbExecute::DeleteFromTableType(QString sqlWhere) {
	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("delete from tableType %1").arg(sqlWhere);
	query.prepare(sql);
	bool isOk = query.exec();

	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::DeleteFromTableType sql is " << sql;
		qDebug() << "\n Sql Error " << query.lastError();
		return -1;
	}
	return 0;
}

int DbExecute::UpdateToTableType(const TableTypeDef& tableTypeDef) {
	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("update tableType set typeName = '%1'"
		", pricePerHour = %2"
		" where uuid = '%3'")
		.arg(tableTypeDef.typeName_)
		.arg(tableTypeDef.pricePerHour_)
		.arg(tableTypeDef.uuid_);
	query.prepare(sql);
	bool isOk = query.exec();

	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::InsertToTableType sql is " << sql;
		qDebug() << "\n Sql Error " << query.lastError();
		return -1;
	}
	return 0;
}

int DbExecute::QueryFromTableType(QVector<TableTypeDef>& vecTableTypeDef) {
	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("select * from tableType");
	query.prepare(sql);
	bool isOk = query.exec();
	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::QueryFromTableType sql is " << sql;
		qDebug() << "\n Sql Error " << query.lastError();
		return -1;
	}

	while (query.next()) {
		TableTypeDef tableTypeDef;
		tableTypeDef.uuid_ = query.value(0).toString();
		tableTypeDef.typeName_ = query.value(1).toString();
		tableTypeDef.pricePerHour_ = query.value(2).toDouble();
		vecTableTypeDef.push_back(tableTypeDef);
	}
	return 0;
}

int DbExecute::InsertToBilliardsTable(const BilliardsTableDef& billiardsTableDef) {
	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("insert into billiardsTable(uuid, tableNum, billiardsTypeId"
		", beginTime, endTime, isBegin)"
		" values('%1', %2, '%3', '%4', '%5', %6)")
		.arg(billiardsTableDef.uuid_)
		.arg(billiardsTableDef.tableNum_)
		.arg(billiardsTableDef.billiardsTypeId_)
		.arg(billiardsTableDef.beginTime_)
		.arg(billiardsTableDef.endTime_)
		.arg(billiardsTableDef.isBegin_);
	query.prepare(sql);
	bool isOk = query.exec();

	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::InsertToBilliardsTable sql is " << sql;
		qDebug() << "\n Sql Error " << query.lastError();
		return -1;
	}
	return 0;
}

int DbExecute::DeleteFromBilliardsTable(QString sqlWhere) {
	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("delete from billiardsTable %1").arg(sqlWhere);
	query.prepare(sql);
	bool isOk = query.exec();

	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::DeleteFromBilliardsTable sql is " << sql;
		qDebug() << "\n Sql Error " << query.lastError();
		return -1;
	}
	return 0;
}

int DbExecute::UpdateToBilliardsTable(const BilliardsTableDef& billiardsTableDef) {
	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("update billiardsTable set tableNum = %1"
		", billiardsTypeId = '%2'"
		", beginTime = '%3'"
		", endTime = '%4'"
		", isBegin = %5"
		" where uuid = '%6'")
		.arg(billiardsTableDef.tableNum_)
		.arg(billiardsTableDef.billiardsTypeId_)
		.arg(billiardsTableDef.beginTime_)
		.arg(billiardsTableDef.endTime_)
		.arg(billiardsTableDef.isBegin_)
		.arg(billiardsTableDef.uuid_);
	query.prepare(sql);
	bool isOk = query.exec();

	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::UpdateToBilliardsTable sql is " << sql;
		qDebug() << "\n Sql Error " << query.lastError();
		return -1;
	}
	return 0;
}

int DbExecute::QueryFromBilliardsTable(QVector<BilliardsTableDef>& vecBilliardsTableDef) {
	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("select uuid,tableNum,billiardsTypeId,beginTime"
		",endTime,isBegin from billiardsTable");
	query.prepare(sql);
	bool isOk = query.exec();
	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::QueryFromBilliardsTable sql is " << sql;
		qDebug() << "\n Sql Error " << query.lastError();
		return -1;
	}

	while (query.next()) {
		int index = 0;
		BilliardsTableDef billiardsTableDef;
		billiardsTableDef.uuid_ = query.value(index++).toString();
		billiardsTableDef.tableNum_ = query.value(index++).toString();
		billiardsTableDef.billiardsTypeId_ = query.value(index++).toString();
		billiardsTableDef.beginTime_ = query.value(index++).toString();
		billiardsTableDef.endTime_ = query.value(index++).toString();
		billiardsTableDef.isBegin_ = query.value(index++).toString();
		vecBilliardsTableDef.push_back(billiardsTableDef);
	}

	return 0;
}

int DbExecute::InsertToBill(const BillDef& billDef) {
	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("insert into bill(uuid, tableNum, tableType"
		", pricePerHour, beginTime, payTime, durationTime, payMoney)"
		" values('%1', '%2', '%3', %4, '%5', '%6', '%7', %8)")
		.arg(billDef.uuid_)
		.arg(billDef.tableNum_)
		.arg(billDef.tableTypeName_)
		.arg(billDef.pricePerHour_)
		.arg(billDef.beginTime_)
		.arg(billDef.payTime_)
		.arg(billDef.durationTime_)
		.arg(billDef.payMoney_);
	query.prepare(sql);
	bool isOk = query.exec();

	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::InsertToBill sql is " << sql;
		qDebug() << "\n Sql Error " << query.lastError();
		return -1;
	}
	return 0;
}

int DbExecute::UpdateToBill(const BillDef& billDef) {
	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("update bill set tableNum = '%1'"
		", tableType = '%2'"
		", pricePerHour = %3"
		", beginTime = '%4'"
		", payTime = '%5'"
		", durationTime = '%6'"
		", payMoney = %7"
		" where uuid = '%8'")
		.arg(billDef.tableNum_)
		.arg(billDef.tableTypeName_)
		.arg(billDef.pricePerHour_)
		.arg(billDef.beginTime_)
		.arg(billDef.payTime_)
		.arg(billDef.durationTime_)
		.arg(billDef.payMoney_)
		.arg(billDef.uuid_);
	query.prepare(sql);
	bool isOk = query.exec();

	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::UpdateToBill() sql is " << sql;
		qDebug() << "\n Sql Error " << query.lastError();
		return -1;
	}
	return 0;
}

int DbExecute::QueryFromBill(QVector<BillDef>& vecBillDef) {
	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("select * from bill");
	query.prepare(sql);
	bool isOk = query.exec();
	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::QueryFromBill sql is " << sql;
		qDebug() << "\n Sql Error " << query.lastError();
		return -1;
	}

	while (query.next()) {
		int index = 0;
		BillDef billDef;
		billDef.uuid_ = query.value(index++).toString();
		billDef.tableNum_ = query.value(index++).toString();
		billDef.tableTypeName_ = query.value(index++).toString();
		billDef.pricePerHour_ = query.value(index++).toDouble();
		billDef.beginTime_ = query.value(index++).toString();
		billDef.payTime_ = query.value(index++).toString();
		billDef.durationTime_ = query.value(index++).toString();
		billDef.payMoney_ = query.value(index++).toDouble();
		vecBillDef.push_back(billDef);
	}
	return 0;
}

int DbExecute::CreateTableTableType() {
	if (IsExistTable("tableType")) {
		return 0;
	}

	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("create table tableType(uuid TEXT, typeName TEXT, pricePerHour REAL)");
	query.prepare(sql);
	bool isOk = query.exec();
	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::CreateTableTableType sql is " << sql;
		qDebug() << "\n Sql Error " << query.lastError();
		return -1;
	}

	return 0;
}

int DbExecute::CreateTableBilliardsTable() {
	if (IsExistTable("billiardsTable")) {
		return 0;
	}

	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("create table billiardsTable(uuid TEXT, tableNum INTEGER"
		", billiardsTypeId TEXT, beginTime TEXT, endTime TEXT, isBegin INTEGER)");
	query.prepare(sql);
	bool isOk = query.exec();
	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::CreateTableBilliardsTable sql is " << sql;
		qDebug() << "\n Sql Error " << query.lastError();
		return -1;
	}

	return 0;
}

int DbExecute::CreateBill() {
	if (IsExistTable("bill")) {
		return 0;
	}

	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("create table bill(uuid TEXT, tableNum TEXT"
		", tableType TEXT, pricePerHour REAL, beginTime TEXT"
		", payTime TEXT, durationTime TEXT, payMoney REAL)");
	query.prepare(sql);
	bool isOk = query.exec();
	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::CreateBill sql is " << sql;
		qDebug() << "\n Sql Error " << query.lastError();
		return -1;
	}

	return 0;
}

bool DbExecute::IsExistTable(QString tableName) {
	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("select count(*) from sqlite_master where type = 'table' and name = '%1'").arg(tableName);
	query.prepare(sql);
	bool isOk = query.exec();
	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::InsertToTableType sql is " << sql;
		qDebug() << "\n Sql Error " << query.lastError();
		return false;
	}
	if (query.next()) {
		return query.value(0).toInt() != 0;
	}
	return true;
}
