#ifndef CONVERQIMAGEORCVMAT_H_H_HEAD__FILE__
#define CONVERQIMAGEORCVMAT_H_H_HEAD__FILE__
#pragma once

#include "ConverQimageOrCvMat_export.h"
#include <opencv2/opencv.hpp>
#include <QImage>

class CONVERQIMAGEORCVMAT_EXPORT ConverQimageOrCvMat {
public:
	static cv::Mat conver( const QImage &qtImage );

	static QImage conver( const cv::Mat &cvMat );

private:
	ConverQimageOrCvMat( ) {}
	~ConverQimageOrCvMat( ) {}
};


#endif // CONVERQIMAGEORCVMAT_H_H_HEAD__FILE__