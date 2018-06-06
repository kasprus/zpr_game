#include "addressdialog.h"
#include "ui_addressdialog.h"

AddressDialog::AddressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddressDialog)
{
    ui->setupUi(this);
}

QString AddressDialog::getIpAddress() const {
    return ui->lineEdit->text();
}

qint32 AddressDialog::getPortNumber() const {
    return ui->lineEdit_2->text().toInt();
}

AddressDialog::~AddressDialog()
{
    delete ui;
}
