#include "mainwindow.h"
#include "ui_mainwindow.h"

#define FILTERS_SUBFOLDER "/filter_plugins/"

MainWindow::MainWindow( QWidget *parent ) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);
	getPluginsList();
}

MainWindow::~MainWindow( ) {
	delete ui;
}

void MainWindow::getPluginsList( ) {
	QString currentPath = qApp->applicationDirPath() + FILTERS_SUBFOLDER;
	QDir filtersDir(currentPath);
	QFileInfoList filters = filtersDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
	foreach(QFileInfo filter, filters) {
		QString absoluteFilePath = filter.absoluteFilePath();
		if( QLibrary::isLibrary(absoluteFilePath) ) {
			QPluginLoader pluginLoader(absoluteFilePath, this);
			if( dynamic_cast<openCVInterface::OpenCVInterface001 *>(pluginLoader.instance()) ) {
				ui->filtersList->addItem(filter.fileName());
				pluginLoader.unload();// we can unload for now
				qDebug() << "发现插件 : " << absoluteFilePath;
			}
		}
	}

	if( ui->filtersList->count() <= 0 ) {
		QMessageBox::critical(this,
			tr("No Plugins"),
			tr("找不到任何一个插件，请注意路径"));
		this->setEnabled(false);
	}
}

void MainWindow::on_inputImgButton_pressed( ) {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Input Image"), QDir::currentPath(), tr("Images") + " (*.jpg *.png *.bmp)");
	if( QFile::exists(fileName) ) {
		ui->inputImgEdit->setText(fileName);
	}
}

void MainWindow::on_helpButton_pressed( ) {
	if( ui->filtersList->currentRow() >= 0 ) {
		QPluginLoader pluginLoader(qApp->applicationDirPath() + FILTERS_SUBFOLDER + ui->filtersList->currentItem()->text());
		openCVInterface::OpenCVInterface001 *plugin = dynamic_cast<openCVInterface::OpenCVInterface001 *>(pluginLoader.instance());
		if( plugin ) {
			QMessageBox::information(this, tr("Plugin Description"), plugin->description());
		} else {
			QMessageBox::warning(this, tr("Warning"), QString(tr("Make sure plugin %1 exists and is usable.")).arg(ui->filtersList->currentItem()->text()));
		}
	} else {
		QMessageBox::warning(this, tr("Warning"), QString(tr("First select a filter plugin from the list.")));
	}
}

void MainWindow::on_filterButton_pressed( ) {
	if( ui->filtersList->currentRow() >= 0 && !ui->inputImgEdit->text().isEmpty() ) {
		QPluginLoader pluginLoader(qApp->applicationDirPath() + FILTERS_SUBFOLDER + ui->filtersList->currentItem()->text());
		openCVInterface::OpenCVInterface001 *plugin = dynamic_cast<openCVInterface::OpenCVInterface001 *>(pluginLoader.instance());
		if( plugin ) {
			if( QFile::exists(ui->inputImgEdit->text()) ) {
				cv::Mat inputImage, outputImage;
				inputImage = cv::imread(ui->inputImgEdit->text().toStdString());
				plugin->processImage(inputImage, outputImage);

				imshow(tr("Filtered Image").toStdString(), outputImage);
				// 拷贝，接下来不会影响到任何图像操作
				cv::Mat image = inputImage.clone();
				cv::Mat centralRow = image.rowRange(image.rows / 2 - 10, image.rows / 2 + 10);
				cv::Size parentSize;
				cv::Point offset;
				centralRow.locateROI(parentSize, offset);
				int parentWidth = parentSize.width;
				int parentHeight = parentSize.height;
				int x = offset.x;
				int y = offset.y;
				// 常规遍历
				for( int i = 0; i < image.rows; ++i )
					for( int j = 0; j < image.cols; ++j )
						image.at<cv::Vec3b>(i, j) /= 5;
				imshow(tr(" /= 5").toStdString(), image);

				// 迭代器遍历
				image = inputImage.clone();
				cv::MatIterator_<cv::Vec3b> begin = image.begin<cv::Vec3b>(), end = image.end<cv::Vec3b>();
				for( ; begin != end; ++begin )
					*begin *= 5;
				imshow(tr("*= 5;").toStdString(), image);

				// 函数遍历
				image = inputImage.clone();
				image.forEach<cv::Vec3b>([]( cv::Vec3b &p, const int * ) {
					p /= 2.5;
				});
				imshow(tr(" /= 2.5").toStdString(), image);

				// 直接运算
				image = inputImage.clone();
				image *= 20;
				imshow(tr("*= 20").toStdString(), image);

				// 旋转
				image = inputImage.clone();
				image = image.t();
				imshow(tr("t()").toStdString(), image);
			} else {
				QMessageBox::warning(this, tr("Warning"), QString(tr("Make sure %1 exists.")).arg(ui->inputImgEdit->text()));
			}
		} else {
			QMessageBox::warning(this, tr("Warning"), QString(tr("Make sure plugin %1 exists and is usable.")).arg(ui->filtersList->currentItem()->text()));
		}
	} else {
		QMessageBox::warning(this, tr("Warning"), QString(tr("First select a filter plugin from the list.")));
	}
}