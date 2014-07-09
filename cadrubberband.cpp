#include "cadrubberband.h"

#include <QStylePainter>
#include <QPaintEvent>
#include <QStyleOptionFocusRect>

CADRubberBand::CADRubberBand(Shape s, QWidget *parent) :
    QRubberBand(s, parent)
{
}

void CADRubberBand::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    QStyleOptionFocusRect option;

    option.initFrom(this);

    QPen pen;

    pen.setWidth(2);
    pen.setColor(QColor(Qt::yellow));
    painter.setPen(pen);

    painter.drawRect(event->rect());
}
