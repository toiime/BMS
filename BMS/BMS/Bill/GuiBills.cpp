#include "GuiBills.h"
#include "ui_guibills.h"
#include "./Bill/BillManager.h"

GuiBills::GuiBills(QWidget * parent) : QWidget(parent) {
    ui = new Ui::GuiBills();
    ui->setupUi(this);

    InitTabWidgetBill();
}

GuiBills::~GuiBills() {
    delete ui;
}

void GuiBills::InitTabWidgetBill() {
    QStringList header;
    header << QStringLiteral("球桌编号")
        << QStringLiteral("球桌类型")
        << QStringLiteral("小时单价")
        << QStringLiteral("开局时间")
        << QStringLiteral("结账时间")
        << QStringLiteral("消费时长")
        << QStringLiteral("消费金额");
    // 设置列数...
    ui->tableWidgetBill->setColumnCount(header.size());
    // 设置表头...
    ui->tableWidgetBill->setHorizontalHeaderLabels(header);
    // 去掉垂直表头...
    ui->tableWidgetBill->verticalHeader()->setVisible(false);
    // 设置不可编辑...
    ui->tableWidgetBill->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 整行选中...
    ui->tableWidgetBill->setSelectionBehavior(QAbstractItemView::SelectRows);
    // 失去焦点 选中没有蓝色的 还挺好看...
    ui->tableWidgetBill->setFocusPolicy(Qt::NoFocus);

    ui->tableWidgetBill->setColumnWidth(3, 188);
    ui->tableWidgetBill->setColumnWidth(4, 188);

    BillManager::GetInstance()->LoadBillsFromDb();
    UpdateBill();
}

void GuiBills::UpdateBill() {
    ui->tableWidgetBill->setRowCount(0);

    QVector<Bill*> vecBill = BillManager::GetInstance()->GetBills();

    for (auto& v : vecBill) {
        int index = 0;
        int rowCount = ui->tableWidgetBill->rowCount();
        ui->tableWidgetBill->insertRow(rowCount);
        ui->tableWidgetBill->setItem(rowCount, index++, new QTableWidgetItem(v->GetTableNum()));
        ui->tableWidgetBill->setItem(rowCount, index++, new QTableWidgetItem(v->GetTableTypeName()));
        ui->tableWidgetBill->setItem(rowCount, index++, new QTableWidgetItem(QString::number(v->GetPricePerHour())));
        ui->tableWidgetBill->setItem(rowCount, index++, new QTableWidgetItem(v->GetBeginTime()));
        ui->tableWidgetBill->setItem(rowCount, index++, new QTableWidgetItem(v->GetPayTime()));
        ui->tableWidgetBill->setItem(rowCount, index++, new QTableWidgetItem(v->GetDurationTime()));
        ui->tableWidgetBill->setItem(rowCount, index++, new QTableWidgetItem(QString::number(v->GetPayMoney(), 'f', 1)));
        ui->tableWidgetBill->item(rowCount, 0)->setData(Qt::UserRole, v->GetUuid());

        // 设置对齐方式...
        ui->tableWidgetBill->item(rowCount, 6)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        for (int i = 0; i < 6; ++i) {
            ui->tableWidgetBill->item(rowCount, i)->setTextAlignment(Qt::AlignCenter);
        }
    }
}