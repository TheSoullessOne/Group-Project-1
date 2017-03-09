#include "Headers\member.h"

// Default Constructor Sets everything to NULL or 0
member::member()    {
    name = "";
    num = 0;
    type = false;
    expiry.setDay(0);
    expiry.setMonth(0);
    expiry.setYear(0);
    total = 0;
    annual_dues = 0;
}

// Specific constructor
member::member(QString tempName,
               int tempNum,
               bool tempType,
               int tempDay,
               int tempMonth,
               int tempYear,
               double tempTotal,
               double tempDues,
               QVector<item*> tempReceipt)   {
    name = tempName;
    num = tempNum;
    type = tempType;
    expiry.setDay(tempDay);
    expiry.setMonth(tempMonth);
    expiry.setYear(tempYear);
    total = tempTotal;
    annual_dues = tempDues;
    receipt = tempReceipt;
}

// Destructor if needed???
//member::~member()   {

//}
