#include "search_solution.h"

void SearchSolution::setSolutionWasFound (const bool solutionWasFound) {
  _solutionWasFound = solutionWasFound;
}

bool SearchSolution::getSolutionWasFound () const {
  return _solutionWasFound;
}

void SearchSolution::addPathState (const State& state) {
  _path.push_back(state);
}

const std::vector<State>& SearchSolution::getPath () const
{
  return _path;
}
