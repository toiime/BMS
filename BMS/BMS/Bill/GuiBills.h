#pragma once

#include <QWidget>

namespace Ui { class GuiBills; }

class GuiBills : public QWidget {
    Q_OBJECT

public:
    GuiBills(QWidget * parent = Q_NULLPTR);
    ~GuiBills();

public:
    void UpdateBill();                // 更新历史账单列表

private:
    void InitTabWidgetBill();         // 初始化历史账单列表

private:
    Ui::GuiBills *ui;
};
