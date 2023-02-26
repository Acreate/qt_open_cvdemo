#include "ColorPlugin002.h"

#include "ui_plugin.h"

openCVInterface::ColorPlugin002::ColorPlugin002( ) {
	// Insert initialization codes here ...
}

openCVInterface::ColorPlugin002::~ColorPlugin002( ) {
	// Insert cleanup codes here ...
}

QString openCVInterface::ColorPlugin002::title( ) {
	return this->metaObject()->className();
}

QString openCVInterface::ColorPlugin002::version( ) {
	return "1.0.0";
}

QString openCVInterface::ColorPlugin002::description( ) {
	return "";
}

QString openCVInterface::ColorPlugin002::help( ) {
	return "";
}

void openCVInterface::ColorPlugin002::setupUi( QWidget *parent ) {
	ui = new Ui::PluginGui;
	ui->setupUi(parent);

	ui->colorMapCombo->addItems(QStringList()
		<< "COLORMAP_AUTUMN"
		<< "COLORMAP_BONE"
		<< "COLORMAP_JET"
		<< "COLORMAP_WINTER"
		<< "COLORMAP_RAINBOW"
		<< "COLORMAP_OCEAN"
		<< "COLORMAP_SUMMER"
		<< "COLORMAP_SPRING"
		<< "COLORMAP_COOL"
		<< "COLORMAP_HSV"
		<< "COLORMAP_PINK"
		<< "COLORMAP_HOT"
		<< "COLORMAP_PARULA");

	connect(ui->colorMapCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_colorMapCombo_currentIndexChanged(int)));
}

void openCVInterface::ColorPlugin002::processImage( const cv::Mat &inputImage, cv::Mat &outputImage ) {
	using namespace cv;
	applyColorMap(inputImage, outputImage, ui->colorMapCombo->currentIndex());
}

void openCVInterface::ColorPlugin002::on_colorMapCombo_currentIndexChanged( int index ) {
	Q_UNUSED(index);
	emit updateNeeded();
}