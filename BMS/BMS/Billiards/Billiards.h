#ifndef BILLIARDS_H_
#define BILLIARDS_H_

#include "BilliardsType.h"

// 台球桌类
class Billiards {
public:
	Billiards();
	~Billiards();

private:
	int _id;                          // 球桌ID
	BilliardsType _billiardsType;     // 球桌类型
	int _beginTime;                   // 开始时间
	int _endTime;                     // 结束时间
};

#endif // !BILLIARDS_H_