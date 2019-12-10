#include "GuiPay.h"
#include "../Global/GlobalDefine.h"
#include "../Bill/Bill.h"
#include "../Bill/BillManager.h"
#include "../Billiards/BilliardsManager.h"

GuiPay::GuiPay(QWidget *parent)
	: QDialog(parent) {
	ui.setupUi(this);

	_payMoney = 0.0;

	ui.lineEditTableNum->setEnabled(false);
	ui.lineEditTableType->setEnabled(false);
	ui.lineEditPricePerHour->setEnabled(false);
	ui.lineEditBeginTime->setEnabled(false);
	ui.lineEditPayTime->setEnabled(false);
	ui.lineEditDurationTime->setEnabled(false);
	ui.lineEditPayMoney->setEnabled(false);

	connect(ui.pushButtonOk, &QPushButton::clicked, this, &GuiPay::SlotBtnOk);
	connect(ui.pushButtonCancel, &QPushButton::clicked, this, &GuiPay::SlotBtnCancel);
}

GuiPay::~GuiPay() {

}

void GuiPay::SetBilliards(Billiards billiards) {
	_billiards = billiards;
}

void GuiPay::UpdateUi() {
	QString billiardsTypeId = _billiards.GetBilliardsTypeId();
	BilliardsType* billiardsType = BilliardsManager::GetInstance()->FindBilliardsType(billiardsTypeId);

	ui.lineEditTableNum->setText(QString::number(_billiards.GetTableNum()));
	if (billiardsType) {
		ui.lineEditTableType->setText(billiardsType->GetTypeName());
		ui.lineEditPricePerHour->setText(QString::number(billiardsType->GetPricePerHour()));
	}
	ui.lineEditBeginTime->setText(_billiards.GetBeginTime());
	ui.lineEditPayTime->setText(_billiards.GetEndTime());

	QDateTime currentDateTime = QDateTime::currentDateTime();
	int mSecond = currentDateTime.toMSecsSinceEpoch()
		- QDateTime::fromString(_billiards.GetBeginTime(), gTimeFormat).toMSecsSinceEpoch();

	_durationTime = QDateTime::fromMSecsSinceEpoch(mSecond).toUTC().toString("hh:mm:ss");
	if (billiardsType) {
		_payMoney = mSecond * 0.001 / 3600.0 * billiardsType->GetPricePerHour();
	}

	ui.lineEditDurationTime->setText(_durationTime);
	ui.lineEditPayMoney->setText(QString::number(_payMoney));
}

void GuiPay::SlotBtnOk() {
	QString billiardsTypeId = _billiards.GetBilliardsTypeId();
	BilliardsType* billiardsType = BilliardsManager::GetInstance()->FindBilliardsType(billiardsTypeId);

	// 创建账单...
	Bill* bill = BillManager::GetInstance()->CreateBill();
	bill->SetTableNum(QString::number(_billiards.GetTableNum()));
	if (billiardsType) {
		bill->SetTableTypeName(billiardsType->GetTypeName());
		bill->SetPricePerHour(billiardsType->GetPricePerHour());
	}
	bill->SetBeginTime(_billiards.GetBeginTime());
	bill->SetPayTime(_billiards.GetEndTime());
	bill->SetDurationTime(_durationTime);
	bill->SetPayMoney(_payMoney);
	BillManager::GetInstance()->UpdateBill(bill);

	accept();
}

void GuiPay::SlotBtnCancel() {
	reject();
}
