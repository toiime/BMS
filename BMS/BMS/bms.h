#ifndef BMS_H
#define BMS_H

#include <QtWidgets/QWidget>
#include "ui_bms.h"

class BMS : public QWidget
{
	Q_OBJECT

public:
	BMS(QWidget *parent = 0);
	~BMS();

private:
	Ui::BMSClass ui;
};

#endif // BMS_H
