#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <QGraphicsView>

class QGraphicsItem;
class CustomRubberBand;

class GridView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GridView(QWidget *parent = 0);
    ~GridView();

    void setViewCenter(QGraphicsItem* viewCenter);

signals:
    void mouseMoved(qreal x, qreal y);
    
public slots:
    
protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void wheelEvent(QWheelEvent *event);

    void updateCenterRect();

    enum CurrentMode
    {
        NORMAL,
        DRAG,
        ZOOM_BOX
    };

    CurrentMode mode;
    QPoint origin;
    QGraphicsItem* viewCenter;
    CustomRubberBand *rubberBand;
};

#endif // GRIDVIEW_H
