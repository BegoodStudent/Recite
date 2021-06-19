#ifndef CHILDDIALOG_H
#define CHILDDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QtWidgets>
#include "asklayout.h"
#include "chapter.h"

#include "user.h"



class ChildDialog : public QDialog
{
    Q_OBJECT
public:
    ChildDialog(QWidget* parent=nullptr);
    ChildDialog(QString filename,int reciteType,QWidget* parent=nullptr);
    ChildDialog(Trainer t,QWidget* parent=nullptr);
    ~ChildDialog();
private:
    QLabel *lbResult;
    AskLayout *w;
    QGridLayout *window;
    QGridLayout *mainLayout;
    QGridLayout *idWindow;

private:
    //command Buttons
    QGridLayout *cmdButtons;
    QPushButton *next;
    QPushButton *previous;
    QPushButton *repeat;
    QPushButton *redoError;
    QPushButton *calc;
    QPushButton *exit;
    QPushButton *see;

    QVector<QPushButton*> idBtns;

    QGroupBox *cmdGroup;
    QGroupBox *idGroup;
    QGroupBox *askGroup;
    QGroupBox *userGroup;

    QLabel *label;

    int idCol =3;
    int saw;
    Record record;

private slots:
    void Previous();
    void Next();
    void RedoError();
    void Calc();
    void Repeat();
    void idBtnsClicked();
    void takeSee();
    void oneTrainEnd();

private:
    //do quesstion
    //User user;
    //QVector<Quesstion> quesstions;
    Chapter oneChapterTrain;;
    int current;
    int correct;
    int count;
    int last;
    int score;
    QVector<bool> everyRecord;
    QString lastAnswer;
    QString lastUserAnswer;

    Trainer trainer;
private:
    void display();
    bool isRight();
    void ask(int i);
    void getLastAnswer();
    void adjustButtonStatus();

private:
    void creatMainWidow();
    void creatIdBtns();
    void creatAsk();
    void creatCmdBtns();
    void creatUserDisplay();
    void doFromTxtFile();
    void doFromSystemDB(int i);

};

#endif // CHILDDIALOG_H
