#include "commonfunctions.h"

#include <QLayoutItem>
#include <QLayout>
#include <QList>

QPushButton* creatButton(QString title)
{
    QPushButton *t= new QPushButton(title);
    //QFont font=t->font();
    //font.setPointSize(iFontSize);
    //t->setFont(font);
    return t;
}


void layoutClear(QLayout* window)
{
    //清空horizontalLayout布局内的所有元素
    if(!window) return;
    QLayoutItem *child;
    while ((child = window->takeAt(0)) != nullptr)
     {
        if(child->widget())
        {
            child->widget()->setParent(NULL);
            delete child->widget();
        }
        if(child->layout())
        {
            layoutClear(child->layout());
        }
     }
}
