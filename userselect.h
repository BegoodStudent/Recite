#ifndef USERSELECT_H
#define USERSELECT_H

#include <QDialog>
#include<QtWidgets>
#include<QSqlQuery>

#include "user.h"

class UserSelect : public QDialog
{
    Q_OBJECT
public:
    UserSelect(QWidget *parent = nullptr);

    //int getUserselectChapterID();
    Trainer getTrainer();
private slots:

    void on_cmbUser_currentTextChanged(const QString &arg1);

    void on_cmbStage_currentTextChanged(const QString &arg1);

    void on_cmbGrade_currentTextChanged(const QString &arg1);

    void on_cmbChapter_currentTextChanged(const QString &arg1);

    void on_cmbSubject_currentTextChanged(const QString &arg1);

    void btnSetUserClicked();

private:
    QLabel * label;
    QComboBox* cmbUser;
    //QLineEdit *lineEdit;
    QComboBox* cmbStage;
    QComboBox* cmbGrade;
    QComboBox* cmbSubject;
    QComboBox* cmbChapter;
    QComboBox* cmbProblem;
    QLabel *lbTitle;
    QLabel *lbAnswer;

    QGridLayout *window;

    QPushButton * btnCancel;
    QPushButton * btnSetUser;

private:

    QString strSql;
    QStringList list;
    QSqlQuery query;

    /*
    int currentUserID;
    QString currentUserName;
    int currentUserStageID;
    QString currentUserStage;
    int currentUserGradeID;
    QString currentUserGrade;
    QString currentUserSubject;
    int currentUserSubjectID;
    int currentUserChapterID;
    QString currentUserChapter;
    int currentProblemID;
    */

    Trainer currentTrainer;
    void addiTtemsTocmbSubject();



private slots:
    //void on_cmbProblem_currentIndexChanged(int index);

};


#endif // USERSELECT_H
