#ifndef ITEM_H_
#define ITEM_H_
#include <QString>
#include "date.h"

/**
 * @brief The item class
 */
class item
{
  public:
    // Constructors
    /**
     * @brief item
     */
    item();
    /**
     * @brief item
     */
    item(QString, double, date);

    /**
     * @brief setShopDate
     * @param m
     * @param d
     * @param y
     */
    void setShopDate(int m,int d,int y)   {
        shopping_day.setDay(d);
        shopping_day.setMonth(m);
        shopping_day.setYear(y);
    }
    /**
     * @brief setItemName
     * @param tempName
     */
    void setItemName(QString tempName)  {
        name = tempName;
    }
    /**
     * @brief setItemPrice
     * @param tempPrice
     */
    void setItemPrice(double tempPrice) {
        price = tempPrice;
    }
    /**
     * @brief setAmtBought
     * @param tempAmt
     */
    void setAmtBought(int tempAmt)  {
        amtBought = tempAmt;
    }
    /**
     * @brief getShopDate
     * @return
     */
    date getShopDate() const  {
        return shopping_day;
    }
    /**
     * @brief getItemName
     * @return
     */
    QString getItemName() const {
        return name;
    }
    /**
     * @brief getItemPrice
     * @return
     */
    double getItemPrice() const {
        return price;
    }
    /**
     * @brief getAmtBought
     * @return
     */
    int getAmtBought() {
        return amtBought;
    }


  private:
    QString name;
    double  price;
    int     amtBought;
    date    shopping_day;
};

#endif
