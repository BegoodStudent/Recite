#include "userselect.h"
#include "initdb.h"

UserSelect::UserSelect(QWidget* parent)
    : QDialog(parent)
{

    cmbUser = new QComboBox;
    connect(cmbUser,SIGNAL(currentTextChanged(QString)),this,SLOT(on_cmbUser_currentTextChanged(QString)));
    //lineEdit = new QLineEdit;
    cmbStage  = new QComboBox;
    connect(cmbStage,SIGNAL(currentTextChanged(QString)),this,SLOT(on_cmbStage_currentTextChanged(QString)));
    cmbGrade = new QComboBox;
    connect(cmbGrade,SIGNAL(currentTextChanged(QString)),this,SLOT(on_cmbGrade_currentTextChanged(QString)));
    cmbSubject = new QComboBox;
    connect(cmbSubject,SIGNAL(currentTextChanged(QString)),this,SLOT(on_cmbSubject_currentTextChanged(QString)));
    //cmbProblem = new QComboBox;
    //connect(cmbProblem,SIGNAL(currentTextChanged(QString)),this,SLOT(on_cmbProblem_currentTextChanged(QString)));
    cmbChapter = new QComboBox;
    connect(cmbChapter,SIGNAL(currentTextChanged(QString)),this,SLOT(on_cmbChapter_currentTextChanged(QString)));
    lbTitle= new QLabel;
    lbAnswer= new QLabel;

    window = new QGridLayout;

    label = new QLabel("User");
    window->addWidget(label,1,0);
    window->addWidget(cmbUser,1,1);

    label = new QLabel("Stage");
    window->addWidget(label,2,0);
    window->addWidget(cmbStage,2,1);

    label = new QLabel("Grade");
    window->addWidget(label,3,0);
    window->addWidget(cmbGrade,3,1);

    label = new QLabel("Subject");
    window->addWidget(label,4,0);
    window->addWidget(cmbSubject,4,1);

    label = new QLabel("Chapter");
    window->addWidget(label,5,0);
    window->addWidget(cmbChapter,5,1);


    btnCancel = new QPushButton("Cancle");
    btnCancel->setStyleSheet("background-color:green");
    btnSetUser = new QPushButton("Set User");
    connect(btnSetUser, SIGNAL(clicked()), this, SLOT(btnSetUserClicked()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(close()));

    window->addWidget(btnCancel,6,0);
    window->addWidget(btnSetUser,6,1);

    //initDb();

    currentTrainer.Name="";
    currentTrainer.Chapter="";
    currentTrainer.ChapterID=-1;
    currentTrainer.Grade="";
    currentTrainer.GradeID=-1;
    currentTrainer.Stage="";
    currentTrainer.StageID=-1;


    cmbUser->addItems(readUsers());
    on_cmbUser_currentTextChanged(cmbUser->currentText());


    window->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(window);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

}

void UserSelect::on_cmbUser_currentTextChanged(const QString &arg1)
{
    currentTrainer.Name=arg1;
    QList<User> l = readUsersMessage();
    currentTrainer.ID = l[cmbUser->currentIndex()].ID;
    //lineEdit->setText(currentTrainer.Name);

    currentTrainer.Stage = getUserLevel(currentTrainer.Name);

    if (currentTrainer.Stage==cmbStage->currentText()){
        //label->setText("Stage Same,No Changed.");
        return;
    }
    else {
        //label->setText("Stage Changed:"+ currentTrainer.Stage);
    }

    if (cmbStage->count()==0)
    {
        cmbStage->addItems(readStages());
        list.clear();
    }

    for(int i=0;i<cmbStage->count();i++)
    {
        if (cmbStage->itemText(i)==currentTrainer.Stage)
        {
            cmbStage->setCurrentIndex(i);
            on_cmbStage_currentTextChanged(currentTrainer.Stage);
            break;
        }
    }

    currentTrainer.Stage=cmbStage->currentText();
    strSql ="select * from Stages where stage = ?";
    query.prepare(strSql);
    query.addBindValue(currentTrainer.Stage);
    query.exec();
    while(query.next())
    {
        currentTrainer.StageID= query.value("ID").toInt();
    }

}

void UserSelect::on_cmbStage_currentTextChanged(const QString &arg1)
{
    currentTrainer.Stage=arg1;
    currentTrainer.StageID=getLevelID(currentTrainer.Stage);
    //label->setText("Enter stage changeed." + QString::number(cmbGrade->count()));
    cmbGrade->clear();

    {
        cmbGrade->addItems(readGrades(currentTrainer.StageID));
        //list.clear();
    }
    currentTrainer.Grade=cmbGrade->currentText();
    strSql ="select ID from grades where grade = ?";
    query.prepare(strSql);
    query.addBindValue(currentTrainer.Grade);
    query.exec();
    while(query.next())
    {
        currentTrainer.GradeID= query.value("ID").toInt();
    }
    addiTtemsTocmbSubject();
}

void UserSelect::addiTtemsTocmbSubject()
{
    QSqlQuery query;
    QStringList l;
    QString strSql="SELECT * from Subjects where gradeID = (SELECT id from Grades WHERE grade=?);";
    query.prepare(strSql);
    query.addBindValue(currentTrainer.Grade);
    query.exec();
    if (cmbSubject->count()!=0)
        cmbSubject->clear();
    while(query.next()){
        l.append(query.value("subject").toString());
    }
    cmbSubject->addItems(l);
    currentTrainer.Subject=cmbSubject->currentText();
}

void UserSelect::on_cmbGrade_currentTextChanged(const QString &arg1)
{
    currentTrainer.Grade=arg1;
    currentTrainer.GradeID=getGradeID(currentTrainer.Grade);
    //label->setText(currentTrainer.Grade);
    addiTtemsTocmbSubject();
}


void UserSelect::on_cmbChapter_currentTextChanged(const QString &arg1)
{
    currentTrainer.Chapter = arg1;
    currentTrainer.ChapterID = getChapterID(currentTrainer.SubjectID,currentTrainer.Chapter);
    //if(cmbProblem->count()!=0)
        //cmbProblem->clear();
    //cmbProblem->addItems(readProblems(currentTrainer.ChapterID));
}


void UserSelect::on_cmbSubject_currentTextChanged(const QString &arg1)
{
    currentTrainer.Subject=arg1;
    currentTrainer.SubjectID = getSubjectID(currentTrainer.GradeID,currentTrainer.Subject);
    //label->setText(currentTrainer.Subject);
    if(cmbChapter->count()!=0)
        cmbChapter->clear();
    cmbChapter->addItems(readChapters(currentTrainer.GradeID,currentTrainer.Subject));

    //label->setText("GradeID: " + QString::number(currentTrainer.GradeID));
    currentTrainer.Chapter=cmbChapter->currentText();
}

void UserSelect::btnSetUserClicked()
{
    //close();
    if(currentTrainer.Chapter.count()==0 or readProblems(currentTrainer.ChapterID).count()==0){
        QLabel * label=new QLabel("当前，库文件中没有对应章节题目。请重新选择，谢谢配合。");
        window->addWidget(label,8,0);
    }
    else
        close();
}

/*
int  UserSelect::getUserselectChapterID()
{
    return currentTrainer.ChapterID;
}
*/

Trainer UserSelect::getTrainer()
{
    return currentTrainer;
}

