#include <QUuid>

#include "../Bill/BillManager.h"
#include "../DbModule/DbExecute.h"
#include "../Speech/Speech.h"
#include "../Config/Config.h"

// 在此处初始化
BillManager* BillManager::_instance = new BillManager();
BillManager* BillManager::GetInstance() {
    return _instance;
}

BillManager::BillManager() {
    _speech = nullptr;
}

BillManager::~BillManager() {
    if (_speech) {
        delete _speech;
        _speech = nullptr;
    }
}

void BillManager::LoadBillsFromDb() {
    QVector<BillDef> vecBillDef;
    DbExecute::QueryFromBill(vecBillDef);

    for (auto& v : vecBillDef) {
        Bill* bill = new Bill;
        bill->SetUuid(v.uuid_);
        bill->SetTableNum(v.tableNum_);
        bill->SetTableTypeName(v.tableTypeName_);
        bill->SetPricePerHour(v.pricePerHour_);
        bill->SetBeginTime(v.beginTime_);
        bill->SetPayTime(v.payTime_);
        bill->SetDurationTime(v.durationTime_);
        bill->SetPayMoney(v.payMoney_);
        _vecBill.push_front(bill);
    }
}

Bill* BillManager::CreateBill() {
    Bill* bill = new Bill;

    QUuid id = QUuid::createUuid();
    QString strId = id.toString();

    bill->SetUuid(strId);

    _vecBill.push_front(bill);

    BillDef billDef;
    billDef.uuid_ = bill->GetUuid();
    billDef.tableNum_ = bill->GetTableNum();
    billDef.tableTypeName_ = bill->GetTableTypeName();
    billDef.pricePerHour_ = bill->GetPricePerHour();
    billDef.beginTime_ = bill->GetBeginTime();
    billDef.payTime_ = bill->GetPayTime();
    billDef.durationTime_ = bill->GetDurationTime();
    billDef.payMoney_ = bill->GetPayMoney();
    DbExecute::InsertToBill(billDef);

    return bill;
}

void BillManager::UpdateBill(Bill* bill) {
    if (!bill) return;

    for (auto& v : _vecBill) {
        if (v->GetUuid() == bill->GetUuid()) {
            *v = *bill;
        }
    }

    BillDef billDef;
    billDef.uuid_ = bill->GetUuid();
    billDef.tableNum_ = bill->GetTableNum();
    billDef.tableTypeName_ = bill->GetTableTypeName();
    billDef.pricePerHour_ = bill->GetPricePerHour();
    billDef.beginTime_ = bill->GetBeginTime();
    billDef.payTime_ = bill->GetPayTime();
    billDef.durationTime_ = bill->GetDurationTime();
    billDef.payMoney_ = bill->GetPayMoney();
    DbExecute::UpdateToBill(billDef);

    SayBill(bill);
}

void BillManager::DeleteBill(QString id) {
    for (auto iter = _vecBill.begin(); iter != _vecBill.end();) {
        if ((*iter)->GetUuid() == id) {
            iter = _vecBill.erase(iter);
        }
        else {
            ++iter;
        }
    }

    QString sqlWhere(QString("where uuid = '%1'").arg(id));
    DbExecute::DeleteFromBill(sqlWhere);
}

QVector<Bill*> BillManager::GetBills() {
    return _vecBill;
}

void BillManager::SayBill(Bill* bill) {
    Config::ConfigSpeech configSpeech;
    configSpeech = Config::GetInstance()->GetConfigSpeech();

    if (configSpeech.powerState_ != 1) return;

    QString content;
    content = configSpeech.content_;
    content.replace("[num]", bill->GetTableNum());

    QString durationTime = bill->GetDurationTime(); // 00:00:00
    QStringList timeList = durationTime.split(":");
    QString time = QStringLiteral("%1小时%2分钟")
        .arg(timeList.at(0).toInt())
        .arg(timeList.at(1).toInt());

    content.replace("[time]", time);
    content.replace("[money]", QString::number(bill->GetPayMoney(), 'f', 1));

    if (!_speech) _speech = new Speech;
    _speech->SetVolume(configSpeech.volume_ / 100.0);
    _speech->Say(content);
}