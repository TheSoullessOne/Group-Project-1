git#include "header.h"

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
}; // End class date
