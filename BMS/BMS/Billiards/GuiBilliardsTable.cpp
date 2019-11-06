#include "GuiBilliardsTable.h"

GuiBilliardsTable::GuiBilliardsTable(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);

	QPixmap pixmap = QPixmap(":/Pic/Res/billiardsTable.png");
	pixmap = pixmap.scaled(pixmap.size() / 4);
	ui.labelPic->setPixmap(pixmap);

	resize(100, 50);
}

GuiBilliardsTable::~GuiBilliardsTable() {

}
