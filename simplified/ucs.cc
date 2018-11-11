#include "ucs.h"

Ucs::Ucs(const SearchProblem& problem)
  : Solver(problem)
{ }

Priority Ucs::_impl_getPriority (const StateInfo& stateInfo)
{
  return stateInfo.pathCost;
}

bool Ucs::_impl_shouldUpdateSeenStates ()
{
  return true;
}
