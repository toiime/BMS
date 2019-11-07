#include "DbExecute.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

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

	return 0;
}

int DbExecute::InsertToTableType(BilliardsType& billiardsType) {
	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("insert into tableType(uuid, typeName, pricePerHour) values('%1', '%2', %3)")
		.arg(billiardsType.GetUuid()).arg(billiardsType.GetTypeName()).arg(billiardsType.GetPricePerHour());
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

int DbExecute::QueryFromTableType(QVector<BilliardsType>& vecBilliardsType) {
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
		BilliardsType billiardsType;
		billiardsType.SetUuid(query.value(0).toString());
		billiardsType.SetTypeName(query.value(1).toString());
		billiardsType.SetPricePerHour(query.value(2).toDouble());
		vecBilliardsType.push_back(billiardsType);
	}
	return 0;
}

int DbExecute::InsertToBilliardsTable(Billiards& billiards) {
	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("insert into billiardsTable(uuid, tableNum, billiardsTypeId"
		", beginTime, endTime)"
		" values('%1', %2, '%3', '%4', '%5')")
		.arg(billiards.GetUuid())
		.arg(billiards.GetTableNum())
		.arg(billiards.GetBilliardsType().GetUuid())
		.arg(billiards.GetBeginTime().toString("yyyy-MM-dd hh:mm:ss"))
		.arg(billiards.GetEndTime().toString("yyyy-MM-dd hh:mm:ss"));
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

int DbExecute::QueryFromBilliardsTable(QVector<Billiards>& vecBilliards) {
	// 先查询球桌类型
	QVector<BilliardsType> vecBilliardsType;
	DbExecute::QueryFromTableType(vecBilliardsType);

	// 再查询球桌
	QSqlDatabase db = QSqlDatabase::database(gConnectionName);
	QSqlQuery query(db);
	QString sql = QString("select * from billiardsTable");
	query.prepare(sql);
	bool isOk = query.exec();
	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::QueryFromBilliardsTable sql is " << sql;
		qDebug() << "\n Sql Error " << query.lastError();
		return -1;
	}

	QString tableTypeUuid;
	while (query.next()) {
		Billiards billiards;
		billiards.SetUuid(query.value(0).toString());
		billiards.SetTableNum(query.value(1).toInt());
		tableTypeUuid = query.value(2).toString();
		for (auto& v : vecBilliardsType) {
			if (tableTypeUuid == v.GetUuid()) {
				billiards.SetBilliardsType(v);
				break;
			}
		}
		billiards.SetBeginTime(QDateTime::fromString(query.value(3).toString()));
		billiards.SetEndTime(QDateTime::fromString(query.value(4).toString()));
		vecBilliards.push_back(billiards);
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
		", billiardsTypeId TEXT, beginTime TEXT, endTime TEXT)");
	query.prepare(sql);
	bool isOk = query.exec();
	if (!isOk) {
		qDebug() << "\n Sql Error in DbExecute::CreateTableBilliardsTable sql is " << sql;
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
