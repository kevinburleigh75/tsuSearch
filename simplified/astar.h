#ifndef __ASTAR_H__
#define __ASTAR_H__

#include "solver.h"

class AStar : public Solver
{
public:
  AStar ()                             = delete;
  AStar (const AStar& orig)            = default;
  AStar (AStar && orig)                = delete;
  AStar& operator= (const AStar& orig) = default;
  ~AStar ()                            = default;

  AStar(const SearchProblem& problem);

protected:
  virtual Priority _impl_getPriority (const StateInfo& stateInfo);

  virtual bool _impl_shouldUpdateSeenStates ();
};

#endif // __ASTAR_H__
