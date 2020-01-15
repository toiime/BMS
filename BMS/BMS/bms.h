#ifndef BMS_H_
#define BMS_H_

#include <QtWidgets/QWidget>
#include "ui_bms.h"

class GuiBilliardsTable;

// 台球计费系统主窗口...
class BMS : public QWidget {
    Q_OBJECT

public:
    BMS(QWidget *parent = 0);
    ~BMS();

private:

    void InitStyle();

    void InitTabWidgetTableType();    // 初始化球桌类型列表
    void UpdateTableType();           // 更新球桌类型列表

    void InitTabWidgetTable();        // 初始化球桌列表
    void UpdateBilliardsTable();      // 更新球桌列表

    void InitBusinessPage();          // 初始化球桌界面...

    void InitConfigUi();              // 初始化配制界面...

private:
    void SlotBtnBusiness();         // 营业
    void SlotBtnSettings();         // 设置
    void SlotBtnBill();             // 历史账单

    void SlotAddBilliardsType();    // 添加球桌类型
    void SlotDeleteBilliardsType(); // 删除球桌类型
    void SlotEditBilliardsType();   // 编辑球桌类型...

    void SlotAddBilliards();        // 添加球桌
    void SlotDeleteBilliardsTable();// 删除球桌
    void SlotEditBilliards();       // 编辑球桌...

    void SlotConfigApply();         // 配制文件应用...

    void SlotTimeOut();             // 定时器

private:
    Ui::BMSClass ui;

    QTimer* _qTimer;
    QVector<GuiBilliardsTable*> _vecGuiBilliardsTable;
};

#endif // BMS_H_
