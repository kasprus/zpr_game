/********************************************************************************
** Form generated from reading UI file 'addressdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDRESSDIALOG_H
#define UI_ADDRESSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_AddressDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *AddressDialog)
    {
        if (AddressDialog->objectName().isEmpty())
            AddressDialog->setObjectName(QStringLiteral("AddressDialog"));
        AddressDialog->resize(319, 248);
        buttonBox = new QDialogButtonBox(AddressDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(210, 200, 81, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        lineEdit = new QLineEdit(AddressDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(130, 100, 161, 25));
        label = new QLabel(AddressDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 40, 281, 20));
        lineEdit_2 = new QLineEdit(AddressDialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(130, 160, 161, 25));
        label_2 = new QLabel(AddressDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 100, 91, 17));
        label_3 = new QLabel(AddressDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 160, 91, 17));

        retranslateUi(AddressDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddressDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddressDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddressDialog);
    } // setupUi

    void retranslateUi(QDialog *AddressDialog)
    {
        AddressDialog->setWindowTitle(QApplication::translate("AddressDialog", "Dialog", nullptr));
        lineEdit->setText(QApplication::translate("AddressDialog", "127.0.0.1", nullptr));
        label->setText(QApplication::translate("AddressDialog", "Please Enter Server I.P and Port Number", nullptr));
        lineEdit_2->setText(QApplication::translate("AddressDialog", "4321", nullptr));
        label_2->setText(QApplication::translate("AddressDialog", "I.P Address", nullptr));
        label_3->setText(QApplication::translate("AddressDialog", "Port Number", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddressDialog: public Ui_AddressDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDRESSDIALOG_H
