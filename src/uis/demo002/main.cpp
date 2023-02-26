#include "mainwindow.h"
#include <QApplication>
#include <opencv2/opencv.hpp>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	
	MainWindow win;

	
	win.show();
	return a.exec();
}
