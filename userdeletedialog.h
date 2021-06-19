#ifndef USERDELETEDIALOG_H
#define USERDELETEDIALOG_H

#include <QtWidgets>
#include "initdb.h"
#include "user.h"

class UserDeleteDialog : public QDialog
{
    Q_OBJECT

public:
    UserDeleteDialog(QWidget *parent = nullptr);
    ~UserDeleteDialog();

private:
    QLabel *lbUser;
    QComboBox * cmbID;
    QLabel *label;
    QLabel *lbStudent;
    QGridLayout *w;
    QPushButton * btnCancel;
    QPushButton * btnDeleteUser;
    QList<User> usersMessage;

private slots:
    void btnDeleteUserClicked();
    void on_cmbID_currentIndexChanged(int index);

};

#endif // USERDELETEDIALOG_H
