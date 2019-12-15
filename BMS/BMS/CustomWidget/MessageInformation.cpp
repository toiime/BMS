#include "MessageInformation.h"

MessageInformation::MessageInformation(QWidget *parent, QString title, QString text)
	: QDialog(parent) {
	ui.setupUi(this);

	this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
	this->setFixedSize(450, 140);

	this->setWindowTitle(title);
	ui.labelMsg->setText(text);

	connect(ui.pushButtonOk, &QPushButton::clicked, [=]() {
		accept();
	});
}

MessageInformation::~MessageInformation() {

}
