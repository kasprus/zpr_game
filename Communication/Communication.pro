#-------------------------------------------------
#
# Project created by QtCreator 2018-04-22T15:33:13
#
#-------------------------------------------------

QT       -= gui

TARGET = Communication
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
CONFIG += create_prl

SOURCES += communication.cpp \
    message.cpp \
    translatortoarray.cpp \
    translatorfromarray.cpp \
    pointmessage.cpp \
    keypressedmessage.cpp \
    keyreleasedmessage.cpp

HEADERS += communication.h \
    message.h \
    translatortoarray.h \
    translatorfromarray.h \
    pointmessage.h \
    keypressedmessage.h \
    keyreleasedmessage.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

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
