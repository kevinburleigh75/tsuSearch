#ifndef __UNIFORM_FIRST_SEARCH__
#define __UNIFORM_FIRST_SEARCH__

#include "search_problem.h"

#include "kevin_pq.h"

#include <deque>
#include <map>
#include <set>

#include <iostream>

template <typename PROBLEMTYPE>
class UniformCostSearch
{
public:
  typedef PROBLEMTYPE                        ProblemType;
  typedef typename ProblemType::StateType    StateType;
  typedef typename ProblemType::ActionType   ActionType;
  typedef typename ProblemType::SolutionType SolutionType;

  UniformCostSearch ()                                         = delete;
  UniformCostSearch (const UniformCostSearch& orig)            = default;
  UniformCostSearch (UniformCostSearch&& orig)                 = delete;
  UniformCostSearch& operator= (const UniformCostSearch& orig) = delete;
  ~UniformCostSearch ()                                        = default;

  UniformCostSearch (const ProblemType& problem)
    : _problem(problem)
  { }

  struct StateInfo {
    StateType                state;
    std::optional<StateType> parentState;
    double                   pathCost;
  };

  SolutionType solve () const
  {
    SolutionType solution;

    long int push_counter = 0;

    std::map<StateType,StateInfo>         visited;
    KevinPq<long int,StateType,StateInfo> frontier;

    auto startState = _problem.getStartState();

    frontier.push({push_counter++, startState, {startState,{},0.0}});

    bool keepSearching = true;

    while (!frontier.isEmpty() && keepSearching) {
      auto [priority, curState, curStateInfo] = frontier.pop();

      std::cout << "curState = " << curState << std::endl;
      visited.insert({curState,curStateInfo});

      if (_problem.isGoal(curState)) {
        solution.setSolutionWasFound(true);

        this->addPathToSolution(solution, curStateInfo, visited);
        keepSearching = false;

        continue;
      }

      for (auto action : _problem.getActionsForState(curState)) {
        auto   successor   = _problem.getActionSuccessor(curState, action);
        double sucPathCost = curStateInfo.pathCost + _problem.getActionCost(curState, action);

        if (!visited.count(successor) && !frontier.contains(successor)) {
          frontier.push({sucPathCost, successor, {successor,curState,sucPathCost}});
        }
        else {
          StateInfo oldStateInfo;
          auto pos = visited.find(successor);
          if (pos != visited.end()) {
            oldStateInfo = pos->second;
            visited.erase(pos);
          }
          if (frontier.contains(successor)) {
            oldStateInfo = std::get<2>(frontier.remove(successor));
          }

          if (sucPathCost < oldStateInfo.pathCost) {
            frontier.push({sucPathCost, successor, {successor,curState,sucPathCost}});
          }
          else {
            visited.insert({successor,oldStateInfo});
          }
        }
      }
    }

    return solution;
  }

  void addPathToSolution (SolutionType&                       solution,
                          const StateInfo&                    curStateInfo,
                          const std::map<StateType,StateInfo> visited) const
  {
    std::deque<StateType> path;
    path.push_front(curStateInfo.state);

    StateInfo current = curStateInfo;
    while (current.parentState.has_value()) {
      current = visited.at(*current.parentState);
      path.push_front(current.state);
    }

    for (auto state : path) {
      solution.addPathState(state);
    }
  }

private:
  const ProblemType _problem;
};

#endif // __UNIFORM_FIRST_SEARCH__