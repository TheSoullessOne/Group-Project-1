#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include "header.h"
#include <QChar>
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
