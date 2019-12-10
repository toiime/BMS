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
	QVector<BillDef> vecBillDef;
	DbExecute::QueryFromBill(vecBillDef);

	for (auto& v : vecBillDef) {
		Bill* bill = new Bill;
		bill->SetUuid(v.uuid_);
		bill->SetTableNum(v.tableNum_);
		bill->SetTableTypeName(v.tableTypeName_);
		bill->SetPricePerHour(v.pricePerHour_);
		bill->SetBeginTime(v.beginTime_);
		bill->SetPayTime(v.payTime_);
		bill->SetDurationTime(v.durationTime_);
		bill->SetPayMoney(v.payMoney_);
		_vecBill.push_back(bill);
	}
}

Bill* BillManager::CreateBill() {
	Bill* bill = new Bill;

	QUuid id = QUuid::createUuid();
	QString strId = id.toString();

	bill->SetUuid(strId);

	_vecBill.push_back(bill);

	BillDef billDef;
	billDef.uuid_ = bill->GetUuid();
	billDef.tableNum_ = bill->GetTableNum();
	billDef.tableTypeName_ = bill->GetTableTypeName();
	billDef.pricePerHour_ = bill->GetPricePerHour();
	billDef.beginTime_ = bill->GetBeginTime();
	billDef.payTime_ = bill->GetPayTime();
	billDef.durationTime_ = bill->GetDurationTime();
	billDef.payMoney_ = bill->GetPayMoney();
	DbExecute::InsertToBill(billDef);

	return bill;
}

void BillManager::UpdateBill(Bill* bill) {
	if (!bill) return;

	for (auto& v : _vecBill) {
		if (v->GetUuid() == bill->GetUuid()) {
			*v = *bill;
		}
	}

	BillDef billDef;
	billDef.uuid_ = bill->GetUuid();
	billDef.tableNum_ = bill->GetTableNum();
	billDef.tableTypeName_ = bill->GetTableTypeName();
	billDef.pricePerHour_ = bill->GetPricePerHour();
	billDef.beginTime_ = bill->GetBeginTime();
	billDef.payTime_ = bill->GetPayTime();
	billDef.durationTime_ = bill->GetDurationTime();
	billDef.payMoney_ = bill->GetPayMoney();
	DbExecute::UpdateToBill(billDef);
}

QVector<Bill*> BillManager::GetBills() {
	return _vecBill;
}