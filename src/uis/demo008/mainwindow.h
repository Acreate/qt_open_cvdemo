#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>

#include "qcustomgraphicseffect.h"

namespace Ui {
	class MainWindow;
}

/// @brief Ö÷Òª´°¿Ú
class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow( QWidget *parent = nullptr );
	~MainWindow( ) override;

protected:
	void dragEnterEvent( QDragEnterEvent *event ) override;
	void dropEvent( QDropEvent *event ) override;

private:
	Ui::MainWindow *ui;
	QGraphicsScene scene;

};

#endif // MAINWINDOW_H