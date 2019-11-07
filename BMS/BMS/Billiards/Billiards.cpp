#include "Billiards.h"

Billiards::Billiards() {
	_tableNum = -1;
	_isBegin = false;
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

void Billiards::SetBeginTime(QDateTime beginTime) {
	_beginTime = beginTime;
}

QDateTime Billiards::GetBeginTime() {
	return _beginTime;
}

void Billiards::SetEndTime(QDateTime endTime) {
	_endTime = endTime;
}

QDateTime Billiards::GetEndTime() {
	return _endTime;
}

void Billiards::SetIsBegin(bool isBegin) {
	_isBegin = isBegin;
}

bool Billiards::GetIsBegin() {
	return _isBegin;
}