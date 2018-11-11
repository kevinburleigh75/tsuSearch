#include "astar.h"

AStar::AStar(const SearchProblem& problem)
  : Solver(problem)
{ }

Priority AStar::_impl_getPriority (const StateInfo& stateInfo)
{
  return stateInfo.pathCost + stateInfo.heuristic;
}

bool AStar::_impl_shouldUpdateSeenStates ()
{
  return true;
}
