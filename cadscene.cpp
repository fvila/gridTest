#include "cadscene.h"

#include <QPainter>

#include <cmath>

#include <QDebug>

CADScene::CADScene(QObject *parent) :
    QGraphicsScene(parent)
{
    space = 50;
    min_space = 10;
    mode = ALL;

    setBackgroundBrush(Qt::black);
}

void CADScene::setGridMode(CADScene::GridMode mode)
{
    this->mode = mode;
}

void CADScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->save();

    double x = rect.x();
    double y = rect.y();

    QRectF newRect(rect);
    newRect.setTopLeft(QPointF(floor(x/space)*space,
                               floor(y/space)*space));

    QPolygonF whitePoints, greenPoints;
    painter->fillRect(newRect, backgroundBrush());

    switch (mode)
    {
    case ALL:
        for (qreal i = newRect.left(); i < newRect.right(); i = i + min_space)
        {
            for (qreal j = newRect.top(); j < newRect.bottom(); j = j + min_space)
            {
                greenPoints.append(QPointF(i, j));
            }
        }
    case MAJOR:
        for (qreal i = newRect.left(); i < newRect.right(); i = i + space)
        {
            for (qreal j = newRect.top(); j < newRect.bottom(); j = j + space)
            {
                whitePoints.append(QPointF(i, j));
            }
        }
    case NONE:
    default:
        break;
    }

    if (!greenPoints.empty())
    {
       painter->setPen(Qt::darkGreen);
       painter->drawPoints(greenPoints);
    }

    if (!whitePoints.empty())
    {
        painter->setPen(Qt::white);
        painter->drawPoints(whitePoints);
    }

    // Short origin marker
//    painter->setPen(Qt::lightGray);
//    painter->drawLine(-20, 0, 20, 0);
//    painter->drawLine(0, -20, 0, 20);

    // Long origin marker
    painter->setPen(Qt::lightGray);
    painter->drawLine(0, rect.top(), 0, rect.bottom());
    painter->drawLine(rect.left(), 0, rect.right(), 0);

    painter->restore();
}
