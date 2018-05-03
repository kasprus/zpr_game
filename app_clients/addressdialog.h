#ifndef ADDRESSDIALOG_H
#define ADDRESSDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class AddressDialog;
}

class AddressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddressDialog(QWidget *parent = 0);
    QString getIpAddress() const;
    qint32 getPortNumber() const;

    ~AddressDialog();

private:
    Ui::AddressDialog *ui;
};

#endif // ADDRESSDIALOG_H
