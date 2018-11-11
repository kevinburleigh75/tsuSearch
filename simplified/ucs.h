#ifndef __UCS_H__
#define __UCS_H__

#include "solver.h"

class Ucs : public Solver
{
public:
  Ucs ()                           = delete;
  Ucs (const Ucs& orig)            = default;
  Ucs (Ucs && orig)                = delete;
  Ucs& operator= (const Ucs& orig) = default;
  ~Ucs ()                          = default;

  Ucs(const SearchProblem& problem);

protected:
  virtual Priority _impl_getPriority (const StateInfo& stateInfo);

  virtual bool _impl_shouldUpdateSeenStates ();
};

#endif // __UCS_H__
