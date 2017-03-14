#include "Headers\mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QChar>
#include <QDebug>

/*************************************************************
 * This function will determine if it is more money savy to
 * either upgrade or downgrade their membership. It will also
 * show their total amount due for the year. This includes
 * the annual membership fee (based on member status i.e.
 * regular/executive) and the rebate if they are an executive
 * member (based off of their total spending for the year)
 *************************************************************/
void MainWindow::upgrade(int id){

    bool executive = false;
    bool found = true;
    double rebate = 0;
    double total = 0;
    int i = 0;

    const int PRICE_DIFFERENCE = 10; //the difference in price between
                                     //a regular member and an executive
    const float REBATE_RATE = .0325;


    while(!found && i < myMembers.execVec.size()){
        if(id == myMembers.execVec[i]->getNum()){
            found = true;
            executive = true;
            total = myMembers.execVec[i]->getTotal();
        }
        i++;
    }

    rebate = memberRebate(id);

    if(executive == true){
        if(rebate < PRICE_DIFFERENCE){
        //  the member should downgrade to save money
        }
        else{
        //  the member should remain an executive
        }
    }
    else{   //this would be for regular members
        if(total > (PRICE_DIFFERENCE/REBATE_RATE)){
        //  the member should upgrade to executive to
        //  save money
        }
        else{
        //  the member should remain a regular member
        }
    }



}
