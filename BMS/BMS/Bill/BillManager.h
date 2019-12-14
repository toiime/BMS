#ifndef BILL_MANAGER_H_
#define BILL_MANAGER_H_

#include <QVector>

#include <../Bill/Bill.h>

class Speech;

// 账单管理器类...
class BillManager {
private:
	BillManager();
	~BillManager();
	BillManager(const BillManager&) {}
	BillManager& operator=(const BillManager&) {}
	static BillManager* _instance;

public:
	static BillManager* GetInstance();

public:
	void LoadBillsFromDb();              // 数据库加载账单...
	Bill* CreateBill();                  // 创建账单...
	void UpdateBill(Bill* bill);         // 更新账单...
	QVector<Bill*> GetBills();           // 返回账单...

private:
	void SayBill(Bill* bill);

private:
	QVector<Bill*> _vecBill;

	Speech* _speech;
};

#endif // !BILL_MANAGER_H_