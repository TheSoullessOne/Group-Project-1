#include "Headers\mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

void UpdateDataFromFile(QString fileName)   {
//    double total = 0;
//    double test;
    QFile inputFile(fileName);

    QTextStream fin(&inputFile);

//    fin.read(test);

//    total += test;

//    qDebug() << test;
}


void UpdateMembersFromFile(QString fileName)    {
    QString tempName;
    int tempId;
    QString tempRank;
    QFile inputFile(fileName);
    QTextStream fin(&inputFile);

    tempName = fin.readLine();

    fin.readLine(tempId);

    tempRank = fin.readLine();

    if(tempRank == "Executive") {
//        execVec.push_back(new executive);
    }
    else    {
//        memberVec.push_back(new member);
    }


}
