#include "bms.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>

#include "./DbModule/DbExecute.h"

int main(int argc, char *argv[]) {
	int rv = 0;

	// 初始化数据库...
	rv = DbExecute::InitDb();
	if (rv != 0) {
		QMessageBox::information(nullptr, QStringLiteral("Note"), QStringLiteral("DB Init Error !"));
		return 0;
	}

	QApplication a(argc, argv);
	BMS w;
	w.show();
	return a.exec();
}
