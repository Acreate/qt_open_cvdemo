#ifndef GRAPHICSWINDOW_H_H_HEAD__FILE__
#define GRAPHICSWINDOW_H_H_HEAD__FILE__
#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsView>

class GraphicsWindow : public QMainWindow {
	Q_OBJECT

private:
	QGraphicsView *view;

public:
	explicit GraphicsWindow( QWidget *parent = nullptr );

	~GraphicsWindow( );
};

#endif // GRAPHICSWINDOW_H_H_HEAD__FILE__