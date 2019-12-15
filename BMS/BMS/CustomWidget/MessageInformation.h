#ifndef MESSAGEINFORMATION_H
#define MESSAGEINFORMATION_H

#include <QDialog>
#include "ui_MessageInformation.h"

class MessageInformation : public QDialog {
	Q_OBJECT

public:
	MessageInformation(QWidget *parent = 0, QString title = "", QString text = "");
	~MessageInformation();

private:
	Ui::MessageInformation ui;
};

#endif // MESSAGEINFORMATION_H
