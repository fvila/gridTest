#ifndef CUSTOMRUBBERBAND_H
#define CUSTOMRUBBERBAND_H

#include <QRubberBand>

class CADRubberBand : public QRubberBand
{
public:
    explicit CADRubberBand(Shape s, QWidget *parent = 0);
    
    void paintEvent(QPaintEvent *event);
signals:
    
public slots:
    
};

#endif // CUSTOMRUBBERBAND_H
