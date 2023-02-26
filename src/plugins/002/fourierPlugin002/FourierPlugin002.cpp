#include "FourierPlugin002.h"

#include <opencv2/imgproc/types_c.h>

#include "ui_plugin.h"

openCVInterface::FourierPlugin002::FourierPlugin002( ) {
	// Insert initialization codes here ...
}

openCVInterface::FourierPlugin002::~FourierPlugin002( ) {
	// Insert cleanup codes here ...
}

QString openCVInterface::FourierPlugin002::title( ) {
	return this->metaObject()->className();
}

QString openCVInterface::FourierPlugin002::version( ) {
	return "1.0.0";
}

QString openCVInterface::FourierPlugin002::description( ) {
	return "A <b>Template</b> plugin";
}

QString openCVInterface::FourierPlugin002::help( ) {
	return "This is a <b>Template</b> plugin. Clone and use it to create new plugins.";
}

void openCVInterface::FourierPlugin002::setupUi( QWidget *parent ) {
	ui = new Ui::PluginGui;
	ui->setupUi(parent);
}

void openCVInterface::FourierPlugin002::processImage( const cv::Mat &inputImage, cv::Mat &outputImage ) {
	using namespace cv;

	Mat grayImg;

	cvtColor(inputImage, grayImg, CV_BGR2GRAY);

	int optH = getOptimalDFTSize(grayImg.rows);
	int optW = getOptimalDFTSize(grayImg.cols);

	Mat padded;
	copyMakeBorder(grayImg,
		padded,
		0,
		optH - grayImg.rows,
		0,
		optW - grayImg.cols,
		BORDER_CONSTANT,
		Scalar::all(0));

	Mat channels[] = {
		Mat_<float>(padded),
		Mat::zeros(padded.size(),
			CV_32F)
	};
	Mat complex;
	merge(channels, 2, complex);

	dft(complex, complex);

	split(complex, channels);
	Mat mag;
	magnitude(channels[0], channels[1], mag);

	mag += Scalar::all(1);
	log(mag, mag);

	mag = mag(Rect(0,
		0,
		mag.cols & -2,
		mag.rows & -2));

	int cx = mag.cols / 2;
	int cy = mag.rows / 2;

	Mat q0(mag, Rect(0, 0, cx, cy));
	Mat q1(mag, Rect(cx, 0, cx, cy));
	Mat q2(mag, Rect(0, cy, cx, cy));
	Mat q3(mag, Rect(cx, cy, cx, cy));

	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(mag, mag, 0, 255, CV_MINMAX);

	Mat_<uchar> magI8bit(mag);
	cvtColor(magI8bit, outputImage, CV_GRAY2BGR);
}