#ifndef CVPLUGININTERFACE_H_H_HEAD__FILE__
#define CVPLUGININTERFACE_H_H_HEAD__FILE__
#pragma once
#include <qobject.h>
#include <opencv2/opencv.hpp>
#include <QString>

namespace openCVInterface {
	class CvPluginInterface001 {
	public:
		virtual ~CvPluginInterface001( ) { }

		virtual QString description( ) {
			return "";
		}

		virtual void processImage( const cv::Mat &inputImage, cv::Mat &outputImage ) {};
	};
}

#define CVPLUGININTERFACE_IID "com.amin.cvplugininterfce"
Q_DECLARE_INTERFACE(openCVInterface::CvPluginInterface001, CVPLUGININTERFACE_IID)

#endif // CVPLUGININTERFACE_H_H_HEAD__FILE__