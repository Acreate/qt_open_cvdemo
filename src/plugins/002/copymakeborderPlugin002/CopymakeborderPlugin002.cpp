#include "CopymakeborderPlugin002.h"

#include "ui_plugin.h"

openCVInterface::CopymakeborderPlugin002::CopymakeborderPlugin002( ) {
    // Insert initialization codes here ...
}

openCVInterface::CopymakeborderPlugin002::~CopymakeborderPlugin002( ) {
    // Insert cleanup codes here ...
}

QString openCVInterface::CopymakeborderPlugin002::title( ) {
    return this->metaObject()->className();
}

QString openCVInterface::CopymakeborderPlugin002::version( ) {
    return "1.0.0";
}

QString openCVInterface::CopymakeborderPlugin002::description( ) {
    return "";
}

QString openCVInterface::CopymakeborderPlugin002::help( ) {
    return "";
}

void openCVInterface::CopymakeborderPlugin002::setupUi( QWidget *parent ) {
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

void openCVInterface::CopymakeborderPlugin002::processImage( const cv::Mat &inputImage, cv::Mat &outputImage ) {
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

void openCVInterface::CopymakeborderPlugin002::on_borderTypeComboBox_currentIndexChanged( int index ) {
    Q_UNUSED(index);
    emit updateNeeded();
}