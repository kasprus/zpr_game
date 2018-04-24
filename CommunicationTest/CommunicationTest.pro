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

TEMPLATE = app

SOURCES += ../GamePlay/gameplay.cpp \
    ../GamePlay/board.cpp \
    ../GamePlay/player.cpp \
    ../GamePlay/point.cpp \
    ../Communication/communication.cpp \
    ../Communication/message.cpp \
    ../Communication/pointmessage.cpp \
    ../Communication/keypressedmessage.cpp \
    ../Communication/keyreleasedmessage.cpp \
    ../Communication/translatorfromarray.cpp \
    ../Communication/translatortoarray.cpp

HEADERS += ../GamePlay/gameplay.h \
    ../GamePlay/board.h \
    ../GamePlay/player.h \
    ../GamePlay/point.h \
    ../Communication/communication.h \
    ../Communication/message.h \
    ../Communication/pointmessage.h \
    ../Communication/keypressedmessage.h \
    ../Communication/keyreleasedmessage.h \
    ../Communication/translatorfromarray.h \
    ../Communication/translatortoarray.h

SOURCES += tst_communicationtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
