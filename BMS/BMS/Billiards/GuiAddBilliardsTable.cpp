#include "GuiAddBilliardsTable.h"

GuiAddBilliardsTable::GuiAddBilliardsTable(QWidget *parent)
	: QDialog(parent) {
	ui.setupUi(this);

	connect(ui.pushButtonOk, &QPushButton::clicked, this, &GuiAddBilliardsTable::SlotBtnOk);
	connect(ui.pushButtonCancel, &QPushButton::clicked, this, &GuiAddBilliardsTable::SlotBtnCancel);
}

GuiAddBilliardsTable::~GuiAddBilliardsTable() {

}

void GuiAddBilliardsTable::SlotBtnOk() {
	accept();
}

void GuiAddBilliardsTable::SlotBtnCancel() {
	reject();
}