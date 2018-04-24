#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"
#include <cassert>

MainWindow::MainWindow(Controller &controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controller.setBoardPixelSize(ui->graphicsView->width());
    connect(&controller, SIGNAL(newItem(QGraphicsItem*)), this, SLOT(newItem(QGraphicsItem*)));
    QGraphicsItem *item = new QGraphicsEllipseItem(260, 260, 20, 20);
    ui->graphicsView->setScene(new QGraphicsScene());
    ui->graphicsView->scene()->setParent(ui->graphicsView);
    emit newItem(item);
}

void MainWindow::newItem(QGraphicsItem *ptr) {
    ui->graphicsView->scene()->addItem(ptr);
}

MainWindow::~MainWindow()
{
    delete ui;
}
