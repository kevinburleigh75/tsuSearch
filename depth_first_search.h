#ifndef __DEPTH_FIRST_SEARCH__
#define __DEPTH_FIRST_SEARCH__

#include "search_problem.h"
#include "kevin_pq.h"

#include <map>
#include <deque>

#include <iostream>

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

  struct StateInfo {
    StateType                state;
    std::optional<StateType> parentState;
  };

  SolutionType solve () const
  {
    SolutionType solution;

    long int push_counter = 0;

    std::map<StateType,StateInfo>         seen;
    KevinPq<long int,StateType,StateInfo> frontier;

    auto startState = _problem.getStartState();

    frontier.push({push_counter--, startState, {startState,{}}});

    bool keepSearching = true;

    while (!frontier.isEmpty() && keepSearching) {
      auto [priority, curState, curStateInfo] = frontier.pop();

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
          frontier.push({push_counter--, successor, {successor,curState}});
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

#endif // __DEPTH_FIRST_SEARCH__