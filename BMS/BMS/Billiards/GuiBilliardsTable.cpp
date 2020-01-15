#include <QDebug>

#include "GuiBilliardsTable.h"
#include "../Bill/GuiPay.h"
#include "../Global/GlobalDefine.h"
#include "../DbModule/DbExecute.h"
#include "../Billiards/BilliardsManager.h"
#include "../CustomWidget/MsgHelper.h"


GuiBilliardsTable::GuiBilliardsTable(QWidget *parent)
    : QWidget(parent) {
    ui.setupUi(this);

    ui.lineEditTableNum->setEnabled(false);
    ui.lineEditTableType->setEnabled(false);
    ui.lineEditBeginTime->setEnabled(false);
    ui.lineEditPerHour->setEnabled(false);
    ui.lineEditDurationTime->setEnabled(false);
    ui.lineEditMoney->setEnabled(false);

    _menu = new QMenu;
    _menu->addAction(QStringLiteral("开局"), this, &GuiBilliardsTable::SlotBegin);
    _menu->addAction(QStringLiteral("结账"), this, &GuiBilliardsTable::SlotEnd);

    _qPixmap = QPixmap(":/Pic/Res/billiardsTable.png");
    _qPixmap = _qPixmap.scaled(QSize(250, 130));

    _qPixmapPlaying = QPixmap(":/Pic/Res/billiardsTablePlaying.png");
    _qPixmapPlaying = _qPixmapPlaying.scaled(QSize(250, 130));

    _money = 0.0;                    // 消费金额
}

GuiBilliardsTable::~GuiBilliardsTable() {
    if (_menu) {
        delete _menu;
        _menu = nullptr;
    }
}

void GuiBilliardsTable::SetBilliards(Billiards& billiards) {
    _billiards = billiards;
}

void GuiBilliardsTable::UpdateUi() {
    QString billiardsTypeId = _billiards.GetBilliardsTypeId();
    BilliardsType* billiardsType = BilliardsManager::GetInstance()->FindBilliardsType(billiardsTypeId);

    ui.lineEditTableNum->setText(QString::number(_billiards.GetTableNum()));
    if (billiardsType) {
        ui.lineEditTableType->setText(billiardsType->GetTypeName());
        ui.lineEditPerHour->setText(QString::number(billiardsType->GetPricePerHour()));
    }

    if (_billiards.GetIsBegin()) {
        ui.lineEditBeginTime->setText(_billiards.GetBeginTime());
        ui.lineEditDurationTime->setText(_durationTime);
        ui.lineEditMoney->setText(QString::number(_money, 'f', 1));
        ui.labelPic->setPixmap(_qPixmapPlaying);
    }
    else {
        ui.lineEditBeginTime->setText(QStringLiteral("未开局"));
        ui.lineEditDurationTime->setText(QStringLiteral("未开局"));
        ui.lineEditMoney->setText(QStringLiteral("未开局"));
        ui.labelPic->setPixmap(_qPixmap);
    }
}

void GuiBilliardsTable::UpdateData(QDateTime currentDateTime) {
    QString billiardsTypeId = _billiards.GetBilliardsTypeId();
    BilliardsType* billiardsType = BilliardsManager::GetInstance()->FindBilliardsType(billiardsTypeId);

    qint64 mSecond = currentDateTime.toMSecsSinceEpoch()
        - QDateTime::fromString(_billiards.GetBeginTime(), gTimeFormat).toMSecsSinceEpoch();
    _durationTime = QDateTime::fromMSecsSinceEpoch(mSecond).toUTC().toString("hh:mm:ss");
    if (billiardsType) {
        _money = mSecond * 0.001 / 3600.0 * billiardsType->GetPricePerHour();
    }
}

void GuiBilliardsTable::contextMenuEvent(QContextMenuEvent *event) {
    _menu->exec(QCursor::pos());
}

void GuiBilliardsTable::SlotBegin() {
    if (_billiards.GetIsBegin()) {
        MsgHelper::MsgInformation(this, QStringLiteral("提示"), QStringLiteral("本桌已经开局!"));
        return;
    }

    ui.labelPic->setPixmap(_qPixmapPlaying);
    _billiards.SetBeginTime(QDateTime::currentDateTime().toString(gTimeFormat));
    _billiards.SetIsBegin(true);
    UpdateUi();

    // 更新数据库信息...
    BilliardsTableDef billiardsTableDef;
    billiardsTableDef.uuid_ = _billiards.GetUuid();
    billiardsTableDef.tableNum_ = QString::number(_billiards.GetTableNum());
    billiardsTableDef.billiardsTypeId_ = _billiards.GetBilliardsTypeId();
    billiardsTableDef.beginTime_ = _billiards.GetBeginTime();
    billiardsTableDef.endTime_ = _billiards.GetEndTime();
    if (_billiards.GetIsBegin()) {
        billiardsTableDef.isBegin_ = "1";
    }
    else {
        billiardsTableDef.isBegin_ = "0";
    }
    DbExecute::UpdateToBilliardsTable(billiardsTableDef);
}

void GuiBilliardsTable::SlotEnd() {

    if (!_billiards.GetIsBegin()) {
        MsgHelper::MsgInformation(this, QStringLiteral("提示"), QStringLiteral("本桌未开局!"));
        return;
    }

    _billiards.SetEndTime(QDateTime::currentDateTime().toString(gTimeFormat));

    GuiPay guiPay;
    guiPay.SetBilliards(_billiards);
    guiPay.UpdateUi();
    int rv = guiPay.exec();

    if (rv != QDialog::Accepted) {
        return;
    }

    ui.labelPic->setPixmap(_qPixmap);
    _billiards.SetIsBegin(false);

    // 更新数据库信息...
    BilliardsTableDef billiardsTableDef;
    billiardsTableDef.uuid_ = _billiards.GetUuid();
    billiardsTableDef.tableNum_ = QString::number(_billiards.GetTableNum());
    billiardsTableDef.billiardsTypeId_ = _billiards.GetBilliardsTypeId();
    billiardsTableDef.beginTime_ = _billiards.GetBeginTime();
    billiardsTableDef.endTime_ = _billiards.GetEndTime();
    if (_billiards.GetIsBegin()) {
        billiardsTableDef.isBegin_ = "1";
    }
    else {
        billiardsTableDef.isBegin_ = "0";
    }
    DbExecute::UpdateToBilliardsTable(billiardsTableDef);
}
