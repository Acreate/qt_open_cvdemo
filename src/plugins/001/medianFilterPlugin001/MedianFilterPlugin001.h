#ifndef MEDIANFILTERPLUGIN_H_H_HEAD__FILE__
#define MEDIANFILTERPLUGIN_H_H_HEAD__FILE__
#pragma once

#include "MedianFilterPlugin001_export.h"
#include <OpenCVInterface001.h>

namespace openCVInterface {
    class MEDIANFILTERPLUGIN001_EXPORT MedianFilterPlugin001 : public QObject, public CvPluginInterface001 {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "com.amin.cvplugininterfce")
        Q_INTERFACES(openCVInterface::CvPluginInterface001)

    public:
        explicit MedianFilterPlugin001( QObject *parent = nullptr );

        ~MedianFilterPlugin001( ) override;

        QString description( ) override;

        void processImage( const cv::Mat &inputImage, cv::Mat &outputImage ) override;
    };
}


#endif // MEDIANFILTERPLUGIN_H_H_HEAD__FILE__