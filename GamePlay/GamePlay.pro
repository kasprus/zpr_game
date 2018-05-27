#-------------------------------------------------
#
# Project created by QtCreator 2018-04-21T16:14:03
#
#-------------------------------------------------

QT       -= gui

TARGET = GamePlay
TEMPLATE = lib
CONFIG += staticlib \
    c++11
CONFIG += create_prl

SOURCES += gameplay.cpp \
    board.cpp \
    player.cpp \
    point.cpp \
    gamemode.cpp \
    bonus.cpp

HEADERS += gameplay.h \
    board.h \
    player.h \
    point.h \
    gamemode.h \
    modes.h \
    bonus.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
