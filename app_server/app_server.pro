QT += core
QT -= gui
QT += network

TARGET = app_server
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    gameserver.cpp

HEADERS += \
    gameserver.h

