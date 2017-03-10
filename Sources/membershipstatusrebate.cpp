#include "Headers\mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QChar>
#include <QDebug>

//pass in id - QString
void memberRebate(QString id){

    bool executive_yes = false;
    //rebate is based off of total purchases for year
    //so we need a running total variable for purchases

    //use a search function using the member's id
    //to determine what kind of member they are
    //(regular or executive)


    if(executive_yes == true){
        //annual executive membership is $95
        //the rebate will be subtracted from this charge
        //rebate = 3.25% * totalsubtotal (before tax)
        //if(month is Dec){
        //  rebate will be paid out
        //}
        //use a for loop to add the totals from each month
        //to create a yearly total?

    }
    else if(executive_yes == false){
        //annual regular membership is $85
        //there is no rebate
    }

}
