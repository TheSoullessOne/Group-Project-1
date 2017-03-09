#ifndef ITEM_H_
#define ITEM_H_
#include <QString>
#include "date.h"

class item
{
  public:
    // Constructors
    item();
    item(QString, double, date);

    void setShopDate(int m,int d,int y)   {
        shopping_day.setDay(d);
        shopping_day.setMonth(m);
        shopping_day.setYear(y);
    }

    void setItemName(QString tempName)  {
        name = tempName;
    }

    void setItemPrice(double tempPrice) {
        price = tempPrice;
    }

    date getShopDate() const  {
        return shopping_day;
    }

    QString getItemName() const {
        return name;
    }

    double getItemPrice() const {
        return price;
    }

  private:
    QString name;
    double price;
    date    shopping_day;
};

#endif
