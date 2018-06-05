#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"
#include "modes.h"
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
    bonusItems(GamePlay::Modes::MODESCOUNT)
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
    if(invisiblePoints.at(pID))
        invisiblePoints.at(pID).reset();

    if(isVisible) {
        ui->graphicsView->scene()->addEllipse(x-radius/2, y-radius/2, radius, radius, QPen(QColor(colors.at(pID))), QBrush(colors.at(pID)));
    }
    else {
        invisiblePoints.at(pID) = std::make_shared<QGraphicsEllipseItem>(x-radius/2, y-radius/2, radius, radius);
        invisiblePoints.at(pID)->setPen(QPen(colors.at(pID)));
        invisiblePoints.at(pID)->setBrush(QBrush(colors.at(pID)));
        ui->graphicsView->scene()->addItem(invisiblePoints.at(pID).get());
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
    std::array<QLabel*, GamePlay::GamePlay::maximumNumberOfPlayers> labels = {{ui->label_2_1, ui->label_2_2, ui->label_2_3, ui->label_2_4, ui->label_2_5, ui->label_2_6 }};
    for(size_t i = 0; i < scr.size(); ++i) {
        labels.at(i)->setText(QString::number(scr[i]));
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

    switch(mode) {
    case(GamePlay::Modes::COLLISIONLESS):
        bonusItems[mode] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/collisionless.png").scaled(20,20));
        bonusItems[mode]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[mode].get());
        break;
    case(GamePlay::Modes::FAST):
        bonusItems[GamePlay::Modes::FAST] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/fast.png").scaled(20,20));
        bonusItems[GamePlay::Modes::FAST]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[GamePlay::Modes::FAST].get());
        break;
    case(GamePlay::Modes::FAST_O):
        bonusItems[GamePlay::Modes::FAST_O] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/fast_o.png").scaled(20,20));
        bonusItems[GamePlay::Modes::FAST_O]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[GamePlay::Modes::FAST_O].get());
        break;
    case(GamePlay::Modes::SLOW):
        bonusItems[GamePlay::Modes::SLOW] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/slow.png").scaled(20,20));
        bonusItems[GamePlay::Modes::SLOW]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[GamePlay::Modes::SLOW].get());
        break;
    case(GamePlay::Modes::SLOW_O):
        bonusItems[GamePlay::Modes::SLOW_O] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/slow_o.png").scaled(20,20));
        bonusItems[GamePlay::Modes::SLOW_O]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[GamePlay::Modes::SLOW_O].get());
        break;
    case(GamePlay::Modes::THICK):
        bonusItems[GamePlay::Modes::THICK] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/thick.png").scaled(20,20));
        bonusItems[GamePlay::Modes::THICK]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[GamePlay::Modes::THICK].get());
        break;
    case(GamePlay::Modes::THICK_O):
        bonusItems[GamePlay::Modes::THICK_O] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/thick_o.png").scaled(20,20));
        bonusItems[GamePlay::Modes::THICK_O]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[GamePlay::Modes::THICK_O].get());
        break;
    case(GamePlay::Modes::THIN):
        bonusItems[GamePlay::Modes::THIN] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/thin.png").scaled(20,20));
        bonusItems[GamePlay::Modes::THIN]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[GamePlay::Modes::THIN].get());
        break;
    case(GamePlay::Modes::THIN_O):
        bonusItems[GamePlay::Modes::THIN_O] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/thin_o.png").scaled(20,20));
        bonusItems[GamePlay::Modes::THIN_O]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[GamePlay::Modes::THIN_O].get());
        break;
    case(GamePlay::Modes::SQUARE):
        bonusItems[GamePlay::Modes::SQUARE] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/angle.png").scaled(20,20));
        bonusItems[GamePlay::Modes::SQUARE]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[GamePlay::Modes::SQUARE].get());
        break;
    case(GamePlay::Modes::SQUARE_O):
        bonusItems[GamePlay::Modes::SQUARE_O] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/angle_o.png").scaled(20,20));
        bonusItems[GamePlay::Modes::SQUARE_O]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[GamePlay::Modes::SQUARE_O].get());
        break;
    case(GamePlay::Modes::REVERSE):
        bonusItems[GamePlay::Modes::REVERSE] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/reverse.png").scaled(20,20));
        bonusItems[GamePlay::Modes::REVERSE]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[GamePlay::Modes::REVERSE].get());
        break;
    case(GamePlay::Modes::REVERSE_O):
        bonusItems[GamePlay::Modes::REVERSE_O] = std::make_shared<QGraphicsPixmapItem>(QPixmap("pic/reverse_o.png").scaled(20,20));
        bonusItems[GamePlay::Modes::REVERSE_O]->setOffset(x,y);
        ui->graphicsView->scene()->addItem(bonusItems[GamePlay::Modes::REVERSE_O].get());
        break;
    }
    qDebug() << "END WINDOW BONUS";

}

void MainWindow::hideBonus(qint32 mode) {
    qDebug() << "HIDE BONUS WINDOW";
    ui->graphicsView->scene()->removeItem(bonusItems[mode].get());
    qDebug() << "HIDE BONUS WINDOWS END";
}





void MainWindow::setScoreBoard(qint32 playersCount, qint32 maxScore, qint32 playerNumber) {
    nPlayers = playersCount;
    std::array<QLabel*, GamePlay::GamePlay::maximumNumberOfPlayers> labels_n = {{ui->label_1_1, ui->label_1_2, ui->label_1_3, ui->label_1_4, ui->label_1_5, ui->label_1_6 }};
    std::array<QLabel*, GamePlay::GamePlay::maximumNumberOfPlayers> labels_s = {{ui->label_2_1, ui->label_2_2, ui->label_2_3, ui->label_2_4, ui->label_2_5, ui->label_2_6 }};
    for(int i = 0; i < nPlayers; ++i) {

        labels_n.at(i)->setVisible(true);
        labels_s.at(i)->setVisible(true);
    }
    ui->label_Not->setText(QString("First Player to reach " + QString::number(maxScore) + " points wins!"));
    ui->label_Not->setVisible(true); //labels
    QPalette palette;
    palette.setColor(QPalette::WindowText, colors.at(playerNumber));
    palette.setBrush(QPalette::WindowText, QBrush(colors.at(playerNumber)));
    ui->label_color->setPalette(palette);
    ui->label_color->setText(QString::fromStdString(std::string("Your color is " + colorsName.at(playerNumber))));
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
