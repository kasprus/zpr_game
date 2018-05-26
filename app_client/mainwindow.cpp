#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"
#include <memory>
#include <QKeyEvent>
#include <QDebug>
#include <cassert>
#include <QObject>
#include <QGraphicsProxyWidget>
#include <QPalette>


MainWindow::MainWindow(Controller &controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    invisiblePoints(6, nullptr)
{
    ui->setupUi(this);

    connect(&controller, SIGNAL(setWindows(qint32, qint32, qint32)), this, SLOT(setWindows(qint32,qint32, qint32)));
    connect(&controller, SIGNAL(newCircle(qreal, qreal, qreal, qint32, bool)), this, SLOT(newCircle(qreal, qreal, qreal, qint32, bool)));
    connect(&controller, SIGNAL(endRoundAndClear(const std::vector<int>&)), this, SLOT(endRoundAndClear(const std::vector<int>&)));
    connect(&controller, SIGNAL(newSceneMessage(QString)), this, SLOT(printSceneMessage(QString)));
    connect(&controller, SIGNAL(clearMessages()), this, SLOT(hideSceneMessage()));
    connect(this, SIGNAL(newKeyPressedMessage(Communication::KeyPressedMessage)), &controller, SLOT(newKeyPressedMessageToSend(Communication::KeyPressedMessage)));
    connect(this, SIGNAL(newKeyReleasedMessage(Communication::KeyReleasedMessage)), &controller, SLOT(newKeyReleasedMessageToSend(Communication::KeyReleasedMessage)));
    ui->graphicsView->setScene(new QGraphicsScene());
    ui->graphicsView->scene()->setParent(ui->graphicsView);
    ui->graphicsView->scene()->setSceneRect(0, 0, ui->graphicsView->height() - ui->graphicsView->viewport()->height() * 0.35, ui->graphicsView->height() - ui->graphicsView->viewport()->height() * 0.35);
    ui->graphicsView->setAlignment(Qt::AlignLeft);
    ui->graphicsView->scene()->addWidget(&sceneMessage);
    controller.setBoardPixelSize(ui->graphicsView->scene()->height());
    controller.setColors(getColorNames());
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


void MainWindow::newCircle(qreal x, qreal y, qreal radius, qint32 pID, bool isVisible) {
       if(invisiblePoints[pID]) {
         delete invisiblePoints[pID];
         invisiblePoints[pID] = nullptr;
    }


    if(isVisible) {
        ui->graphicsView->scene()->addEllipse(x, y, radius, radius, Qt::NoPen, QBrush(colors[pID]));
    }
    else {
        invisiblePoints[pID] = new QGraphicsEllipseItem(x, y, radius, radius);
        invisiblePoints[pID]->setBrush(QBrush(colors[pID]));
        ui->graphicsView->scene()->addItem(invisiblePoints[pID]);
    }
}

void MainWindow::printSceneMessage(QString message) {
    sceneMessage.setVisible(true);
    sceneMessage.setText(message);
    sceneMessage.setAlignment(Qt::AlignCenter);
    sceneMessage.setStyleSheet("QLabel {color : blue; font-size : 40px; background-color : black;}");

}


void MainWindow::endRoundAndClear(const std::vector<int>& scr) {
    setScores(scr);
    clearBoard(scr.size());
}

void MainWindow::setScores(const std::vector<int>& scr) {
    QLabel* labels[6] = {ui->label_2_1, ui->label_2_2, ui->label_2_3, ui->label_2_4, ui->label_2_5, ui->label_2_6 };
    for(size_t i = 0; i < scr.size(); ++i) {
        labels[i]->setText(QString::number(scr[i]));
    }
}

void MainWindow::clearBoard(int sz) {

    for(int i = 0; i < sz; ++i) {
        if(invisiblePoints[i]) {
            delete invisiblePoints[i];
            invisiblePoints[i] = nullptr;
        }
    }
    auto items = ui->graphicsView->scene()->items();
//Changed way of clearing messages, because we don't want to remove widget
    for (auto &it : items) {
        if(it != static_cast<QGraphicsItem*>(sceneMessage.graphicsProxyWidget())) {
            ui->graphicsView->scene()->removeItem(it);
            delete it;
        }
    }
}

void MainWindow::setWindows(qint32 playersCount, qint32 maxScore, qint32 playerNumber) {
    nPlayers = playersCount;
    QLabel* labels_n[6] = {ui->label_1_1, ui->label_1_2, ui->label_1_3, ui->label_1_4, ui->label_1_5, ui->label_1_6 };
    QLabel* labels_s[6] = {ui->label_2_1, ui->label_2_2, ui->label_2_3, ui->label_2_4, ui->label_2_5, ui->label_2_6 };
    for(int i = 0; i < nPlayers; ++i) {

        labels_n[i]->setVisible(true);
        labels_s[i]->setVisible(true);
    }
    ui->label_Not->setText(QString("First Player to reach " + QString::number(maxScore) + " points wins!"));
    ui->label_Not->setVisible(true); //labels
    QPalette palette;
    palette.setColor(QPalette::WindowText, colors[playerNumber]);
    palette.setBrush(QPalette::WindowText, QBrush(colors[playerNumber]));
    ui->label_color->setPalette(palette);
    ui->label_color->setText(QString::fromStdString(std::string("Your color is " + colorsName[playerNumber])));
}

void MainWindow::hideSceneMessage() {
    sceneMessage.setVisible(false);
}

const std::vector<std::string> MainWindow::getColorNames() const{
    return colorsName;
}

MainWindow::~MainWindow()
{
    for(int i = 0; i < nPlayers; ++i) {
        if(invisiblePoints[i]) {
            delete invisiblePoints[i];
        }
    }
    delete ui;
}
