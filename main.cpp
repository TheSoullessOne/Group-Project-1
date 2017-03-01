#include "mainwindow.h"
#include <QApplication>
#include "header.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    UpdateDataFromFile("day1.txt");

    return a.exec();
}
