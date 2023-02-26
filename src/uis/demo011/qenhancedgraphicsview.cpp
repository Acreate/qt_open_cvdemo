#include "qenhancedgraphicsview.h"

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