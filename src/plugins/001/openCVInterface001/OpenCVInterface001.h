#ifndef CVPLUGININTERFACE_H_H_HEAD__FILE__
#define CVPLUGININTERFACE_H_H_HEAD__FILE__
#pragma once
#include <qobject.h>
#include "OpenCVInterface001_export.h"
#include <opencv2/opencv.hpp>
#include <QString>

namespace openCVInterface {
    class OPENCVINTERFACE001_EXPORT CvPluginInterface001 {
    public:
        virtual ~CvPluginInterface001( ) = default;

        virtual QString description( ) = 0;

        virtual void processImage( const cv::Mat &inputImage, cv::Mat &outputImage ) =0;
    };
}

#define CVPLUGININTERFACE_IID "com.amin.OpenCVInterface001"
Q_DECLARE_INTERFACE(openCVInterface::CvPluginInterface001, CVPLUGININTERFACE_IID)

#endif // CVPLUGININTERFACE_H_H_HEAD__FILE__