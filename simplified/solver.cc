#include "solver.h"

#include "scratchpad.h"

#include <deque>
#include <iostream>

using namespace std;

typedef Scratchpad::StateInfo StateInfo;
typedef Scratchpad::TupleType TupleType;

Solver::Solver (const SearchProblem& problem)
  : _problem(problem)
{ }

SearchSolution Solver::solve ()
{
  SearchSolution solution;

  Scratchpad scratch;

  auto startState = _problem.getStartState();

  StateInfo startStateInfo {
    startState,
    {},
    0.0,
    _problem.getStateHeuristic(startState),
  };

  scratch.frontierPush(
    _impl_getPriority(startStateInfo),
    startStateInfo
  );

  while (!scratch.frontierIsEmpty())
  {
    auto tuple = scratch.frontierPop();
    auto priority     = get<0>(tuple);
    auto curState     = get<1>(tuple);
    auto curStateInfo = get<2>(tuple);

    cout << "curState = " << curState << endl;

    scratch.addToVisited(curStateInfo);

    if (_problem.isGoal(curState)) {
      solution.setSolutionWasFound(true);
      _addPathToSolution(solution, curStateInfo, scratch);
      break;
    }

    for (auto action : _problem.getActionsForState(curState)) {
      auto   successor   = _problem.getActionSuccessor(curState, action);
      double actionCost  = _problem.getActionCost(curState, action);
      double pathCost    = curStateInfo.pathCost + actionCost;
      double heuristic   = _problem.getStateHeuristic(successor);

      StateInfo sucStateInfo {
        successor,
        curState,
        pathCost,
        heuristic,
      };

      auto sucPriority = _impl_getPriority(sucStateInfo);

      if (!scratch.contains(successor)) {
        scratch.frontierPush(sucPriority, sucStateInfo);
      }
      else if (_impl_shouldUpdateSeenStates()) {
        StateInfo oldStateInfo = scratch.remove(successor);
        auto oldSucPriority = _impl_getPriority(oldStateInfo);

        if (sucPriority < oldSucPriority) {
          scratch.frontierPush(sucPriority, sucStateInfo);
        }
        else {
          scratch.addToVisited(sucStateInfo);
        }
      }
    }
  }

  return solution;
}

void Solver::_addPathToSolution (SearchSolution&   solution,
                                 const StateInfo&  curStateInfo,
                                 const Scratchpad& scratch) const
{
  deque<State> path;
  path.push_front(curStateInfo.state);

  StateInfo current = curStateInfo;
  while (current.predecessor) {
    current = scratch.getStateInfo(*(current.predecessor));
    path.push_front(current.state);
  }

  for (auto state : path) {
    solution.addPathState(state);
  }
}
