#ifndef __BFS_H__
#define __BFS_H__

#include "solver.h"

class Bfs : public Solver
{
public:
  Bfs ()                           = delete;
  Bfs (const Bfs& orig)            = default;
  Bfs (Bfs && orig)                = delete;
  Bfs& operator= (const Bfs& orig) = default;
  ~Bfs ()                          = default;

  Bfs(const SearchProblem& problem);

protected:
  virtual Priority _impl_getPriority (const StateInfo& stateInfo);

  virtual bool _impl_shouldUpdateSeenStates ();

private:
  Priority _counter;
};

#endif // __BFS_H__
