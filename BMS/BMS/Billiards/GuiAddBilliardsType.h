#ifndef GUIADDBILLIARDSTYPE_H
#define GUIADDBILLIARDSTYPE_H

#include <QDialog>
#include "ui_GuiAddBilliardsType.h"

class BilliardsType;

// 添加球桌类型
class GuiAddBilliardsType : public QDialog {
	Q_OBJECT

public:
	GuiAddBilliardsType(BilliardsType* billiardsType = nullptr, QWidget *parent = 0);
	~GuiAddBilliardsType();

private:
	void InitUi();

private:
	void SlotBtnOk();
	void SlotBtnCancel();

private:
	Ui::GuiAddBilliardsType ui;

	BilliardsType* _billiardsType;
};

#endif // GUIADDBILLIARDSTYPE_H
