#include "bms.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	BMS w;
	w.show();
	return a.exec();
}
