#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>

class CADScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CADScene(QObject *parent = 0);
    
    enum GridMode
    {
        ALL,
        MAJOR,
        NONE
    };

    void setGridMode(GridMode mode);

signals:
    
public slots:
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    int space;
    int min_space;

    GridMode mode;
};

#endif // GRIDSCENE_H
