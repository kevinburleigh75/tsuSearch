#ifndef __SOLVER_H__
#define __SOLVER_H__

#include "types.h"

#include "search_problem.h"
#include "search_solution.h"

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

private:
  const SearchProblem _problem;
};

#endif // __SOLVER_H__
