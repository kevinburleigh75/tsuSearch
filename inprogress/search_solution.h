#ifndef __SEARCH_SOLUTION_H__
#define __SEARCH_SOLUTION_H__

#include "types.h"

#include <vector>

class SearchSolution
{
public:
  typedef std::vector<State> Path;

public:
  SearchSolution ()                           = default;
  SearchSolution (const SearchSolution& orig) = default;
  SearchSolution (SearchSolution&& orig)      = default;
  SearchSolution& operator= (const SearchSolution& orig) = default;
  ~SearchSolution () = default;

public:
  bool getSolutionWasFound () const;
  void setSolutionWasFound (bool solutionFound);

  void addPathState (const State& state);
  const Path& getPath () const;

private:
  bool _solutionWasFound;
  Path _path;
};

#endif // __SEARCH_SOLUTION_H__
