#ifndef FOURIERPLUGIN002_H_H_HEAD__FILE__
#define FOURIERPLUGIN002_H_H_HEAD__FILE__
#pragma once

#include "FourierPlugin002_export.h"
#include <OpenCVInterface002.h>

namespace Ui {
	class PluginGui;
}

namespace openCVInterface {

	class FOURIERPLUGIN002_EXPORT FourierPlugin002 : public QObject, public OpenCVInterface002 {
		Q_OBJECT
		Q_PLUGIN_METADATA(IID OpenCVInterface002_iid)
		Q_INTERFACES(openCVInterface::OpenCVInterface002)

	public:
		FourierPlugin002( );
		~FourierPlugin002( );

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

	private slots:

	private:
		Ui::PluginGui *ui;

	};

}

#endif // FOURIER_PLUGIN_H