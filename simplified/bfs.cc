#include "bfs.h"

Bfs::Bfs(const SearchProblem& problem)
  : Solver(problem),
    _counter(0.0)
{ }

Priority Bfs::_impl_getPriority (const StateInfo& stateInfo)
{
  return _counter++;
}

bool Bfs::_impl_shouldUpdateSeenStates ()
{
  return false;
}
