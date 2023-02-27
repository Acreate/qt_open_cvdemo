#ifndef TEMPLATEPLUGIN002_H_H_HEAD__FILE__
#define TEMPLATEPLUGIN002_H_H_HEAD__FILE__
#pragma once


#include "TemplatePlugin002_export.h"
#include <OpenCVInterface002.h>

namespace Ui {
	class PluginGui;
}

namespace openCVInterface {
	class TEMPLATEPLUGIN002_EXPORT TemplatePlugin002 : public QObject, public OpenCVInterface002 {
		Q_OBJECT
		Q_PLUGIN_METADATA(IID OpenCVInterface002_iid)
		Q_INTERFACES(openCVInterface::OpenCVInterface002)

	public:
		TemplatePlugin002( );
		~TemplatePlugin002( );

		QString title( );
		QString version( );
		QString description( );
		QString help( );
		void setupUi( QWidget *parent );
		void processImage( const cv::Mat &inputImage, cv::Mat &outputImage );

	signals:
		void updateNeeded( );
		void errorMessage( QString msg );
		void infoMessage( QString msg );

	private:
		Ui::PluginGui *ui;

	};
}
#endif // TEMPLATE_PLUGIN_H