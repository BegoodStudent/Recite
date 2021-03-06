#include "dialog.h"
#include "initdb.h"
#include "useradddialog.h"
#include "userdeletedialog.h"
#include "txtfiledialog.h"
#include "userselect.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    userFont.setPointSize(16);
    userFont.setFamily("STZhongsong");
    this->setFont(userFont);

    createMenus();
    initDb();
    curDialog=nullptr;


    mainLayout = new QVBoxLayout;

    mainLayout->setMenuBar(menuBar);

    setLayout(mainLayout);
    setWindowTitle(tr("Recitation is the foundation of learning"));
    //mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setWindowState(Qt::WindowMaximized);

    //loadDialog(new ChildDialog(1,this));
}

Dialog::~Dialog()
{
    delete curDialog;
}



void Dialog::createMenus()
{
    menuBar = new QMenuBar;

    //User menu
    userMenu = new QMenu(tr("&User"),this);

    setCurrentUserAct = userMenu->addAction(tr("Select"));
    connect(setCurrentUserAct, &QAction::triggered, this, &Dialog::setCurrentUser);

    newUserAct = userMenu->addAction(tr("New"));
    connect(newUserAct, &QAction::triggered, this, &Dialog::newUser);


    removeUserAct = userMenu->addAction(tr("Delete"));
    connect(removeUserAct, &QAction::triggered, this, &Dialog::removeUser);

    userMenu->addSeparator();

    exitAct =  userMenu->addAction(tr("E&xit"));
    connect(exitAct, &QAction::triggered, this, &QDialog::accept);

    menuBar->addMenu(userMenu);

    //Quick recit, From signal File
    quickMenu = new QMenu(tr("&Quick(TXT File)"),this);

    chineseAct = quickMenu->addAction(tr("Chinese"));
    connect(chineseAct, &QAction::triggered, this, &Dialog::reciteChinese);


    englishWordAct = quickMenu->addAction(tr("English Words"));
    connect(englishWordAct, &QAction::triggered, this, &Dialog::reciteEnglishWord);

    englishSentenceAct =  quickMenu->addAction(tr("English Sentence"));
    connect(englishSentenceAct, &QAction::triggered, this, &Dialog::reciteEnglishSentence);

    menuBar->addMenu(quickMenu);

    fontMenu = new QMenu(tr("Font"),this);

    setFontAct = fontMenu->addAction(tr("Set Font"));
    connect(setFontAct, &QAction::triggered, this, &Dialog::setUserFont);

    menuBar->addMenu(fontMenu);

}

void Dialog::loadDialog(QDialog* actDialog)
{
    if (curDialog != nullptr)
        curDialog->close();
    curDialog =actDialog;

    curDialog->adjustSize();

    curDialog->resize(width(),height());

    curDialog->move(100, 100);

    curDialog->exec();
}

void Dialog::newUser()
{
    loadDialog(new UserAddDialog(this));
}

void Dialog::removeUser()
{
    loadDialog(new UserDeleteDialog(this));
}

void Dialog::on_cmbID_currentIndexChanged(int index)
{

}

void Dialog::setCurrentUser()
{
    loadDialog(new UserSelect(this));
    trainer =  static_cast<UserSelect*>(curDialog)->getTrainer();
    //int chapter =trainer.ChapterID;
    loadDialog(new ChildDialog(trainer,this));

}

void Dialog::setUserFont()
{
    //ok ??????????????????????????? ok ??????
    bool ok;
    userFont = QFontDialog::getFont(&ok,this);
    //???????????? OK ????????????????????????????????????????????????????????????
    //???????????? Cancel ???????????????????????????
    if(ok)
        this->setFont(userFont);
    else
        qDebug()<<tr("??????????????????");
}

QString Dialog::getFilename()
{
    QString filename="";
    while (filename.isEmpty())
    {
        //loadDialog(new TXTFileDialog(CHINESE,this));
         QFileDialog *fileDialog = new QFileDialog();
         //???????????????????????????
         fileDialog->setWindowTitle(tr("??????TXT"));
         //????????????????????????
         fileDialog->setDirectory(".");
         //?????????????????????
         fileDialog->setNameFilter(tr("TXT(*.txt)"));
         //??????????????????????????????,?????????????????????????????????QFileDialog::ExistingFiles
         fileDialog->setFileMode(QFileDialog::ExistingFiles);
         //??????????????????
         fileDialog->setViewMode(QFileDialog::Detail);
         //????????????????????????????????????
         QStringList fileNames;
         if(fileDialog->exec())
         {
             fileNames = fileDialog->selectedFiles();
         }
         filename=fileNames[0];
    }
    return filename;
}

void Dialog::reciteChinese()
{
    loadDialog(new ChildDialog(getFilename(),12,this));
}
void Dialog::reciteEnglishWord()
{
    loadDialog(new ChildDialog(getFilename(),10,this));
}
void Dialog::reciteEnglishSentence()
{
   loadDialog(new ChildDialog(getFilename(),11,this));
}

Trainer Dialog::getCurrentTrainer()
{
    return trainer;
}

