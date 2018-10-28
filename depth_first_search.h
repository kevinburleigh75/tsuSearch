#ifndef __DEPTH_FIRST_SEARCH__
#define __DEPTH_FIRST_SEARCH__

#include "search_problem.h"

#include <set>
#include <stack>

template <typename PROBLEMTYPE>
class DepthFirstSearch
{
public:
  typedef PROBLEMTYPE                        ProblemType;
  typedef typename ProblemType::StateType    StateType;
  typedef typename ProblemType::ActionType   ActionType;
  typedef typename ProblemType::SolutionType SolutionType;

  DepthFirstSearch ()                                        = delete;
  DepthFirstSearch (const DepthFirstSearch& orig)            = default;
  DepthFirstSearch (DepthFirstSearch&& orig)                 = delete;
  DepthFirstSearch& operator= (const DepthFirstSearch& orig) = delete;
  ~DepthFirstSearch ()                                       = default;

  DepthFirstSearch (const ProblemType& problem)
    : _problem(problem)
  { }

  SolutionType solve () const
  {
    SolutionType solution;

    std::set<StateType>   expanded;
    std::set<StateType>   seen;
    std::stack<StateType> frontier;

    frontier.push(_problem.getStartState());

    while (!frontier.empty()) {
      StateType curState = frontier.top();
      frontier.pop();

      seen.insert(curState);

      if (_problem.isGoal(curState)) {
        solution.setSolutionWasFound(true);
        break;
      }

      expanded.insert(curState);

      for (auto action : _problem.getActionsForState(curState)) {
        auto successor = _problem.getActionSuccessor(curState, action);
        if (!seen.count(successor)) {
          frontier.push(successor);
        }
      }
    }

    return solution;
  }

private:
  const ProblemType _problem;
};

#endif // __DEPTH_FIRST_SEARCH__