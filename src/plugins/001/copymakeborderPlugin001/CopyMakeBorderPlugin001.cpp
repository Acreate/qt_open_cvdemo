#include "CopyMakeBorderPlugin001.h"

#include "ui_plugin.h"

openCVInterface::CopyMakeBorderPlugin001::CopyMakeBorderPlugin001( ) {
    // Insert initialization codes here ...
}

openCVInterface::CopyMakeBorderPlugin001::~CopyMakeBorderPlugin001( ) {
    // Insert cleanup codes here ...
}

QString openCVInterface::CopyMakeBorderPlugin001::title( ) {
    return this->metaObject()->className();
}

QString openCVInterface::CopyMakeBorderPlugin001::version( ) {
    return "1.0.0";
}

QString openCVInterface::CopyMakeBorderPlugin001::description( ) {
    return "";
}

QString openCVInterface::CopyMakeBorderPlugin001::help( ) {
    return "";
}

void openCVInterface::CopyMakeBorderPlugin001::setupUi( QWidget *parent ) {
    ui = new Ui::PluginGui;
    ui->setupUi(parent);
    QStringList items;
    items.append("BORDER_CONSTANT");
    items.append("BORDER_REPLICATE");
    items.append("BORDER_REFLECT");
    items.append("BORDER_WRAP");
    items.append("BORDER_REFLECT_101");
    ui->borderTypeComboBox->addItems(items);
    connect(ui->borderTypeComboBox,
        SIGNAL(currentIndexChanged(int)),
        this,
        SLOT(on_borderTypeComboBox_currentIndexChanged(int)));
}

void openCVInterface::CopyMakeBorderPlugin001::processImage( const cv::Mat &inputImage, cv::Mat &outputImage ) {
    int top, bot, left, right;
    top = bot = inputImage.rows / 2;
    left = right = inputImage.cols / 2;
    cv::copyMakeBorder(inputImage,
        outputImage,
        top,
        bot,
        left,
        right,
        ui->borderTypeComboBox->currentIndex());
}

void openCVInterface::CopyMakeBorderPlugin001::on_borderTypeComboBox_currentIndexChanged( int index ) {
    Q_UNUSED(index);
    emit updateNeeded();
}