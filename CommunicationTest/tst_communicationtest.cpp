#include <QString>
#include <QtTest>
#include "../Communication/message.h"
#include "../Communication/pointmessage.h"
#include "../Communication/translatortoarray.h"
#include "../Communication/communication.h"
#include "../GamePlay/point.h"
#include "../Communication/translatorfromarray.h"
#include <memory>

class CommunicationTest : public QObject
{
    Q_OBJECT

public:
    CommunicationTest();

private Q_SLOTS:
    void messageSizeTest1();
    void outputMessageTest1();
    void messageSizeTest2();
    void outputMessageTest2();
};

CommunicationTest::CommunicationTest()
{
}

void CommunicationTest::messageSizeTest1()
{
    GamePlay::Point p1(0, 0, 0.1, 0, 1);
    Communication::PointMessage m;
    Communication::TranslatorToArray t;
    QVERIFY2(m.addPoint(p1), "Can't add point");
    QVERIFY2(m.getPoints().size() == 1, "Wrong number of points");
    m.accept(t);
    QVERIFY2(t.getLastMessage().length() == Communication::Communication::messageSize, "Wrong message size");
}

void CommunicationTest::messageSizeTest2()
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

void CommunicationTest::outputMessageTest1()
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

void CommunicationTest::outputMessageTest2()
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

QTEST_APPLESS_MAIN(CommunicationTest)

#include "tst_communicationtest.moc"
