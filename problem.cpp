#include "problem.h"


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

Problem::Problem()
{
}


const auto SELECT_PROBLEM_SQL = QLatin1String(R"(
    SELECT * FROM PROBLEMS WHERE ID=?
    )");
const auto SELECT_SELECTIONS_SQL = QLatin1String(R"(
    SELECT * FROM SELECTIONS WHERE problemID=?;
    )");
const auto SELECT_RELATIONKNOWLEDGES_SQL = QLatin1String(R"(
    SELECT * FROM RELATIONKNOWLEDGES WHERE ID=?
    )");

const auto SELECT_BASEKNOWLEDGES_SQL = QLatin1String(R"(
    SELECT * FROM BASEKNOWLEDGES WHERE ID=?
    )");

void getProblem(QSqlQuery &q, int id)
{
    q.addBindValue(id);
    q.exec();
}

void getSelections(QSqlQuery &q, int id)
{
    q.addBindValue(id);
    q.exec();
}

void getRelations(QSqlQuery &q, int id)
{
    q.addBindValue(id);
    q.exec();
}

void getRelationKnowledges(QSqlQuery &q, int id)
{
    q.addBindValue(id);
    q.exec();
}

void getSubject(QSqlQuery &q, int id)
{
    q.addBindValue(id);
    q.exec();
}

void getGrade(QSqlQuery &q, int id)
{
    q.addBindValue(id);
    q.exec();
}

void getStage(QSqlQuery &q, int id)
{
    q.addBindValue(id);
    q.exec();
}

Problem::Problem(int id)
{
    QSqlQuery q;
    ID=id;

    if (!q.prepare(SELECT_PROBLEM_SQL))
        ;//return q.lastError();
    getProblem(q,id);

    while(q.next())
    {
        chapterID=q.value("chapterID").toInt();
        typeID = q.value("typeID").toInt();
        title =q.value("title").toString();
        isPng = q.value("isPNG").toInt()==1 ? true:false;
        answer= q.value("answer").toString();
        describe =q.value("describe").toString();
    }

    if (!q.prepare(SELECT_SELECTIONS_SQL))
        ;//return q.lastError();
    getSelections(q,id);

    while(q.next())
    {
        selections.append(q.value("content").toString());
        qDebug() << q.value("content").toString();
    }

    if (!q.prepare(SELECT_RELATIONKNOWLEDGES_SQL))
        ;//return q.lastError();
    getRelations(q,id);

    while(q.next())
    {
        relationKnowledgesID.append(q.value("knowledgeID").toInt());
    }
}
