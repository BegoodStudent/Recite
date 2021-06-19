#include "asklayout.h"
#include <QtWidgets>

#include "commonfunctions.h"

AskLayout::AskLayout(const Problem &p)
{
    title=nullptr;
    leBlank=nullptr;
    tkOther=nullptr;
    sentenceLayout=nullptr;
    relationKnowledge=nullptr;

    type=p.typeID;


    int gridLine=1;
    if(!p.isPng and p.typeID<4)
    {
        title = new QLabel(p.title);
        addWidget(title,gridLine++,0);
    }
    else
    {
        //只有title为图片
    }
    switch (p.typeID){
    case 1://单项选择题
    case 5://判断题
    {
        QRadioButton *rt;
        for(int i=0;i<p.selections.size();i++){
            rt= new QRadioButton("ABCDEFGH"[i]+p.selections[i]);
            rt->setChecked(false);
            radioBtns.append(rt);
            addWidget(radioBtns[i],gridLine++,0);
        }
        break;
    }
    case 2:
    case 3:
        //多项选择题，不定项选择题
    {
        QCheckBox *ct;
        for(int i=0;i<p.selections.size();i++){
            ct= new QCheckBox("ABCDEFGH"[i]+p.selections[i]);
            ct->setChecked(false);
            checkBtns.append(ct);
            addWidget(checkBtns[i],gridLine++,0);
        }
        break;
    }
    case 4://填空题
    case 6://计算题
    {
        QStringList list =p.title.split(" ");
        title = new QLabel(list[0]);
        leBlank = new QPlainTextEdit;//QLineEdit;
        leBlank->setObjectName("Answer");
        //leBlank->setText("成功");
        //leBlank->setMaxLength(p.answer.size());
        //leBlank->adjustSize();
        tkOther = new QLabel(list[1]);

        tkLayout= new QHBoxLayout;
        tkLayout->addWidget(title);
        tkLayout->addWidget(leBlank);
        tkLayout->addWidget(tkOther);
        tkLayout->addStretch();
        addLayout(tkLayout,1,0);

        gridLine=2;
        break;
    }
    case 7:
    {
        title = new QLabel;
        addWidget(title,1,0);
        title->setText(p.title);

        leBlank = new QPlainTextEdit;//QLineEdit;
        //QFontMetrics fm(leBlank->font());
        //leBlank->setFixedWidth(fm.horizontalAdvance(p.answer+" "));
        //leBlank->setMaxLength(p.answer.size());
        leBlank->setObjectName("Answer");

        tkLayout= new QHBoxLayout;
        tkLayout->addWidget(leBlank);
        //tkLayout->addStretch();
        addLayout(tkLayout,2,0);

        //addWidget(leBlank,2,0);
        QString ans=p.answer;
        ans=ans.simplified();

        QStringList list;
        foreach(QChar c,ans)
            list.append(c);
        std::random_shuffle(list.begin(),list.end());
        blankBtnsLayout = new FlowLayout;
        foreach(QString s,list)
        {
            QPushButton *button = creatButton(s);
            connect(button, SIGNAL(clicked()), this, SLOT(btnsCommendClicked()));
            blankBtnsLayout->addWidget(button);
        }

        addLayout(blankBtnsLayout,3,0);

        break;
    }
    case 8:
    case 9:
    {
        title = new QLabel;
        addWidget(title,1,0);
        title->setText(p.title);

        leBlank = new QPlainTextEdit;//QLineEdit;
        leBlank->setObjectName("Answer");
        addWidget(leBlank,2,0);

        QString ans=p.answer;
        ans=ans.simplified();

        QStringList list = ans.split(" ");
        std::random_shuffle(list.begin(),list.end());
        blankBtnsLayout = new FlowLayout;
        foreach(QString s,list)
        {
            QPushButton *button = creatButton(s);
            connect(button, SIGNAL(clicked()), this, SLOT(btnsCommendClicked()));
            blankBtnsLayout->addWidget(button);
        }

        addLayout(blankBtnsLayout,3,0);

        break;
    }

    case 10:
    {
        leBlank = new QPlainTextEdit;//QLineEdit;
        leBlank->setObjectName("Answer");
        addWidget(leBlank,1,0);

        QString ans=p.title;
        ans=ans.simplified();

        QStringList list;
        foreach(QChar c,ans)
            list.append(c);
        std::random_shuffle(list.begin(),list.end());
        blankBtnsLayout = new FlowLayout;
        foreach(QString s,list)
        {
            QPushButton *button = creatButton(s);
            connect(button, SIGNAL(clicked()), this, SLOT(btnsCommendClicked()));
            blankBtnsLayout->addWidget(button);
        }

        addLayout(blankBtnsLayout,2,0);

        break;
    }
    case 11:
    case 12:
    {
        leBlank = new QPlainTextEdit;//QLineEdit;
        leBlank->setObjectName("Answer");
        addWidget(leBlank,1,0);

        QString ans=p.title;
        ans=ans.simplified();

        QStringList list =ans.split(" ");
        std::random_shuffle(list.begin(),list.end());
        blankBtnsLayout = new FlowLayout;
        foreach(QString s,list)
        {
            QPushButton *button = creatButton(s);
            connect(button, SIGNAL(clicked()), this, SLOT(btnsCommendClicked()));
            blankBtnsLayout->addWidget(button);
        }

        addLayout(blankBtnsLayout,2,0);

        break;
    }
    }
}

AskLayout::~AskLayout()
{
    /*
    delete title;
    delete leBlank;
    delete tkOther;
    delete sentenceLayout;
    delete relationKnowledge;
    for (int i=0;i<radioBtns.size();i++)
        delete radioBtns[i];
    for (int i=0;i<checkBtns.size();i++)
        delete checkBtns[i];
    */
}

void AskLayout::btnsCommendClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    switch (type) {    
    case 7:
    case 9:
    case 10:
    case 12:{
        QString lt=leBlank->toPlainText();
        leBlank->clear();
        leBlank->appendPlainText(lt+clickedButton->text());//->setText(leBlank->text()+clickedButton->text());
        break;
    }
    case 8:
    case 11:{
        //leBlank->setText(leBlank->text() + " " + clickedButton->text());
        QString lt=leBlank->toPlainText();
        leBlank->clear();
        leBlank->appendPlainText(lt + " " + clickedButton->text());//->setText(leBlank->text()+clickedButton->text());
        break;
    }
    }

    //clickedButton->setParent(NULL);
    //delete  clickedButton;
    clickedButton->setDisabled(true);
}
