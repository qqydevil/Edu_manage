#-------------------------------------------------
#
# Project created by QtCreator 2017-07-08T10:39:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Exam_management_system
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addperinfor.cpp \
    addthform.cpp \
    addstdform.cpp \
    studentform.cpp \
    teacherform.cpp

HEADERS  += mainwindow.h \
    database.h \
    addperinfor.h \
    addthform.h \
    addstdform.h \
    studentform.h \
    teacherform.h

FORMS    += mainwindow.ui \
    addperinfor.ui \
    addthform.ui \
    addstdform.ui \
    studentform.ui \
    teacherform.ui


RESOURCES += \
    resource.qrc

QT       +=sql
