#ifndef BILLIARDS_H_
#define BILLIARDS_H_

#include <QDateTime>

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

	void SetBeginTime(QString beginTime);
	QString GetBeginTime();

	void SetEndTime(QString endTime);
	QString GetEndTime();

	void SetIsBegin(bool isBegin);
	bool GetIsBegin();

private:
	QString _uuid;                    // 球桌ID
	int _tableNum;                    // 桌号
	BilliardsType _billiardsType;     // 球桌类型
	QString _beginTime;               // 开始时间
	QString _endTime;                 // 结束时间
	bool _isBegin;                    // 是否开局
};

#endif // !BILLIARDS_H_