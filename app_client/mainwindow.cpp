#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"
#include "gameplay.h"
#include <memory>
#include <QKeyEvent>
#include <QDebug>
#include <cassert>
#include <QObject>
#include <QGraphicsProxyWidget>
#include <QPalette>
#include <QPixmap>
#include <QGraphicsPixmapItem>


MainWindow::MainWindow(Controller &controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    invisiblePoints(GamePlay::GamePlay::maximumNumberOfPlayers),
    bonusItems(7) // to wygląda brzydkoS
{
    ui->setupUi(this);

    connect(&controller, SIGNAL(setScoreBoard(qint32, qint32, qint32)), this, SLOT(setScoreBoard(qint32,qint32, qint32)));
    connect(&controller, SIGNAL(newCircle(qreal, qreal, qreal, qint32, bool)), this, SLOT(newCircle(qreal, qreal, qreal, qint32, bool)));
    connect(&controller, SIGNAL(endRoundAndClear(const std::vector<int>&)), this, SLOT(endRoundAndClear(const std::vector<int>&)));
    connect(&controller, SIGNAL(newSceneMessage(QString)), this, SLOT(printSceneMessage(QString)));
    connect(&controller, SIGNAL(clearMessages()), this, SLOT(hideSceneMessage()));
    connect(&controller, SIGNAL(showBonus(qint32,qreal,qreal)), this, SLOT(showBonus(qint32,qreal,qreal)));
    connect(&controller, SIGNAL(hideBonus(qint32)), this, SLOT(hideBonus(qint32)));
    connect(this, SIGNAL(newKeyPressedMessage(Communication::KeyPressedMessage)), &controller, SLOT(newKeyPressedMessageToSend(Communication::KeyPressedMessage)));
    connect(this, SIGNAL(newKeyReleasedMessage(Communication::KeyReleasedMessage)), &controller, SLOT(newKeyReleasedMessageToSend(Communication::KeyReleasedMessage)));
    connect(this, SIGNAL(accept()), &controller, SLOT(checkReconnect()));
    ui->graphicsView->setFrameShape(QGraphicsView::NoFrame);
    ui->graphicsView->setScene(new QGraphicsScene());
    ui->graphicsView->scene()->setParent(ui->graphicsView);
    ui->graphicsView->scene()->setSceneRect(ui->graphicsView->rect());
    ui->graphicsView->setAlignment(Qt::AlignLeft|Qt::AlignTop);
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
    else if(event->key() == Qt::Key_Space) {
        qDebug()<<"Space";
        emit accept();
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
    if(invisiblePoints[pID])
        invisiblePoints[pID].reset();

    if(isVisible) {
        ui->graphicsView->scene()->addEllipse(x-radius/2, y-radius/2, radius, radius, QPen(QColor(colors[pID])), QBrush(colors[pID]));
    }
    else {
        invisiblePoints[pID] = std::make_shared<QGraphicsEllipseItem>(x-radius/2, y-radius/2, radius, radius);
        invisiblePoints[pID]->setPen(QPen(colors[pID]));
        invisiblePoints[pID]->setBrush(QBrush(colors[pID]));
        ui->graphicsView->scene()->addItem(invisiblePoints[pID].get());
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
    clearBoard();
}

void MainWindow::setScores(const std::vector<int>& scr) {
    QLabel* labels[6] = {ui->label_2_1, ui->label_2_2, ui->label_2_3, ui->label_2_4, ui->label_2_5, ui->label_2_6 };
    for(size_t i = 0; i < scr.size(); ++i) {
        labels[i]->setText(QString::number(scr[i]));
    }
}

void MainWindow::clearBoard() {
    qDebug() << "BEFORE CLEAR";
    auto items = ui->graphicsView->scene()->items();
//Changed way of clearing messages, because we don't want to remove widget
    for (auto &it : items) {
        if(it != static_cast<QGraphicsItem*>(sceneMessage.graphicsProxyWidget())) {
            ui->graphicsView->scene()->removeItem(it);
        }
    }
    qDebug() << "AFTER CLEAR";
}

void MainWindow::showBonus(qint32 mode, qreal x, qreal y) {
    qDebug() << "WINDOW BONUS";
    if(mode == GamePlay::Modes::SQUARE || mode == GamePlay::Modes::SQUARE_O) {
        qDebug() << mode <<"   " << x << " " << y;
        bonusItems[0] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/angle.png").scaled(20,20));
        bonusItems[0]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[0].get());
    }
    else if(mode == GamePlay::Modes::FAST || mode == GamePlay::Modes::FAST_O) {
        bonusItems[1] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/fast.png").scaled(20,20));
        bonusItems[1]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[1].get());
    }
    else if(mode == GamePlay::Modes::SLOW || mode == GamePlay::Modes::SLOW_O) {
        bonusItems[2] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/slow.png").scaled(20,20));
        bonusItems[2]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[2].get());
    }
    else if(mode == GamePlay::Modes::THICK || mode == GamePlay::Modes::THICK_O) {
        bonusItems[3] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/thick.png").scaled(20,20));
        bonusItems[3]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[3].get());
    }
    else if(mode == GamePlay::Modes::THIN || mode == GamePlay::Modes::THIN_O) {
        bonusItems[4] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/thin.png").scaled(20,20));
        bonusItems[4]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[4].get());
    }
    else if(mode == GamePlay::Modes::COLLISIONLESS) {
        bonusItems[5] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/collisionless.png").scaled(20,20));
        bonusItems[5]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[5].get());
    }
    else if(mode == GamePlay::Modes::REVERSE || GamePlay::Modes::REVERSE_O) {
        bonusItems[6] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/reverse.png").scaled(20,20));
        bonusItems[6]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[6].get());
    }
    qDebug() << "END WINDOW BONUS";

}

void MainWindow::hideBonus(qint32 mode) {
    qDebug() << "HIDE BONUS WINDOW";
    if(mode == GamePlay::Modes::SQUARE || mode == GamePlay::Modes::SQUARE_O) {
        ui->graphicsView->scene()->removeItem(bonusItems[0].get());
    }
    else if(mode == GamePlay::Modes::FAST || mode == GamePlay::Modes::FAST_O) {
        ui->graphicsView->scene()->removeItem(bonusItems[1].get());
    }
    else if(mode == GamePlay::Modes::SLOW || mode == GamePlay::Modes::SLOW_O) {
        ui->graphicsView->scene()->removeItem(bonusItems[2].get());
    }
    else if(mode == GamePlay::Modes::THICK || mode == GamePlay::Modes::THICK_O) {
        ui->graphicsView->scene()->removeItem(bonusItems[3].get());
    }
    else if(mode == GamePlay::Modes::THIN || mode == GamePlay::Modes::THIN_O) {
        ui->graphicsView->scene()->removeItem(bonusItems[4].get());
    }
    else if(mode == GamePlay::Modes::COLLISIONLESS) {
        ui->graphicsView->scene()->removeItem(bonusItems[5].get());
    }
    else if(mode == GamePlay::Modes::REVERSE || mode == GamePlay::Modes::REVERSE_O) {
        ui->graphicsView->scene()->removeItem(bonusItems[6].get());
    }
    qDebug() << "HIDE BONUS WINDOWS END";
}





void MainWindow::setScoreBoard(qint32 playersCount, qint32 maxScore, qint32 playerNumber) {
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
    delete ui;
}
