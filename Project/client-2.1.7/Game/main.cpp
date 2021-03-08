#include "gamewindow.h"
//#include <qsplashscreen.h> //若有过场动画则需要

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GameWindow w;
	w.show();
	QCursor cursor(QPixmap(":/IconSrc/cursor"), 1, 1);
	a.setOverrideCursor(cursor);
	return a.exec();
}
