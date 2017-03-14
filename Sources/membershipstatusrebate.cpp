#include "Headers\mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QChar>
#include <QDebug>

//pass in id

double MainWindow::memberRebate(int id){

    bool executive_yes = false;
    bool found = true;
    double rebate = 0;
    double totalAnnualCost = 0;
    double subtotal = 0;
    int annualCharge = 0;
    int i = 0;

    const float REBATE_RATE = .0325;
    const int   ANNUAL_EXEC_FEE = 95;
    const int   ANNUAL_REG_FEE = 85;

    //using a search function using the member's id
    //to determine what kind of member they are
    //(regular or executive)
    while(!found && i < myMembers.execVec.size()){
        if(id == myMembers.execVec[i]->getNum()){
            found = true;
            executive_yes = true;
            subtotal = myMembers.memberVec[i]->getTotal();
        }
        i++;
    }

    //rebate is based off of total purchases for year
    //so we need a running total variable for purchases

    if(executive_yes == true){
        annualCharge = ANNUAL_EXEC_FEE;

        //the rebate will be subtracted from this charge
        rebate = REBATE_RATE * subtotal;

        totalAnnualCost = annualCharge - rebate;

        //output to user their total payment for the year

    }
    else{
        annualCharge = ANNUAL_REG_FEE;

        totalAnnualCost = annualCharge;
        //output to user their total payment for the year

    }

 return rebate;
}
