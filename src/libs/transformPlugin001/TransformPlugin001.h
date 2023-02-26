#ifndef TRANSFORM_PLUGIN_H
#define TRANSFORM_PLUGIN_H
#include "TransformPlugin001_export.h"
#include "CvPluginInterface001.h"
#include <QObject>
#include <QtMath>

namespace Ui {
	class PluginGui;
}

namespace openCVInterface {
	class TRANSFORMPLUGIN001_EXPORT TransformPlugin001 : public QObject, public openCVInterface::CvPluginInterface001 {
		Q_OBJECT
		Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
		Q_INTERFACES(openCVInterface::CvPluginInterface001)

	public:
		TransformPlugin001( );
		~TransformPlugin001( );

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