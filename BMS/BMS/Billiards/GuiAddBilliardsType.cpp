#include "GuiAddBilliardsType.h"
#include "BilliardsManager.h"

GuiAddBilliardsType::GuiAddBilliardsType(BilliardsType* billiardsType, QWidget *parent)
	: _billiardsType(billiardsType), QDialog(parent) {
	ui.setupUi(this);

	InitUi();

	connect(ui.pushButtonOk, &QPushButton::clicked, this, &GuiAddBilliardsType::SlotBtnOk);
	connect(ui.pushButtonCancel, &QPushButton::clicked, this, &GuiAddBilliardsType::SlotBtnCancel);
}

GuiAddBilliardsType::~GuiAddBilliardsType() {

}

void GuiAddBilliardsType::InitUi() {
	if (_billiardsType) {
		ui.lineEditBilliardsTypeName->setText(_billiardsType->GetTypeName());
		ui.lineEditPerPrice->setText(QString::number(_billiardsType->GetPricePerHour()));
	}
}

void GuiAddBilliardsType::SlotBtnOk() {

	QString typeName = ui.lineEditBilliardsTypeName->text();
	double pricePerHour = ui.lineEditPerPrice->text().toDouble();

	if (_billiardsType) {
		_billiardsType->SetTypeName(typeName);
		_billiardsType->SetPricePerHour(pricePerHour);
		BilliardsManager::GetInstance()->UpdateTableType(_billiardsType);
	}
	else {
		BilliardsType* billiardsType = BilliardsManager::GetInstance()->CreateTableType();
		if (billiardsType) {
			billiardsType->SetTypeName(typeName);
			billiardsType->SetPricePerHour(pricePerHour);
			BilliardsManager::GetInstance()->UpdateTableType(billiardsType);
		}
	}

	accept();
}

void GuiAddBilliardsType::SlotBtnCancel() {
	reject();
}
