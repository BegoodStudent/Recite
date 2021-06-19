#include "childdialog.h"
#include "initdb.h"
#include "commonfunctions.h"
#include "dialog.h"

void ChildDialog::creatUserDisplay()
{
    lbResult = new QLabel;
    QVBoxLayout * ul= new QVBoxLayout;
    ul->addWidget(lbResult);
    ul->addStretch();

    userGroup  = new QGroupBox;

    userGroup->setLayout(ul);
}

void ChildDialog::creatAsk()
{
    w=nullptr;

    creatCmdBtns();

    window = new QGridLayout;

    window->addWidget(cmdGroup,2,0);

    QVBoxLayout *winBo = new QVBoxLayout;
    winBo->addStretch();
    window->addLayout(winBo,4,0);
    //window->setSizeConstraint(QLayout::SetFixedSize);
    label=  new QLabel;


    askGroup  = new QGroupBox;    

    askGroup->setLayout(window);

}

void ChildDialog::creatCmdBtns()
{
    cmdButtons= new QGridLayout;

    //creat cmd button and connect command
    next = creatButton("下一题");
    connect(next, SIGNAL(clicked()), this, SLOT(Next()));
    if(count==1) next->setDisabled(true);

    previous = creatButton("上一题");
    connect(previous, SIGNAL(clicked()), this, SLOT(Previous()));
    if (current==0) previous->setDisabled(true);

    repeat = creatButton("重做本题");
    connect(repeat, SIGNAL(clicked()), this, SLOT(Repeat()));

    redoError = creatButton("做第一个错题");
    connect(redoError, SIGNAL(clicked()), this, SLOT(RedoError()));

    calc= creatButton("判题");
    connect(calc, SIGNAL(clicked()), this, SLOT(Calc()));

    see= creatButton("看答案");
    connect(see, SIGNAL(clicked()), this, SLOT(takeSee()));

    exit = creatButton("退出");
    connect(exit, SIGNAL(clicked()), this, SLOT(oneTrainEnd()));

    cmdButtons->addWidget(previous,1,0);
    cmdButtons->addWidget(next,1,1);
    cmdButtons->addWidget(calc,1,3);

    cmdButtons->addWidget(repeat,1,2);
    cmdButtons->addWidget(redoError,1,4);
    cmdButtons->addWidget(see,1,5);
    cmdButtons->addWidget(exit,1,6);

    cmdGroup  = new QGroupBox;

    cmdGroup->setLayout(cmdButtons);
}

void ChildDialog::creatMainWidow()
{       
    mainLayout= new QGridLayout;
    idCol =3;
    saw =0;

    creatAsk();
    creatUserDisplay();

    creatIdBtns();

    /*
    if (idGroup->height()>this->geometry().height())
    {
        idCol = static_cast<int>(idGroup->height()/geometry().height())*idCol+1;
        layoutClear(idWindow);
        creatIdBtns();
    }
    */

    mainLayout->addWidget(userGroup,1,0);

    mainLayout->addWidget(askGroup,1,1);

    mainLayout->addWidget(idGroup,1,2);


    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(mainLayout);

    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);    
}

void ChildDialog::creatIdBtns()
{
    //idWindow

    idWindow= new QGridLayout;
    idWindow->setSizeConstraint(QLayout::SetFixedSize);

    //idBtns init

    for(int i=0;i<count;i++)
    {
        QPushButton *t =new QPushButton(QString::number(i+1));
        //t->setMaximumSize(t->sizeHint().width(),t->sizeHint().height());
        connect(t, SIGNAL(clicked()), this, SLOT(idBtnsClicked()));
        idBtns.append(t);
        idWindow->addWidget(idBtns.last(),i/idCol,i%idCol);
    }
    idGroup = new QGroupBox;
    idGroup->setLayout(idWindow);
}

void ChildDialog::doFromTxtFile()
{
    count =oneChapterTrain.problems.count();

    creatMainWidow();

    if(count!=0){

        current=0;
        correct=0;
        ask(current);
    }

}
void ChildDialog::doFromSystemDB(int i)
{
    //initDb();
    oneChapterTrain = Chapter(i);
    count =oneChapterTrain.problems.count();
    record=readRecord(trainer.ID);

    creatMainWidow();

    if(count!=0){
        current=0;
        correct=0;
        display();
        ask(current);
    }
}

ChildDialog::ChildDialog(Trainer t,QWidget* parent)
    :QDialog(parent)
{
    trainer = t;
    doFromSystemDB(trainer.ChapterID);
}

ChildDialog::ChildDialog(QString filename,int reciteType,QWidget* parent)
    :QDialog(parent)
{
    QFile dictionaryFile(filename);
    dictionaryFile.open(QIODevice::ReadOnly);

    QString line;

    while(!dictionaryFile.atEnd())
    {
        line = dictionaryFile.readLine();
        line=line.trimmed();
        //line.chop(1);
        if (!line.isEmpty()){
            oneChapterTrain.problems.append(Problem());
            oneChapterTrain.problems.last().title=line;
            oneChapterTrain.problems.last().typeID=reciteType;
        }
    }    
    doFromTxtFile();
}

ChildDialog::ChildDialog(QWidget *parent)
    :QDialog(parent)
{
    creatMainWidow();
}

ChildDialog::~ChildDialog()
{
    delete lbResult;
    delete w;
    delete window;
}

void ChildDialog::adjustButtonStatus()
{
    if(current==0)
        previous->setDisabled(true);
    else
        previous->setDisabled(false);

    if(current==count-1)
        next->setDisabled(true);
    else
        next->setDisabled(false);

    if (correct==count)
        redoError->setDisabled(true);
    else
        redoError->setDisabled(false);
}

void ChildDialog::ask(int i)
{
    current=i;
    if (i<0 || i==count) return;

    adjustButtonStatus();

    layoutClear(w);

    w = new AskLayout(oneChapterTrain.problems[i]);

    window->addLayout(w,1,0);    


    if (idGroup)
        label->setText(QString::number(idGroup->width()) + " " + QString::number(idGroup->height()));

}

void ChildDialog::Previous()
{
    if ((current < everyRecord.count() and !everyRecord[current]) or current >=everyRecord.count())
        Calc();

    if (current>0) current--;
    display();

    Repeat();
}

void ChildDialog::Next()
{
    if ((current < everyRecord.count() and !everyRecord[current]) or current >=everyRecord.count())
        Calc();

    if (current<count)
        current++;
    display();

    Repeat();
}

void ChildDialog::RedoError()
{
    for (int i=0;i<everyRecord.count();i++)
        if (!everyRecord[i]){
            if ((current < everyRecord.count() and !everyRecord[current]) or current >=everyRecord.count())
                Calc();
            current=i;
            display();
            ask(current);
            break;
        }
}

void ChildDialog::Repeat()
{    
    ask(current);
}


bool ChildDialog::isRight()
{
    if (oneChapterTrain.problems.count()==0) return false;

    if (lastUserAnswer==lastAnswer)
        return true;
    else
        return false;
}

void ChildDialog::display()
{
    score = static_cast<int>(static_cast<float>(correct)/count*100);
    QString dfStr;
    if (score==100)
        dfStr="厉害！你很棒！";
    else if (score>=80)
        dfStr="优秀！";
    else if (score>=60)
        dfStr="及格了！";
    else
        dfStr="努力！加油！";
    bool allRight = false;
    if (everyRecord.count()>0 and  correct==everyRecord.count())
        allRight=true;

    QString dispMessage="";
    dispMessage += "欢迎，" + trainer.Name + "\n"
                  + "你已经进行过" + QString::number(record.trainTimes) +"次测试。\n"
                  + "做过" + QString::number(record.count) + "题。\n"
                  + "总计得到" +QString::number(record.score)  + "分。\n"
                  + "看过" + QString::number(record.seenTimes) + "次答案。\n\n";

    dispMessage += "本次测试，总计：" + QString::number(count) + "题。\n"
                       + "正确：" + QString::number(correct) +"题。\n\n"
                       + (allRight?"目前，全对！强！\n":"")
                       + "得分："+QString::number(score) + "分。\n\n"
                       + dfStr ;

    lbResult->setText(dispMessage);

    askGroup->setTitle("第"+ QString::number(current+1)+"题：");

    //if (count==correct)
        //close();
}

void ChildDialog::getLastAnswer()
{
    last=current;
    switch (oneChapterTrain.problems[last].typeID){
    case 1://单项选择题
    case 5://判断题
    {
        lastAnswer = oneChapterTrain.problems[last].answer;
        QList<QRadioButton*> radioBtns = findChildren<QRadioButton*>();
        for(int i=0;i<radioBtns.size();i++)
        {
            if ( radioBtns[i]->isChecked() )
            {
                lastUserAnswer=radioBtns[i]->text()[0];
                break;
            }
        }
         break;
    }
    case 2:
    case 3:
        //多项选择题，不定项选择题
    {
        lastAnswer = oneChapterTrain.problems[last].answer;
        lastUserAnswer="";
        QList<QCheckBox*> checkBtns = findChildren<QCheckBox*>();
        for(int i=0;i<checkBtns.size();i++)
            if ( checkBtns[i]->isChecked() ){
                lastUserAnswer +=checkBtns[i]->text()[0];
            }
        break;
    }
    case 4://填空题
    case 6://计算题
    {
        lastAnswer = oneChapterTrain.problems[last].answer;
        //QLineEdit* leBlank = findChild<QLineEdit*>("Answer");
        QPlainTextEdit* leBlank = findChild<QPlainTextEdit*>("Answer");
        if (leBlank)
            //lastUserAnswer=leBlank->text();
            lastUserAnswer=leBlank->toPlainText().remove(" ").remove("\n");
        break;
    }
    case 7:
    case 8:
    case 9:
    {
        QString t =oneChapterTrain.problems[last].answer;
        lastAnswer = t.remove(" ").remove("\n");
        //QLineEdit* lbRecite = findChild<QLineEdit*>("Answer");
        QPlainTextEdit* lbRecite = findChild<QPlainTextEdit*>("Answer");
        if (lbRecite)
            //lastUserAnswer=lbRecite->text().remove(" ");
            lastUserAnswer=lbRecite->toPlainText().remove(" ").remove("\n");
        break;
    }
    case 10:
    case 11:
    case 12:
    {
        QString t =oneChapterTrain.problems[last].title;
        lastAnswer = t.remove(" ").remove("\n");
        //lastAnswer = t.remove("\n");
        //QLineEdit* lbRecite = findChild<QLineEdit*>("Answer");
        QPlainTextEdit* lbRecite = findChild<QPlainTextEdit*>("Answer");
        if (lbRecite)
            //lastUserAnswer=lbRecite->text().remove(" ");
            lastUserAnswer=lbRecite->toPlainText().remove(" ").remove("\n");
        break;
    }
    }
}

void ChildDialog::Calc()
{
    getLastAnswer();    

    bool curR = isRight();
    if(!curR)
        idBtns[current]->setStyleSheet("background-color:red");
    else
        idBtns[current]->setStyleSheet("background-color:green");

    if (everyRecord.count()>0  and last < everyRecord.count())
        everyRecord[last]=curR;
    else
        everyRecord.append(curR);

    correct = everyRecord.count(true);
    adjustButtonStatus();
    display();
}

void ChildDialog::takeSee()
{
    last=current;
    saw++;
    QString lastAnswer;

    switch (oneChapterTrain.problems[last].typeID){
    case 1://单项选择题
    case 5://判断题
    case 2:
    case 3: //多项选择题，不定项选择题
    case 4://填空题
    case 6://计算题
    {
        lastAnswer = oneChapterTrain.problems[last].answer;
        break;
    }
    case 7:
    case 8:
    case 9:
    {
        QString t =oneChapterTrain.problems[last].answer;
        lastAnswer = t.remove(" ");
        lastAnswer = t.remove("\n");
        break;
    }
    case 10:
    case 11:
    case 12:
    {
        QString t =oneChapterTrain.problems[last].title;
        lastAnswer = t.remove(" ");
        lastAnswer = t.remove("\n");
        break;
    }
    }
    lbResult->setText(lastAnswer);
}


void ChildDialog::idBtnsClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if ((current < everyRecord.count() and !everyRecord[current]) or current >=everyRecord.count())
        Calc();
    current=clickedButton->text().toInt()-1;
    ask(current);
}

void ChildDialog::oneTrainEnd()
{

    //写训练记录
    //章节记录
    QSqlQuery q;

    QString sqlStr ="INSERT INTO UserTrainRecord VALUES(?,?,?,?,?,?,?);";
    q.prepare(sqlStr);
    q.addBindValue(trainer.ID);
    q.addBindValue(trainer.ChapterID);

    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");

    q.addBindValue(current_date);
    q.addBindValue(score);
    q.addBindValue(saw);
    q.addBindValue(count);
    q.addBindValue(correct);
    q.exec();

    //题目记录
    sqlStr ="INSERT INTO UserProblemRecords VALUES(?,?,?,?);";
    q.prepare(sqlStr);

    for (int i=0;i<everyRecord.count();i++)
    {
        q.addBindValue(trainer.ID);
        q.addBindValue(oneChapterTrain.problems[i].ID);
        q.addBindValue(current_date);
        q.addBindValue(everyRecord[i]);
        q.exec();
    }
    close();
}

