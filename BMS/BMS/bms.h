#ifndef BMS_H_
#define BMS_H_

#include <QtWidgets/QWidget>
#include "ui_bms.h"

// 台球计费系统高窗口...
class BMS : public QWidget {
	Q_OBJECT

public:
	BMS(QWidget *parent = 0);
	~BMS();

private:
	void InitTabWidgetTableType();
	void UpdateTableType();

	void InitTabWidgetTable();
	void UpdateBilliardsTable();

	void InitBusinessPage();

private:
	void SlotBtnBusiness();         // 营业
	void SlotBtnSettings();         // 设置
	void SlotAddBilliardsType();    // 添加球桌类型
	void SlotDeleteBilliardsType(); // 删除球桌类型
	void SlotAddBilliards();        // 添加球桌
	void SlotDeleteBilliardsTable();// 删除球桌


private:
	Ui::BMSClass ui;
};

#endif // BMS_H_
