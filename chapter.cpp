#include "chapter.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

Chapter::Chapter()
{

}

Chapter::Chapter(int chapterId)
{
    chapterID=chapterId;

    QString strSql ="select id FROM Problems WHERE chapterID=?;";
    QSqlQuery q;
    q.prepare(strSql);
    q.addBindValue(chapterId);
    q.exec();

    while (q.next()) {
        problems.append(Problem(q.value("id").toInt()));
    }
}
