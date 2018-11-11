#ifndef __GBFS_H__
#define __GBFS_H__

#include "solver.h"

class Gbfs : public Solver
{
public:
  Gbfs ()                            = delete;
  Gbfs (const Gbfs& orig)            = default;
  Gbfs (Gbfs && orig)                = delete;
  Gbfs& operator= (const Gbfs& orig) = default;
  ~Gbfs ()                           = default;

  Gbfs(const SearchProblem& problem);

protected:
  virtual Priority _impl_getPriority (const StateInfo& stateInfo);

  virtual bool _impl_shouldUpdateSeenStates ();
};

#endif // __GBFS_H__
