#ifndef GUIPAY_H
#define GUIPAY_H

#include <QDialog>
#include "ui_GuiPay.h"

#include "./Billiards/Billiards.h"

// 结账页面...
class GuiPay : public QDialog {
	Q_OBJECT

public:
	GuiPay(QWidget *parent = 0);
	~GuiPay();

public:
	void SetBilliards(Billiards billiards);
	void UpdateUi();

private:
	void SlotBtnOk();
	void SlotBtnCancel();

private:
	Ui::GuiPay ui;

	Billiards _billiards;

	QString _durationTime;
	double _payMoney;
};

#endif // GUIPAY_H
