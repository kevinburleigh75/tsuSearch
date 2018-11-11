#ifndef __SEARCH_SOLUTION_H__
#define __SEARCH_SOLUTION_H__

#include "types.h"

#include <vector>

class SearchSolution
{
public:
  SearchSolution ()                                       = default;
  SearchSolution (const SearchSolution& orig)             = default;
  SearchSolution (SearchSolution&& orig)                  = default;
  SearchSolution& operator= (const SearchSolution& orig)  = default;
  ~SearchSolution ()                                      = default;

public:
  void setSolutionWasFound (const bool solutionWasFound);

  bool getSolutionWasFound () const;

  void addPathState (const State& state);

  const std::vector<State>& getPath () const;

private:
  bool               _solutionWasFound;
  std::vector<State> _path;
};

#endif // __SEARCH_SOLUTION_H__
