#ifndef INITDB_H
#define INITDB_H


#include <QtSql>
#include<QMessageBox>
#include <QStringList>
#include <QString>
#include <QList>

#include "user.h"


QSqlError initDb();

QStringList readStages();
void addUser(QString name, QString stage);


QStringList readUsersID();
QList<User> readUsersMessage();
void deleteUser(int id);

QStringList readUsers();

int getLevelID(const QString &level);

int getUserLevelID(const QString & name);

int  getGradeID(const QString &grade);

int  getSubjectID(int gradeID,const QString &subject);

int  getChapterID(int subjectID, const QString &chapter);

QString getUserLevel(const QString & name);

QStringList readGrades(int stageId);

QStringList readChapters(int gradeId,const QString &subject);

QStringList readProblems(int chpaterID);

Record readRecord(int userId);

#endif // INITDB_H
