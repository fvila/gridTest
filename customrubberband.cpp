#include "customrubberband.h"

#include <QStylePainter>
#include <QPaintEvent>
#include <QStyleOptionFocusRect>

CustomRubberBand::CustomRubberBand(Shape s, QWidget *parent) :
    QRubberBand(s, parent)
{
    QPalette palette;
    palette.setBrush(QPalette::WindowText, QBrush(Qt::red));
    setPalette(palette);

    repaint();
}

void CustomRubberBand::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    QStyleOptionFocusRect option;

    option.initFrom(this);

    QPen pen;

    pen.setStyle(Qt::DashLine);
    pen.setWidth(2);
    pen.setColor(QColor(Qt::red));
    painter.setPen(pen);

    painter.drawRect(event->rect());
}
