#-------------------------------------------------
#
# Project created by QtCreator 2017-02-27T14:08:39
#
#-------------------------------------------------

QT       += core gui quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Group-Project-1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    functions.cpp \
    membershipstatusrebate.cpp \
    buildll.cpp \
    finalmenu.cpp \
    mainmenu.cpp \
    submenu.cpp \
    member.cpp \
    date.cpp

HEADERS  += mainwindow.h \
    date.h \
    executive.h \
    header.h \
    item.h \
    member.h \
    mainmenu.h

FORMS    += mainwindow.ui