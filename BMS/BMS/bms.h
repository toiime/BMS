#ifndef BMS_H
#define BMS_H

#include <QtWidgets/QWidget>
#include "ui_bms.h"

// 台球计费系统高窗口...
class BMS : public QWidget {
	Q_OBJECT

public:
	BMS(QWidget *parent = 0);
	~BMS();

private:
	void SlotBtnBusiness();
	void SlotBtnSettings();

private:
	Ui::BMSClass ui;
};

#endif // BMS_H
