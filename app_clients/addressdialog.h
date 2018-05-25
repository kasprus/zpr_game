#ifndef ADDRESSDIALOG_H
#define ADDRESSDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class AddressDialog;
}

/**
 * @brief The class provides the implementation of a simple dialog box for entering IP address and port number of a game server.
 */
class AddressDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs simple dialog box with required fields and buttons.
     * @param parent The parameter specifies parent of the widget for memory management and is optional.
     */
    explicit AddressDialog(QWidget *parent = 0);

    /**
     * @brief The method returns IP adress entered by the user.
     * @return Ip address entered by the user.
     */
    QString getIpAddress() const;

    /**
     * @brief The method returns port number entered by the user.
     * @return Port numvber entered by the user.
     */
    qint32 getPortNumber() const;

    ~AddressDialog();

private:
    Ui::AddressDialog *ui;
};

#endif // ADDRESSDIALOG_H
