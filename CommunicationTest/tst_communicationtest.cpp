#include <memory>
#include <exception>
#include <QString>
#include <QtTest>

#include "message.h"
#include "pointmessage.h"
#include "keypressedmessage.h"
#include "translatortoarray.h"
#include "communication.h"
#include "point.h"
#include "translatorfromarray.h"
#include "keyreleasedmessage.h"
#include "gamedelaymessage.h"
#include "gameovermessage.h"
#include "gamestartmessage.h"
#include "roundendmessage.h"
#include "gamescoremessage.h"


class CommunicationTest : public QObject
{
    Q_OBJECT

public:
    CommunicationTest();

private Q_SLOTS:
    void pointMessageSizeTest1();
    void outputPointMessageTest1();
    void pointMessageSizeTest2();
    void outputPointMessageTest2();
    void keyPressedMessegeSizeTest1();
    void outputKeyPressedMessegeTest1();
    void keyReleasedMessegeSizeTest1();
    void outputKeyReleasedMessegeTest1();
    void gameDelayMessageTest1();
    void gameOverMessageTest1();
    void gameStartMessageTest1();
    void roundEndMessageTest1();
};

CommunicationTest::CommunicationTest()
{
}

void CommunicationTest::pointMessageSizeTest1()
{
    GamePlay::Point p1(0, 0, 0.1, 0, 1);
    Communication::PointMessage m;
    Communication::TranslatorToArray t;
    QVERIFY2(m.addPoint(p1), "Can't add point");
    QVERIFY2(m.getPoints().size() == 1, "Wrong number of points");
    m.accept(t);
    QVERIFY2(t.getLastMessage().length() == Communication::Communication::messageSize, "Wrong message size");
}

void CommunicationTest::pointMessageSizeTest2()
{
    GamePlay::Point p1(0, 0, 0.1, 0, 1);
    Communication::PointMessage m;
    Communication::TranslatorToArray t;
    QVERIFY2(m.addPoint(p1), "Can't add point");
    QVERIFY2(m.addPoint(p1), "Can't add point");
    QVERIFY2(m.getPoints().size() == 2, "Wrong number of points");
    m.accept(t);
    QVERIFY2(t.getLastMessage().length() == Communication::Communication::messageSize, "Wrong message size");
}

void CommunicationTest::outputPointMessageTest1()
{
    GamePlay::Point p1(0, 0, 0.1, 0, 1);
    Communication::PointMessage m;
    Communication::TranslatorToArray tt;
    Communication::TranslatorFromArray tf;
    m.addPoint(p1);
    m.accept(tt);
    auto msg = std::move(tf.getMessage(tt.getLastMessage()));
    QVERIFY2(!(msg == nullptr), "Wrong outpus message - nullptr");
    QVERIFY2((dynamic_cast<Communication::PointMessage*>(msg.get())->getPoints()).size() == 1, "Wrong outpus message - size");
    auto p2 = (dynamic_cast<Communication::PointMessage*>(msg.get())->getPoints())[0];
    QVERIFY2(p1.getX() == p2.getX() && p1.getY() == p2.getY() && p1.getRadius() == p2.getRadius() && p1.getTurnNumber() == p2.getTurnNumber() && p1.getPlayerId() == p2.getPlayerId(), "Wrong output message - points");
}

void CommunicationTest::outputPointMessageTest2()
{
    GamePlay::Point p1(0, 0, 0.1, 0, 1);
    Communication::PointMessage m;
    Communication::TranslatorToArray tt;
    Communication::TranslatorFromArray tf;
    m.addPoint(p1);
    m.addPoint(p1);
    m.accept(tt);
    auto msg = std::move(tf.getMessage(tt.getLastMessage()));
    QVERIFY2(!(msg == nullptr), "Wrong outpus message - nullptr");
    QVERIFY2((dynamic_cast<Communication::PointMessage*>(msg.get())->getPoints()).size() == 2, "Wrong outpus message - size");
    auto p2 = (dynamic_cast<Communication::PointMessage*>(msg.get())->getPoints())[0];
    QVERIFY2(p1.getX() == p2.getX() && p1.getY() == p2.getY() && p1.getRadius() == p2.getRadius() && p1.getTurnNumber() == p2.getTurnNumber() && p1.getPlayerId() == p2.getPlayerId(), "Wrong output message - points");
}

void CommunicationTest::keyPressedMessegeSizeTest1() {
    Communication::KeyPressedMessage m(Communication::Communication::leftKeyId);
    Communication::TranslatorToArray tt;
    Communication::TranslatorFromArray tf;
    m.accept(tt);
    QVERIFY2(m.getHeader() == Communication::Communication::keyPressedMessageHeader, "Wrong header");
    QVERIFY2(m.getKeyId() == Communication::Communication::leftKeyId, "Wrong key id");
    QVERIFY2(tt.getLastMessage().length() == Communication::Communication::messageSize, "Wrong message size");
}

void CommunicationTest::outputKeyPressedMessegeTest1() {
    Communication::KeyPressedMessage m(Communication::Communication::leftKeyId);
    Communication::TranslatorToArray tt;
    Communication::TranslatorFromArray tf;
    m.accept(tt);
    auto msg = std::move(tf.getMessage(tt.getLastMessage()));
    QVERIFY2(!(msg == nullptr), "Wrong outpus message - nullptr");
    QVERIFY2(dynamic_cast<Communication::KeyPressedMessage*>(msg.get())->getHeader() == Communication::Communication::keyPressedMessageHeader, "Wrong header");
    QVERIFY2(dynamic_cast<Communication::KeyPressedMessage*>(msg.get())->getKeyId() == Communication::Communication::leftKeyId, "Wrong key id");

}

void CommunicationTest::keyReleasedMessegeSizeTest1() {
    Communication::KeyReleasedMessage m(Communication::Communication::leftKeyId);
    Communication::TranslatorToArray tt;
    Communication::TranslatorFromArray tf;
    m.accept(tt);
    QVERIFY2(m.getHeader() == Communication::Communication::keyReleasedMessageHeader, "Wrong header");
    QVERIFY2(m.getKeyId() == Communication::Communication::leftKeyId, "Wrong key id");
    QVERIFY2(tt.getLastMessage().length() == Communication::Communication::messageSize, "Wrong message size");
}

void CommunicationTest::outputKeyReleasedMessegeTest1() {
    Communication::KeyReleasedMessage m(Communication::Communication::leftKeyId);
    Communication::TranslatorToArray tt;
    Communication::TranslatorFromArray tf;
    m.accept(tt);
    auto msg = std::move(tf.getMessage(tt.getLastMessage()));
    QVERIFY2(!(msg == nullptr), "Wrong outpus message - nullptr");
    QVERIFY2(dynamic_cast<Communication::KeyReleasedMessage*>(msg.get())->getHeader() == Communication::Communication::keyReleasedMessageHeader, "Wrong header");
    QVERIFY2(dynamic_cast<Communication::KeyReleasedMessage*>(msg.get())->getKeyId() == Communication::Communication::leftKeyId, "Wrong key id");

}

void CommunicationTest::gameDelayMessageTest1() {
    Communication::GameDelayMessage m(3);
    Communication::TranslatorToArray tt;
    Communication::TranslatorFromArray tf;
    m.accept(tt);
    QVERIFY2(tt.getLastMessage().size() == Communication::Communication::messageSize, "Wrong message size");
    auto msg = std::move(tf.getMessage(tt.getLastMessage()));
    QVERIFY2(dynamic_cast<Communication::GameDelayMessage*>(msg.get())->getHeader() == Communication::Communication::gameDelayMessageHeader, "Wrong header");
    QVERIFY2(dynamic_cast<Communication::GameDelayMessage*>(msg.get())->getDelay() == 3, "Wrong delay");
}

void CommunicationTest::gameOverMessageTest1() {
    Communication::GameOverMessage m(5);
    Communication::TranslatorToArray tt;
    Communication::TranslatorFromArray tf;
    m.accept(tt);
    QVERIFY2(tt.getLastMessage().size() == Communication::Communication::messageSize, "Wrong message size");
    auto msg = std::move(tf.getMessage(tt.getLastMessage()));
    QVERIFY2(dynamic_cast<Communication::GameOverMessage*>(msg.get())->getHeader() == Communication::Communication::gameOverMessageHeader, "Wrong header");
    QVERIFY2(dynamic_cast<Communication::GameOverMessage*>(msg.get())->getWinner() == 5, "Wrong winner number");
}

void CommunicationTest::gameStartMessageTest1() {
    Communication::GameStartMessage m(3, 2, 1);
    Communication::TranslatorToArray tt;
    Communication::TranslatorFromArray tf;
    m.accept(tt);
    QVERIFY2(tt.getLastMessage().size() == Communication::Communication::messageSize, "Wrong message size");
    auto msg = std::move(tf.getMessage(tt.getLastMessage()));
    QVERIFY2(dynamic_cast<Communication::GameStartMessage*>(msg.get())->getHeader() == Communication::Communication::gameStartMessageHeader, "Wrong header");
    QVERIFY2(dynamic_cast<Communication::GameStartMessage*>(msg.get())->getNumberOfPlayers() == 3, "Wrong number of players");
    QVERIFY2(dynamic_cast<Communication::GameStartMessage*>(msg.get())->getMaxScore() == 2, "Wrong max score");
    QVERIFY2(dynamic_cast<Communication::GameStartMessage*>(msg.get())->getPlayerNumber() == 1, "Wrong player number");
}

void CommunicationTest::roundEndMessageTest1() {
    Communication::GameScoreMessage m(3);
    Communication::TranslatorToArray tt;
    Communication::TranslatorFromArray tf;
    m.accept(tt);
    QVERIFY2(tt.getLastMessage().size() == Communication::Communication::messageSize, "Wrong message size");
    auto msg = std::move(tf.getMessage(tt.getLastMessage()));
    dynamic_cast<Communication::GameScoreMessage*>(msg.get())->addScore(1, 8);
    QVERIFY2(dynamic_cast<Communication::GameScoreMessage*>(msg.get())->getHeader() == Communication::Communication::gameScoreMessageHeader, "Wrong header");
    QVERIFY2(dynamic_cast<Communication::GameScoreMessage*>(msg.get())->getScore() == std::vector<int>({0, 8, 0}), "Wrong scores");
    QVERIFY_EXCEPTION_THROWN(dynamic_cast<Communication::GameScoreMessage*>(msg.get())->addScore(3, 3), std::out_of_range);
}

QTEST_APPLESS_MAIN(CommunicationTest)

#include "tst_communicationtest.moc"
