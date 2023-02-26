#include "MedianFilterPlugin001.h"

openCVInterface::MedianFilterPlugin001::MedianFilterPlugin001( QObject *parent  ) { }

openCVInterface::MedianFilterPlugin001::~MedianFilterPlugin001( ) {}

QString openCVInterface::MedianFilterPlugin001::description( ) {
	return "This plugin applies median blur filters to any image."
		" This plugin's goal is to make us more familiar with the"
		" concept of plugins in general.";
}

void openCVInterface::MedianFilterPlugin001::processImage( const cv::Mat &inputImage, cv::Mat &outputImage ) {
	cv::medianBlur(inputImage, outputImage, 5);
}