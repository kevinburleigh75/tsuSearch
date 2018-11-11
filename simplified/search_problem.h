#ifndef __SEARCH_PROBLEM_H__
#define __SEARCH_PROBLEM_H__

#include "types.h"

#include <map>
#include <experimental/optional>
#include <set>
#include <utility>
#include <vector>

class SearchProblem;

class SearchProblemBuilder
{
  typedef std::tuple<State,State,Cost> Transition;
  typedef std::tuple<State,Heuristic>  StateHeuristic;

public:
  SearchProblemBuilder ()                                             = default;
  SearchProblemBuilder (const SearchProblemBuilder& orig)             = default;
  SearchProblemBuilder (SearchProblemBuilder&& orig)                  = delete;
  SearchProblemBuilder& operator= (const SearchProblemBuilder& orig)  = delete;
  ~SearchProblemBuilder ()                                            = default;

public:
  SearchProblemBuilder& addStates          (const std::vector<State>& states);
  SearchProblemBuilder& addState           (const State& state);
  SearchProblemBuilder& addTransitions     (const std::vector<Transition>& transitions);
  SearchProblemBuilder& addTransition      (const Transition& transition);
  SearchProblemBuilder& setStateState      (const State& startState);
  SearchProblemBuilder& addGoalState       (const State& goalState);
  SearchProblemBuilder& addStateHeuristics (const std::vector<StateHeuristic>& stateHeuristics);
  SearchProblemBuilder& addStateHeuristic  (const StateHeuristic& stateHeuristic);
  SearchProblem         build              ();

private:
  std::set<State>                     _states;
  std::map<State,double>              _heuristicByState;
  std::map<State,std::set<Action>>    _actionsByState;
  std::map<StateAction,double>        _costByStateAction;
  std::map<StateAction,State>         _successorByStateAction;
  std::experimental::optional<State>  _startState;
  std::set<State>                     _goalStates;
};

class SearchProblem
{
public:
  SearchProblem ()                                      = delete;
  SearchProblem (const SearchProblem& orig)             = default;
  SearchProblem (SearchProblem&& orig)                  = default;
  SearchProblem& operator= (const SearchProblem& orig)  = default;
  ~SearchProblem ()                                     = default;

  friend class SearchProblemBuilder;

public:
  const State& getStartState () const;

  const Heuristic& getStateHeuristic (const State& state) const;

  bool isGoal (const State& state) const;

  const std::set<Action>& getActionsForState (const State& state) const;

  const State& getActionSuccessor (const State& state, const Action& action) const;

  const Cost& getActionCost (const State& state, const Action& action) const;

private:
  SearchProblem (const std::set<State>&                   states,
                 const std::map<State,Heuristic>&         heuristicByState,
                 const std::map<State,std::set<Action>>&  actionsByState,
                 const std::map<StateAction,Cost>&        costByStateAction,
                 const std::map<StateAction,State>&       successorByStateAction,
                 const State&                             startState,
                 const std::set<State>&                   goalStates);

private:
  std::set<State>                     _states;
  std::map<State,double>              _heuristicByState;
  std::map<State,std::set<Action>>    _actionsByState;
  std::map<StateAction,double>        _costByStateAction;
  std::map<StateAction,State>         _successorByStateAction;
  State                               _startState;
  std::set<State>                     _goalStates;
};

#endif // __SEARCH_PROBLEM_H__
