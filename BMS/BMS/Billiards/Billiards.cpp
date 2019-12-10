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

void Billiards::SetBilliardsTypeId(QString billiardsTypeId) {
	_billiardsTypeId = billiardsTypeId;
}

QString Billiards::GetBilliardsTypeId() {
	return _billiardsTypeId;
}

void Billiards::SetBeginTime(QString beginTime) {
	_beginTime = beginTime;
}

QString Billiards::GetBeginTime() {
	return _beginTime;
}

void Billiards::SetEndTime(QString endTime) {
	_endTime = endTime;
}

QString Billiards::GetEndTime() {
	return _endTime;
}

void Billiards::SetIsBegin(bool isBegin) {
	_isBegin = isBegin;
}

bool Billiards::GetIsBegin() {
	return _isBegin;
}