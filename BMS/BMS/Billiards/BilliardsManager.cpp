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

void BilliardsManager::AddTableType(QString typeName, double pricePerHour) {
	BilliardsType billiardsType;

	QUuid id = QUuid::createUuid();
	QString strId = id.toString();

	billiardsType.SetUuid(strId);
	billiardsType.SetTypeName(typeName);
	billiardsType.SetPricePerHour(pricePerHour);

	_vecBilliardsType.push_back(billiardsType);   // 内存

	DbExecute::InsertToTableType(billiardsType);  // 数据库
}

void BilliardsManager::DeleteTableType(QString uuid) {
	for (auto iter = _vecBilliardsType.begin(); iter != _vecBilliardsType.end();) {
		if (iter->GetUuid() == uuid) {
			iter = _vecBilliardsType.erase(iter);
		}
		else {
			++iter;
		}
	}

	QString sqlWhere(QString("where uuid = '%1'").arg(uuid));
	DbExecute::DeleteFromTableType(sqlWhere);
}

QVector<BilliardsType> BilliardsManager::GetTableTypes() {
	return _vecBilliardsType;
}

BilliardsManager::BilliardsManager() {

}

BilliardsManager::~BilliardsManager() {

}
