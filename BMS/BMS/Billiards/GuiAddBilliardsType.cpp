#include "GuiAddBilliardsType.h"
#include "BilliardsManager.h"

GuiAddBilliardsType::GuiAddBilliardsType(QWidget *parent)
	: QDialog(parent) {
	ui.setupUi(this);

	connect(ui.pushButtonOk, &QPushButton::clicked, this, &GuiAddBilliardsType::SlotBtnOk);
	connect(ui.pushButtonCancel, &QPushButton::clicked, this, &GuiAddBilliardsType::SlotBtnCancel);
}

GuiAddBilliardsType::~GuiAddBilliardsType() {

}

void GuiAddBilliardsType::SlotBtnOk() {

	QString typeName = ui.lineEditBilliardsTypeName->text();
	double pricePerHour = ui.lineEditPerPrice->text().toDouble();

	BilliardsManager::GetInstance()->AddTableType(typeName, pricePerHour);

	accept();
}

void GuiAddBilliardsType::SlotBtnCancel() {
	reject();
}
