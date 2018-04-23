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

SOURCES += communication.cpp \
    message.cpp \
    translatortoarray.cpp \
    translatorfromarray.cpp \
    pointmessage.cpp

HEADERS += communication.h \
    message.h \
    translatortoarray.h \
    translatorfromarray.h \
    pointmessage.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
