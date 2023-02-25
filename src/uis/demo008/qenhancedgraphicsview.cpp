#include "qenhancedgraphicsview.h"
#include <QPoint>

QEnhancedGraphicsView::QEnhancedGraphicsView( QWidget *parent )
	: QGraphicsView(parent) {}

void QEnhancedGraphicsView::wheelEvent( QWheelEvent *event ) {
	auto angleDelta = event->angleDelta();
	if( !angleDelta.isNull() ) {
		double angleDeltaY = event->angleDelta().y();
		double zoomFactor = qPow(1.0015, angleDeltaY);
		scale(zoomFactor, zoomFactor);
		if( angleDeltaY > 0 ) {
			this->centerOn(sceneMousePos);
			QPointF point = event->position();
			int x = point.x(),
				y = point.y();

			QPoint mouPos(x, y);
			sceneMousePos = this->mapToScene(mouPos);
		}
		this->viewport()->update();
		event->accept();
	} else {
		event->ignore();
	}
}

void QEnhancedGraphicsView::mousePressEvent( QMouseEvent *event ) {
	if( event->button() == Qt::RightButton ) {
		QGraphicsScene *graphicsScene = scene();
		if( graphicsRectItem == nullptr ) {
			graphicsRectItem = new QGraphicsRectItem(0, 0, width(), height());
			graphicsScene->addItem(graphicsRectItem);
		}
		QPoint point = event->pos();
		fromScene = mapToScene(point);
		QMenu menu;
		QAction *clearAllAction = menu.addAction("Clear All");
		connect(clearAllAction,
			SIGNAL(triggered(bool)),
			this,
			SLOT(clearAll(bool)));

		QAction *clearSelectedAction = menu.addAction("Clear Selected");
		connect(clearSelectedAction,
			SIGNAL(triggered(bool)),
			this,
			SLOT(clearSelected(bool)));

		QAction *noEffectAction = menu.addAction("No Effect");
		connect(noEffectAction,
			SIGNAL(triggered(bool)),
			this,
			SLOT(noEffect(bool)));

		QAction *blurEffectAction = menu.addAction("Blur Effect");
		connect(blurEffectAction,
			SIGNAL(triggered(bool)),
			this,
			SLOT(blurEffect(bool)));

		QAction *dropShadEffectAction = menu.addAction("Drop Shadow Effect");
		connect(dropShadEffectAction,
			SIGNAL(triggered(bool)),
			this,
			SLOT(dropShadowEffect(bool)));

		QAction *colorizeEffectAction = menu.addAction("Colorize Effect");
		connect(colorizeEffectAction,
			SIGNAL(triggered(bool)),
			this,
			SLOT(colorizeEffect(bool)));

		QAction *customEffectAction = menu.addAction("Custom Effect");
		connect(customEffectAction,
			SIGNAL(triggered(bool)),
			this,
			SLOT(customEffect(bool)));

		/////////////
		///  	void addQGraphicsRectItem( bool );
		///  	void addQGraphicsEllipseItem( bool );
		///  	void addQGraphicsPathItem( bool );
		///  	void addQGraphicsPolygonItem( bool );
		///  	void addQGraphicsSimpleTextItem( bool );
		/////////////		
		QAction *addGraphicsItemsAction = menu.addAction("addQGraphicsRectItem");
		connect(addGraphicsItemsAction,
			SIGNAL(triggered(bool)),
			this,
			SLOT(addQGraphicsRectItem(bool)));

		addGraphicsItemsAction = menu.addAction("addQGraphicsEllipseItem");
		connect(addGraphicsItemsAction,
			SIGNAL(triggered(bool)),
			this,
			SLOT(addQGraphicsEllipseItem(bool)));
		addGraphicsItemsAction = menu.addAction("addQGraphicsPathItem");
		connect(addGraphicsItemsAction,
			SIGNAL(triggered(bool)),
			this,
			SLOT(addQGraphicsPathItem(bool)));

		addGraphicsItemsAction = menu.addAction("addQGraphicsPolygonItem");
		connect(addGraphicsItemsAction,
			SIGNAL(triggered(bool)),
			this,
			SLOT(addQGraphicsPolygonItem(bool)));

		addGraphicsItemsAction = menu.addAction("addQGraphicsSimpleTextItem");
		connect(addGraphicsItemsAction,
			SIGNAL(triggered(bool)),
			this,
			SLOT(addQGraphicsSimpleTextItem(bool)));

		menu.exec(event->globalPos());
		event->accept();
	} else {
		QGraphicsView::mousePressEvent(event);
	}
}

void QEnhancedGraphicsView::clearAll( bool ) {
	scene()->clear();
	graphicsRectItem = nullptr;
}

void QEnhancedGraphicsView::clearSelected( bool ) {
	while( scene()->selectedItems().count() > 0 ) {
		QGraphicsItem *graphicsItem = scene()->selectedItems().at(0);
		if( graphicsRectItem == graphicsItem )
			graphicsRectItem = nullptr;
		scene()->selectedItems().removeAt(0);
		delete graphicsItem;
	}
}

void QEnhancedGraphicsView::noEffect( bool ) {
	foreach(QGraphicsItem *item, scene()->selectedItems()) {
		item->setGraphicsEffect(Q_NULLPTR);
	}
}

void QEnhancedGraphicsView::blurEffect( bool ) {
	foreach(QGraphicsItem *item, scene()->selectedItems()) {
		item->setGraphicsEffect(new QGraphicsBlurEffect(this));
	}
}

void QEnhancedGraphicsView::dropShadowEffect( bool ) {
	foreach(QGraphicsItem *item, scene()->selectedItems()) {
		item->setGraphicsEffect(new QGraphicsDropShadowEffect(this));
	}
}

void QEnhancedGraphicsView::colorizeEffect( bool ) {
	foreach(QGraphicsItem *item, scene()->selectedItems()) {
		item->setGraphicsEffect(new QGraphicsColorizeEffect(this));
	}
}

void QEnhancedGraphicsView::customEffect( bool ) {
	foreach(QGraphicsItem *item, scene()->selectedItems()) {
		item->setGraphicsEffect(new QCustomGraphicsEffect(this));
	}
}

void QEnhancedGraphicsView::addQGraphicsRectItem( bool ) {
	QGraphicsRectItem *graphicsRectItem = new QGraphicsRectItem(fromScene.x() - 50, fromScene.y() - 50, 100, 100);
	scene()->addItem(graphicsRectItem);

}

void QEnhancedGraphicsView::addQGraphicsEllipseItem( bool ) {
	QGraphicsEllipseItem *graphicsEllipseItem = new QGraphicsEllipseItem(fromScene.x() - 50, fromScene.y() - 50, 100, 100);
	scene()->addItem(graphicsEllipseItem);
}

void QEnhancedGraphicsView::addQGraphicsPathItem( bool ) {
	QPainterPath qPainterPathQGraphicsPathItem;
	qPainterPathQGraphicsPathItem.moveTo(fromScene.x(), fromScene.y());
	qPainterPathQGraphicsPathItem.cubicTo(120, -20, 60, 100, 120, 80);
	QGraphicsPathItem *graphicsPathItem = new QGraphicsPathItem(qPainterPathQGraphicsPathItem);
	scene()->addItem(graphicsPathItem);

}

void QEnhancedGraphicsView::addQGraphicsPolygonItem( bool ) {
	QPolygonF qPointFs;
	qPointFs << QPointF(fromScene.x() - 50, fromScene.y() - 50) << QPointF(fromScene.x() + 50, fromScene.y() + 50);
	QGraphicsPolygonItem *graphicsPolygonItem = new QGraphicsPolygonItem(qPointFs);
	scene()->addItem(graphicsPolygonItem);
}

void QEnhancedGraphicsView::addQGraphicsSimpleTextItem( bool ) {


	QGraphicsSimpleTextItem *graphicsSimpleTextItem = new QGraphicsSimpleTextItem();
	graphicsSimpleTextItem->setText(tr("QGraphicsSimpleTextItem"));
	graphicsSimpleTextItem->setX(fromScene.x());
	graphicsSimpleTextItem->setY(fromScene.y());
	scene()->addItem(graphicsSimpleTextItem);
}