#include "gbfs.h"

Gbfs::Gbfs(const SearchProblem& problem)
  : Solver(problem)
{ }

Priority Gbfs::_impl_getPriority (const StateInfo& stateInfo)
{
  return stateInfo.heuristic;
}

bool Gbfs::_impl_shouldUpdateSeenStates ()
{
  return false;
}
