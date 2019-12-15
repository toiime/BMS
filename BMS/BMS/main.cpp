#include "bms.h"
#include <QtWidgets/QApplication>
#include <QDir>

#include "./DbModule/DbExecute.h"
#include "./Config/Config.h"
#include "./CustomWidget/MsgHelper.h"

int main(int argc, char *argv[]) {
	// 1.设置库路径...
	QApplication a(argc, argv);
	QString strLibPath(QDir::toNativeSeparators(QApplication::applicationDirPath()) + QDir::separator() + "plugins");
	a.addLibraryPath(strLibPath);

	// 2.加载配置文件...
	Config::GetInstance()->LoadConfigFile();

	// 3.初始化数据库...
	int rv = DbExecute::InitDb();
	if (rv != 0) {
		MsgHelper::MsgInformation(nullptr, QStringLiteral("Note"), QStringLiteral("DB Init Error !"));
		return 0;
	}

	// 4.创建窗口...
	BMS w;
	w.show();
	return a.exec();
}
