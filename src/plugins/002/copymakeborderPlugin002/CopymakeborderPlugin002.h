#ifndef COPYMAKEBORDER_PLUGIN_H
#define COPYMAKEBORDER_PLUGIN_H

#include <QObject>

#include "CopymakeborderPlugin002_export.h"

#include <QtCore/qglobal.h>

#include <OpenCVInterface002.h>

namespace Ui {
	class PluginGui;
}

namespace openCVInterface {
	class COPYMAKEBORDERPLUGIN002_EXPORT CopymakeborderPlugin002 : public QObject, public OpenCVInterface002 {
		Q_OBJECT
		Q_PLUGIN_METADATA(IID "com.computervision.OpenCVInterface002")
		Q_INTERFACES(openCVInterface::OpenCVInterface002)

	public:
		CopymakeborderPlugin002( );
		~CopymakeborderPlugin002( );

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