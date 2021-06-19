#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "childdialog.h"
#include "user.h"
#include "commonfunctions.h"

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    Trainer getCurrentTrainer();
private:
    QDialog *curDialog;
    QString currentUser;
    int currentID;

    Trainer  trainer;

private:
    void createMenus();
    void loadDialog(QDialog*);

    //menu
    QMenuBar *menuBar;
    QMenu *userMenu;
    QAction *setCurrentUserAct;
    QAction *newUserAct;
    QAction *removeUserAct;
    QAction *exitAct;

    QMenu *quickMenu;
    QAction *chineseAct;
    QAction *englishWordAct;
    QAction *englishSentenceAct;

    QMenu *fontMenu;
    QAction *setFontAct;

    QVBoxLayout *mainLayout;

    QFont userFont;

private slots:
    void newUser();
    void removeUser();
    void setCurrentUser();
    void on_cmbID_currentIndexChanged(int index);
    //void btnAddUserClicked();

    void reciteChinese();
    void reciteEnglishWord();
    void reciteEnglishSentence();
    QString getFilename();
    void setUserFont();


};
#endif // DIALOG_H
