#ifndef QENHANCEDGRAPHICSVIEW_H
#define QENHANCEDGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QtMath>
#include <QContextMenuEvent>
#include <QMenu>
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsEffect>
#include "qcustomgraphicseffect.h"

class QEnhancedGraphicsView : public QGraphicsView {
	Q_OBJECT

public:
	explicit QEnhancedGraphicsView( QWidget *parent = nullptr );

protected:
	void wheelEvent( QWheelEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;

signals:

public slots:

private slots:
	void clearAll( bool );
	void clearSelected( bool );
	void noEffect( bool );
	void blurEffect( bool );
	void dropShadowEffect( bool );
	void colorizeEffect( bool );
	void customEffect( bool );
	void addQGraphicsRectItem( bool );
	void addQGraphicsEllipseItem( bool );
	void addQGraphicsPathItem( bool );
	void addQGraphicsPolygonItem( bool );
	void addQGraphicsSimpleTextItem( bool );

private:
	QPointF sceneMousePos;
	QPointF fromScene;
	QGraphicsRectItem *graphicsRectItem = nullptr;
};

#endif // QENHANCEDGRAPHICSVIEW_H