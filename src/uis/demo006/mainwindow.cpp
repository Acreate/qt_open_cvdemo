#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    loadMat(nullptr) {
    ui->setupUi(this);
    setAcceptDrops(true);
}

MainWindow::~MainWindow( ) {
    delete ui;
    if( loadMat )
        delete loadMat;
}

void MainWindow::dragEnterEvent( QDragEnterEvent *event ) {
    QStringList acceptedFileTypes;
    acceptedFileTypes.append("jpg");
    acceptedFileTypes.append("png");
    acceptedFileTypes.append("bmp");

    if( event->mimeData()->hasUrls() &&
        event->mimeData()->urls().count() == 1 ) {

        QFileInfo file(event->mimeData()->urls().at(0).toLocalFile());
        if( acceptedFileTypes.contains(file.suffix().toLower()) ) {
            event->acceptProposedAction();
        }
    }
}

void MainWindow::dropEvent( QDropEvent *event ) {
    QFileInfo file(event->mimeData()->urls().at(0).toLocalFile());
    if( ! loadMat )
        loadMat = new cv::Mat();
    *loadMat = cv::imread(file.absoluteFilePath().toStdString());
    if( !loadMat->empty() ) {
        cv::cvtColor(*loadMat, *loadMat, CV_BGR2RGB);
        QImage loadQImage(loadMat->data, loadMat->cols, loadMat->rows, loadMat->step, QImage::Format_RGB888);
        if( pixmap.convertFromImage(loadQImage) ) {
            ui->label->setPixmap(pixmap.scaled(ui->label->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation));
        }
    } else {
        QMessageBox::critical(this,
            tr("Error"),
            tr("The image file cannot be read!"));
    }
}

void MainWindow::resizeEvent( QResizeEvent *event ) {
    Q_UNUSED(event);
    if( !pixmap.isNull() ) {
        ui->label->setPixmap(pixmap.scaled(ui->label->width() - 5,
            ui->label->height() - 5,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation));
    }
}