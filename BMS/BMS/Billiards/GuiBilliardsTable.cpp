#include "GuiBilliardsTable.h"

GuiBilliardsTable::GuiBilliardsTable(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);

	QPixmap pixmap = QPixmap(":/Pic/Res/billiardsTable.png");
	pixmap = pixmap.scaled(QSize(250, 130));
	ui.labelPic->setPixmap(pixmap);
}

GuiBilliardsTable::~GuiBilliardsTable() {

}

void GuiBilliardsTable::SetBilliards(Billiards& billiards) {
	_billiards = billiards;
}

void GuiBilliardsTable::UpdateUi() {
	ui.lineEditTableNum->setText(QString::number(_billiards.GetTableNum()));
	ui.lineEditTableType->setText(_billiards.GetBilliardsType().GetTypeName());
	ui.lineEditBeginTime->setText(_billiards.GetBeginTime().toString("yyyy-MM-dd hh:mm:ss"));
	ui.lineEditPerHour->setText(QString::number(_billiards.GetBilliardsType().GetPricePerHour()));
	ui.lineEditDurationTime->setText(QString::number(0.0));
	ui.lineEditMoney->setText(QString::number(0.0));
}
