#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class GridScene;
class QGraphicsRectItem;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void updateCoords(qreal x, qreal y);

private:
    Ui::MainWindow *ui;
    GridScene *scene;

    QGraphicsRectItem *viewCenter;

    QLabel *xCoordsLabel;
    QLabel *yCoordsLabel;
};

#endif // MAINWINDOW_H
