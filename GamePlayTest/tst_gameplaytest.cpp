#include <QString>
#include <QtTest>
#include <chrono>
#include "point.h"
#include "board.h"
#include "modes.h"
#include "gameplay.h"
#include "player.h"
#include <QDebug>

class GamePlayTest : public QObject
{
    Q_OBJECT

public:
    GamePlayTest();

private Q_SLOTS:
    void testPointProperties1();
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
    void testPlayerProperties1();
    void testPlayerPropertiesAfterReset1();
    void testPlayerInactivity1();
    void testBoardClear1();
    void testNewBonusID1();
    void testNewBonusID2();
    void testBonusBoard1();
    void testBonusActivity1();
    void testBonusActivity2();
    void testBonusActivity3();
    void testBonus();
    void testBonusMovement1();
    void testBonusMovement2();
    void testBonusMovement3();
    void testBonusMovement4();
    void testBonusReset();
    void testGamemode();
};

GamePlayTest::GamePlayTest()
{

}

void GamePlayTest::testPointProperties1() {
    GamePlay::Point p(0.0, 0.0, 0.0, 1, 2, true);
    QVERIFY2(p.getX() == 0.0, "Wrong X position");
    QVERIFY2(p.getY() == 0.0, "Wrong Y position");
    QVERIFY2(p.getRadius() == 0.0, "Wrong radius");
    QVERIFY2(p.getTurnNumber() == 1, "Wrong turn number");
    QVERIFY2(p.getPlayerId() == 2, "Wrong player ID");
    QVERIFY2(p.isVisible(), "Should be visible");
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

void GamePlayTest::testPlayerProperties1() {
    GamePlay::Player p(1, 0.0, 0.0, 0.0);
    QVERIFY2(p.getID() == 1, "Wrong ID");
    QVERIFY2(p.getScore() == 0, "Wrong score number");
    QVERIFY2(p.getX() == 0.0, "Wrong X position");
    QVERIFY2(p.getY() == 0.0, "Wrong Y position");
    QVERIFY2(p.isActive() == true, "Player is inactive");
}

void GamePlayTest::testPlayerPropertiesAfterReset1() {
    GamePlay::Player p(1, 0.0, 0.0, 0.0);
    p.reset();
    QVERIFY2(p.getID() == 1, "Wrong ID");
    QVERIFY2(p.getScore() == 0, "Wrong score number");
    QVERIFY2(p.getX() == 0.0, "Wrong X position");
    QVERIFY2(p.getY() == 0.0, "Wrong Y position");
    QVERIFY2(p.isActive() == true, "Player is inactive");
}

void GamePlayTest::testPlayerInactivity1() {
    GamePlay::Player p(1, 0.0, 0.0, 0.0);
    p.setInactive();
    QVERIFY2(p.isActive() == false, "Player is active");
    p.reset();
    QVERIFY2(p.isActive() == false, "Player is active");
    p.setActive();
    QVERIFY2(p.isActive() == true, "Player is inactive");
}

void GamePlayTest::testBoardClear1() {
    GamePlay::Board b;
    for(int i = 0; i < 100; ++i) {
        b.registerPoint(GamePlay::Point(0.5, 0.5, 0.1, 1, 1, true));
    }
    QVERIFY2(b.checkCollision(GamePlay::Point(0.5, 0.5, 0.1, 1000, 1, true)), "Points should make collision");
    b.eraseBoard();
    QVERIFY2(!b.checkCollision(GamePlay::Point(0.5, 0.5, 0.1, 1000, 1, true)), "Board is not clean");
}

void GamePlayTest::testNewBonusID1() {
    GamePlay::GameMode gamemode;
    GamePlay::Bonus bonus = gamemode.tryBonus();
    while(bonus.getMode() != GamePlay::Modes::FAST_O) {
       gamemode.removeAllBonuses();
       bonus = gamemode.tryBonus();
    }

    GamePlay::Bonus bonus1 = gamemode.tryBonus();
    while (bonus1.getMode() == GamePlay::Modes::EMPTY_BONUS) {
        bonus1 = gamemode.tryBonus();
    }
    QVERIFY2(bonus.getMode() == GamePlay::Modes::FAST_O, "Wrong mode");
    QVERIFY2(bonus1.getMode() != GamePlay::Modes::EMPTY_BONUS, "Wrong mode");


    GamePlay::Bonus bns_fast = gamemode.getBonus(GamePlay::Modes::FAST);
    GamePlay::Bonus bns_slow = gamemode.getBonus(GamePlay::Modes::SLOW_O);
    GamePlay::Bonus bns_slow_o = gamemode.getBonus(GamePlay::Modes::SLOW);
    QVERIFY2(bns_fast.getMode() == -1, "Cannot create this bonus while fast bonus is present");
    QVERIFY2(bns_slow.getMode() == -1, "Cannot create this bonus while fast bonus is present");
    QVERIFY2(bns_slow_o.getMode() == -1, "Cannot create this bonus while fast bonus is present");
}

void GamePlayTest::testNewBonusID2() {
    GamePlay::GameMode gamemode;
    GamePlay::Bonus bonus = gamemode.tryBonus();
    while(bonus.getMode() != GamePlay::Modes::THICK) {
        gamemode.removeAllBonuses();
        bonus = gamemode.tryBonus();
    }
    GamePlay::Bonus bonus1 = gamemode.tryBonus();
    while (bonus1.getMode() == GamePlay::Modes::EMPTY_BONUS) {
        bonus1 = gamemode.tryBonus();
    }
    QVERIFY2(bonus.getMode() == GamePlay::Modes::THICK, "Wrong mode");
    QVERIFY2(bonus1.getMode() != GamePlay::Modes::EMPTY_BONUS, "Wrong mode");

    GamePlay::Bonus bns_thin = gamemode.getBonus(GamePlay::Modes::THIN);
    GamePlay::Bonus bns_thin_o = gamemode.getBonus(GamePlay::Modes::THIN_O);
    GamePlay::Bonus bns_thick_o = gamemode.getBonus(GamePlay::Modes::THICK_O);
    QVERIFY2(bns_thin.getMode() == -1, "Cannot create this bonus while fast bonus is present");
    QVERIFY2(bns_thin_o.getMode() == -1, "Cannot create this bonus while fast bonus is present");
    QVERIFY2(bns_thick_o.getMode() == -1, "Cannot create this bonus while fast bonus is present");
}

void GamePlayTest::testBonus() {
    GamePlay::Bonus bonus(GamePlay::Modes::FAST, 0);
    QVERIFY2(bonus.isActive() == false, "Bonus should be inactive");
}

void GamePlayTest::testBonusActivity1() {
    GamePlay::Player player(0, 0.5, 0.5, 1);

    GamePlay::Bonus bonus(GamePlay::Modes::COLLISIONLESS);
    QVERIFY2(bonus.isActive() == false, "Bonus should be inactive");
    bonus.setActive(0);
    player.updateMode(bonus);
    GamePlay::Point point(player.move(1));

    QVERIFY2(point.isVisible() == false, "Point should be invisible");
}

void GamePlayTest::testBonusActivity2() {
    GamePlay::Player player(0, 0.5, 0.5, 1);


    GamePlay::Bonus bonus(GamePlay::Modes::THICK);
    bonus.setActive(0);
    player.updateMode(bonus);
    GamePlay::Point point(player.move(1));

    QVERIFY2(point.getRadius() == GamePlay::GamePlay::bigRadius, "Radius should change");
}

void GamePlayTest::testBonusActivity3() {
    GamePlay::Player player(0, 0.5, 0.5, 1);


    GamePlay::Bonus bonus(GamePlay::Modes::THICK_O);
    bonus.setActive(0);
    player.updateMode(bonus);
    GamePlay::Point point(player.move(1));

    QVERIFY2(point.getRadius() == GamePlay::GamePlay::defaultRadius, "Radius should not change");
}

void GamePlayTest::testBonusReset() {
    GamePlay::Player player(3, 0.5, 0.5, 1);
    GamePlay::Bonus bonus0(GamePlay::Modes::FAST);
    GamePlay::Bonus bonus1(GamePlay::Modes::THICK);
    bonus0.setActive(3);
    bonus1.setActive(3);
    player.updateMode(bonus0);
    player.updateMode(bonus1);
    GamePlay::Point point(player.move(1));

    QVERIFY2(point.getRadius() == GamePlay::GamePlay::bigRadius, "Wrong radius");
    player.updateMode(GamePlay::Bonus(GamePlay::Modes::NORMAL));
    GamePlay::Point point1(player.move(2));
    QVERIFY2(point1.getRadius() == GamePlay::GamePlay::defaultRadius, "Wrong radius");
}

void GamePlayTest::testBonusMovement1() {
    GamePlay::Player player(0, 0.5, 0.5, 0);
    GamePlay::Bonus bonus(GamePlay::Modes::SQUARE);
    bonus.setActive(0);
    player.updateMode(bonus);
    GamePlay::Point point1 = player.move(1);
    QVERIFY2(point1.getX() >= 0.5, "Wrong movement");
    QVERIFY2(point1.getY() == 0.5, "Wrong movement");
    player.setRotatingRight();
    GamePlay::Point point2 = player.move(2);
    QVERIFY2(point2.getY() > 0.5, "Wrong movement");
}

void GamePlayTest::testBonusMovement2() {
    GamePlay::Player player(0, 0.5, 0.5, 0);
    GamePlay::Bonus bonus(GamePlay::Modes::REVERSE);
    bonus.setActive(0);
    player.updateMode(bonus);
    GamePlay::Point point1 = player.move(1);
    QVERIFY2(point1.getX() >= 0.5, "Wrong movement");
    QVERIFY2(point1.getY() == 0.5, "Wrong movement");
    player.setRotatingRight();
    GamePlay::Point point2 = player.move(2);
    QVERIFY2(point2.getY() < 0.5, "Wrong movement");

}

void GamePlayTest::testBonusMovement3() {
    GamePlay::Player player0(0, 0.2, 0.2, 0);
    GamePlay::Player player1(1, 0.2, 0.8, 0);

    GamePlay::Bonus bonus1(GamePlay::Modes::FAST);
    bonus1.setActive(0);
    player0.updateMode(bonus1);

    GamePlay::Point point0 = player0.move(1);
    GamePlay::Point point1 = player1.move(1);

    QVERIFY2(point0.getY() == 0.2, "Wrong movement");
    QVERIFY2(point1.getY() == 0.8, "Wrong movement");

    QVERIFY2(point0.getX() > point1.getX(), "Wrong movement");

}

void GamePlayTest::testBonusMovement4() {
    GamePlay::Player player0(0, 0.2, 0.2, 0);
    GamePlay::Player player1(1, 0.2, 0.8, 0);

    GamePlay::Bonus bonus1(GamePlay::Modes::SLOW);
    bonus1.setActive(0);
    player0.updateMode(bonus1);

    GamePlay::Point point0 = player0.move(1);
    GamePlay::Point point1 = player1.move(1);

    QVERIFY2(point0.getY() == 0.2, "Wrong movement");
    QVERIFY2(point1.getY() == 0.8, "Wrong movement");

    QVERIFY2(point0.getX() < point1.getX(), "Wrong movement");

}


void GamePlayTest::testBonusBoard1() {
    GamePlay::Board board;
    GamePlay::Bonus bonus(GamePlay::Modes::COLLISIONLESS, -1, std::chrono::system_clock::now(), 0.1, 0.1);
    GamePlay::Player player(3, 0.09, 0.13, 0);
    board.registerBonus(bonus);
    GamePlay::Point pointBeforeMove = player.getPoint(0);

    auto bonusCheck = board.checkBonusCollision(pointBeforeMove);
    QVERIFY2(bonusCheck.getMode() == -1, "There should be no collsion");
    QVERIFY2(bonusCheck.isActive() == false, "Bonus should be inactive");
    GamePlay::Point pointAfterMove = player.move(1);
    bonusCheck = board.checkBonusCollision(pointAfterMove);

    QVERIFY2(bonusCheck.getMode() != -1, "There shouldbe collision");
    QVERIFY2(bonusCheck.getPlayerID() == 3, "Wrong Player");
    QVERIFY2(bonusCheck.isActive() == true, "Bonus should be active");
}

void GamePlayTest::testGamemode() {
    GamePlay::GameMode gamemode;
    GamePlay::Bonus bonus = gamemode.tryBonus();
    while(bonus.getMode() == GamePlay::Modes::EMPTY_BONUS) {
        bonus = gamemode.tryBonus();
    }
    QVERIFY2(gamemode.getBonus(bonus.getMode()).getMode() != GamePlay::Modes::EMPTY_BONUS, "Wrong behaviour" );
    gamemode.removeAllBonuses();
    QVERIFY2(gamemode.getBonus(bonus.getMode()).getMode() == GamePlay::Modes::EMPTY_BONUS, "Should be empty");
}




QTEST_APPLESS_MAIN(GamePlayTest)

#include "tst_gameplaytest.moc"
