#include "gamewindow.h"
//#include <qsplashscreen.h> //���й�����������Ҫ

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GameWindow w;
	w.show();
	QCursor cursor(QPixmap(":/IconSrc/cursor"), 1, 1);
	a.setOverrideCursor(cursor);
	return a.exec();
}
