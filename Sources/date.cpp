#include "Headers\date.h"
#include <QString>

// Default contructor sets the date to 0, 0, 0000
date::date()    {
    day = 0;
    month = 0;
    year = 0;
}

// Specific Constructor
date::date(int tempDay, int tempMonth, int tempYear)   {
    day = tempDay;
    month = tempMonth;
    year = tempYear;
}

QString date::printDate()  {
    QString tempDate;

    if(getMonth() < 10) {
        tempDate += "0";
    }
    tempDate += QString::number(getMonth());
    tempDate += "/";
    if(getDay()<10) {
        tempDate += "0";
    }
    tempDate += QString::number(getDay());
    tempDate += "/";
    tempDate += QString::number(getYear());

    return tempDate;
}
