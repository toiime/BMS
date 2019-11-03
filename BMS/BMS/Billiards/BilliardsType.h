#ifndef BILLIARDS_TYPE_H
#define BILLIARDS_TYPE_H

#include <QString>

// 球桌类型
class BilliardsType {
public:
	BilliardsType();
	~BilliardsType();

private:
	int _id;                     // 类型ID
	QString _typeName;           // 类型名称
	double _pricePerHour;        // 每小时单价 RMB
};

#endif // !BILLIARDS_TYPE_H