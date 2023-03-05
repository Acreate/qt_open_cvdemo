#include <QApplication>

#include "GraphicsWindow.h"

int main( int argc, char *argv[] ) {
	QApplication a(argc, argv);
	GraphicsWindow graphicsView;
	graphicsView.show();
	return a.exec();
}
