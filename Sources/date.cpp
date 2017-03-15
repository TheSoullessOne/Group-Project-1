#include "Headers\date.h"
#include <QString>

// Default contructor sets the date to 0, 0, 0000
/**
 * @brief date::date
 */
date::date()    {
    day = 0;
    month = 0;
    year = 0;
}

// Specific Constructor
/**
 * @brief date::date
 * @param tempDay
 * @param tempMonth
 * @param tempYear
 */
date::date(int tempDay, int tempMonth, int tempYear)   {
    day = tempDay;
    month = tempMonth;
    year = tempYear;
}

/**
 * @brief date::printDate
 * @return
 */
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
