#include <QMenu>
#include <QDebug>
#include "GuiBilliardsTable.h"

GuiBilliardsTable::GuiBilliardsTable(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);

	QPixmap pixmap = QPixmap(":/Pic/Res/billiardsTable.png");
	pixmap = pixmap.scaled(QSize(250, 130));
	ui.labelPic->setPixmap(pixmap);

	_money = 0.0;                    // 消费金额
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
	ui.lineEditDurationTime->setText(_durationTime);
	ui.lineEditMoney->setText(QString::number(_money));
}

void GuiBilliardsTable::UpdateData(QDateTime currentDateTime) {
	int mSecond = currentDateTime.toMSecsSinceEpoch() - _billiards.GetBeginTime().toMSecsSinceEpoch();
	_durationTime = QDateTime::fromMSecsSinceEpoch(mSecond).toUTC().toString("hh:mm:ss");
	_money = mSecond * 0.001 / 3600.0 * _billiards.GetBilliardsType().GetPricePerHour();
}

void GuiBilliardsTable::contextMenuEvent(QContextMenuEvent *event) {
	QMenu *menu = new QMenu(this);
	menu->addAction(QStringLiteral("开局"), this, &GuiBilliardsTable::SlotBegin);
	menu->addAction(QStringLiteral("结账"), this, &GuiBilliardsTable::SlotEnd);
	menu->move(cursor().pos());
	menu->show();
}

void GuiBilliardsTable::SlotBegin() {
	qDebug() << "GuiBilliardsTable::SlotBegin";
	_billiards.SetBeginTime(QDateTime::currentDateTime());
	_billiards.SetIsBegin(true);
	UpdateUi();
}

void GuiBilliardsTable::SlotEnd() {
	qDebug() << "GuiBilliardsTable::SlotEnd";
}
