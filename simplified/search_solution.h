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
  bool getSolutionWasFound () const;

  const std::vector<State>& getPath () const;
};

#endif // __SEARCH_SOLUTION_H__
