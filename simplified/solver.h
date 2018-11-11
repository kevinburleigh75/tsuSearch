#ifndef __SOLVER_H__
#define __SOLVER_H__

#include "types.h"

#include "search_problem.h"
#include "search_solution.h"
#include "scratchpad.h"

class Solver
{
public:
  Solver ()                               = delete;
  Solver (const Solver& orig)             = default;
  Solver (Solver&& orig)                  = delete;
  Solver& operator= (const Solver& orig)  = default;
  virtual ~Solver ()                      = default;

  Solver (const SearchProblem& problem);

public:
  SearchSolution solve ();

protected:
  virtual Priority _impl_getPriority (const StateInfo& stateInfo) = 0;

  virtual bool _impl_shouldUpdateSeenStates () = 0;

private:
  void _addPathToSolution (SearchSolution&   solution,
                           const StateInfo&  curStateInfo,
                           const Scratchpad& scratch) const;

private:
  const SearchProblem _problem;
};

#endif // __SOLVER_H__
