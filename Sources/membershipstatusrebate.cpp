#include "Headers\mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QChar>
#include <QDebug>

/**************************************************
 * This function will search the executive
 * member vector to locate a specified
 * id number, and then output the rebate for
 * that member (based on their total spending for
 * the year
 *************************************************/

//pass in id
double MainWindow::memberRebate(int id){

    double rebate = 0;
    double subtotal = 0;
    bool exec_found = false;
    int exec_index = 0;
    int idTemp = id;

    const float REBATE_RATE = .0325;


    while(!exec_found && exec_index < myMembers.execVec.size()){
        if(idTemp == myMembers.execVec[exec_index]->getNum()){
            exec_found = true;
            subtotal = myMembers.execVec[exec_index]->getTotal();
            rebate = (REBATE_RATE * subtotal);
        }
        else{
            exec_index++;
        }
    }


 return rebate;
}
