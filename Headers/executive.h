#ifndef EXECUTIVE_H_
#define EXECUTIVE_H_
#include "member.h"

/**
 * @brief The executive class
 */
class executive: public member
{
  public:
    // Constructors
    /**
     * @brief executive
     */
    executive(): member(){
        rebate = 0;
    }

    executive(double         tempRebate,
              QString        tempName,
              int            tempNum,
              bool           tempType,
              int            tempDay,
              int            tempMonth,
              int            tempYear,
              double         tempTotal,
              double         tempDues,
              int           *tempP,
              QVector<item*> tempReceipt): member(tempName,
                                                  tempNum,
                                                  tempType,
                                                  tempDay,
                                                  tempMonth,
                                                  tempYear,
                                                  tempTotal,
                                                  tempDues,
                                                  tempP,
                                                  tempReceipt)
    {
        rebate = tempRebate;
    }

    // Function Members
    /**
     * @brief getRebate
     * @return
     */
    double getRebate() const {
        return rebate;
    }

    /**
     * @brief setRebate
     * @param tempRebate
     */
    void setRebate(double tempRebate) {
        rebate = tempRebate;
    }

  private:
    /**
     * @brief rebate
     */
    double rebate;
}; // End class executive

#endif
