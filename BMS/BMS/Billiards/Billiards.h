#ifndef BILLIARDS_H_
#define BILLIARDS_H_

#include "BilliardsType.h"

// 台球桌类
class Billiards {
public:
	Billiards();
	~Billiards();

	void SetUuid(QString uuid);
	QString GetUuid();

	void SetTableNum(int tableNum);
	int GetTableNum();

	void SetBilliardsType(BilliardsType billiardsType);
	BilliardsType GetBilliardsType();

	void SetBeginTime(int beginTime);
	int GetBeginTime();

	void SetEndTime(int endTime);
	int GetEndTime();

private:
	QString _uuid;                    // 球桌ID
	int _tableNum;                    // 桌号
	BilliardsType _billiardsType;     // 球桌类型
	int _beginTime;                   // 开始时间
	int _endTime;                     // 结束时间
};

#endif // !BILLIARDS_H_