#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gridscene.h"

#include <QGraphicsRectItem>
#include <QLabel>

#include <limits>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new GridScene;

    ui->graphicsView->setScene(scene);
    ui->graphicsView->scale(1, -1);

    QRect viewport_rect(0, 0, ui->graphicsView->viewport()->width(),
                        ui->graphicsView->viewport()->height());
    QRectF visible_scene_rect = ui->graphicsView->mapToScene(viewport_rect).boundingRect();

    viewCenter = new QGraphicsRectItem(visible_scene_rect);

//    qDebug() << viewport_rect;
//    qDebug() << visible_scene_rect;

    this->scene->addItem(viewCenter);
    viewCenter->setPen(QPen(Qt::red));

    qobject_cast<GridView *>(ui->graphicsView)->setViewCenter(viewCenter);

    xCoordsLabel = new QLabel("X: 0");
    yCoordsLabel = new QLabel("Y: 0");

    ui->statusBar->addPermanentWidget(xCoordsLabel);
    ui->statusBar->addPermanentWidget(yCoordsLabel);

    connect(ui->graphicsView, SIGNAL(mouseMoved(qreal,qreal)),
            this, SLOT(updateCoords(qreal,qreal)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCoords(qreal x, qreal y)
{
    xCoordsLabel->setText(QString("X: %1").arg(x));
    yCoordsLabel->setText(QString("Y: %1").arg(y));
}
