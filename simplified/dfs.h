#ifndef __DFS_H__
#define __DFS_H__

#include "solver.h"

class Dfs : public Solver
{
public:
  Dfs ()                           = delete;
  Dfs (const Dfs& orig)            = default;
  Dfs (Dfs && orig)                = delete;
  Dfs& operator= (const Dfs& orig) = default;
  ~Dfs ()                          = default;

  Dfs(const SearchProblem& problem);

protected:
  virtual Priority _impl_getPriority (const StateInfo& stateInfo);

  virtual bool _impl_shouldUpdateSeenStates ();

private:
  Priority _counter;
};

#endif // __DFS_H__
