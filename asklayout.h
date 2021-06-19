#ifndef ASKLAYOUT_H
#define ASKLAYOUT_H

#include <QtWidgets>

#include "problem.h"

#include "flowlayout.h"


class AskLayout : public QGridLayout
{
    Q_OBJECT
public:
    AskLayout(const Problem &p);
    ~AskLayout();
private:
    QLabel *title;
    //QLineEdit *leBlank;
    QPlainTextEdit *leBlank;
    QLabel *tkOther;
    QVector<QRadioButton*> radioBtns;
    QVector<QCheckBox*> checkBtns;
    QGridLayout* sentenceLayout;
    QComboBox* relationKnowledge;
    FlowLayout* blankBtnsLayout;

    QHBoxLayout *tkLayout;

    //QLabel* bsAnswer;

    int type;

private slots:
    void btnsCommendClicked();
};

#endif // ASKLAYOUT_H
