#-------------------------------------------------
#
# Project created by QtCreator 2018-04-21T22:05:40
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_gameplaytest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app

HEADERS += ../GamePlay/point.h

SOURCES += ../GamePlay/gameplay.cpp \
    ../GamePlay/board.cpp \
    ../GamePlay/player.cpp \
    ../GamePlay/point.cpp

HEADERS += ../GamePlay/gameplay.h \
    ../GamePlay/board.h \
    ../GamePlay/player.h \
    ../GamePlay/point.h

SOURCES += \
    tst_gameplaytest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
