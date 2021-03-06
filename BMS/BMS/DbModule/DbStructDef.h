﻿#ifndef DB_STRUCT_DEF_H_
#define DB_STRUCT_DEF_H_

#include <QString>

// 表 tableType ...
struct TableTypeDef {
	QString uuid_;                  // ID ...
	QString typeName_;              // 球桌类型名称...
	double pricePerHour_;           // 球桌类型单价...
};

// 表 billiardsTable ...
struct BilliardsTableDef {
	QString uuid_;                  // ID ...
	QString tableNum_;              // 球桌编号...
	QString billiardsTypeId_;       // 球桌类型 ID ...
	QString beginTime_;             // 开局时间...
	QString endTime_;               // 结账时间...
	QString isBegin_;               // 是否开局...
};

// 表 bill ...
struct BillDef {
	QString uuid_;                  // ID ...
	QString tableNum_;              // 球桌编号...
	QString tableTypeName_;         // 球桌类型名称...
	double pricePerHour_;           // 球桌类型单价...
	QString beginTime_;             // 开局时间...
	QString payTime_;               // 结账时间...
	QString durationTime_;          // 消费时长...
	double payMoney_;               // 消费金额...
};

#endif // !DB_STRUCT_DEF_H_