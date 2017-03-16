#ifndef MEMBER_H_
#define MEMBER_H_
#include "date.h"
#include "item.h"
#include <QVector>

/**
 * @brief The member class
 */
class member
{
  public:
    // Constructors
    /**
     * @brief member
     */
    member();
    /**
     * @brief member
     */
    member(QString, int, bool, int, int, int, double, double, int*, QVector<item*>);

    // Copy Constructor
    member(const member&);

    // Gets
    /**
     * @brief getName
     * @return
     */
    QString getName() const{
    return name;
    }
    /**
     * @brief getNum
     * @return
     */
    int getNum() const{
    return num;
    }
    /**
     * @brief getType
     * @return
     */
    bool getType() const{
    return type;
    }
    /**
     * @brief getExpiry
     * @return
     */
    date getExpiry() const{
    return expiry;
    }
    /**
     * @brief getTotal
     * @return
     */
    double getTotal() const{
    return total;
    }
    /**
     * @brief getAnnual
     * @return
     */
    double getAnnual() const{
    return annual_dues;
    }
    /**
     * @brief getReceipt
     * @return
     */
    QVector<item*> getReceipt() const{
        return receipt;
    }

    // Sets
    /**
     * @brief setName
     * @param na
     */
    void setName(QString na){
    name = na;
    }
    /**
     * @brief setNum
     * @param nu
     */
    void setNum(int nu){
    num = nu;
    }
    /**
     * @brief setType
     * @param ty
     */
    void setType(bool ty){
    type = ty;
    }
    /**
     * @brief setExpiry
     * @param d
     * @param m
     * @param y
     */
    void setExpiry(int d, int m, int y){
    expiry.setDay(d);
    expiry.setMonth(m);
    expiry.setYear(y);
    }
    /**
     * @brief setTotal
     * @param to
     */
    void setTotal(double to){
    total = to;
    }
    /**
     * @brief setAnnual
     * @param a
     */
    void setAnnual(double a){
    annual_dues = a;
    }
    /**
     * @brief setReceipt
     * @param tempItem
     */
    void setReceipt(item* tempItem){
        receipt.push_back(tempItem);
    }

    // Operator Overloads
    /*** Satisfy the Overload Requirement ***/


    // Destructor
    ~member();


  private:
    QString name;
    int     num;            // Membership #
    bool    type;           // Membership Type:
                            // False = Regular Member
                            // True  = Executive Member
    date    expiry;         // Membership Expiration Date
                            /*** Satisfies Composition Requirement ***/
    double  total;          // Total Amount Spent
    double  annual_dues;    // Regular   Member: $85.00
                            // Executive Member: $95.00
    int     *p;             // Mysterious pointer that does who-knows-what
                            /*** Satisfies Pointer Requirement ***/
    QVector<item*> receipt; // Will attempt to keep track of members' purchases
}; // End class member

#endif
