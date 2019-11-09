#include "GuiPay.h"

GuiPay::GuiPay(QWidget *parent)
	: QDialog(parent) {
	ui.setupUi(this);

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
	ui.lineEditBeginTime->setText(_billiards.GetBeginTime().toString("yyyy-MM-dd hh:mm:ss"));
	ui.lineEditPayTime->setText(_billiards.GetEndTime().toString("yyyy-MM-dd hh:mm:ss"));

	QDateTime currentDateTime = QDateTime::currentDateTime();
	int mSecond = currentDateTime.toMSecsSinceEpoch() - _billiards.GetBeginTime().toMSecsSinceEpoch();

	ui.lineEditDurationTime->setText(QDateTime::fromMSecsSinceEpoch(mSecond).toUTC().toString("hh:mm:ss"));
	ui.lineEditPayMoney->setText(QString::number(mSecond * 0.001 / 3600.0 * _billiards.GetBilliardsType().GetPricePerHour()));
}

void GuiPay::SlotBtnOk() {
	close();
}

void GuiPay::SlotBtnCancel() {
	close();
}
