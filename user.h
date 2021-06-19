#ifndef USER_H
#define USER_H

#include <QString>

class User{
public:
    int ID;
    QString name;
    int age;
    QString sex;
    QString school;
    QString className;
    int stageID;
    QString stage;

    User();
};


class Trainer{
public:
    int ID;
    QString Name;
    int StageID;
    QString Stage;
    int GradeID;
    QString Grade;
    QString Subject;
    int SubjectID;
    int ChapterID;
    QString Chapter;
};

class Record{
public:
    int trainTimes;
    int score;
    int count;
    int correct;
    int seenTimes;
};

#endif // USER_H
