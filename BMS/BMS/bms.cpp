#include <QDebug>

#include "bms.h"

#include "./DbModule/DbExecute.h"
#include "./Billiards/GuiAddBilliardsType.h"
#include "./Billiards/GuiAddBilliardsTable.h"
#include "./Billiards/BilliardsManager.h"

BMS::BMS(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);

	InitTabWidgetTableType();

	connect(ui.pushButtonBusiness, &QPushButton::clicked, this, &BMS::SlotBtnBusiness);
	connect(ui.pushButtonSettings, &QPushButton::clicked, this, &BMS::SlotBtnSettings);
	connect(ui.pushButtonAddBilliardsType, &QPushButton::clicked, this, &BMS::SlotAddBilliardsType);
	connect(ui.pushButtonDeleteTableType, &QPushButton::clicked, this, &BMS::SlotDeleteBilliardsType);
	connect(ui.pushButtonAddBilliards, &QPushButton::clicked, this, &BMS::SlotAddBilliards);
}

BMS::~BMS() {

}

void BMS::InitTabWidgetTableType() {
	QStringList header;
	header << QStringLiteral("球桌类型") << QStringLiteral("小时单价");
	// 设置列数...
	ui.tableWidgetTableType->setColumnCount(header.size());
	// 设置表头...
	ui.tableWidgetTableType->setHorizontalHeaderLabels(header);
	// 去掉垂直表头...
	ui.tableWidgetTableType->verticalHeader()->setVisible(false);
	// 设置不可编辑...
	ui.tableWidgetTableType->setEditTriggers(QAbstractItemView::NoEditTriggers);
	// 整行选中...
	ui.tableWidgetTableType->setSelectionBehavior(QAbstractItemView::SelectRows);
	// 失去焦点 选中没有蓝色的 还挺好看...
	ui.tableWidgetTableType->setFocusPolicy(Qt::NoFocus);

	BilliardsManager::GetInstance()->LoadTableTypeFromDb();
	UpdateTableType();
}

void BMS::UpdateTableType() {
	ui.tableWidgetTableType->setRowCount(0);

	QVector<BilliardsType> tableTypes = BilliardsManager::GetInstance()->GetTableTypes();

	for (auto& v : tableTypes) {
		int row_count = ui.tableWidgetTableType->rowCount();
		ui.tableWidgetTableType->insertRow(row_count);
		ui.tableWidgetTableType->setItem(row_count, 0, new QTableWidgetItem(v.GetTypeName()));
		ui.tableWidgetTableType->setItem(row_count, 1, new QTableWidgetItem(QString::number(v.GetPricePerHour())));
	}
}

void BMS::SlotBtnBusiness() {
	ui.stackedWidgetMainWindow->setCurrentIndex(0);
}

void BMS::SlotBtnSettings() {
	ui.stackedWidgetMainWindow->setCurrentIndex(1);
}

void BMS::SlotAddBilliardsType() {
	GuiAddBilliardsType addTypeDlg;

	if (addTypeDlg.exec() == QDialog::Accepted) {
		UpdateTableType();
	}
}

void BMS::SlotDeleteBilliardsType() {
	// todo ...
}

void BMS::SlotAddBilliards() {
	GuiAddBilliardsTable addTableDlg;

	if (addTableDlg.exec() == QDialog::Accepted) {

	}
}
