#ifndef MSG_HELPER_H_
#define MSG_HELPER_H_

#include <QWidget>
#include <QString>

class MsgHelper {
public:
	MsgHelper();
	~MsgHelper();

public:
	static int MsgInformation(QWidget* parent = nullptr, QString title = "", QString text = "");
	static int MsgQuestion(QWidget* parent = nullptr, QString title = "", QString text = "");
};

#endif // !MSG_HELPER_H_