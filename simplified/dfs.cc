#include "dfs.h"

Dfs::Dfs(const SearchProblem& problem)
  : Solver(problem),
    _counter(0.0)
{ }

Priority Dfs::_impl_getPriority (const StateInfo& stateInfo)
{
  return _counter--;
}

bool Dfs::_impl_shouldUpdateSeenStates ()
{
  return false;
}
