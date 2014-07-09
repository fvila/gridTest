#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <QGraphicsView>

class QGraphicsItem;
class CADRubberBand;

class CADView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CADView(QWidget *parent = 0);
    ~CADView();

    void setViewCenter(QGraphicsItem* viewCenter);

signals:
    void mouseMoved(qreal x, qreal y);
    
public slots:

private:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void wheelEvent(QWheelEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);

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
    CADRubberBand *rubberBand;
};

#endif // GRIDVIEW_H
