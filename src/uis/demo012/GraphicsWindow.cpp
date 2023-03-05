#include "GraphicsWindow.h"
#include <QGraphicsScene>
#include <QMenuBar>
#include <QAction>
#include <QObject>
#include <QStringList>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QPixmap>
#include <QImage>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/opencv.hpp>

GraphicsWindow::GraphicsWindow( QWidget *parent ): QMainWindow(parent) {
	view = new QGraphicsView(this);
	setCentralWidget(view);
	auto graphicsScene = new QGraphicsScene(view);
	view->setScene(graphicsScene);
	QMenuBar *menuBar = this->menuBar();
	if( !menuBar ) {
		menuBar = new QMenuBar;
		setMenuBar(menuBar);
	}
	QAction *addAction = menuBar->addAction(tr("加载主要图片"));
	connect(addAction, &QAction::triggered, [=]( bool flage ) {
		QStringList filePath = QFileDialog::getOpenFileNames(this, tr("打开图片"), ".", tr("图片文件(*.jpg *.png)"));
		if( filePath.length() == 0 )
			return;
		auto graphicsPixmapItem = new QGraphicsPixmapItem();
		QImage qImage(filePath[0]);
		QPixmap pixmap = QPixmap::fromImage(qImage);
		graphicsPixmapItem->setPixmap(pixmap);
		QGraphicsScene *scene = view->scene();
		scene->clear();
		scene->addItem(graphicsPixmapItem);
		this->resize(pixmap.width(), pixmap.height());
	});

	addAction = menuBar->addAction(tr("加载匹配图片"));
	connect(addAction, &QAction::triggered, [=]( bool flage ) {
		// 没有原始图像则退出
		QGraphicsScene *scene = view->scene();
		if( scene->items().length() == 0 )
			return;
		// 类型转换失败则退出
		QGraphicsPixmapItem *graphicsPixmapItem = static_cast<QGraphicsPixmapItem *>(scene->items()[0]);
		if( !graphicsPixmapItem )
			return;
		// 没有打开文件则退出
		QStringList filePath = QFileDialog::getOpenFileNames(this, tr("打开图片"), ".", tr("图片文件(*.jpg *.png)"));
		if( filePath.length() == 0 )
			return;
		// 获取图片
		QPixmap orgPixmap = graphicsPixmapItem->pixmap();
		// 转换到 rgb
		QImage image = orgPixmap.toImage().convertToFormat(QImage::Format_RGB888);
		// r 与 b 互换
		image.rgbSwap();
		cv::Mat readFile = cv::imread(filePath[0].toStdString());
		// 转换到 opengcv 的 Mat
		cv::Mat mat = cv::Mat(image.height(), image.width(), CV_8UC3, image.bits(), image.bytesPerLine());
		// 匹配图像
		cv::Mat outResult;
		cv::matchTemplate(mat, readFile, outResult, cv::TM_CCORR_NORMED);
		// 查找匹配位置

		double minVal, maxVal;
		cv::Point minLoc, maxLoc;
		cv::minMaxLoc(outResult, &minVal, &maxVal, &minLoc, &maxLoc);
		cv::rectangle(mat,
			cv::Rect(maxLoc.x, maxLoc.y, readFile.cols, readFile.rows),
			cv::Scalar(255, 255, 255),
			2
			);
		cv::cvtColor(mat, mat, CV_BGR2RGB);
		QPixmap pixmap = QPixmap::fromImage(QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888));
		graphicsPixmapItem->setPixmap(pixmap);
	});
}

GraphicsWindow::~GraphicsWindow( ) {
	view->scene()->clear();
}