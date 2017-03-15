#ifndef SALESREPORT_H
#define SALESREPORT_H
#include "date.h"
#include "item.h"
#include "member.h"

/*class created to aid with the sales report*/
class salesReport
{
/*private members created to reach out and retrive private members from the other classes
 * its a private party yo*/
private:
    item* theItem;
    member* theMember;
    double thePrice;
    date saledate;

public:
    salesReport(item* theItem, member* theMember, double thePrice, date saledate)
    {
        this->theItem = theItem;
        this->theMember = theMember;
        this->thePrice = thePrice;
        this->saledate = saledate;
    }
/*gets so I can get the information */
    item* getTheItem()
    {
        return theItem;
    }

    member* getTheMember()
    {
        return theMember;
    }
    double getThePrice()
    {
        return thePrice;
    }
    date getDate()
    {
        return saledate;
    }
};

/* functor in order to make the slaes report work*/
struct salesCheck
{
    int day,month,year;
    /*this function is used in order to get the information from the user*/
    salesCheck(int day, int month, int year){this->day = day;
                                             this->month = month;
                                             this->year = year;}
/* the bool operator is used to take the date entered from the user and
 * implement it in order to gather the specific information for that day*/
    bool operator()(salesReport* s)
    {
        return s->getDate().getMonth() == month
                && s->getDate().getDay() == day
                && s->getDate().getYear() == year;
    }
};

#endif // SALESREPORT_H
