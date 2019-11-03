#include "bms.h"

BMS::BMS(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);

	connect(ui.pushButtonBusiness, &QPushButton::clicked, this, &BMS::SlotBtnBusiness);
	connect(ui.pushButtonSettings, &QPushButton::clicked, this, &BMS::SlotBtnSettings);
}

BMS::~BMS() {

}

void BMS::SlotBtnBusiness() {
	ui.stackedWidgetMainWindow->setCurrentIndex(0);
}

void BMS::SlotBtnSettings() {
	ui.stackedWidgetMainWindow->setCurrentIndex(1);
}
