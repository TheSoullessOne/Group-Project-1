#ifndef EXECUTIVE_H_
#define EXECUTIVE_H_
#include "member.h"

class executive: public member
{
  public:
    executive(): member() {}
  private:
    double rebate;
}; // End class executive

#endif
