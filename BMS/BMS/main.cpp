#include "bms.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <QDir>

#include "./DbModule/DbExecute.h"

int main(int argc, char *argv[]) {

	QApplication a(argc, argv);
	QString strLibPath(QDir::toNativeSeparators(QApplication::applicationDirPath()) + QDir::separator() + "plugins");
	a.addLibraryPath(strLibPath);


	int rv = 0;

	// 初始化数据库...
	rv = DbExecute::InitDb();
	if (rv != 0) {
		QMessageBox::information(nullptr, QStringLiteral("Note"), QStringLiteral("DB Init Error !"));
		return 0;
	}

	BMS w;
	w.show();
	return a.exec();
}
