#ifndef COPYMAKEBORDER_PLUGIN_H
#define COPYMAKEBORDER_PLUGIN_H

#include "CopymakeborderPlugin001_export.h"
#include "CvPluginInterface001.h"

#include <QtCore/qglobal.h>

namespace Ui {
	class PluginGui;
}

namespace openCVInterface {
	class COPYMAKEBORDERPLUGIN001_EXPORT CopyMakeBorderPlugin001 : public QObject, public CvPluginInterface001 {
		Q_OBJECT
		Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
		Q_INTERFACES(openCVInterface::CvPluginInterface001)

	public:
		CopyMakeBorderPlugin001( );
		~CopyMakeBorderPlugin001( );

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
		void on_borderTypeComboBox_currentIndexChanged( int index );

	private:
		Ui::PluginGui *ui;
	};
}


#endif // COPYMAKEBORDER_PLUGIN_H