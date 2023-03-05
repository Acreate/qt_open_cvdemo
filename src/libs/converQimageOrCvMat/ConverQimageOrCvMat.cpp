#include "ConverQimageOrCvMat.h"
#include <opencv2/imgproc/types_c.h>

cv::Mat ConverQimageOrCvMat::conver( const QImage &qtImage ) {
	// 转换到标准 rgb888 格式
	QImage image = qtImage.convertToFormat(QImage::Format_RGB888);
	image.rgbSwap();
	qint64 inBytes = image.sizeInBytes();
	uchar *data = image.bits();
	unsigned char *bits = new unsigned char[inBytes];
	for( qint64 index = 0; index < inBytes; ++index )
		bits[index] = data[index];
	// 转换到 opengcv 的 Mat
	return cv::Mat(image.height(), image.width(), CV_8UC3, bits, image.bytesPerLine());
}

QImage ConverQimageOrCvMat::conver( const cv::Mat &cvMat ) {
	qint64 inBytes = cvMat.cols * cvMat.rows * cvMat.channels();
	uchar *data = cvMat.data;
	unsigned char *bits = new unsigned char[inBytes];
	for( qint64 index = 0; index < inBytes; ++index )
		bits[index] = data[index];
	QImage result(cvMat.data, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_RGB888);
	result.rgbSwap();
	return result;
}