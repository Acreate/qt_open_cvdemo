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
			}/*else {
				QMessageBox::warning(this,
					tr("Warning"),
					QString(tr("%1 虽然它是一个库，但并不是一个插件")).arg(filter.fileName()));
			}*/
		}/*else {
			QMessageBox::warning(this,
				tr("Warning"),
				QString(tr("%1 它甚至不是一个库！")).arg(filter.fileName()));
		}*/
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
				using namespace cv;
				Mat inputImage, outputImage;
				inputImage = imread(ui->inputImgEdit->text().toStdString());
				// 拷贝，接下来不会影响到任何图像操作
				Mat clone = inputImage.clone();
				// 引用某一块域
				Mat roi(clone, Rect(500, 138, 65, 65));
				// 对域进行设置(全部填充为 0)
				roi = Scalar(0);

				// 对中间设置一个加号
				int rows = clone.rows / 2;
				int cols = clone.cols / 2;
				Mat centralRows = clone.rowRange(rows - 10, rows + 10);
				Mat centralColums = clone.colRange(cols - 10, cols + 10);
				centralRows = Scalar(255 / 2);
				centralColums = Scalar(255 / 4);
				plugin->processImage(inputImage, outputImage);
				imshow(tr("Filtered Image").toStdString(), outputImage);
				imshow(tr("clone Image").toStdString(), clone);
				imshow(tr("roi Image").toStdString(), roi);
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