#ifndef MESSAGEQUESTION_H
#define MESSAGEQUESTION_H

#include <QDialog>
#include "ui_MessageQuestion.h"

class MessageQuestion : public QDialog {
	Q_OBJECT

public:
	MessageQuestion(QWidget *parent = 0, QString title = "", QString text = "");
	~MessageQuestion();

private:
	Ui::MessageQuestion ui;
};

#endif // MESSAGEQUESTION_H
