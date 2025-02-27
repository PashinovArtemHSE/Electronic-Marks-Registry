QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addstudent.cpp \
    controlpanel.cpp \
    homework.cpp \
    homeworkstudent.cpp \
    main.cpp \
    mainwindow.cpp \
    marks.cpp \
    ratings.cpp \
    removestudent.cpp \
    userpanel.cpp

HEADERS += \
    addstudent.h \
    controlpanel.h \
    homework.h \
    homeworkstudent.h \
    mainwindow.h \
    marks.h \
    ratings.h \
    removestudent.h \
    userpanel.h

FORMS += \
    addstudent.ui \
    controlpanel.ui \
    homework.ui \
    homeworkstudent.ui \
    mainwindow.ui \
    marks.ui \
    ratings.ui \
    removestudent.ui \
    userpanel.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
