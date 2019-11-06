#ifndef GUIBILLIARDSTABLE_H
#define GUIBILLIARDSTABLE_H

#include <QWidget>
#include "ui_GuiBilliardsTable.h"

class GuiBilliardsTable : public QWidget {
	Q_OBJECT

public:
	GuiBilliardsTable(QWidget *parent = 0);
	~GuiBilliardsTable();

private:
	Ui::GuiBilliardsTable ui;
};

#endif // GUIBILLIARDSTABLE_H
