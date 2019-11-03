#ifndef BILLIARDS_MANAGER_H_
#define BILLIARDS_MANAGER_H_

#include <QVector>

class Billiards;

// 球桌管理器...
class BilliardsManager {
public:
	BilliardsManager();
	~BilliardsManager();

private:
	QVector<Billiards> _vecBilliards;
};

#endif // !BILLIARDS_MANAGER_H_