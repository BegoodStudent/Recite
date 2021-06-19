#ifndef PROBLEM_H
#define PROBLEM_H

#include <QString>
#include <QVector>

class Problem
{
public:
    Problem();
    Problem(int id);

public:
    int ID;

    int chapterID;

    int typeID;
    bool isPng;

    QString title;
    QVector<QString> selections;
    QString answer;
    QString describe;
    QVector<int> relationKnowledgesID;
};

#endif // PROBLEM_H
