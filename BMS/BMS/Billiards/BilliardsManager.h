#ifndef BILLIARDS_MANAGER_H_
#define BILLIARDS_MANAGER_H_

#include <QVector>

#include "Billiards.h"
#include "BilliardsType.h"

// 球桌管理器...
class BilliardsManager {
private:
	BilliardsManager();
	~BilliardsManager();
	BilliardsManager(const BilliardsManager&) {}
	BilliardsManager& operator=(const BilliardsManager&) {}

public:
	static BilliardsManager* GetInstance();

public:
	void LoadTableTypeFromDb();                               // 数据库加载球桌类型
	void AddTableType(QString typeName, double pricePerHour); // 添加球桌类型
	void DeleteTableType(QString uuid);                       // 删除球桌类型
	QVector<BilliardsType> GetTableTypes();                   // 返回球桌类型数组拷贝


private:
	QVector<Billiards> _vecBilliards;     // 球桌数组
	QVector<BilliardsType> _vecBilliardsType;   // 球桌类型数组

	static BilliardsManager* _instance;
};

#endif // !BILLIARDS_MANAGER_H_