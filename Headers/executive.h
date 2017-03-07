#ifndef EXECUTIVE_H_
#define EXECUTIVE_H_
#include "member.h"

class executive: public member
{
  public:
    executive(): member() {}

    double getRebate() const {
        return rebate;
    }

    void setRebate(double tempRebate) {
        rebate = tempRebate;
    }

  private:
    double rebate;
}; // End class executive

#endif