#include <QString>
#include <QtTest>
#include "../GamePlay/point.h"
#include "../GamePlay/board.h"

class GamePlayTest : public QObject
{
    Q_OBJECT

public:
    GamePlayTest();

private Q_SLOTS:
    void testPointCollision1();
    void testPointCollision2();
    void testBoardCollision1();
    void testBoardCollision2();
};

GamePlayTest::GamePlayTest()
{

}

void GamePlayTest::testPointCollision1()
{
    GamePlay::Point p1(0, 0, 0.1, 0, 1);
    GamePlay::Point p2(0, 0.15, 0.1, 100, 1);
    QVERIFY2(p1.checkCollision(p2), "Error in point collision test");
}

void GamePlayTest::testPointCollision2()
{
    GamePlay::Point p1(0, 1.0, 0.1, 0, 1);
    GamePlay::Point p2(0, 0.15, 0.1, 100, 1);
    QVERIFY2(!p1.checkCollision(p2), "Error in point collision test");
}

void GamePlayTest::testBoardCollision1()
{
    GamePlay::Board b;
    GamePlay::Point p1(0, 0, 0.1, 0, 1);
    GamePlay::Point p2(0, 0.15, 0.1, 100, 1);
    b.registerPoint(p1);
    QVERIFY2(b.checkCollision(p2), "Error in board collision test");
}

void GamePlayTest::testBoardCollision2()
{
    GamePlay::Board b;
    GamePlay::Point p1(0, 1.0, 0.1, 0, 1);
    GamePlay::Point p2(1.0, 0.15, 0.1, 100, 1);
    GamePlay::Point p3(0.5, 0.5, 0.1, 1, 1);
    QVERIFY2(b.checkCollision(p1), "Error in board collision test");
    QVERIFY2(b.checkCollision(p2), "Error in board collision test");
    QVERIFY2(!b.checkCollision(p3), "Error in board collision test");
}

QTEST_APPLESS_MAIN(GamePlayTest)

#include "tst_gameplaytest.moc"
