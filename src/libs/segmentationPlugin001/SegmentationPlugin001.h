#ifndef SEGMENTATION_PLUGIN_H
#define SEGMENTATION_PLUGIN_H

#include "CvPluginInterface001.h"
#include "SegmentationPlugin001_export.h"

namespace Ui {
	class PluginGui;
}

namespace openCVInterface {
	class SEGMENTATIONPLUGIN001_EXPORT SegmentationPlugin001 : public QObject, public openCVInterface::CvPluginInterface001 {
		Q_OBJECT
		Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
		Q_INTERFACES(openCVInterface::CvPluginInterface001)

	public:
		SegmentationPlugin001( );
		~SegmentationPlugin001( );

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