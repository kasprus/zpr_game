#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QGraphicsItem>
#include <memory>
#include "point.h"

class GameClient;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(GameClient& client, QObject *parent = 0);
    void setBoardPixelSize(int size);
signals:
    void newItem(QGraphicsItem*);


private slots:
    void newPoint(GamePlay::Point);

private:
    qreal boardPixelSize;


};

#endif // CONTROLLER_H
