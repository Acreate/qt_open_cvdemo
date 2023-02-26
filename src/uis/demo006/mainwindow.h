#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QResizeEvent>
#include <opencv2/opencv.hpp>
namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow( QWidget *parent = 0 );
	~MainWindow( ) override;

protected:
	void dragEnterEvent( QDragEnterEvent *event ) override;
	void dropEvent( QDropEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;

private:
	Ui::MainWindow *ui;
	QPixmap pixmap;
	cv::Mat* loadMat;
};

#endif // MAINWINDOW_H