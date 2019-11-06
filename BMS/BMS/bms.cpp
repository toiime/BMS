#include <QDebug>
#include <QMessageBox>

#include "bms.h"

#include "./DbModule/DbExecute.h"
#include "./Billiards/GuiAddBilliardsType.h"
#include "./Billiards/GuiAddBilliardsTable.h"
#include "./Billiards/BilliardsManager.h"
#include "./Billiards/GuiBilliardsTable.h"

BMS::BMS(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);

	InitTabWidgetTableType();
	InitTabWidgetTable();
	InitBusinessPage();


	connect(ui.pushButtonBusiness, &QPushButton::clicked, this, &BMS::SlotBtnBusiness);
	connect(ui.pushButtonSettings, &QPushButton::clicked, this, &BMS::SlotBtnSettings);
	connect(ui.pushButtonAddBilliardsType, &QPushButton::clicked, this, &BMS::SlotAddBilliardsType);
	connect(ui.pushButtonDeleteTableType, &QPushButton::clicked, this, &BMS::SlotDeleteBilliardsType);
	connect(ui.pushButtonAddBilliards, &QPushButton::clicked, this, &BMS::SlotAddBilliards);
	connect(ui.pushButtonDeleteTable, &QPushButton::clicked, this, &BMS::SlotDeleteBilliardsTable);
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
		int rowCount = ui.tableWidgetTableType->rowCount();
		ui.tableWidgetTableType->insertRow(rowCount);
		ui.tableWidgetTableType->setItem(rowCount, 0, new QTableWidgetItem(v.GetTypeName()));
		ui.tableWidgetTableType->setItem(rowCount, 1, new QTableWidgetItem(QString::number(v.GetPricePerHour())));
		ui.tableWidgetTableType->item(rowCount, 0)->setData(Qt::UserRole, v.GetUuid());
	}
}

void BMS::InitTabWidgetTable() {
	QStringList header;
	header << QStringLiteral("球桌编号") << QStringLiteral("球桌类型");
	// 设置列数...
	ui.tableWidgetTables->setColumnCount(header.size());
	// 设置表头...
	ui.tableWidgetTables->setHorizontalHeaderLabels(header);
	// 去掉垂直表头...
	ui.tableWidgetTables->verticalHeader()->setVisible(false);
	// 设置不可编辑...
	ui.tableWidgetTables->setEditTriggers(QAbstractItemView::NoEditTriggers);
	// 整行选中...
	ui.tableWidgetTables->setSelectionBehavior(QAbstractItemView::SelectRows);
	// 失去焦点 选中没有蓝色的 还挺好看...
	ui.tableWidgetTables->setFocusPolicy(Qt::NoFocus);

	BilliardsManager::GetInstance()->LoadTableFromDb();
	UpdateBilliardsTable();
}

void BMS::UpdateBilliardsTable() {
	ui.tableWidgetTables->setRowCount(0);

	QVector<Billiards> billiardsTables = BilliardsManager::GetInstance()->GetBilliardsTables();

	for (auto& v : billiardsTables) {
		int rowCount = ui.tableWidgetTables->rowCount();
		ui.tableWidgetTables->insertRow(rowCount);
		ui.tableWidgetTables->setItem(rowCount, 0, new QTableWidgetItem(QString::number(v.GetTableNum())));
		ui.tableWidgetTables->setItem(rowCount, 1, new QTableWidgetItem(v.GetBilliardsType().GetTypeName()));
		ui.tableWidgetTables->item(rowCount, 0)->setData(Qt::UserRole, v.GetUuid());
	}
}

void BMS::InitBusinessPage() {
	QGridLayout* qGridLayout = dynamic_cast<QGridLayout*>(ui.widgetBusiness->layout());
	if (!qGridLayout) return;

	QVector<Billiards> vecBilliards = BilliardsManager::GetInstance()->GetBilliardsTables();
	for (auto& v : vecBilliards) {
		GuiBilliardsTable* guiBilliardsTable = new GuiBilliardsTable(this);
		qGridLayout->addWidget(guiBilliardsTable);
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
	int rowIndex = ui.tableWidgetTableType->currentRow();
	if (rowIndex < 0) {
		QMessageBox::information(this, "Note", "No Data Selected");
		return;
	}

	int rv = QMessageBox::question(this, QString("Note"), QStringLiteral("确定要删除吗?")
		, QStringLiteral("确定"), QStringLiteral("取消"));
	if (rv != 0) {
		return;
	}

	QString uuid = ui.tableWidgetTableType->item(rowIndex, 0)->data(Qt::UserRole).toString();
	ui.tableWidgetTableType->removeRow(rowIndex);
	ui.tableWidgetTableType->setCurrentItem(nullptr);

	BilliardsManager::GetInstance()->DeleteTableType(uuid);
}

void BMS::SlotAddBilliards() {
	GuiAddBilliardsTable addTableDlg;

	if (addTableDlg.exec() == QDialog::Accepted) {
		UpdateBilliardsTable();
	}
}

void BMS::SlotDeleteBilliardsTable() {
	int rowIndex = ui.tableWidgetTables->currentRow();
	if (rowIndex < 0) {
		QMessageBox::information(this, "Note", "No Data Selected");
		return;
	}

	int rv = QMessageBox::question(this, QString("Note"), QStringLiteral("确定要删除吗?")
		, QStringLiteral("确定"), QStringLiteral("取消"));
	if (rv != 0) {
		return;
	}

	QString uuid = ui.tableWidgetTables->item(rowIndex, 0)->data(Qt::UserRole).toString();
	ui.tableWidgetTables->removeRow(rowIndex);
	ui.tableWidgetTables->setCurrentItem(nullptr);

	BilliardsManager::GetInstance()->DeleteBilliardsTable(uuid);
}
