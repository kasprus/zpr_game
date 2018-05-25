/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QLabel *label_1_1;
    QLabel *label_1_2;
    QLabel *label_1_3;
    QLabel *label_1_4;
    QLabel *label_1_5;
    QLabel *label_1_6;
    QLabel *label_2_3;
    QLabel *label_2_5;
    QLabel *label_2_4;
    QLabel *label_2_1;
    QLabel *label_2_2;
    QLabel *label_2_6;
    QLabel *label_Not;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 575);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(10, 10, 500, 500));
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setAutoFillBackground(false);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        graphicsView->setBackgroundBrush(brush);
        graphicsView->setSceneRect(QRectF(0, 0, 480, 480));
        label_1_1 = new QLabel(centralWidget);
        label_1_1->setObjectName(QStringLiteral("label_1_1"));
        label_1_1->setEnabled(true);
        label_1_1->setGeometry(QRect(550, 70, 71, 17));
        label_1_1->setVisible(false);
        label_1_2 = new QLabel(centralWidget);
        label_1_2->setObjectName(QStringLiteral("label_1_2"));
        label_1_2->setGeometry(QRect(550, 110, 71, 20));
        label_1_2->setVisible(false);
        label_1_3 = new QLabel(centralWidget);
        label_1_3->setObjectName(QStringLiteral("label_1_3"));
        label_1_3->setGeometry(QRect(550, 150, 71, 17));
        label_1_3->setVisible(false);
        label_1_4 = new QLabel(centralWidget);
        label_1_4->setObjectName(QStringLiteral("label_1_4"));
        label_1_4->setGeometry(QRect(550, 190, 71, 17));
        label_1_4->setVisible(false);
        label_1_5 = new QLabel(centralWidget);
        label_1_5->setObjectName(QStringLiteral("label_1_5"));
        label_1_5->setGeometry(QRect(550, 230, 81, 17));
        label_1_5->setVisible(false);
        label_1_6 = new QLabel(centralWidget);
        label_1_6->setObjectName(QStringLiteral("label_1_6"));
        label_1_6->setGeometry(QRect(550, 270, 81, 17));
        label_1_6->setVisible(false);
        label_2_3 = new QLabel(centralWidget);
        label_2_3->setObjectName(QStringLiteral("label_2_3"));
        label_2_3->setGeometry(QRect(660, 150, 71, 17));
        label_2_3->setVisible(false);
        label_2_5 = new QLabel(centralWidget);
        label_2_5->setObjectName(QStringLiteral("label_2_5"));
        label_2_5->setGeometry(QRect(660, 230, 81, 17));
        label_2_5->setVisible(false);
        label_2_4 = new QLabel(centralWidget);
        label_2_4->setObjectName(QStringLiteral("label_2_4"));
        label_2_4->setGeometry(QRect(660, 190, 71, 17));
        label_2_4->setVisible(false);
        label_2_1 = new QLabel(centralWidget);
        label_2_1->setObjectName(QStringLiteral("label_2_1"));
        label_2_1->setGeometry(QRect(660, 70, 71, 17));
        label_2_1->setVisible(false);
        label_2_2 = new QLabel(centralWidget);
        label_2_2->setObjectName(QStringLiteral("label_2_2"));
        label_2_2->setGeometry(QRect(660, 110, 71, 20));
        label_2_2->setVisible(false);
        label_2_6 = new QLabel(centralWidget);
        label_2_6->setObjectName(QStringLiteral("label_2_6"));
        label_2_6->setGeometry(QRect(660, 270, 81, 17));
        label_2_6->setVisible(false);
        label_Not = new QLabel(centralWidget);
        label_Not->setObjectName(QStringLiteral("label_Not"));
        label_Not->setGeometry(QRect(520, 30, 261, 20));
        label_Not->setVisible(false);
        label_Not->setLayoutDirection(Qt::RightToLeft);
        label_Not->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_1_1->setText(QApplication::translate("MainWindow", "RED", 0));
        label_1_2->setText(QApplication::translate("MainWindow", "BLUE", 0));
        label_1_3->setText(QApplication::translate("MainWindow", "GREEN", 0));
        label_1_4->setText(QApplication::translate("MainWindow", "YELLOW", 0));
        label_1_5->setText(QApplication::translate("MainWindow", "PINK", 0));
        label_1_6->setText(QApplication::translate("MainWindow", "WHITE", 0));
        label_2_3->setText(QApplication::translate("MainWindow", "0", 0));
        label_2_5->setText(QApplication::translate("MainWindow", "0", 0));
        label_2_4->setText(QApplication::translate("MainWindow", "0", 0));
        label_2_1->setText(QApplication::translate("MainWindow", "0", 0));
        label_2_2->setText(QApplication::translate("MainWindow", "0", 0));
        label_2_6->setText(QApplication::translate("MainWindow", "0", 0));
        label_Not->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
