#include "search_solution.h"

bool SearchSolution::getSolutionWasFound () const
{
  return _solutionWasFound;
}

void SearchSolution::setSolutionWasFound (bool solutionFound)
{
  _solutionWasFound = solutionFound;
}

void SearchSolution::addPathState (const State& state)
{
  _path.push_back(state);
}

const SearchSolution::Path& SearchSolution::getPath () const
{
  return _path;
}
