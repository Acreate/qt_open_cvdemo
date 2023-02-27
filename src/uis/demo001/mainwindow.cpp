#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <OpenCVInterface002.h>
#define FILTERS_SUBFOLDER "/filter_plugins/"
#define PLUGINS_SUBFOLDER "/cvplugins/"
// 决定是否使用后期插件
#if 1

#define Ing_Subfolder FILTERS_SUBFOLDER
using InterFace = openCVInterface::OpenCVInterface001;

#else

#define Ing_Subfolder PLUGINS_SUBFOLDER
using InterFace = openCVInterface::OpenCVInterface002;

#endif


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
	QString currentPath = qApp->applicationDirPath() + Ing_Subfolder;
	QDir filtersDir(currentPath);
	QFileInfoList filters = filtersDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
	foreach(QFileInfo filter, filters) {
		QString absoluteFilePath = filter.absoluteFilePath();
		if( QLibrary::isLibrary(absoluteFilePath) ) {
			QPluginLoader pluginLoader(absoluteFilePath, this);
			QObject *instance = pluginLoader.instance();
			if( instance ) {
				qDebug() << "可以实例话的插件 : " << absoluteFilePath;
				auto *openCvInterface = dynamic_cast<InterFace *>(instance);
				if( openCvInterface ) {
					ui->filtersList->addItem(filter.fileName());
					pluginLoader.unload();// we can unload for now
					qDebug() << "发现插件 : " << absoluteFilePath;
				} else
					qDebug() << "无法转换 : " << absoluteFilePath;
			} else
				qDebug() << "无法实例话的插件 : " << absoluteFilePath;
		}
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
		QPluginLoader pluginLoader(qApp->applicationDirPath() + Ing_Subfolder + ui->filtersList->currentItem()->text());
		auto *plugin = dynamic_cast<InterFace *>(pluginLoader.instance());
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
		QPluginLoader pluginLoader(qApp->applicationDirPath() + Ing_Subfolder + ui->filtersList->currentItem()->text());
		auto *plugin = dynamic_cast<InterFace *>(pluginLoader.instance());
		if( plugin ) {
			if( QFile::exists(ui->inputImgEdit->text()) ) {
				using namespace cv;
				Mat inputImage, outputImage;
				inputImage = imread(ui->inputImgEdit->text().toStdString());
				plugin->processImage(inputImage, outputImage);
				imshow(tr("Filtered Image").toStdString(), outputImage);
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