#pragma once

#include <QWidget>
#include <QMenu>

namespace Ui { class GuiBills; }

class GuiBills : public QWidget {
    Q_OBJECT

public:
    GuiBills(QWidget * parent = Q_NULLPTR);
    ~GuiBills();

public:
    void UpdateBill();                // 更新历史账单列表

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private:
    void InitTabWidgetBill();         // 初始化历史账单列表

private:
    void SlotDeleteBills();           // 删除账单...

private:
    Ui::GuiBills *ui;
    QMenu* _menu;
};
