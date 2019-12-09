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
		ui.comboBoxTableType->setCurrentText(_billiards->GetBilliardsType().GetTypeName());
	}
}

void GuiAddBilliardsTable::SlotBtnOk() {
	int tableNum = ui.lineEditTableNum->text().toInt();
	QString tableTypeId = ui.comboBoxTableType->currentData().toString();
	BilliardsType* billiardsType = BilliardsManager::GetInstance()->FindBilliardsType(tableTypeId);

	if (_billiards) {
		_billiards->SetTableNum(tableNum);
		if (billiardsType) {
			_billiards->SetBilliardsType(*billiardsType);
		}
		BilliardsManager::GetInstance()->UpdateBilliardsTable(_billiards);
	}
	else {
		Billiards* billiards = BilliardsManager::GetInstance()->CreateBilliardsTable();
		if (billiards) {
			billiards->SetTableNum(tableNum);
			if (billiardsType) {
				billiards->SetBilliardsType(*billiardsType);
			}
			BilliardsManager::GetInstance()->UpdateBilliardsTable(billiards);
		}
	}

	accept();
}

void GuiAddBilliardsTable::SlotBtnCancel() {
	reject();
}