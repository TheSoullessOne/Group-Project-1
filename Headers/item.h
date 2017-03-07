#ifndef ITEM_H_
#define ITEM_H_
#include <QString>

class item
{
  public:
    // Constructors
    item();
    item(QString*, double*, date);

  private:
    QString* names;
    double* prices;       // names & prices are intended to be parallel arrays
    date    shopping_day;
};

#endif
