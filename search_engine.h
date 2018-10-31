#ifndef __SEARCH_ENGINE__
#define __SEARCH_ENGINE__

#include "search_problem.h"

#include "kevin_pq.h"
#include "scratchpad.h"

#include <deque>

#include <iostream>

template <typename PROBLEMTYPE>
class SearchEngine
{
public:
  typedef PROBLEMTYPE                        ProblemType;
  typedef typename ProblemType::StateType    StateType;
  typedef typename ProblemType::ActionType   ActionType;
  typedef typename ProblemType::SolutionType SolutionType;
  typedef Scratchpad<StateType>              ScratchpadType;
  typedef typename ScratchpadType::StateInfo StateInfo;

  SearchEngine ()                                    = delete;
  SearchEngine (const SearchEngine& orig)            = default;
  SearchEngine (SearchEngine&& orig)                 = delete;
  SearchEngine& operator= (const SearchEngine& orig) = delete;
  virtual ~SearchEngine ()                           = default;

  SearchEngine (const ProblemType& problem)
    : _problem(problem)
  { }

  SolutionType solve ()
  {
    std::cout << "starting solve" << std::endl;

    SolutionType solution;

    ScratchpadType scratch;

    auto startState = _problem.getStartState();

    std::cout << "  1" << std::endl;

    StateInfo startStateInfo {
      startState,
      {},
      0.0,
      _problem.getStateHeuristic(startState),
    };

    std::cout << "  2" << std::endl;

    scratch.frontierPush(
      _impl_getPriority(startStateInfo),
      startStateInfo
    );

    std::cout << "  3" << std::endl;

    while (!scratch.frontierIsEmpty()) {
      auto [priority, curState, curStateInfo] = scratch.frontierPop();

      std::cout << "curState = " << curState << std::endl;

      scratch.addToVisited(curStateInfo);
      std::cout << "    4" << std::endl;

      if (_problem.isGoal(curState)) {
        solution.setSolutionWasFound(true);
        _addPathToSolution(solution, curStateInfo, scratch);
        break;
      }

      std::cout << "    5" << std::endl;

      for (auto action : _problem.getActionsForState(curState)) {

        std::cout << "      6" << std::endl;
        auto   successor   = _problem.getActionSuccessor(curState, action);
        double actionCost  = _problem.getActionCost(curState, action);
        double pathCost    = curStateInfo.pathCost + actionCost;
        double heuristic   = _problem.getStateHeuristic(successor);

        std::cout << "      7" << std::endl;

        StateInfo sucStateInfo {
          successor,
          curState,
          pathCost,
          heuristic,
        };

        auto priority = _impl_getPriority(sucStateInfo);

        std::cout << "      8" << std::endl;

        if (!scratch.contains(successor)) {
          std::cout << "        9" << std::endl;

          scratch.frontierPush(priority, sucStateInfo);
        }
        else if (_impl_shouldUpdateSeenStates()) {
          std::cout << "        10" << std::endl;
          StateInfo oldStateInfo = scratch.remove(successor);

          if (sucStateInfo.pathCost < oldStateInfo.pathCost) {
            scratch.frontierPush(priority, sucStateInfo);
          }
          else {
            scratch.addToVisited(sucStateInfo);
          }
        }
      }
    }

    return solution;
  }

protected:
  virtual double _impl_getPriority (const StateInfo& stateInfo) = 0;

  virtual bool   _impl_shouldUpdateSeenStates () = 0;

private:
  void _addPathToSolution (SolutionType&         solution,
                           const StateInfo&      curStateInfo,
                           const ScratchpadType& scratch) const
  {
    std::deque<StateType> path;
    path.push_front(curStateInfo.state);

    StateInfo current = curStateInfo;
    while (current.predecessor.has_value()) {
      current = scratch.getStateInfo(*current.predecessor);
      path.push_front(current.state);
    }

    for (auto state : path) {
      solution.addPathState(state);
    }
  }

private:
  const ProblemType _problem;
};

#endif // __SEARCH_ENGINE__