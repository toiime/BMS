#include <QMenu>
#include <QDebug>
#include <QMessageBox>

#include "GuiBilliardsTable.h"
#include "./Bill/GuiPay.h"

GuiBilliardsTable::GuiBilliardsTable(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);

	ui.lineEditTableNum->setEnabled(false);
	ui.lineEditTableType->setEnabled(false);
	ui.lineEditBeginTime->setEnabled(false);
	ui.lineEditPerHour->setEnabled(false);
	ui.lineEditDurationTime->setEnabled(false);
	ui.lineEditMoney->setEnabled(false);

	_qPixmap = QPixmap(":/Pic/Res/billiardsTable.png");
	_qPixmap = _qPixmap.scaled(QSize(250, 130));
	ui.labelPic->setPixmap(_qPixmap);

	_qPixmapPlaying = QPixmap(":/Pic/Res/billiardsTablePlaying.png");
	_qPixmapPlaying = _qPixmapPlaying.scaled(QSize(250, 130));

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
	ui.lineEditPerHour->setText(QString::number(_billiards.GetBilliardsType().GetPricePerHour()));

	if (_billiards.GetIsBegin()) {
		ui.lineEditBeginTime->setText(_billiards.GetBeginTime().toString("yyyy-MM-dd hh:mm:ss"));
		ui.lineEditDurationTime->setText(_durationTime);
		ui.lineEditMoney->setText(QString::number(_money));
	}
	else {
		ui.lineEditBeginTime->setText(QStringLiteral("未开局"));
		ui.lineEditDurationTime->setText(QStringLiteral("未开局"));
		ui.lineEditMoney->setText(QStringLiteral("未开局"));
	}
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
	if (_billiards.GetIsBegin()) {
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("本桌已经开局!"));
		return;
	}

	ui.labelPic->setPixmap(_qPixmapPlaying);
	_billiards.SetBeginTime(QDateTime::currentDateTime());
	_billiards.SetIsBegin(true);
	UpdateUi();
}

void GuiBilliardsTable::SlotEnd() {

	_billiards.SetEndTime(QDateTime::currentDateTime());

	GuiPay guiPay;
	guiPay.SetBilliards(_billiards);
	guiPay.UpdateUi();
	guiPay.exec();

	ui.labelPic->setPixmap(_qPixmap);
	_billiards.SetIsBegin(false);
}
