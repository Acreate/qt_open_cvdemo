#ifndef SEGMENTATION_PLUGIN_H
#define SEGMENTATION_PLUGIN_H

#include <OpenCVInterface002.h>
#include "SegmentationPlugin002_export.h"

namespace Ui {
	class PluginGui;
}

namespace openCVInterface {
	class SEGMENTATIONPLUGIN002_EXPORT SegmentationPlugin002 : public QObject, public openCVInterface::OpenCVInterface002 {
		Q_OBJECT
		Q_PLUGIN_METADATA(IID "com.computervision.OpenCVInterface002")
		Q_INTERFACES(openCVInterface::OpenCVInterface002)

	public:
		SegmentationPlugin002( );
		~SegmentationPlugin002( );

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
		void on_threshAdaptiveCheck_toggled( bool checked );

		void on_threshAdaptiveCombo_currentIndexChanged( int index );

		void on_threshTypeCombo_currentIndexChanged( int index );

		void on_threshSlider_valueChanged( int value );

		void on_threshMaxSlider_valueChanged( int value );

	private:
		Ui::PluginGui *ui;

	};
}
#endif // SEGMENTATION_PLUGIN_H