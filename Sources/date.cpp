#include "Headers\date.h"

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


