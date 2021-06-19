#include "useradddialog.h"
#include "initdb.h"

#include <QtWidgets>

UserAddDialog::UserAddDialog(QWidget *parent)
    : QDialog(parent)
{
    //initDb();

    lbName = new QLabel("Name:");
    lbStage = new QLabel("Stage:");
    leName = new QLineEdit;
    cmbStage = new QComboBox;

    w = new QGridLayout;
    w->addWidget(lbName,0,0);
    w->addWidget(leName,0,1);
    w->addWidget(lbStage,1,0);
    w->addWidget(cmbStage,1,1);

    cmbStage->addItems(readStages());

    btnCancel = new QPushButton("Cancle");
    btnAddUser = new QPushButton("Add User");
    //connect(btnAddUser, &QPushButton::, this, &QDialog::accept);
    connect(btnAddUser, SIGNAL(clicked()), this, SLOT(btnAddUserClicked()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(close()));
    w->addWidget(btnCancel,2,0);
    w->addWidget(btnAddUser,2,1);

    w->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(w);
    //setWindowTitle(tr("Add New User"));
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
}

UserAddDialog::~UserAddDialog()
{
}

void UserAddDialog::btnAddUserClicked()
{
    QString name = leName->text();
    QString stage = cmbStage->currentText();
    if (!name.isEmpty())
        addUser(name,stage);
    close();
}
