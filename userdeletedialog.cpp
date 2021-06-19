#include "userdeletedialog.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>


UserDeleteDialog::UserDeleteDialog(QWidget *parent)
    : QDialog(parent)
{
    //initDb();

    lbUser = new QLabel("User:");
    lbUser->adjustSize();
    //label = new QLabel();
    //label->adjustSize();

    cmbID = new QComboBox;

    w = new QGridLayout;
    w->addWidget(lbUser,0,0);
    w->addWidget(cmbID,0,1);
    //w->addWidget(label,0,2);

    lbStudent = new QLabel;
    w->addWidget(lbStudent,1,1);

    usersMessage=readUsersMessage();
    QStringList listID=readUsersID();
    qDebug() << listID.count();

    cmbID->addItems(listID);

    on_cmbID_currentIndexChanged(cmbID->currentIndex());
    connect(cmbID,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cmbID_currentIndexChanged(int)));


    btnCancel = new QPushButton("Cancle");
    btnDeleteUser = new QPushButton("Delete User");
    connect(btnDeleteUser, SIGNAL(clicked()), this, SLOT(btnDeleteUserClicked()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(close()));

    w->addWidget(btnCancel,2,0);
    w->addWidget(btnDeleteUser,2,1);

    w->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(w);
    //setWindowTitle(tr("Add New User"));
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
}

UserDeleteDialog::~UserDeleteDialog()
{
}

void UserDeleteDialog::btnDeleteUserClicked()
{
    int userID = -1;

    QRegularExpression re("([0-9]+)");


    QRegularExpressionMatch match=re.match(cmbID->currentText());

    if(match.hasMatch())
    {
        userID = match.captured(1).toInt();
    }

    deleteUser(userID);

    close();
}

void UserDeleteDialog::on_cmbID_currentIndexChanged(int index)
{
    lbStudent->setText(
                usersMessage[index].name + "\n"
                + usersMessage[index].sex + "\n"
                + QString::number(usersMessage[index].age) + "\n"
                + usersMessage[index].school + "\n"
                + usersMessage[index].className + "\n"
                + usersMessage[index].stage + "\n"
                );
    lbStudent->adjustSize();
}

