#include "DbExecute.h"

#include <QSqlDatabase>
#include <QSqlQuery>
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

	return 0;
}