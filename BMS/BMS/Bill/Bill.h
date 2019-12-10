#ifndef BILL_H_
#define BILL_H_

#include <QString>

// 账单类...
class Bill {
public:
	Bill();
	~Bill();

	void SetUuid(QString uuid);
	QString GetUuid();

	void SetTableNum(QString tableNum);
	QString GetTableNum();

	void SetTableTypeName(QString tableTypeName);
	QString GetTableTypeName();

	void SetPricePerHour(double pricePerHour);
	double GetPricePerHour();

	void SetBeginTime(QString beginTime);
	QString GetBeginTime();

	void SetPayTime(QString payTime);
	QString GetPayTime();

	void SetDurationTime(QString durationTime);
	QString GetDurationTime();

	void SetPayMoney(double payMoney);
	double GetPayMoney();

private:
	QString _uuid;                // ID
	QString _tableNum;            // 球桌编号
	QString _tableTypeName;       // 球桌类型名称
	double _pricePerHour;         // 小时单价
	QString _beginTime;           // 开局时间
	QString _payTime;             // 结账时间
	QString _durationTime;        // 消费时长
	double _payMoney;             // 消费金额
};

#endif // !BILL_H_