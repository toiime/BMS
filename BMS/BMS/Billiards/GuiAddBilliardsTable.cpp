#include "GuiAddBilliardsTable.h"

#include "./Billiards/BilliardsManager.h"

GuiAddBilliardsTable::GuiAddBilliardsTable(Billiards* billiards, QWidget *parent)
	: _billiards(billiards), QDialog(parent) {
	ui.setupUi(this);

	InitUi();

	connect(ui.pushButtonOk, &QPushButton::clicked, this, &GuiAddBilliardsTable::SlotBtnOk);
	connect(ui.pushButtonCancel, &QPushButton::clicked, this, &GuiAddBilliardsTable::SlotBtnCancel);
}

GuiAddBilliardsTable::~GuiAddBilliardsTable() {

}

void GuiAddBilliardsTable::InitUi() {
	QVector<BilliardsType*> vecBilliardsType = BilliardsManager::GetInstance()->GetTableTypes();
	int index = 0;
	for (auto& v : vecBilliardsType) {
		ui.comboBoxTableType->addItem(v->GetTypeName());
		ui.comboBoxTableType->setItemData(index++, v->GetUuid(), Qt::UserRole);
	}

	if (_billiards) {
		ui.lineEditTableNum->setText(QString::number(_billiards->GetTableNum()));

		QString billiardsTypeId = _billiards->GetBilliardsTypeId();
		BilliardsType* billiardsType = BilliardsManager::GetInstance()->FindBilliardsType(billiardsTypeId);
		if (billiardsType) {
			ui.comboBoxTableType->setCurrentText(billiardsType->GetTypeName());
		}
	}
}

void GuiAddBilliardsTable::SlotBtnOk() {
	int tableNum = ui.lineEditTableNum->text().toInt();
	QString tableTypeId = ui.comboBoxTableType->currentData().toString();

	if (_billiards) {
		_billiards->SetTableNum(tableNum);
		_billiards->SetBilliardsTypeId(tableTypeId);
		BilliardsManager::GetInstance()->UpdateBilliardsTable(_billiards);
	}
	else {
		Billiards* billiards = BilliardsManager::GetInstance()->CreateBilliardsTable();
		if (billiards) {
			billiards->SetTableNum(tableNum);
			billiards->SetBilliardsTypeId(tableTypeId);
			BilliardsManager::GetInstance()->UpdateBilliardsTable(billiards);
		}
	}

	accept();
}

void GuiAddBilliardsTable::SlotBtnCancel() {
	reject();
}