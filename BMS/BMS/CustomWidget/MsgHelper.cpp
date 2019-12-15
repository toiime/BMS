#include "MsgHelper.h"

#include "MessageInformation.h"
#include "MessageQuestion.h"


MsgHelper::MsgHelper() {

}

MsgHelper::~MsgHelper() {

}

int MsgHelper::MsgInformation(QWidget* parent, QString title, QString text) {
	MessageInformation messageInformation(parent, title, text);
	return messageInformation.exec();
}

int MsgHelper::MsgQuestion(QWidget* parent, QString title, QString text) {
	MessageQuestion messageQuestion(parent, title, text);
	return messageQuestion.exec();
}