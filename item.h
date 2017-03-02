#ifndef ITEM_H_
#define ITEM_H_
#include "header.h"

class item
{
  public:
    // Constructors
    item();
    item(string*, double*, date);

  private:
    string* names;
    double* prices;       // names & prices are intended to be parallel arrays
    date    shopping_day;
};

#endif
