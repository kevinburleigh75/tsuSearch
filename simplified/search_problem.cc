#include "search_problem.h"

SearchProblemBuilder& SearchProblemBuilder::addStates (const std::vector<State>& states)
{
  for (auto state : states) {
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
  for (auto transition : transitions) {
    this->addTransition(transition);
  }
  return *this;
}

SearchProblemBuilder& SearchProblemBuilder::addTransition (const Transition& transition)
{
  auto state      = std::get<0>(transition);
  auto successor  = std::get<1>(transition);
  auto cost       = std::get<2>(transition);

  auto action = successor;

  this->addState(state);
  this->addState(successor);

  _actionsByState.at(state).insert(action);

  StateAction stateAction {state,action};

  _costByStateAction.insert({stateAction,cost});

  _successorByStateAction.insert({stateAction,successor});

  return *this;
}

SearchProblemBuilder& SearchProblemBuilder::setStateState (const State& startState)
{
  this->addState(startState);
  _startState = startState;
  return *this;
}

SearchProblemBuilder& SearchProblemBuilder::addGoalState (const State& goalState)
{
  this->addState(goalState);

  _goalStates.insert(goalState);

  _heuristicByState.erase(goalState);
  _heuristicByState.insert({goalState,0.0});;

  return *this;
}

SearchProblemBuilder& SearchProblemBuilder::addStateHeuristics (const std::vector<StateHeuristic>& stateHeuristics)
{
  for (auto stateHeuristic : stateHeuristics) {
    this->addStateHeuristic(stateHeuristic);
  }
  return *this;
}

SearchProblemBuilder& SearchProblemBuilder::addStateHeuristic (const StateHeuristic& stateHeuristic)
{
  auto state      = std::get<0>(stateHeuristic);
  auto heuristic  = std::get<1>(stateHeuristic);

  this->addState(state);

  _heuristicByState.erase(state);
  _heuristicByState.insert({state,heuristic});

  return *this;
}

SearchProblem SearchProblemBuilder::build ()
{
  if (!_startState) {
    throw std::logic_error("start state must be specified");
  }

  for (auto stateHeuristic : _heuristicByState) {
    auto state      = std::get<0>(stateHeuristic);
    auto heuristic  = std::get<1>(stateHeuristic);

    if (_goalStates.count(state) != 0) {
      if (heuristic != 0.0) {
        throw std::logic_error("all goal states must have zero heuristic");
      }
    }
  }

  SearchProblem problem(
    _states,
    _heuristicByState,
    _actionsByState,
    _costByStateAction,
    _successorByStateAction,
    *_startState,
    _goalStates
  );

  return problem;
}

SearchProblem::SearchProblem (const std::set<State>&                   states,
                              const std::map<State,Heuristic>&         heuristicByState,
                              const std::map<State,std::set<Action>>&  actionsByState,
                              const std::map<StateAction,Cost>&        costByStateAction,
                              const std::map<StateAction,State>&       successorByStateAction,
                              const State&                             startState,
                              const std::set<State>&                   goalStates)
  : _states(states),
    _heuristicByState(heuristicByState),
    _actionsByState(actionsByState),
    _costByStateAction(costByStateAction),
    _successorByStateAction(successorByStateAction),
    _startState(startState),
    _goalStates(goalStates)
{ }

const State& SearchProblem::getStartState () const
{
  return _startState;
}

const Heuristic&  SearchProblem::getStateHeuristic (const State& state) const
{
  auto pos = _heuristicByState.find(state);
  return pos->second;
}

bool SearchProblem::isGoal (const State& state) const
{
  return (_goalStates.count(state) != 0);
}

const std::set<Action>& SearchProblem::getActionsForState (const State& state) const
{
  return _actionsByState.at(state);
}

const State& SearchProblem::getActionSuccessor (const State& state, const Action& action) const
{
  StateAction stateAction(state, action);
  return _successorByStateAction.at(stateAction);
}

const Cost& SearchProblem::getActionCost (const State& state, const Action& action) const {
  StateAction stateAction(state, action);
  return _costByStateAction.at(stateAction);
}
