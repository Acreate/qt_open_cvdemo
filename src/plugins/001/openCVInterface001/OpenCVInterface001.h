#ifndef CVPLUGININTERFACE_H_H_HEAD__FILE__
#define CVPLUGININTERFACE_H_H_HEAD__FILE__
#pragma once
#include <qobject.h>
#include "OpenCVInterface001_export.h"
#include <opencv2/opencv.hpp>
#include <QString>

namespace openCVInterface {
    class OPENCVINTERFACE001_EXPORT OpenCVInterface001 {
    public:
        virtual ~OpenCVInterface001( ) = default;

        virtual QString description( ) = 0;

        virtual void processImage( const cv::Mat &inputImage, cv::Mat &outputImage ) =0;
    };
}


#define OpenCVInterface001_iid "com.amin.OpenCVInterface001"
Q_DECLARE_INTERFACE(openCVInterface::OpenCVInterface001, OpenCVInterface001_iid)

#endif // CVPLUGININTERFACE_H_H_HEAD__FILE__