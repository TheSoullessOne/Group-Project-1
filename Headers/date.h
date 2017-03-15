#ifndef DATE_H
#define DATE_H

#include <QString>

/**
 * @brief The date class
 */
class date
{
  public:
    // Constructors
    /**
     * @brief date
     */
    date();
    /**
     * @brief date
     */
    date(int, int, int);

    // Gets
    /**
     * @brief getDay
     * @return
     */
    int getDay() const{
    return day;
    }
    /**
     * @brief getMonth
     * @return
     */
    int getMonth() const{
    return month;
    }
    /**
     * @brief getYear
     * @return
     */
    int getYear() const{
    return year;
    }

    // Sets
    /**
     * @brief setDay
     * @param d
     */
    void setDay(int d){
    day = d;
    }
    /**
     * @brief setMonth
     * @param m
     */
    void setMonth(int m){
    month = m;
    }
    /**
     * @brief setYear
     * @param y
     */
    void setYear(int y){
    year = y;
    }

    /**
     * @brief printDate
     * @return
     */
    QString printDate();

  private:
    int day;
    int month;
    int year;
}; // End class date


#endif
