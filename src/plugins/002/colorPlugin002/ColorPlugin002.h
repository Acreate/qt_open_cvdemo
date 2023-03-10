#ifndef COLORPLUGIN002_H_H_HEAD__FILE__
#define COLORPLUGIN002_H_H_HEAD__FILE__
#pragma once


#include "ColorPlugin002_export.h"
#include <OpenCVInterface002.h>

#include <QtCore/qglobal.h>

namespace Ui {
	class PluginGui;
}

namespace openCVInterface {
	class COLORPLUGIN002_EXPORT ColorPlugin002 : public QObject, public OpenCVInterface002 {
		Q_OBJECT
		Q_PLUGIN_METADATA(IID OpenCVInterface002_iid)
		Q_INTERFACES(openCVInterface::OpenCVInterface002)
	public:
		ColorPlugin002( );
		~ColorPlugin002( ) override;

		QString title( );
		QString version( );
		QString description( ) override;
		QString help( );
		void setupUi( QWidget *parent );
		void processImage( const cv::Mat &inputImage, cv::Mat &outputImage ) override;

	signals:
		void updateNeeded( );
		void errorMessage( QString msg );
		void infoMessage( QString msg );

	private slots:
		void on_colorMapCombo_currentIndexChanged( int index );

	private:
		Ui::PluginGui *ui;

	};

}

#endif // COLOR_PLUGIN_H