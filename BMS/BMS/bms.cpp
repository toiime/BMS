#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QFile>

#include "bms.h"

#include "./DbModule/DbExecute.h"
#include "./Billiards/GuiAddBilliardsType.h"
#include "./Billiards/GuiAddBilliardsTable.h"
#include "./Billiards/BilliardsManager.h"
#include "./Billiards/GuiBilliardsTable.h"
#include "./Bill/BillManager.h"
#include "./Config/Config.h"

BMS::BMS(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);

	showMaximized();

	_qTimer = new QTimer;
	connect(_qTimer, &QTimer::timeout, this, &BMS::SlotTimeOut);
	_qTimer->start(1000);

	InitTabWidgetTableType();
	InitTabWidgetTable();
	InitBusinessPage();
	InitTabWidgetBill();
	InitConfigUi();

	connect(ui.pushButtonBusiness, &QPushButton::clicked, this, &BMS::SlotBtnBusiness);
	connect(ui.pushButtonSettings, &QPushButton::clicked, this, &BMS::SlotBtnSettings);
	connect(ui.pushButtonBill, &QPushButton::clicked, this, &BMS::SlotBtnBill);
	connect(ui.pushButtonAddBilliardsType, &QPushButton::clicked, this, &BMS::SlotAddBilliardsType);
	connect(ui.pushButtonDeleteTableType, &QPushButton::clicked, this, &BMS::SlotDeleteBilliardsType);
	connect(ui.pushButtonAddBilliards, &QPushButton::clicked, this, &BMS::SlotAddBilliards);
	connect(ui.pushButtonDeleteTable, &QPushButton::clicked, this, &BMS::SlotDeleteBilliardsTable);
	connect(ui.pushButtonEditBallType, &QPushButton::clicked, this, &BMS::SlotEditBilliardsType);
	connect(ui.pushButtonEditBall, &QPushButton::clicked, this, &BMS::SlotEditBilliards);
	connect(ui.pushButtonApply, &QPushButton::clicked, this, &BMS::SlotConfigApply);

	// 显示顺序...
	ui.tabWidget->setCurrentWidget(ui.tabTableType);
	ui.stackedWidgetMainWindow->setCurrentWidget(ui.pageBusiness);

	// InitStyle();
}

BMS::~BMS() {
	_qTimer->stop();
	if (_qTimer) {
		delete _qTimer;
		_qTimer = nullptr;
	}
}

void BMS::InitStyle() {
	// 加载样式表
	// QFile file(":/qssFile/qss/flatwhite.css");
	// QFile file(":/qssFile/qss/lightblue.css");
	QFile file(":/qssFile/qss/psblack.css");
	if (file.open(QFile::ReadOnly)) {
		QString qss = QLatin1String(file.readAll());
		QString paletteColor = qss.mid(20, 7);
		qApp->setPalette(QPalette(QColor(paletteColor)));
		qApp->setStyleSheet(qss);
		file.close();
	}
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

	QVector<BilliardsType*> tableTypes = BilliardsManager::GetInstance()->GetTableTypes();

	for (auto& v : tableTypes) {
		int rowCount = ui.tableWidgetTableType->rowCount();
		ui.tableWidgetTableType->insertRow(rowCount);
		ui.tableWidgetTableType->setItem(rowCount, 0, new QTableWidgetItem(v->GetTypeName()));
		ui.tableWidgetTableType->setItem(rowCount, 1, new QTableWidgetItem(QString::number(v->GetPricePerHour())));
		ui.tableWidgetTableType->item(rowCount, 0)->setData(Qt::UserRole, v->GetUuid());
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

	QVector<Billiards*> billiardsTables = BilliardsManager::GetInstance()->GetBilliardsTables();

	for (auto& v : billiardsTables) {
		int rowCount = ui.tableWidgetTables->rowCount();
		ui.tableWidgetTables->insertRow(rowCount);
		ui.tableWidgetTables->setItem(rowCount, 0, new QTableWidgetItem(QString::number(v->GetTableNum())));
		QString billiardsTypeId = v->GetBilliardsTypeId();
		BilliardsType* billiardsType = BilliardsManager::GetInstance()->FindBilliardsType(billiardsTypeId);
		if (billiardsType) {
			ui.tableWidgetTables->setItem(rowCount, 1, new QTableWidgetItem(billiardsType->GetTypeName()));
		}
		ui.tableWidgetTables->item(rowCount, 0)->setData(Qt::UserRole, v->GetUuid());
	}
}

void BMS::InitTabWidgetBill() {
	QStringList header;
	header << QStringLiteral("球桌编号")
		<< QStringLiteral("球桌类型")
		<< QStringLiteral("小时单价")
		<< QStringLiteral("开局时间")
		<< QStringLiteral("结账时间")
		<< QStringLiteral("消费时长")
		<< QStringLiteral("消费金额");
	// 设置列数...
	ui.tableWidgetBill->setColumnCount(header.size());
	// 设置表头...
	ui.tableWidgetBill->setHorizontalHeaderLabels(header);
	// 去掉垂直表头...
	ui.tableWidgetBill->verticalHeader()->setVisible(false);
	// 设置不可编辑...
	ui.tableWidgetBill->setEditTriggers(QAbstractItemView::NoEditTriggers);
	// 整行选中...
	ui.tableWidgetBill->setSelectionBehavior(QAbstractItemView::SelectRows);
	// 失去焦点 选中没有蓝色的 还挺好看...
	ui.tableWidgetBill->setFocusPolicy(Qt::NoFocus);

	ui.tableWidgetBill->setColumnWidth(3, 188);
	ui.tableWidgetBill->setColumnWidth(4, 188);

	BillManager::GetInstance()->LoadBillsFromDb();
	UpdateBill();
}

void BMS::UpdateBill() {
	ui.tableWidgetBill->setRowCount(0);

	QVector<Bill*> vecBill = BillManager::GetInstance()->GetBills();

	for (auto& v : vecBill) {
		int index = 0;
		int rowCount = ui.tableWidgetBill->rowCount();
		ui.tableWidgetBill->insertRow(rowCount);
		ui.tableWidgetBill->setItem(rowCount, index++, new QTableWidgetItem(v->GetTableNum()));
		ui.tableWidgetBill->setItem(rowCount, index++, new QTableWidgetItem(v->GetTableTypeName()));
		ui.tableWidgetBill->setItem(rowCount, index++, new QTableWidgetItem(QString::number(v->GetPricePerHour())));
		ui.tableWidgetBill->setItem(rowCount, index++, new QTableWidgetItem(v->GetBeginTime()));
		ui.tableWidgetBill->setItem(rowCount, index++, new QTableWidgetItem(v->GetPayTime()));
		ui.tableWidgetBill->setItem(rowCount, index++, new QTableWidgetItem(v->GetDurationTime()));
		ui.tableWidgetBill->setItem(rowCount, index++, new QTableWidgetItem(QString::number(v->GetPayMoney())));
		ui.tableWidgetBill->item(rowCount, 0)->setData(Qt::UserRole, v->GetUuid());
	}
}

void BMS::InitBusinessPage() {

	QGridLayout *qGridLayout = new QGridLayout;
	QVector<Billiards*> vecBilliards = BilliardsManager::GetInstance()->GetBilliardsTables();
	int colCount = 6;
	int index = 0;
	for (auto& v : vecBilliards) {
		GuiBilliardsTable* guiBilliardsTable = new GuiBilliardsTable(this);
		_vecGuiBilliardsTable.push_back(guiBilliardsTable);
		guiBilliardsTable->SetBilliards(*v);
		guiBilliardsTable->UpdateUi();
		qGridLayout->addWidget(guiBilliardsTable, index / colCount, index % colCount);
		++index;
	}
	ui.scrollArea->widget()->setLayout(qGridLayout);
}

void BMS::InitConfigUi() {
	Config::ConfigSpeech configSpeech = Config::GetInstance()->GetConfigSpeech();

	if (configSpeech.powerState_ == 1) {
		ui.radioButtonSpeechOn->setChecked(true);
		ui.radioButtonSpeechOff->setChecked(false);
	}
	else if (configSpeech.powerState_ == 0) {
		ui.radioButtonSpeechOn->setChecked(false);
		ui.radioButtonSpeechOff->setChecked(true);
	}

	ui.horizontalSliderSpeechVolume->setValue(configSpeech.volume_);

	ui.lineEditSpeechContent->setText(configSpeech.content_);
}

void BMS::SlotBtnBusiness() {
	ui.stackedWidgetMainWindow->setCurrentWidget(ui.pageBusiness);
}

void BMS::SlotBtnSettings() {
	ui.stackedWidgetMainWindow->setCurrentWidget(ui.pageSettings);
}

void BMS::SlotBtnBill() {
	ui.stackedWidgetMainWindow->setCurrentWidget(ui.pageBill);
	UpdateBill();
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

void BMS::SlotEditBilliardsType() {
	int rowIndex = ui.tableWidgetTableType->currentRow();
	if (rowIndex < 0) {
		QMessageBox::information(this, "Note", "No Data Selected");
		return;
	}

	QString uuid = ui.tableWidgetTableType->item(rowIndex, 0)->data(Qt::UserRole).toString();
	ui.tableWidgetTableType->setCurrentItem(nullptr);

	BilliardsType* billiardsType = BilliardsManager::GetInstance()->FindBilliardsType(uuid);

	if (billiardsType) {
		GuiAddBilliardsType addTypeDlg(billiardsType);
		if (addTypeDlg.exec() == QDialog::Accepted) {
			UpdateTableType();
		}
	}
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

void BMS::SlotEditBilliards() {
	int rowIndex = ui.tableWidgetTables->currentRow();
	if (rowIndex < 0) {
		QMessageBox::information(this, "Note", "No Data Selected");
		return;
	}

	QString uuid = ui.tableWidgetTables->item(rowIndex, 0)->data(Qt::UserRole).toString();
	ui.tableWidgetTables->setCurrentItem(nullptr);

	Billiards* billiards = BilliardsManager::GetInstance()->FindBilliards(uuid);
	if (!billiards) return;

	GuiAddBilliardsTable addTableDlg(billiards);
	if (addTableDlg.exec() == QDialog::Accepted) {
		UpdateBilliardsTable();
	}
}

void BMS::SlotConfigApply() {
	// speech ...
	int speechPowerState = 0;
	if (ui.radioButtonSpeechOn->isChecked()) speechPowerState = 1;
	int speechVolume = ui.horizontalSliderSpeechVolume->value();
	QString speechContent = ui.lineEditSpeechContent->text();

	Config::ConfigSpeech configSpeech;
	configSpeech.powerState_ = speechPowerState;
	configSpeech.volume_ = speechVolume;
	configSpeech.content_ = speechContent;

	Config::GetInstance()->SetConfigSpeech(configSpeech);
	Config::GetInstance()->SaveConfigFile();

	QMessageBox::information(nullptr, QString("Note"), QString("Success!!!"));
}

void BMS::SlotTimeOut() {
	// 更新球桌信息...
	QDateTime qDateTime = QDateTime::currentDateTime();
	for (auto& v : _vecGuiBilliardsTable) {
		v->UpdateData(qDateTime);
		v->UpdateUi();
	}

	// 更新时间...
	ui.labelCurrentTime->setText(QDateTime::currentDateTime().toString("ddd yyyy-MM-dd hh:mm:ss"));
}
