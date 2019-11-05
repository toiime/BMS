#include "Billiards.h"

Billiards::Billiards() {

}

Billiards::~Billiards() {

}

void Billiards::SetUuid(QString uuid) {
	_uuid = uuid;
}

QString Billiards::GetUuid() {
	return _uuid;
}

void Billiards::SetTableNum(int tableNum) {
	_tableNum = tableNum;
}

int Billiards::GetTableNum() {
	return _tableNum;
}

void Billiards::SetBilliardsType(BilliardsType billiardsType) {
	_billiardsType = billiardsType;
}

BilliardsType Billiards::GetBilliardsType() {
	return _billiardsType;
}

void Billiards::SetBeginTime(int beginTime) {
	_beginTime = beginTime;
}

int Billiards::GetBeginTime() {
	return _beginTime;
}

void Billiards::SetEndTime(int endTime) {
	_endTime = endTime;
}

int Billiards::GetEndTime() {
	return _endTime;
}