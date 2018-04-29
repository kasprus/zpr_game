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
#include <memory>

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

QTEST_APPLESS_MAIN(CommunicationTest)

#include "tst_communicationtest.moc"
