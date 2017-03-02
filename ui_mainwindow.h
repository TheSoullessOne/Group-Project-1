/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *Adduser;
    QPushButton *deleteRec;
    QPushButton *reportsSearch;
    QPushButton *readInFile;
    QPushButton *upgrade;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(665, 388);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(30, 0, 160, 170));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Adduser = new QPushButton(verticalLayoutWidget);
        Adduser->setObjectName(QStringLiteral("Adduser"));

        verticalLayout->addWidget(Adduser);

        deleteRec = new QPushButton(verticalLayoutWidget);
        deleteRec->setObjectName(QStringLiteral("deleteRec"));

        verticalLayout->addWidget(deleteRec);

        reportsSearch = new QPushButton(verticalLayoutWidget);
        reportsSearch->setObjectName(QStringLiteral("reportsSearch"));

        verticalLayout->addWidget(reportsSearch);

        readInFile = new QPushButton(verticalLayoutWidget);
        readInFile->setObjectName(QStringLiteral("readInFile"));

        verticalLayout->addWidget(readInFile);

        upgrade = new QPushButton(verticalLayoutWidget);
        upgrade->setObjectName(QStringLiteral("upgrade"));

        verticalLayout->addWidget(upgrade);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 665, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        Adduser->setText(QApplication::translate("MainWindow", "ADD MEMBER", Q_NULLPTR));
        deleteRec->setText(QApplication::translate("MainWindow", "DELETE A  RECORD", Q_NULLPTR));
        reportsSearch->setText(QApplication::translate("MainWindow", "REPORTS", Q_NULLPTR));
        readInFile->setText(QApplication::translate("MainWindow", "READ FILE", Q_NULLPTR));
        upgrade->setText(QApplication::translate("MainWindow", "UPGRADE", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
