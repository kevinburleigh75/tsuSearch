#ifndef __BREADTH_FIRST_SEARCH__
#define __BREADTH_FIRST_SEARCH__

#include "search_problem.h"

#include <map>
#include <set>
#include <queue>

#include <iostream>

template <typename PROBLEMTYPE>
class BreadthFirstSearch
{
public:
  typedef PROBLEMTYPE                        ProblemType;
  typedef typename ProblemType::StateType    StateType;
  typedef typename ProblemType::ActionType   ActionType;
  typedef typename ProblemType::SolutionType SolutionType;

  BreadthFirstSearch ()                                          = delete;
  BreadthFirstSearch (const BreadthFirstSearch& orig)            = default;
  BreadthFirstSearch (BreadthFirstSearch&& orig)                 = delete;
  BreadthFirstSearch& operator= (const BreadthFirstSearch& orig) = delete;
  ~BreadthFirstSearch ()                                         = default;

  BreadthFirstSearch (const ProblemType& problem)
    : _problem(problem)
  { }

  struct StateInfo {
    StateType                state;
    std::optional<StateType> parentState;
  };

  SolutionType solve () const
  {
    SolutionType solution;

    std::map<StateType,StateInfo> seen;
    std::queue<StateInfo>         frontier;

    frontier.push({_problem.getStartState(), {}});

    bool keepSearching = true;

    while (!frontier.empty() && keepSearching) {
      auto curStateInfo = frontier.front();
      frontier.pop();

      auto curState = curStateInfo.state;
      std::cout << "curState = " << curState << std::endl;
      seen.insert({curState,curStateInfo});

      if (_problem.isGoal(curState)) {
        solution.setSolutionWasFound(true);

        this->addPathToSolution(solution, curStateInfo, seen);
        keepSearching = false;

        continue;
      }

      for (auto action : _problem.getActionsForState(curState)) {
        auto successor = _problem.getActionSuccessor(curState, action);
        if (!seen.count(successor)) {
          frontier.push({successor,curState});
        }
      }
    }

    return solution;
  }

  void addPathToSolution (SolutionType&                       solution,
                          const StateInfo&                    curStateInfo,
                          const std::map<StateType,StateInfo> seen) const
  {
    std::deque<StateType> path;
    path.push_front(curStateInfo.state);

    StateInfo current = curStateInfo;
    while (current.parentState.has_value()) {
      current = seen.at(*current.parentState);
      path.push_front(current.state);
    }

    for (auto state : path) {
        solution.addPathState(state);
    }
  }

private:
  const ProblemType _problem;
};

#endif // __BREADTH_FIRST_SEARCH__