#include "Headers\mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QChar>
#include <QDebug>

void MainWindow::upgrade(int id){

    bool executive = false;
    bool found = true;
    double rebate = 0;
    int i = 0;

    while(!found && i < myMembers.execVec.size()){
        if(id == myMembers.execVec[i]->getNum()){
            found = true;
            executive = true;
        }
        i++;
    }

    rebate = memberRebate(id);

    if(executive == true){
        if(rebate < 10){
        //  the member should downgrade to save money
        }
        else{
        //  the member should remain an executive
        }
    }
    else{   //this would be for regular members
//        if(totalSubTotal > 307.69){
//        //  the member should upgrade to executive to
//        //  save money
//        }
//        else{
//        //  the member should remain a regular member
//        }
    }



}
