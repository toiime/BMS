#include <QUuid>

#include "BilliardsManager.h"
#include "./DbModule/DbExecute.h"

// 在此处初始化
BilliardsManager* BilliardsManager::_instance = new BilliardsManager();
BilliardsManager* BilliardsManager::GetInstance() {
	return _instance;
}

void BilliardsManager::LoadTableTypeFromDb() {
	QVector<TableTypeDef> vecTableTypeDef;
	DbExecute::QueryFromTableType(vecTableTypeDef);

	for (auto& v : vecTableTypeDef) {
		BilliardsType* billiardsType = new BilliardsType;
		billiardsType->SetUuid(v.uuid_);
		billiardsType->SetTypeName(v.typeName_);
		billiardsType->SetPricePerHour(v.pricePerHour_);
		_vecBilliardsType.push_back(billiardsType);
	}
}

BilliardsType* BilliardsManager::CreateTableType() {
	BilliardsType* billiardsType = new BilliardsType;

	QUuid id = QUuid::createUuid();
	QString strId = id.toString();

	billiardsType->SetUuid(strId);

	_vecBilliardsType.push_back(billiardsType);   // 内存

	TableTypeDef tableTypeDef;
	tableTypeDef.uuid_ = billiardsType->GetUuid();
	tableTypeDef.typeName_ = billiardsType->GetTypeName();
	tableTypeDef.pricePerHour_ = billiardsType->GetPricePerHour();
	DbExecute::InsertToTableType(tableTypeDef);  // 数据库

	return billiardsType;
}

void BilliardsManager::UpdateTableType(BilliardsType* billiardsType) {
	if (!billiardsType) return;

	for (auto& v : _vecBilliardsType) {
		if (v->GetUuid() == billiardsType->GetUuid()) {
			*v = *billiardsType;
		}
	}

	TableTypeDef tableTypeDef;
	tableTypeDef.uuid_ = billiardsType->GetUuid();
	tableTypeDef.typeName_ = billiardsType->GetTypeName();
	tableTypeDef.pricePerHour_ = billiardsType->GetPricePerHour();
	DbExecute::UpdateToTableType(tableTypeDef);  // 数据库
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
	QVector<BilliardsTableDef> vecBilliardsTableDef;
	DbExecute::QueryFromBilliardsTable(vecBilliardsTableDef);

	for (auto& v : vecBilliardsTableDef) {
		Billiards* billiards = new Billiards;
		billiards->SetUuid(v.uuid_);
		billiards->SetTableNum(v.tableNum_.toInt());
		billiards->SetBilliardsTypeId(v.billiardsTypeId_);
		billiards->SetBeginTime(v.beginTime_);
		billiards->SetEndTime(v.endTime_);
		if (v.isBegin_ == "1") {
			billiards->SetIsBegin(true);
		}
		else {
			billiards->SetIsBegin(false);
		}
		_vecBilliards.push_back(billiards);
	}
}

Billiards* BilliardsManager::CreateBilliardsTable() {
	Billiards* billiards = new Billiards;

	QUuid id = QUuid::createUuid();
	QString strId = id.toString();

	billiards->SetUuid(strId);

	_vecBilliards.push_back(billiards);            // 内存

	BilliardsTableDef billiardsTableDef;
	billiardsTableDef.uuid_ = billiards->GetUuid();
	billiardsTableDef.tableNum_ = QString::number(billiards->GetTableNum());
	billiardsTableDef.billiardsTypeId_ = billiards->GetBilliardsTypeId();
	billiardsTableDef.beginTime_ = billiards->GetBeginTime();
	billiardsTableDef.endTime_ = billiards->GetEndTime();
	if (billiards->GetIsBegin()) {
		billiardsTableDef.isBegin_ = "1";
	}
	else {
		billiardsTableDef.isBegin_ = "0";
	}
	DbExecute::InsertToBilliardsTable(billiardsTableDef);  // 数据库

	return billiards;
}

void BilliardsManager::UpdateBilliardsTable(Billiards* billiards) {
	if (!billiards) return;

	for (auto& v : _vecBilliards) {
		if (v->GetUuid() == billiards->GetUuid()) {
			*v = *billiards;
		}
	}

	BilliardsTableDef billiardsTableDef;
	billiardsTableDef.uuid_ = billiards->GetUuid();
	billiardsTableDef.tableNum_ = QString::number(billiards->GetTableNum());
	billiardsTableDef.billiardsTypeId_ = billiards->GetBilliardsTypeId();
	billiardsTableDef.beginTime_ = billiards->GetBeginTime();
	billiardsTableDef.endTime_ = billiards->GetEndTime();
	if (billiards->GetIsBegin()) {
		billiardsTableDef.isBegin_ = "1";
	}
	else {
		billiardsTableDef.isBegin_ = "0";
	}
	DbExecute::UpdateToBilliardsTable(billiardsTableDef);
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
