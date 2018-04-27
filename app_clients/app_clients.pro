#-------------------------------------------------
#
# Project created by QtCreator 2018-04-21T16:01:37
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app_clients
CONFIG += c++11
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameclient.cpp \
    controller.cpp \
    addressdialog.cpp

HEADERS  += mainwindow.h \
    gameclient.h \
    controller.h \
    addressdialog.h

INCLUDEPATH += ../GamePlay \
    ../Communication

LIBS += -L../Communication -lCommunication \
    -L../GamePlay -lGamePlay

FORMS    += mainwindow.ui \
    addressdialog.ui
