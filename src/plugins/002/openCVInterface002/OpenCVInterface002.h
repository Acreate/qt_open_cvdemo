#ifndef OPENCVINTERFACE002_H_H_HEAD__FILE__
#define OPENCVINTERFACE002_H_H_HEAD__FILE__
#pragma once

#include <QObject>
#include <QWidget>
#include <QString>

#include "opencv2/opencv.hpp"
#include "OpenCVInterface002_export.h"

namespace openCVInterface {
	class OPENCVINTERFACE002_EXPORT OpenCVInterface002 {
	public:
		virtual ~OpenCVInterface002( ) {}
		virtual QString title( ) = 0;
		virtual QString version( ) = 0;
		virtual QString description( ) = 0;
		virtual QString help( ) = 0;
		virtual void setupUi( QWidget *parent ) = 0;
		virtual void processImage( const cv::Mat &inputImage, cv::Mat &outputImage ) = 0;
	};

}

#define CVPLUGININTERFACE_IID "com.computervision.OpenCVInterface002"
Q_DECLARE_INTERFACE(openCVInterface::OpenCVInterface002, CVPLUGININTERFACE_IID)


#endif // OPENCVINTERFACE002_H_H_HEAD__FILE__