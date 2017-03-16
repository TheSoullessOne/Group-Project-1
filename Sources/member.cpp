#include "Headers\member.h"

// Default Constructor Sets Everything to NULL or 0
/**
 * @brief member::member
 */
member::member()    {
    name = "";
    num  = 0;
    type = false;
    expiry.setDay(0);
    expiry.setMonth(0);
    expiry.setYear(0);
    total = 0;
    annual_dues = 0;
    p = NULL;
}

// Specific Constructor
/**
 * @brief member::member
 * @param tempName
 * @param tempNum
 * @param tempType
 * @param tempDay
 * @param tempMonth
 * @param tempYear
 * @param tempTotal
 * @param tempDues
 * @param tempReceipt
 */
member::member(QString        tempName,
               int            tempNum,
               bool           tempType,
               int            tempDay,
               int            tempMonth,
               int            tempYear,
               double         tempTotal,
               double         tempDues,
               int           *tempP,
               QVector<item*> tempReceipt)
{
    name = tempName;
    num  = tempNum;
    type = tempType;
    expiry.setDay(tempDay);
    expiry.setMonth(tempMonth);
    expiry.setYear(tempYear);
    total       = tempTotal;
    annual_dues = tempDues;
    receipt     = tempReceipt;

    p  = new int;
    *p = *tempP;
}

// Copy Constructor
member::member(const member& obj)
{
    name        = obj.name;
    num         = obj.num;
    type        = obj.type;
    expiry      = obj.expiry;
    total       = obj.total;
    annual_dues = obj.annual_dues;
    receipt     = obj.receipt;

    p  = new int;
    *p = *obj.p;
}



// Destructor
member::~member()
{
    delete p;
}
