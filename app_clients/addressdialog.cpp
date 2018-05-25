#include "addressdialog.h"
#include "ui_addressdialog.h"

/**
 * @brief Constructs simple dialog box with required fields and buttons.
 * @param The parameter specifies parent of the widget for memory management and is optional.
 */
AddressDialog::AddressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddressDialog)
{
    ui->setupUi(this);
}

/**
 * @brief The method returns IP adress entered by the user.
 * @return Ip address entered by the user.
 */
QString AddressDialog::getIpAddress() const {
    //check input
    return ui->lineEdit->text();
}

/**
 * @brief The method returns port number entered by the user.
 * @return Port numvber entered by the user.
 */
qint32 AddressDialog::getPortNumber() const {
    //check input
    return ui->lineEdit_2->text().toInt();
}

AddressDialog::~AddressDialog()
{
    delete ui;
}
