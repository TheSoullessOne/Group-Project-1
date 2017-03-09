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


#<<<<<<< HEAD
SOURCES += main.cpp\
        mainwindow.cpp \
    functions.cpp \
#<<<<<<< HEAD \
    addrecwindow.cpp \
    buildll.cpp \
    date.cpp \
    finalmenu.cpp \
    mainmenu.cpp \
    member.cpp \
    memberrebatefunc.cpp \
    membershipstatusrebate.cpp \
    submenu.cpp
#<<<<<<< HEAD
#<<<<<<< HEAD
    buildll.cpp
    finalmenu.cpp
    mainmenu.cpp
    membershipstatusrebate.cpp
    submenu.cpp
#=======
#    membershipstatusrebate.cpp
#>>>>>>> 14450dcdbb905e14d55ca2314f3cab8ef9cddfcc
#=======
#    mainmenu.cpp \
#    submenu.cpp
#    finalmenu.cpp
#>>>>>>> 69e57ac48e994ab5d8438c3335693712c8b9c65f
#=======
    membershipstatusrebate.cpp \
    buildll.cpp \
    finalmenu.cpp \
    mainmenu.cpp \
    submenu.cpp \
    member.cpp \
#<<<<<<< HEAD
    date.cpp \
    addrecwindow.cpp
#>>>>>>> 6e8a67cf476172d09012fc049c5b8d1183f67986
#=======
    date.cpp
#>>>>>>> d0b5a8857acb7452d0a0c5ae6dd4999efcbaee28

HEADERS  += mainwindow.h \
    date.h \
    executive.h \
    header.h \
    item.h \
    member.h \
#<<<<<<< HEAD
#<<<<<<< HEAD \
    addrecwindow.h \
    linkedlist.h
#<<<<<<< HEAD \
    addrecwindow.h \
    linkedlist.h
    addrecwindow.h
#=======
    linkedlist.h
#>>>>>>> 43272280820e008d5101a297129f2adc1d0ff363
#=======
    addrecwindow.h
#>>>>>>> 6e8a67cf476172d09012fc049c5b8d1183f67986

FORMS    += mainwindow.ui \
    addRecWindow.ui

DISTFILES += \
    User Stories.docx \
    Group-Project-1.pro.user \
    .gitignore
#=======
    mainmenu.h

FORMS    += mainwindow.ui
#>>>>>>> d0b5a8857acb7452d0a0c5ae6dd4999efcbaee28
#=======
SOURCES += Sources\main.cpp\
    Sources\mainwindow.cpp \
    Sources\functions.cpp \
    Sources\membershipstatusrebate.cpp \
    Sources\buildll.cpp \
    Sources\finalmenu.cpp \
    Sources\mainmenu.cpp \
    Sources\submenu.cpp \
    Sources\member.cpp \
    Sources\date.cpp \
    Sources\vectors.cpp

HEADERS  += Headers\mainwindow.h \
    Headers\date.h \
    Headers\executive.h \
    Headers\header.h \
    Headers\item.h \
    Headers\member.h \
    Headers\mainmenu.h \
    Headers\linkedlist.h

FORMS    += Forms\mainwindow.ui
#>>>>>>> d937bd0fb638a297cfd833ef4b3a0d1dc3bd8dfc
