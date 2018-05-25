#include <QString>
#include <QtTest>
#include "point.h"
#include "board.h"

class GamePlayTest : public QObject
{
    Q_OBJECT

public:
    GamePlayTest();

private Q_SLOTS:
    void testPointCollision1();
    void testPointCollision2();
    void testPointCollision3();
    void testTwoInvisibleCollisionTest1();
    void testBoardCollision1();
    void testBoardCollision2();
    void testPlayerPoints1();
    void testPlayerDirections1();
    void testPlayerDirections2();
    void testPlayerDirections3();
    void testPlayerDirections4();
};

GamePlayTest::GamePlayTest()
{

}

void GamePlayTest::testPointCollision1()
{
    GamePlay::Point p1(0, 0, 0.1, 0, 1, true);
    GamePlay::Point p2(0, 0.15, 0.1, 100, 1, true);
    QVERIFY2(p1.checkCollision(p2), "Error in point collision test");
}

void GamePlayTest::testPointCollision2()
{
    GamePlay::Point p1(0, 1.0, 0.1, 0, 1, true);
    GamePlay::Point p2(0, 0.15, 0.1, 100, 1, true);
    QVERIFY2(!p1.checkCollision(p2), "Error in point collision test");
}

void GamePlayTest::testPointCollision3()
{
    GamePlay::Point p1(0, 1.0, 0.1, 0, 1, true);
    GamePlay::Point p2(0, 1.0, 0.1, 100, 1, true);
    QVERIFY2(p1.checkCollision(p2), "Error - the same points should collide");
}

void GamePlayTest::testTwoInvisibleCollisionTest1()
{
    GamePlay::Point p1(0, 1.0, 0.1, 0, 1);
    GamePlay::Point p2(0, 1.0, 0.1, 100, 1);
    QVERIFY2(!p1.checkCollision(p2), "Error - two invisible points can't collide");
    QVERIFY2(!p2.checkCollision(p1), "Error - two invisible points can't collide");
}

void GamePlayTest::testBoardCollision1()
{
    GamePlay::Board b;
    GamePlay::Point p1(0, 0, 0.1, 0, 1, true);
    GamePlay::Point p2(0, 0.15, 0.1, 100, 1, true);
    b.registerPoint(p1);
    QVERIFY2(b.checkCollision(p2), "Error in board collision test");
}

void GamePlayTest::testBoardCollision2()
{
    GamePlay::Board b;
    GamePlay::Point p1(0, 1.0, 0.1, 0, 1, true);
    GamePlay::Point p2(1.0, 0.15, 0.1, 100, 1, true);
    GamePlay::Point p3(0.5, 0.5, 0.1, 1, 1, true);
    QVERIFY2(b.checkCollision(p1), "Error in board collision test");
    QVERIFY2(b.checkCollision(p2), "Error in board collision test");
    QVERIFY2(!b.checkCollision(p3), "Error in board collision test");
}

void GamePlayTest::testPlayerPoints1() {
    GamePlay::Player p(1, 0, 0, 0);
    int sum = 0;
    for(int i = 0; i < 100; ++i) {
        sum += i;
        p.addScore(i);
    }
    QVERIFY2(sum == p.getScore(), "Wrong number of points");
}

void GamePlayTest::testPlayerDirections1() {
    GamePlay::Player p(1, 0, 0, 0);
    double x = 0;
    double y = 0;
    p.move(1);
    QVERIFY2(p.getX() > x, "Wrong movement effects");
    QVERIFY2(p.getY() == y, "Wrong movement effects");
}

void GamePlayTest::testPlayerDirections2() {
    GamePlay::Player p(1, 0, 0, 0);
    p.setRotatingLeft();
    double x = 0;
    double y = 0;
    p.move(1);
    QVERIFY2(p.getX() > x, "Wrong movement effects");
    QVERIFY2(p.getY() < y, "Wrong movement effects");
}

void GamePlayTest::testPlayerDirections3() {
    GamePlay::Player p(1, 0, 0, 0);
    p.setRotatingRight();
    double x = 0;
    double y = 0;
    p.move(1);
    QVERIFY2(p.getX() > x, "Wrong movement effects");
    QVERIFY2(p.getY() > y, "Wrong movement effects");
}

void GamePlayTest::testPlayerDirections4() {
    GamePlay::Player p(1, 0, 0, 0);
    p.setRotatingRight();
    p.setRotatingLeft();
    double x = 0;
    double y = 0;
    p.move(1);
    QVERIFY2(p.getX() > x, "Wrong movement effects");
    QVERIFY2(p.getY() == y, "Wrong movement effects");
}

QTEST_APPLESS_MAIN(GamePlayTest)

#include "tst_gameplaytest.moc"
