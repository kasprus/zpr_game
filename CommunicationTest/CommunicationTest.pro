#-------------------------------------------------
#
# Project created by QtCreator 2018-04-23T00:47:49
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_communicationtest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11
CONFIG  += link_prl

TEMPLATE = app

SOURCES += tst_communicationtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Communication/release/ -lCommunication
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Communication/debug/ -lCommunication
else:unix: LIBS += -L$$OUT_PWD/../Communication/ -lCommunication

INCLUDEPATH += $$PWD/../Communication
DEPENDPATH += $$PWD/../Communication

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Communication/release/libCommunication.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Communication/debug/libCommunication.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Communication/release/Communication.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Communication/debug/Communication.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Communication/libCommunication.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GamePlay/release/ -lGamePlay
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GamePlay/debug/ -lGamePlay
else:unix: LIBS += -L$$OUT_PWD/../GamePlay/ -lGamePlay

INCLUDEPATH += $$PWD/../GamePlay
DEPENDPATH += $$PWD/../GamePlay

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../GamePlay/release/libGamePlay.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../GamePlay/debug/libGamePlay.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../GamePlay/release/GamePlay.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../GamePlay/debug/GamePlay.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../GamePlay/libGamePlay.a


