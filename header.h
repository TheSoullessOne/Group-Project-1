#ifndef HEADER_H
#define HEADER_H

#include <iostream>
using namespace std;

/*******************************************************************************************/
// Globals
const double SALES_TAX   =  7.25;

class date
{
  public:
    // Constructors
    date();
    date(int, int, int);

    // Gets
    int getDay() const{
    return day;
    }
    int getMonth() const{
    return month;
    }
    int getYear() const{
    return year;
    }

    // Sets
    void setDay(int d){
    day = d;
    }
    void setMonth(int m){
    month = m;
    }
    void setYear(int y){
    year = y;
    }

  private:
    int day;
    int month;
    int year;
} // End class date

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
}

class member
{
  public:
    // Constructors
    member();
    member(string, int, bool, date, double, double, item*);

    // Gets
    string getName() const{
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
    item* getReceipt() const{
    return receipt;
    }

    // Sets
    void setName(string na){
    name = na;
    }
    void setNum(int nu){
    num = nu;
    }
    void setType(bool ty){
    type = ty;
    }
    void setExpiry(int d, int m, int y){
    date::setDay(d);
    date::setMonth(m);
    date::setYear(y);
    }
    void setTotal(double to){
    total = to;
    }
    void setAnnual(double a){
    annual_dues = a;
    }
    void setReceipt(item* r){
    receipt = r;
    }

    // Operator Overloads
    /*** Satisfy the Overload Requirement ***/





  private:
    string name;
    int    num;          // Membership #
    bool   type;         // Membership Type:
                         // False = Regular Member
                         // True  = Executive Member
    date   expiry;       // Membership Expiration Date
                         /*** Satisfies Composition Requirement ***/
    double total;        // Total Amount Spent
    double annual_dues;  // Regular   Member: $85.00
                         // Executive Member: $95.00
    item*  receipt;      // Will attempt to keep track of members' purchases
                         /*** Satisfies Pointer Requirement ***/
} // End class member

class executive: public member
{
  public:
    executive():member();

  private:
    double rebate;
} // End class executive

/*****************************************************************************************/





#endif
