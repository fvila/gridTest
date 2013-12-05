#include "gridview.h"
#include "gridscene.h"
#include "customrubberband.h"

#include <QMouseEvent>
#include <cmath>
#include <QGraphicsRectItem>

#include <QScrollBar>
#include <QDebug>

GridView::GridView(QWidget *parent) :
    QGraphicsView(parent)
{
    mode = NORMAL;

    setMouseTracking(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    viewCenter = 0;
    rubberBand = 0;
}

GridView::~GridView()
{
    delete rubberBand;
}

void GridView::setViewCenter(QGraphicsItem *viewCenter)
{
    this->viewCenter = viewCenter;
}

void GridView::mousePressEvent(QMouseEvent *event)
{
    switch (event->button())
    {
    case Qt::MidButton:
        mode = DRAG;
        origin = event->pos();

        setCursor(Qt::ClosedHandCursor);

        event->accept();
        break;
    case Qt::RightButton:
        origin = event->pos();

        if (!rubberBand)
            rubberBand = new CustomRubberBand(CustomRubberBand::Rectangle, this);

        rubberBand->setGeometry(QRect(origin, QSize()));
        rubberBand->show();

        mode = ZOOM_BOX;

        event->accept();
        break;
    default:
        event->ignore();
    }
}

void GridView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF start, end, realTranslate;

    switch (mode)
    {
    case DRAG:
        // Calculate the offset to drag relative to scene
        // coordinates.
        start = mapToScene(origin);
        end = mapToScene(event->pos());
        realTranslate = start - end;

        viewCenter->moveBy(realTranslate.x(), realTranslate.y());
        centerOn(viewCenter);

        origin = event->pos();

        event->accept();
        break;
    case ZOOM_BOX:
        rubberBand->setGeometry(QRect(origin, event->pos()).normalized());

        event->accept();
        break;
    default:
        event->ignore();
    }

    QPointF sceneCoords = mapToScene(event->pos());
    emit mouseMoved(sceneCoords.x(), sceneCoords.y());
}

void GridView::mouseReleaseEvent(QMouseEvent *event)
{
    qreal factor;

    switch(event->button())
    {
    case Qt::MidButton:
        mode = NORMAL;
        setCursor(Qt::ArrowCursor);

        event->accept();
        break;
    case Qt::RightButton:
        rubberBand->hide();
        mode = NORMAL;
        fitInView(mapToScene(rubberBand->geometry()).boundingRect(), Qt::KeepAspectRatio);
        factor = matrix().mapRect(QRectF(0, 0, 1, 1)).width();

        if (factor  <= 0.2)
            qobject_cast<GridScene *>(scene())->setGridMode(GridScene::NONE);
        else if (factor <= 0.7)
            qobject_cast<GridScene *>(scene())->setGridMode(GridScene::MAJOR);
        else
            qobject_cast<GridScene *>(scene())->setGridMode(GridScene::ALL);

        event->accept();
        break;
    default:
        event->ignore();
    }

    updateCenterRect();
}

void GridView::wheelEvent(QWheelEvent *event)
{
    qreal scaleFactor = ::pow(2.0, event->delta() / 240.0);
    qreal factor = matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

    if (factor < 0.07 || factor > 100)
        return;

    if (factor  <= 0.2)
        qobject_cast<GridScene *>(scene())->setGridMode(GridScene::NONE);
    else if (factor <= 0.7)
        qobject_cast<GridScene *>(scene())->setGridMode(GridScene::MAJOR);
    else
        qobject_cast<GridScene *>(scene())->setGridMode(GridScene::ALL);

    scale(scaleFactor, scaleFactor);

    updateCenterRect();
}

void GridView::updateCenterRect()
{
    QRect viewRect = this->viewport()->rect();

    // This setPos is necessary because we translate the rect on the mouseMove event handler
    // If we update the rect, the shape will still be translated, so we have to return
    // it to the centre of the scene.
    this->viewCenter->setPos(0, 0);
    dynamic_cast<QGraphicsRectItem*>(this->viewCenter)->setRect(mapToScene(viewRect).boundingRect());
}

void GridView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);

    updateCenterRect();
}
