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
