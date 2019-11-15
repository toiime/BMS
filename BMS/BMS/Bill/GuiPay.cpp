#include "GuiPay.h"
#include "../Global/GlobalDefine.h"
#include "../Bill/Bill.h"
#include "../Bill/BillManager.h"

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
	ui.lineEditTableNum->setText(QString::number(_billiards.GetTableNum()));
	ui.lineEditTableType->setText(_billiards.GetBilliardsType().GetTypeName());
	ui.lineEditPricePerHour->setText(QString::number(_billiards.GetBilliardsType().GetPricePerHour()));
	ui.lineEditBeginTime->setText(_billiards.GetBeginTime());
	ui.lineEditPayTime->setText(_billiards.GetEndTime());

	QDateTime currentDateTime = QDateTime::currentDateTime();
	int mSecond = currentDateTime.toMSecsSinceEpoch()
		- QDateTime::fromString(_billiards.GetBeginTime(), gTimeFormat).toMSecsSinceEpoch();

	_durationTime = QDateTime::fromMSecsSinceEpoch(mSecond).toUTC().toString("hh:mm:ss");
	_payMoney = mSecond * 0.001 / 3600.0 * _billiards.GetBilliardsType().GetPricePerHour();

	ui.lineEditDurationTime->setText(_durationTime);
	ui.lineEditPayMoney->setText(QString::number(_payMoney));
}

void GuiPay::SlotBtnOk() {

	// 创建账单...
	Bill bill;
	bill.SetTableNum(QString::number(_billiards.GetTableNum()));
	bill.SetTableType(_billiards.GetBilliardsType().GetTypeName());
	bill.SetPricePerHour(_billiards.GetBilliardsType().GetPricePerHour());
	bill.SetBeginTime(_billiards.GetBeginTime());
	bill.SetPayTime(_billiards.GetEndTime());
	bill.SetDurationTime(_durationTime);
	bill.SetPayMoney(_payMoney);
	BillManager::GetInstance()->AddBill(bill);

	accept();
}

void GuiPay::SlotBtnCancel() {
	reject();
}
