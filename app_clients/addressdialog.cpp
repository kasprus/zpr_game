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

AddressDialog::~AddressDialog()
{
    delete ui;
}
