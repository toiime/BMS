#include "Bill\Bill.h"

Bill::Bill() {

}

Bill::~Bill() {

}

void Bill::SetUuid(QString uuid) {
	_uuid = uuid;
}

QString Bill::GetUuid() {
	return _uuid;
}

void Bill::SetTableNum(QString tableNum) {
	_tableNum = tableNum;
}

QString Bill::GetTableNum() {
	return _tableNum;
}

void Bill::SetTableType(QString tableType) {
	_tableType = tableType;
}

QString Bill::GetTableType() {
	return _tableType;
}

void Bill::SetPricePerHour(double pricePerHour) {
	_pricePerHour = pricePerHour;
}

double Bill::GetPricePerHour() {
	return _pricePerHour;
}

void Bill::SetBeginTime(QString beginTime) {
	_beginTime = beginTime;
}

QString Bill::GetBeginTime() {
	return _beginTime;
}

void Bill::SetPayTime(QString payTime) {
	_payTime = payTime;
}

QString Bill::GetPayTime() {
	return _payTime;
}

void Bill::SetDurationTime(QString durationTime) {
	_durationTime = durationTime;
}

QString Bill::GetDurationTime() {
	return _durationTime;
}

void Bill::SetPayMoney(double payMoney) {
	_payMoney = payMoney;
}

double Bill::GetPayMoney() {
	return _payMoney;
}