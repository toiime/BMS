#include <QUuid>

#include "../Bill/BillManager.h"
#include "../DbModule/DbExecute.h"

// 在此处初始化
BillManager* BillManager::_instance = new BillManager();
BillManager* BillManager::GetInstance() {
	return _instance;
}

BillManager::BillManager() {

}

BillManager::~BillManager() {

}

void BillManager::LoadBillsFromDb() {
	DbExecute::QueryFromBill(_vecBill);
}

void BillManager::AddBill(Bill bill) {

	QUuid id = QUuid::createUuid();
	QString strId = id.toString();

	bill.SetUuid(strId);

	_vecBill.push_back(bill); // 内存

	DbExecute::InsertToBill(bill); // 数据库...
}

QVector<Bill> BillManager::GetBills() {
	return _vecBill;
}