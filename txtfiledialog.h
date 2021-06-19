#ifndef TXTFILEDIALOG_H
#define TXTFILEDIALOG_H

#include <QtWidgets>
#include "flowlayout.h"

class TXTFileDialog: public QDialog
{

    Q_OBJECT

public:
    TXTFileDialog(int iType,QWidget *parent = nullptr);
    ~TXTFileDialog();

private:
    int reciteType;

private:

    QLabel *lbResult;
    QLabel *label;
    FlowLayout *w;

    QVBoxLayout *window;

    QHBoxLayout *btns;
    QPushButton *next;
    QPushButton *previous;
    QPushButton *repeat;
    QPushButton *calc;
    QPushButton *exit;

    QStringList lines;

    std::size_t current;
    int correct;
    QVector<bool> everyRecord;

    bool isRight();
    void display();
    QString lastAnswer;
    QString lastAsk;
    QString getTxtFile();

private slots:
    void btnsCommendClicked();
    void ask(int i);
    void goPrevious();
    void goNext();
    void goRepeat();
    void Calc();
};

#endif // TXTFILEDIALOG_H
