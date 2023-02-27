
#ifndef TRANSFORMPLUGIN002_H_H_HEAD__FILE__
#define TRANSFORMPLUGIN002_H_H_HEAD__FILE__
#pragma once


#include "TransformPlugin002_export.h"
#include <OpenCVInterface002.h>
#include <QObject>
#include <QtMath>

namespace Ui {
	class PluginGui;
}

namespace openCVInterface {
	class TRANSFORMPLUGIN002_EXPORT TransformPlugin002 : public QObject, public openCVInterface::OpenCVInterface002 {
		Q_OBJECT
		Q_PLUGIN_METADATA(IID OpenCVInterface002_iid)
		Q_INTERFACES(openCVInterface::OpenCVInterface002)

	public:
		TransformPlugin002( );
		~TransformPlugin002( );

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
		void on_resizeHalfRadio_toggled( bool checked );

		void on_resizeDoubleRadio_toggled( bool checked );

		void on_remapRadio_toggled( bool checked );

		void on_affineRadio_toggled( bool checked );

		void on_perspectiveRadio_toggled( bool checked );

		void on_borderTypeCombo_currentIndexChanged( int index );

		void on_interpolationCombo_currentIndexChanged( int index );

	private:
		Ui::PluginGui *ui;

	};
}
#endif // TRANSFORM_PLUGIN_H