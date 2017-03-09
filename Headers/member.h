#ifndef MEMBER_H_
#define MEMBER_H_
#include "date.h"
#include "item.h"
#include <QVector>


class member
{
  public:
    // Constructors
    member();
    member(QString, int, bool, int, int, int, double, double, QVector<item*>);

    // Gets
    QString getName() const{
    return name;
    }
    int getNum() const{
    return num;
    }
    bool getType() const{
    return type;
    }
    date getExpiry() const{
    return expiry;
    }
    double getTotal() const{
    return total;
    }
    double getAnnual() const{
    return annual_dues;
    }
    QVector<item*> getReceipt() const{
        return receipt;
    }

    // Sets
    void setName(QString na){
    name = na;
    }
    void setNum(int nu){
    num = nu;
    }
    void setType(bool ty){
    type = ty;
    }
    void setExpiry(int d, int m, int y){
    expiry.setDay(d);
    expiry.setMonth(m);
    expiry.setYear(y);
    }
    void setTotal(double to){
    total = to;
    }
    void setAnnual(double a){
    annual_dues = a;
    }
    void setReceipt(item* tempItem){
        receipt.push_back(tempItem);
    }

    // Operator Overloads
    /*** Satisfy the Overload Requirement ***/





  private:
    QString name;
    int    num;          // Membership #
    bool   type;         // Membership Type:
                         // False = Regular Member
                         // True  = Executive Member
    date   expiry;       // Membership Expiration Date
                         /*** Satisfies Composition Requirement ***/
    double total;        // Total Amount Spent
    double annual_dues;  // Regular   Member: $85.00
                         // Executive Member: $95.00
    QVector<item*>  receipt;      // Will attempt to keep track of members' purchases
                         /*** Satisfies Pointer Requirement ***/
}; // End class member

#endif
