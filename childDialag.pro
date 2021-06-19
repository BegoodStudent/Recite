QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    asklayout.cpp \
    chapter.cpp \
    childdialog.cpp \
    commonfunctions.cpp \
    flowlayout.cpp \
    initdb.cpp \
    main.cpp \
    dialog.cpp \
    problem.cpp \
    user.cpp \
    useradddialog.cpp \
    userdeletedialog.cpp \
    userselect.cpp

HEADERS += \
    asklayout.h \
    chapter.h \
    childdialog.h \
    commonfunctions.h \
    dialog.h \
    flowlayout.h \
    initdb.h \
    problem.h \
    user.h \
    useradddialog.h \
    userdeletedialog.h \
    userselect.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
