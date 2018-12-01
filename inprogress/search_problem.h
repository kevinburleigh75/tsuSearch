#ifndef __SEARCH_PROBLEM_H__
#define __SEARCH_PROBLEM_H__

#include "types.h"

#include <map>
#include <set>
#include <utility>
#include <vector>

class SearchProblem;

class SearchProblemBuilder
{
public:
  typedef std::tuple<State,State,Cost> Transition;
  typedef std::tuple<State,Heuristic>  StateHeuristic;

public:
  SearchProblemBuilder ()                                             = default;
  SearchProblemBuilder (const SearchProblemBuilder& orig)             = default;
  SearchProblemBuilder (SearchProblemBuilder&& orig)                  = delete;
  SearchProblemBuilder& operator= (const SearchProblemBuilder& orig)  = delete;
  ~SearchProblemBuilder ()                                            = default;

public:
  SearchProblemBuilder& addStates           (const std::vector<State>& states);
  SearchProblemBuilder& addState            (const State& state);
  SearchProblemBuilder& addTransitions      (const std::vector<Transition>& transitions);
  SearchProblemBuilder& addTransition       (const Transition& transition);
  SearchProblemBuilder& setStartState       (const State& startState);
  SearchProblemBuilder& addGoalState        (const State& goalState);
  SearchProblemBuilder& addStateHeuristics  (const std::vector<StateHeuristic>& stateHeuristics);
  SearchProblemBuilder& addStateHeuristic   (const StateHeuristic& stateHeuristic);
  SearchProblem         build               ();

private:
  std::set<State>                    _states;
  std::map<State,std::set<Action>>   _actionsByState;
  std::map<StateAction,Cost>         _costByStateAction;
  std::map<StateAction,State>        _successorByStateAction;
  std::vector<State>                 _startState;
  std::set<State>                    _goalStates;
  std::map<State,Heuristic>          _heuristicByState;
};

#endif // __SEARCH_PROBLEM_H__
