#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include "header.h"
#include <QChar>
#include <QDebug>

/*********************************************
 * This function will provide the rebate
 * amount according to membership status and
 * provide the amount that the membership
 * will cost (including rebate).
 ********************************************/

void memberRebate(  ){//what parameters will
                      //be needed?
    double cost = 0;
    int rebate = 0;

//here, search for the member by id or name
//input search func
    if(memberVar == 'R '){
        //there is no rebate for regular members

    }
    else if(memberVar == 'E'){
        //executive members has rebate
    }

    //need to account for if a member switches:
    //NEED RUNNING TOTAL
return;
}
