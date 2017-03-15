#ifndef EXECUTIVE_H_
#define EXECUTIVE_H_
#include "member.h"

/**
 * @brief The executive class
 */
class executive: public member
{
  public:
    /**
     * @brief executive
     */
    executive(): member() {}

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
