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
	static BilliardsManager* _instance;

public:
	static BilliardsManager* GetInstance();

public:
	void LoadTableTypeFromDb();                               // 数据库加载球桌类型
	BilliardsType* CreateTableType();                         // 创建球桌类型...
	void UpdateTableType(BilliardsType* billiardsType);       // 更新球桌类型...
	void DeleteTableType(QString uuid);                       // 删除球桌类型
	BilliardsType* FindBilliardsType(QString id);             // 查找球桌类型...
	QVector<BilliardsType*> GetTableTypes();                  // 返回球桌类型数组拷贝

	void LoadTableFromDb();                                   // 数据库中加载球桌
	Billiards* CreateBilliardsTable();                        // 创建球桌...
	void UpdateBilliardsTable(Billiards* billiards);          // 更新球桌...
	void DeleteBilliardsTable(QString uuid);                  // 删除球桌
	Billiards* FindBilliards(QString id);                     // 查找球桌...
	QVector<Billiards*> GetBilliardsTables();                 // 返回球桌数组拷贝


private:
	QVector<Billiards*> _vecBilliards;                        // 球桌数组
	QVector<BilliardsType*> _vecBilliardsType;                // 球桌类型数组
};

#endif // !BILLIARDS_MANAGER_H_