#include "BilliardsType.h"

BilliardsType::BilliardsType() {

}

BilliardsType::~BilliardsType() {

}

void BilliardsType::SetUuid(QString uuid) {
	_uuid = uuid;
}

QString BilliardsType::GetUuid() {
	return _uuid;
}

void BilliardsType::SetTypeName(QString typeName) {
	_typeName = typeName;
}

QString BilliardsType::GetTypeName() {
	return _typeName;
}

void BilliardsType::SetPricePerHour(double pricePerHour) {
	_pricePerHour = pricePerHour;
}

double BilliardsType::GetPricePerHour() {
	return _pricePerHour;
}