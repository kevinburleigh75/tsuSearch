#ifndef __SEARCH_PROBLEM_H__
#define __SEARCH_PROBLEM_H__

#include <functional>
#include <map>
#include <optional>
#include <set>
#include <utility>
#include <vector>

template<typename StateType, typename ActionType>
class StateAction
{
public:
  StateAction(const StateType& state, const ActionType& action)
    : _state(state),
      _action(action)
  { }

  bool operator< (const StateAction& other) const {
    if (_state < other._state) {
      return true;
    }
    else if (_action < other._action) {
      return true;
    }
    else {
      return false;
    }
  }

private:
  const StateType  _state;
  const ActionType _action;
};

template <typename StateType, typename ActionType>
class Solution
{ };

template<typename StateType, typename ActionType>
class SearchProblem
{
public:
  typedef StateAction<StateType,ActionType>                 StateActionType;
  typedef std::tuple<StateType,ActionType,double,StateType> TransitionInfoType;
  typedef std::function<bool(const StateType&)>             GoalTestType;
  typedef Solution<StateType,ActionType>                    SolutionType;

  ///////////////////////////////////////
  //
  // Big-5
  //
  ///////////////////////////////////////

public:

  SearchProblem ()                                    = default;
  SearchProblem (const SearchProblem& orig)           = delete;
  SearchProblem (const SearchProblem&& orig)          = delete;
  SearchProblem& operator=(const SearchProblem& orig) = delete;
  ~SearchProblem ()                                   = default;

  ///////////////////////////////////////
  //
  // Public Interface
  //
  ///////////////////////////////////////

public:

  SearchProblem& addState (const StateType& state) {
    _states.insert(state);

    if (_actionsByState.count(state) == 0) {
      std::set<ActionType> actions;
      _actionsByState.insert({state,actions});
    }

    return *this;
  }

  SearchProblem& addStates (const std::vector<StateType>& states) {
    for (auto state : states) {
      this->addState(state);
    }
    return *this;
  }

  SearchProblem& addTransition (const TransitionInfoType& info)
  {
    auto [state, action, cost, successor] = info;

    //
    // update states
    //

    this->addState(state);
    this->addState(successor);

    //
    // update actions
    //

    auto pos = _actionsByState.find(state);
    _actionsByState.at(state).insert(action);

    StateAction stateAction {state, action};

    //
    // update costs
    //

    _costByStateAction.insert({stateAction,cost});

    //
    // update successors
    //

    _successorsByStateAction.insert({stateAction,successor});

    return *this;
  }

  SearchProblem& addTransitions (const std::vector<TransitionInfoType>& infos) {
    for (auto info : infos) {
      this->addTransition(info);
    }
    return *this;
  }

  SearchProblem& setStateState (const StateType& startState) {
    this->addState(startState);
    _startState = startState;
    return *this;
  }

  SearchProblem& addGoalState (const StateType& goalState) {
    this->addState(goalState);
    _goalStates.insert(goalState);
    return *this;
  }

  SearchProblem& addGoalStates (const std::vector<StateType>& goalStates) {
    for (auto state : goalStates) {
      this->addGoalState(state);
    }
    return *this;
  }

  SearchProblem& addGoalTest (const GoalTestType& goalTest) {
    _goalTests.push_back(goalTest);
    return *this;
  }

  SolutionType solve () const {

    return SolutionType();
  }

  ///////////////////////////////////////
  //
  // Private Attributes
  //
  ///////////////////////////////////////

private:
  std::set<StateType>                      _states;
  std::map<StateType,std::set<ActionType>> _actionsByState;
  std::map<StateActionType,double>         _costByStateAction;
  std::map<StateActionType,StateType>      _successorsByStateAction;
  std::optional<StateType>                 _startState;
  std::set<StateType>                      _goalStates;
  std::vector<GoalTestType>                _goalTests;
};

#endif // __SEARCH_PROBLEM_H__