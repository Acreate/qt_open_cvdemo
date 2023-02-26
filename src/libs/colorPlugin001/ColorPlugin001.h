#ifndef COLOR_PLUGIN_H
#define COLOR_PLUGIN_H

#include "ColorPlugin001_export.h"
#include <CvPluginInterface001.h>

#include <QtCore/qglobal.h>

namespace Ui {
	class PluginGui;
}

namespace openCVInterface {
	class COLORPLUGIN001_EXPORT ColorPlugin001 : public QObject, public CvPluginInterface001 {
		Q_OBJECT
		Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
		Q_INTERFACES(openCVInterface::CvPluginInterface001)
	public:
		ColorPlugin001( );
		~ColorPlugin001( ) override;

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