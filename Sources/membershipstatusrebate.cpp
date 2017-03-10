#include "Headers\mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QChar>
#include <QDebug>

//pass in id - QString

double MainWindow::memberRebate(int id){

    bool executive_yes = false;
    bool found = true;
    double rebate = 0;
    double totalAnnualCost = 0;
    int annualCharge = 0;
    int i = 0;

    //use a search function using the member's id
    //to determine what kind of member they are
    //(regular or executive)
    while(!found && i < myMembers.execVec.size()){
        if(id == myMembers.execVec[i]->getNum()){
            found = true;
            executive_yes = true;
        }
        i++;
    }

    //rebate is based off of total purchases for year
    //so we need a running total variable for purchases

    if(executive_yes == true){
        annualCharge = 95;

        //the rebate will be subtracted from this charge
        //rebate = 3.25% * subtotal (before tax)

        totalAnnualCost = annualCharge - rebate;

        //output to user their total payment for the year

    }
    else{
        annualCharge = 85;

        totalAnnualCost = annualCharge;
        //output to user their total payment for the year

    }

 return rebate;
}
