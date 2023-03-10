#ifndef FILTERPLUGIN002_H_H_HEAD__FILE__
#define FILTERPLUGIN002_H_H_HEAD__FILE__
#pragma once


#include <QtCore/qglobal.h>
#include <OpenCVInterface002.h>
#include "FilterPlugin002_export.h"
#include <QObject>
#include <QSpinBox>

namespace Ui {
    class PluginGui;
}

namespace openCVInterface {
    class FILTERPLUGIN002_EXPORT FilterPlugin002 : public QObject, public openCVInterface::OpenCVInterface002 {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID OpenCVInterface002_iid)
        Q_INTERFACES(openCVInterface::OpenCVInterface002)

    public:
        FilterPlugin002( );
        ~FilterPlugin002( );

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
        void on_bilateralDiaSpin_valueChanged( int arg1 );

        void on_bilateralSigmaColorSpin_valueChanged( double arg1 );

        void on_bilateralSigmaSpaceSpin_valueChanged( double arg1 );

        void on_blurKernelSizeSpinBox_valueChanged( int arg1 );

        void on_blurAnchoXSpin_valueChanged( int arg1 );

        void on_blurAnchoYSpin_valueChanged( int arg1 );

        void on_boxKernelSizeSpinBox_valueChanged( int arg1 );

        void on_boxDepthSpin_valueChanged( int arg1 );

        void on_boxAnchoXSpin_valueChanged( int arg1 );

        void on_boxAnchoYSpin_valueChanged( int arg1 );

        void on_boxNormalCheck_toggled( bool checked );

        void on_gaussKernelSizeSpinBox_valueChanged( int arg1 );

        void on_gaussSigmaXSpin_valueChanged( double arg1 );

        void on_gaussSigmaYSpin_valueChanged( double arg1 );

        void on_medianApertureSpin_valueChanged( int arg1 );

        void on_mainTabs_currentChanged( int index );

        void on_derivSobelRadio_toggled( bool checked );

        void on_derivScharrRadio_toggled( bool checked );

        void on_derivLaplacRadio_toggled( bool checked );

        void on_derivScaleSpin_valueChanged( double arg1 );

        void on_derivDeltaSpin_valueChanged( double arg1 );

        void on_morphErodeRadio_toggled( bool checked );

        void on_morphDilateRadio_toggled( bool checked );

        void on_morphMorphRadio_toggled( bool checked );

        void on_morphIterSpin_valueChanged( int arg1 );

        void on_morphTypesCombo_currentIndexChanged( int index );

        void on_morphShapesCombo_currentIndexChanged( int index );

    private:
        Ui::PluginGui *ui;

    };

}

#endif // FILTER_PLUGIN_H