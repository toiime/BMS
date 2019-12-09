#include <QUuid>

#include "BilliardsManager.h"
#include "./DbModule/DbExecute.h"

// 在此处初始化
BilliardsManager* BilliardsManager::_instance = new BilliardsManager();
BilliardsManager* BilliardsManager::GetInstance() {
	return _instance;
}

void BilliardsManager::LoadTableTypeFromDb() {
	DbExecute::QueryFromTableType(_vecBilliardsType);
}

BilliardsType* BilliardsManager::CreateTableType() {
	BilliardsType* billiardsType = new BilliardsType;

	QUuid id = QUuid::createUuid();
	QString strId = id.toString();

	billiardsType->SetUuid(strId);

	_vecBilliardsType.push_back(billiardsType);   // 内存
	DbExecute::InsertToTableType(billiardsType);  // 数据库

	return billiardsType;
}

void BilliardsManager::UpdateTableType(BilliardsType* billiardsType) {
	if (!billiardsType) return;

	for (auto& v : _vecBilliardsType) {
		if (v->GetUuid() == billiardsType->GetUuid()) {
			*v = *billiardsType;
		}
	}

	DbExecute::UpdateToTableType(billiardsType);  // 数据库
}

void BilliardsManager::DeleteTableType(QString uuid) {
	for (auto iter = _vecBilliardsType.begin(); iter != _vecBilliardsType.end();) {
		if ((*iter)->GetUuid() == uuid) {
			iter = _vecBilliardsType.erase(iter);
		}
		else {
			++iter;
		}
	}

	QString sqlWhere(QString("where uuid = '%1'").arg(uuid));
	DbExecute::DeleteFromTableType(sqlWhere);
}

BilliardsType* BilliardsManager::FindBilliardsType(QString id) {
	for (auto& v : _vecBilliardsType) {
		if (v->GetUuid() == id) {
			return v;
		}
	}

	return nullptr;
}

QVector<BilliardsType*> BilliardsManager::GetTableTypes() {
	return _vecBilliardsType;
}

void BilliardsManager::LoadTableFromDb() {
	DbExecute::QueryFromBilliardsTable(_vecBilliards);
}

Billiards* BilliardsManager::CreateBilliardsTable() {
	Billiards* billiards = new Billiards;

	QUuid id = QUuid::createUuid();
	QString strId = id.toString();

	billiards->SetUuid(strId);

	_vecBilliards.push_back(billiards);            // 内存
	DbExecute::InsertToBilliardsTable(billiards);  // 数据库

	return billiards;
}

void BilliardsManager::UpdateBilliardsTable(Billiards* billiards) {
	if (!billiards) return;

	for (auto& v : _vecBilliards) {
		if (v->GetUuid() == billiards->GetUuid()) {
			*v = *billiards;
		}
	}

	DbExecute::UpdateToBilliardsTable(billiards);
}

void BilliardsManager::DeleteBilliardsTable(QString uuid) {
	for (auto iter = _vecBilliards.begin(); iter != _vecBilliards.end();) {
		if ((*iter)->GetUuid() == uuid) {
			iter = _vecBilliards.erase(iter);
		}
		else {
			++iter;
		}
	}

	QString sqlWhere(QString("where uuid = '%1'").arg(uuid));
	DbExecute::DeleteFromBilliardsTable(sqlWhere);
}

Billiards* BilliardsManager::FindBilliards(QString id) {
	for (auto& v : _vecBilliards) {
		if (v->GetUuid() == id) {
			return v;
		}
	}

	return nullptr;
}

QVector<Billiards*> BilliardsManager::GetBilliardsTables() {
	return _vecBilliards;
}

BilliardsManager::BilliardsManager() {

}

BilliardsManager::~BilliardsManager() {

}
