#include <QUuid>

#include "BilliardsManager.h"

// 在此处初始化
BilliardsManager* BilliardsManager::_instance = new BilliardsManager();
BilliardsManager* BilliardsManager::GetInstance() {
	return _instance;
}

void BilliardsManager::AddTableType(QString typeName, double pricePerHour) {
	BilliardsType billiardsType;

	QUuid id = QUuid::createUuid();
	QString strId = id.toString();

	billiardsType.SetUuid(strId);
	billiardsType.SetTypeName(typeName);
	billiardsType.SetPricePerHour(pricePerHour);

	_vecBilliardsType.push_back(billiardsType);
}

QVector<BilliardsType> BilliardsManager::GetTableTypes() {
	return _vecBilliardsType;
}

BilliardsManager::BilliardsManager() {

}

BilliardsManager::~BilliardsManager() {

}
