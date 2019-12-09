#ifndef GUIADDBILLIARDSTABLE_H
#define GUIADDBILLIARDSTABLE_H

#include <QDialog>
#include "ui_GuiAddBilliardsTable.h"

class Billiards;

// 添加球桌
class GuiAddBilliardsTable : public QDialog {
	Q_OBJECT

public:
	GuiAddBilliardsTable(Billiards* billiards = nullptr, QWidget *parent = 0);
	~GuiAddBilliardsTable();

private:
	void InitUi();

private:
	void SlotBtnOk();
	void SlotBtnCancel();

private:
	Ui::GuiAddBilliardsTable ui;

	Billiards* _billiards;
};

#endif // GUIADDBILLIARDSTABLE_H
