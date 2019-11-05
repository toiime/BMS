#include "GuiAddBilliardsTable.h"

#include "./Billiards/BilliardsManager.h"

GuiAddBilliardsTable::GuiAddBilliardsTable(QWidget *parent)
	: QDialog(parent) {
	ui.setupUi(this);

	InitUi();

	connect(ui.pushButtonOk, &QPushButton::clicked, this, &GuiAddBilliardsTable::SlotBtnOk);
	connect(ui.pushButtonCancel, &QPushButton::clicked, this, &GuiAddBilliardsTable::SlotBtnCancel);
}

GuiAddBilliardsTable::~GuiAddBilliardsTable() {

}

void GuiAddBilliardsTable::InitUi() {
	QVector<BilliardsType> vecBilliardsType = BilliardsManager::GetInstance()->GetTableTypes();
	int index = 0;
	for (auto& v : vecBilliardsType) {
		ui.comboBoxTableType->addItem(v.GetTypeName());
		ui.comboBoxTableType->setItemData(index++, v.GetUuid(), Qt::UserRole);
	}
}

void GuiAddBilliardsTable::SlotBtnOk() {
	int tableNum = ui.lineEditTableNum->text().toInt();
	QString tableTypeId = ui.comboBoxTableType->currentData().toString();

	BilliardsManager::GetInstance()->AddBilliardsTable(tableNum, tableTypeId);

	accept();
}

void GuiAddBilliardsTable::SlotBtnCancel() {
	reject();
}