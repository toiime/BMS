#include "bms.h"

#include "./DbModule/DbExecute.h"

BMS::BMS(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);

	connect(ui.pushButtonBusiness, &QPushButton::clicked, this, &BMS::SlotBtnBusiness);
	connect(ui.pushButtonSettings, &QPushButton::clicked, this, &BMS::SlotBtnSettings);
	connect(ui.pushButtonAddBilliardsType, &QPushButton::clicked, this, &BMS::SlotAddBilliardsType);
	connect(ui.pushButtonAddBilliards, &QPushButton::clicked, this, &BMS::SlotAddBilliards);
}

BMS::~BMS() {

}

void BMS::SlotBtnBusiness() {
	ui.stackedWidgetMainWindow->setCurrentIndex(0);
}

void BMS::SlotBtnSettings() {
	ui.stackedWidgetMainWindow->setCurrentIndex(1);

	DbExecute::InitDb();
}

void BMS::SlotAddBilliardsType() {

}

void BMS::SlotAddBilliards() {

}
