#ifndef BILL_MANAGER_H_
#define BILL_MANAGER_H_

#include <QVector>

#include <Bill\Bill.h>

// 账单管理器类...
class BillManager {
private:
	BillManager();
	~BillManager();
	BillManager(const BillManager&) {}
	BillManager& operator=(const BillManager&) {}

public:
	static BillManager* GetInstance();

public:
	void LoadBillsFromDb();             // 数据库加载账单
	void AddBill(Bill bill);            // 添加账单
	QVector<Bill> GetBills();           // 返回账单拷贝

private:
	static BillManager* _instance;

	QVector<Bill> _vecBill;
};

#endif // !BILL_MANAGER_H_