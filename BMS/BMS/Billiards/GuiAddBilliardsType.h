#ifndef GUIADDBILLIARDSTYPE_H
#define GUIADDBILLIARDSTYPE_H

#include <QDialog>
#include "ui_GuiAddBilliardsType.h"

// 添加球桌类型
class GuiAddBilliardsType : public QDialog {
	Q_OBJECT

public:
	GuiAddBilliardsType(QWidget *parent = 0);
	~GuiAddBilliardsType();

private:
	void SlotBtnOk();
	void SlotBtnCancel();

private:
	Ui::GuiAddBilliardsType ui;
};

#endif // GUIADDBILLIARDSTYPE_H
