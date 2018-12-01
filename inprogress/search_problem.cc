#include "search_problem.h"

SearchProblemBuilder& SearchProblemBuilder::addStates (const std::vector<State>& states)
{
  for (auto& state : states) {
    this->addState(state);
  }
  return *this;
}

SearchProblemBuilder& SearchProblemBuilder::addState (const State& state)
{
  _states.insert(state);

  if (_actionsByState.count(state) == 0) {
    std::set<Action> actions;
    _actionsByState.insert({state,actions});
    _heuristicByState.insert({state,0.0});
  }

  return *this;
}

SearchProblemBuilder& SearchProblemBuilder::addTransitions (const std::vector<Transition>& transitions)
{
  for (auto& transition : transitions) {
    this->addTransition(transition);
  }
  return *this;
}

SearchProblemBuilder& SearchProblemBuilder::addTransition (const Transition& transition)
{
  auto state     = std::get<0>(transition);
  auto successor = std::get<1>(transition);
  auto cost      = std::get<2>(transition);

  auto& action = successor;

  this->addState(state);
  this->addState(successor);

  _actionsByState.at(state).insert(action);

  StateAction stateAction {state,action};

  _costByStateAction.insert({stateAction, cost});
  _successorByStateAction.insert({stateAction, successor});

  return *this;
}

SearchProblemBuilder& SearchProblemBuilder::setStartState (const State& startState)
{
  this->addState(startState);

  if (_startState.empty()) {
    _startState.push_back(startState);
  }
  else {
    _startState[0] = startState;
  }
  return *this;
}

SearchProblemBuilder& SearchProblemBuilder::addGoalState (const State& goalState)
{
  this->addState(goalState);

  _goalStates.insert(goalState);

  _heuristicByState.erase(goalState);
  _heuristicByState.insert({goalState,0.0});

  return *this;
}

SearchProblemBuilder& SearchProblemBuilder::addStateHeuristics (const std::vector<StateHeuristic>& stateHeuristics)
{
  for (auto& stateHeuristic : stateHeuristics) {
    this->addStateHeuristic(stateHeuristic);
  }
  return *this;
}

SearchProblemBuilder& SearchProblemBuilder::addStateHeuristic (const StateHeuristic& stateHeuristic)
{
  auto state     = std::get<0>(stateHeuristic);
  auto heuristic = std::get<1>(stateHeuristic);

  this->addState(state);

  _heuristicByState.erase(state);
  _heuristicByState.insert({state,heuristic});

  return *this;
}
