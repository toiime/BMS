#ifndef GUIADDBILLIARDSTABLE_H
#define GUIADDBILLIARDSTABLE_H

#include <QDialog>
#include "ui_GuiAddBilliardsTable.h"

// 添加球桌
class GuiAddBilliardsTable : public QDialog {
	Q_OBJECT

public:
	GuiAddBilliardsTable(QWidget *parent = 0);
	~GuiAddBilliardsTable();

private:
	void SlotBtnOk();
	void SlotBtnCancel();

private:
	Ui::GuiAddBilliardsTable ui;
};

#endif // GUIADDBILLIARDSTABLE_H
