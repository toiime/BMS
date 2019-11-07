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
	void UpdateData(QDateTime currentDateTime);

protected:
	void contextMenuEvent(QContextMenuEvent *event);

private:
	void SlotBegin();
	void SlotEnd();

private:
	Ui::GuiBilliardsTable ui;

	Billiards _billiards;
	QString _durationTime;           // 开局时长
	double _money;                   // 消费金额
};

#endif // GUIBILLIARDSTABLE_H
