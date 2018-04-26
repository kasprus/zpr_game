#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"
#include <QKeyEvent>
#include <QDebug>
#include <cassert>

MainWindow::MainWindow(Controller &controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pen.setColor(Qt::red);
    connect(&controller, SIGNAL(newCircle(qreal, qreal, qreal)), this, SLOT(newCircle(qreal, qreal, qreal)));
    connect(this, SIGNAL(newKeyPressedMessage(Communication::KeyPressedMessage)), &controller, SLOT(newKeyPressedMessageToSend(Communication::KeyPressedMessage)));
    connect(this, SIGNAL(newKeyReleasedMessage(Communication::KeyReleasedMessage)), &controller, SLOT(newKeyReleasedMessageToSend(Communication::KeyReleasedMessage)));
    ui->graphicsView->setScene(new QGraphicsScene());
    ui->graphicsView->scene()->setParent(ui->graphicsView);
    ui->graphicsView->scene()->setSceneRect(0, 0, ui->graphicsView->height(), ui->graphicsView->height());
    ui->graphicsView->setAlignment(Qt::AlignCenter);
    controller.setBoardPixelSize(ui->graphicsView->scene()->height() - ui->graphicsView->viewport()->height());
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(event->isAutoRepeat())return;
    qDebug()<<"Some key pressed";
    if(event->key() == Qt::Key_A) {
        qDebug()<<"Left key pressed";
        emit newKeyPressedMessage(Communication::KeyPressedMessage(Communication::Communication::leftKeyId));
    }
    else if(event->key() == Qt::Key_D) {
        qDebug()<<"Right key pressed";
        emit newKeyPressedMessage(Communication::KeyPressedMessage(Communication::Communication::rightKeyId));
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if(event->isAutoRepeat())return;
    qDebug()<<"Some key released";
    if(event->key() == Qt::Key_A) {
        qDebug()<<"Left key released";
        emit newKeyReleasedMessage(Communication::KeyReleasedMessage(Communication::Communication::leftKeyId));
    }
    else if(event->key() == Qt::Key_D) {
        qDebug()<<"Right key released";
        emit newKeyReleasedMessage(Communication::KeyReleasedMessage(Communication::Communication::rightKeyId));
    }
}

void MainWindow::newCircle(qreal x, qreal y, qreal radius) {
    ui->graphicsView->scene()->addEllipse(x, y, radius, radius, pen, QBrush(Qt::red));
}

MainWindow::~MainWindow()
{
    delete ui;
}
