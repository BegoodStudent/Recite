#include "initdb.h"


QSqlError initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("recite.db");
    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                        "This example needs SQLite support. Please read "
                        "the Qt SQL driver documentation for information how "
                        "to build it.\n\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        return db.lastError();
    }

    return QSqlError();
}


QStringList readStages()
{
    QSqlQuery q;
    QStringList l;
    q.exec("select * from Stages");
    while(q.next())
    {
        l << q.value("stage").toString();
    }
    return l;
}

void addUser(QString name, QString stage)
{
    QSqlQuery q;
    //QStringList l;
    QString sqlStr ="INSERT INTO Users(name,levelID) VALUES(?,(SELECT id FROM Stages where stage=?));";
    q.prepare(sqlStr);
    q.addBindValue(name);
    q.addBindValue(stage);
    q.exec();
}

QStringList readUsersID()
{
    QSqlQuery q;
    QStringList l;
    q.exec("SELECT id from  users;");
    while (q.next())
    {
        l.append(q.value("id").toString());
    }
    return l;
}

QList<User> readUsersMessage()
{
    User student;
    QSqlQuery q;
    QList<User> l;
    q.exec("SELECT a.*,b.stage from  users as a, Stages as b where a.levelID=b.id;");
    while (q.next())
    {
        //l.append(q.value("id").toString()+q.value("name").toString()+q.value("stage").toString());
        student.ID=q.value("id").toInt();
        student.name=q.value("name").toString();
        student.age=q.value("age").toInt();
        student.school=q.value("school").toString();
        student.className=q.value("class").toString();
        student.sex=q.value("sex").toString();
        student.stageID=q.value("levelid").toInt();
        student.stage=q.value("stage").toString();
        l.append(student);
    }
    return l;
}

void deleteUser(int id)
{
    QSqlQuery q;
    QString sqlStr="DELETE from users where id=?;";
    q.prepare(sqlStr);
    q.addBindValue(id);
    q.exec();
}


QStringList readUsers()
{
    QSqlQuery query;
    QStringList list;
    query.exec("select * from Users");
    while(query.next())
    {
        list << query.value("name").toString();
    }
    return list;
}



int getLevelID(const QString &level)
{
    QSqlQuery query;
    QString strSql ="select * from stages where stage = ?";
    query.prepare(strSql);
    query.addBindValue(level);
    query.exec();
    int levelID;
    while(query.next())
    {
        levelID= query.value("ID").toInt();
    }
    return levelID;
}

int getUserLevelID(const QString & name)
{
    QSqlQuery query;
    QString strSql ="select levelID from Users where name = ?";
    query.prepare(strSql);
    query.addBindValue(name);
    query.exec();
    int levelID;
    while(query.next())
    {
        levelID= query.value("levelID").toInt();
    }
    return levelID;
}

int  getGradeID(const QString &grade)
{
    QSqlQuery query;
    QString strSql ="select ID from Grades where grade= ?";
    query.prepare(strSql);
    query.addBindValue(grade);
    query.exec();
    int gradeID;
    while(query.next())
    {
        gradeID= query.value("ID").toInt();
    }
    return gradeID;
}

int  getSubjectID(int gradeID,const QString &subject)
{
    QSqlQuery q;
    QString strSql ="SELECT id from Subjects where gradeID=? and subject = ?;";
    q.prepare(strSql);
    q.addBindValue(gradeID);
    q.addBindValue(subject);
    q.exec();
    int subjectID;
    while(q.next())
    {
        subjectID= q.value("ID").toInt();
    }
    return subjectID;
}

int  getChapterID(int subjectID, const QString &chapter)
{
    QSqlQuery query;
    QString strSql ="select id from Chapters where subjectID = ? and chapter = ?;";
    query.prepare(strSql);
    query.addBindValue(subjectID);
    query.addBindValue(chapter);
    query.exec();
    int chpaterID;
    while(query.next())
    {
        chpaterID= query.value("ID").toInt();
    }
    return chpaterID;
}

QString getUserLevel(const QString & name)
{
    QSqlQuery query;
    QString strSql ="select * from stages where id=(select levelID from Users where name = ?)";
    query.prepare(strSql);
    query.addBindValue(name);
    query.exec();
    QString stage;

    while(query.next())
    {
       stage= query.value("stage").toString();
    }
    return stage;
}

QStringList readGrades(int stageId)
{
    QSqlQuery q;
    QStringList l;

    QString strSql ="select * from grades where stageid = ?;";
    q.prepare(strSql);
    q.addBindValue(stageId);
    q.exec();
    while(q.next())
    {
        l << q.value("grade").toString();
    }
    return l;
}

QStringList readChapters(int gradeId,const QString &subject)
{
    QSqlQuery q;
    QStringList l;

    QString strSql ="SELECT * from chapters where subjectID =(SELECT id FROM Subjects where subject = ? and Gradeid=?);";
    q.prepare(strSql);
    q.addBindValue(subject);
    q.addBindValue(gradeId);
    q.exec();
    while(q.next())
    {
        l << q.value("chapter").toString();
    }
    return l;
}

QStringList readProblems(int chpaterID)
{
    QSqlQuery q;
    QStringList l;

    QString strSql ="SELECT * from Problems where chapterID=?;";
    q.prepare(strSql);
    q.addBindValue(chpaterID);
    q.exec();
    while(q.next())
    {
        l << q.value("id").toString();
    }
    return l;
}


Record readRecord(int userId)
{
    QSqlQuery q;
    Record r;
    r.trainTimes=0;
    r.count=0;
    r.correct=0;
    r.score=0;
    r.seenTimes=0;

    QString strSql ="SELECT count(),sum(count),sum(score),sum(correct),sum(seetimes) from UserTrainRecord where userID=?;";
    q.prepare(strSql);
    q.addBindValue(userId);
    q.exec();
    while(q.next())
    {
        r.trainTimes= q.value("count()").toInt();
        r.count =q.value("sum(count)").toInt();
        r.correct=q.value("sum(correct)").toInt();
        r.score=q.value("sum(score)").toInt();
        r.seenTimes=q.value("sum(seetimes)").toInt();

    }
    return r;
}
