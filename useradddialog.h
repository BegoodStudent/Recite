#ifndef USERADDDIALOG_H
#define USERADDDIALOG_H

#include <QtWidgets>

class UserAddDialog : public QDialog
{
    Q_OBJECT

public:
    UserAddDialog(QWidget *parent = nullptr);
    ~UserAddDialog();

private:
    QLabel *lbName;
    QLabel *lbStage;
    QLineEdit *leName;
    QComboBox * cmbStage;
    QGridLayout *w;
    QPushButton * btnCancel;
    QPushButton * btnAddUser;

private slots:
    void btnAddUserClicked();

};

#endif // USERADDDIALOG_H
