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
    //auto const labels = {ui->label, ui->label_2, ui->label_3, ui->label_4, ui->label_5, ui->label_6 };
    pen.setColor(Qt::red); //todo:change color
    connect(&controller, SIGNAL(setWindows(qint32, qint32)), this, SLOT(setWindows(qint32,qint32)));
    connect(&controller, SIGNAL(newCircle(qreal, qreal, qreal, qint32)), this, SLOT(newCircle(qreal, qreal, qreal, qint32)));
    connect(&controller, SIGNAL(endRoundAndClear(const std::vector<int>&)), this, SLOT(endRoundAndClear(const std::vector<int>&)));
    connect(this, SIGNAL(newKeyPressedMessage(Communication::KeyPressedMessage)), &controller, SLOT(newKeyPressedMessageToSend(Communication::KeyPressedMessage)));
    connect(this, SIGNAL(newKeyReleasedMessage(Communication::KeyReleasedMessage)), &controller, SLOT(newKeyReleasedMessageToSend(Communication::KeyReleasedMessage)));
    ui->graphicsView->setScene(new QGraphicsScene());
    ui->graphicsView->scene()->setParent(ui->graphicsView);
    ui->graphicsView->scene()->setSceneRect(0, 0, ui->graphicsView->height() - ui->graphicsView->viewport()->height() * 0.35, ui->graphicsView->height() - ui->graphicsView->viewport()->height() * 0.35);
    ui->graphicsView->setAlignment(Qt::AlignLeft);
    controller.setBoardPixelSize(ui->graphicsView->scene()->height());
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
//change color
void MainWindow::newCircle(qreal x, qreal y, qreal radius, qint32 pID) {
    ui->graphicsView->scene()->addEllipse(x, y, radius, radius, Qt::NoPen, QBrush(colors[pID]));// ?
}


void MainWindow::endRoundAndClear(const std::vector<int>& scr) {
    setScores(scr);
    clearBoard();
}

void MainWindow::setScores(const std::vector<int>& scr) {
    QLabel* labels[6] = {ui->label_2_1, ui->label_2_2, ui->label_2_3, ui->label_2_4, ui->label_2_5, ui->label_2_6 };
    for(size_t i = 0; i < scr.size(); ++i) {

        labels[i]->setText(QString::number(scr[i]));
    }
}

void MainWindow::clearBoard() {
    ui->graphicsView->scene()->clear();
}

void MainWindow::setWindows(qint32 nPlayers, qint32 maxScore) {
    qDebug() << nPlayers << maxScore;
    QLabel* labels_n[6] = {ui->label_1_1, ui->label_1_2, ui->label_1_3, ui->label_1_4, ui->label_1_5, ui->label_1_6 };
    QLabel* labels_s[6] = {ui->label_2_1, ui->label_2_2, ui->label_2_3, ui->label_2_4, ui->label_2_5, ui->label_2_6 };
    for(int i = 0; i < nPlayers; ++i) {

        labels_n[i]->setVisible(true);
        labels_s[i]->setVisible(true);
    }
    ui->label_Not->setText(QString("First Player to reach " + QString::number(maxScore) + " points wins!"));
    ui->label_Not->setVisible(true); //labels
}

MainWindow::~MainWindow()
{
    delete ui;
}
