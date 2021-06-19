#include "txtfiledialog.h"
#include <QSize>


#include <QtWidgets>
#include <QFont>
#include <QString>
#include <QFile>
#include <QTextStream>

#include <QMessageBox>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "commonfunctions.h"

bool TXTFileDialog::isRight()
{
   if (lastAsk.remove(" ")==lastAnswer.remove(" "))
        return true;
    else
        return false;
}

void TXTFileDialog::display()
{
   QString dispMessage="Count : " + QString::number(lines.count()) + ".\n "
                       + "  LAST ask  is " + QString::number(current) + ":"+lastAsk+".\n"
                       + "LAST answer is " + QString::number(current) + ":"+lastAnswer+".\n"
                       + " Correct : " + QString::number(correct)+".\n";
    dispMessage = dispMessage + "Last is " + (lastAsk.remove(" ")==lastAnswer.remove(" ")?"Right":"Error");

    lbResult->setText(dispMessage);
}


void TXTFileDialog::goPrevious()
{
    Calc();
    if (current) current--;
    ask(current);
}

void TXTFileDialog::Calc()
{
    lastAnswer=label->text();
    lastAsk = lines[current];

    bool curR = isRight();

    if (current>=0 and current<everyRecord.count())
        everyRecord[current]=curR;
    else
        everyRecord.append(curR);

    correct = everyRecord.count(true);//std::count(everyRecord.begin(),everyRecord.end(),true);
    display();

}


void TXTFileDialog::goRepeat()
{
    ask(current);
}

void TXTFileDialog::goNext()
{
    Calc();
    if (current< lines.count()) current++;
    ask(current);
}


void TXTFileDialog::ask(int i)
{
    if (window)
        delete window;
    if (lbResult)
        delete lbResult;
    if (label)
        delete label;
    //if (w)
        //delete w;
    if (next)
        delete next;
    if (previous)
        delete previous;
    if (repeat)
        delete repeat;
    if (calc)
        delete calc;
    if (exit)
        delete exit;
    //+if (btns)
        //delete btns;


    lbResult = new QLabel();
    label = new QLabel();
    QFont font= label->font();
    font.setPointSize(iFontSize);
    label->setFont(font);
    //label->setText("Hello world.");
    label->setWordWrap(true);
    label->adjustSize();
    label->setStyleSheet("border:2px solid red;");

    w = new FlowLayout;

    next = creatButton("Next");
    connect(next, SIGNAL(clicked()), this, SLOT(goNext()));
    previous = creatButton("Previous");
    connect(previous, SIGNAL(clicked()), this, SLOT(goPrevious()));
    repeat = creatButton("Repeat");
    connect(repeat, SIGNAL(clicked()), this, SLOT(goRepeat()));
    calc= creatButton("Calc");
    connect(calc, SIGNAL(clicked()), this, SLOT(Calc()));
    exit = creatButton("Quit");
    connect(exit, SIGNAL(clicked()), this, SLOT(close()));

    btns = new QHBoxLayout;
    btns->addWidget(previous);
    btns->addWidget(next);
    btns->addWidget(repeat);
    btns->addWidget(calc);
    btns->addWidget(exit);

    window = new QVBoxLayout;
    window->addWidget(lbResult);
    window->addStretch(1);
    window->addWidget(label);
    window->addStretch(1);
    window->addLayout(w);
    window->addStretch(3);
    window->addLayout(btns);

    this->setLayout(window);





    //this->hide();
    if (i<0 || i==lines.count()) return;

    //current=i;
    if(i==0)
        previous->setDisabled(true);
    else
        previous->setDisabled(false);
    if(i==lines.count()-1)
        next->setDisabled(true);
    else
        next->setDisabled(false);

    //window->removeItem(w);
    //清空horizontalLayout布局内的所有元素
    QLayoutItem *child;
    while ((child = w->takeAt(0)) != 0)
     {
            //setParent为NULL，防止删除之后界面不消失
            if(child->widget())
            {
                child->widget()->setParent(NULL);
            }

            delete child;
     }
    label->setText("");

    QString line=lines[i];
    if (!line.isEmpty())
    {
        QStringList list = line.split(" ");
        std::random_shuffle(list.begin(),list.end());

        foreach(QString s,list)
        {
            QPushButton *button = new QPushButton(s);
            QFont font=button->font();
            font.setPointSize(iFontSize);
            //font.setUnderline(true);
            button->setFont(font);
            connect(button, SIGNAL(clicked()), this, SLOT(btnsCommendClicked()));
            w->addWidget(button);
        }
    }
}


void TXTFileDialog::btnsCommendClicked()

{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    switch(reciteType)
    {
    case 1:
    case 2:
        label->setText(label->text() +clickedButton->text());
            clickedButton->setParent(NULL);
        break;
    case 3:
        label->setText(label->text() + " " +clickedButton->text());
            clickedButton->setParent(NULL);
        break;
    }

    delete  clickedButton;
}

QString TXTFileDialog::getTxtFile()
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("打开TXT"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("TXT(*.txt)"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;
    if(fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }
    return fileNames[0];
}

TXTFileDialog::TXTFileDialog(int iType,QWidget *parent)
    : QDialog(parent),reciteType(iType)
{
    lbResult=nullptr;
    label=nullptr;
    w=nullptr;
    btns=nullptr;
    window=nullptr;

    next=nullptr;
    previous=nullptr;
    repeat=nullptr;
    calc=nullptr;
    exit=nullptr;


    QString filename="";
    while (filename.isEmpty())
        filename=getTxtFile();
    QFile dictionaryFile(filename);//(QStringLiteral(":/dictionary/words.txt"));
    dictionaryFile.open(QIODevice::ReadOnly);

    QString line;

    while(!dictionaryFile.atEnd())
    {
        line = dictionaryFile.readLine();
        line=line.trimmed();
        //line.chop(1);
        if (!line.isEmpty())
            lines.append(line);
    }
    if(!lines.empty()){
        current=0;
        correct=0;
        //display();
        ask(0);
    }

    window->setSizeConstraint(QLayout::SetFixedSize);


    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    //resize(600,600);

}

TXTFileDialog::~TXTFileDialog()
{
}

