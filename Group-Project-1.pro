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


SOURCES += Sources\main.cpp\
    Sources\mainwindow.cpp \
    Sources\membershipstatusrebate.cpp \
    Sources\finalmenu.cpp \
    Sources\mainmenu.cpp \
    Sources\submenu.cpp \
    Sources\member.cpp \
    Sources\date.cpp \
    Sources\vectors.cpp \
<<<<<<< HEAD
    Sources\item.cpp
=======
    Sources/item.cpp \
    Sources/upgrade.cpp
>>>>>>> a5057a34a4c43680f473e8ce011d56d660565fac

HEADERS  += Headers\mainwindow.h \
    Headers\date.h \
    Headers\executive.h \
    Headers\header.h \
    Headers\item.h \
    Headers\member.h \
    Headers\mainmenu.h

FORMS    += Forms\mainwindow.ui
