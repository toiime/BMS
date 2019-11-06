#ifndef GUIBILLIARDSTABLE_H
#define GUIBILLIARDSTABLE_H

#include <QWidget>
#include "ui_GuiBilliardsTable.h"
#include "./Billiards/Billiards.h"

class GuiBilliardsTable : public QWidget {
	Q_OBJECT

public:
	GuiBilliardsTable(QWidget *parent = 0);
	~GuiBilliardsTable();

public:
	void SetBilliards(Billiards& billiards);
	void UpdateUi();

private:
	Ui::GuiBilliardsTable ui;

	Billiards _billiards;
};

#endif // GUIBILLIARDSTABLE_H
