#include "TemplatePlugin002.h"

#include "ui_plugin.h"

openCVInterface::TemplatePlugin002::TemplatePlugin002( ) {
	// Insert initialization codes here ...
}

openCVInterface::TemplatePlugin002::~TemplatePlugin002( ) {
	// Insert cleanup codes here ...
}

QString openCVInterface::TemplatePlugin002::title( ) {
	return this->metaObject()->className();
}

QString openCVInterface::TemplatePlugin002::version( ) {
	return "1.0.0";
}

QString openCVInterface::TemplatePlugin002::description( ) {
	return "A <b>Template</b> plugin";
}

QString openCVInterface::TemplatePlugin002::help( ) {
	return "This is a <b>Template</b> plugin. Clone and use it to create new plugins.";
}

void openCVInterface::TemplatePlugin002::setupUi( QWidget *parent ) {
	ui = new Ui::PluginGui;
	ui->setupUi(parent);

	// Connect signals for GUI elemnts manually here since they won't be connected by name in a plugin
	// ...
	// emit updateNeeded(); should be added whenever parameters on the plugin GUI change
}

void openCVInterface::TemplatePlugin002::processImage( const cv::Mat &inputImage, cv::Mat &outputImage ) {
	// Replace the following line with the actual image processing task
	inputImage.copyTo(outputImage);

	// Otherwise, if the process doesn't affect the output image, update plugin GUI here ...
}