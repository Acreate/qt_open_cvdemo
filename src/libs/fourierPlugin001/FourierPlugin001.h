#ifndef FOURIER_PLUGIN_H
#define FOURIER_PLUGIN_H

#include "FourierPlugin001_export.h"
#include "CvPluginInterface001.h"

namespace Ui {
	class PluginGui;
}

namespace openCVInterface {

	class FOURIERPLUGIN001_EXPORT FourierPlugin001 : public QObject, public CvPluginInterface001 {
		Q_OBJECT
		Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
		Q_INTERFACES(openCVInterface::CvPluginInterface001)

	public:
		FourierPlugin001( );
		~FourierPlugin001( );

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