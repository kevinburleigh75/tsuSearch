#ifndef __SEARCH_PROBLEM_H__
#define __SEARCH_PROBLEM_H__

#include <iostream>
#include <sstream>
#include <string>

#include <functional>
#include <map>
#include <optional>
#include <set>
#include <utility>
#include <vector>

template<typename STATETYPE, typename ACTIONTYPE>
class SearchProblem
{
public:
  class StateAction;
  class Builder;
  class Solution;

public:
  typedef STATETYPE  StateType;
  typedef ACTIONTYPE ActionType;
  typedef Solution   SolutionType;

  typedef std::tuple<StateType,ActionType,double,StateType> TransitionInfoType;
  typedef std::function<bool(const StateType&)>             GoalTestType;

  ///////////////////////////////////////////////////////////////////
  //
  // inner class StateAction
  //
  ///////////////////////////////////////////////////////////////////

public:
  class StateAction
  {
  public:
    StateAction(const StateType& state, const ActionType& action)
      : _state(state),
        _action(action)
    { }

    bool operator== (const StateAction& other) const {
      return (_state == other._state) && (_action == other._action);
    }

    bool operator< (const StateAction& other) const {
      if (_state < other._state) {
        return true;
      }
      else if ((_state == other._state) && (_action < other._action)) {
        return true;
      }
      else {
        return false;
      }
    }

    std::string toString () const {
      std::ostringstream ostr;
      ostr << "SA<" << _state << "," << _action << ">";
      return ostr.str();
    }

  private:
    const StateType  _state;
    const ActionType _action;
  };

  ///////////////////////////////////////////////////////////////////
  //
  // inner class Builder
  //
  ///////////////////////////////////////////////////////////////////

public:

  class Builder
  {
  public:

    ///////////////////////////////////////
    // Big-5
    ///////////////////////////////////////

  public:
    Builder ()                              = default;
    Builder (const Builder& orig)           = delete;
    Builder (Builder&& orig)                = delete;
    Builder& operator=(const Builder& orig) = delete;
    ~Builder ()                             = default;

    ///////////////////////////////////////
    // Public Interface
    ///////////////////////////////////////

  public:

    Builder& addState (const StateType& state) {
      _states.insert(state);

      if (_actionsByState.count(state) == 0) {
        std::set<ActionType> actions;
        _actionsByState.insert({state,actions});
      }

      return *this;
    }

    Builder& addStates (const std::vector<StateType>& states) {
      for (auto state : states) {
        this->addState(state);
      }
      return *this;
    }

    Builder& addTransition (const TransitionInfoType& info) {
      auto [state, action, cost, successor] = info;

      // update states
      this->addState(state);
      this->addState(successor);

      // update actions
      auto pos = _actionsByState.find(state);
      _actionsByState.at(state).insert(action);

      StateAction stateAction {state, action};

      // update costs
      _costByStateAction.insert({stateAction,cost});

      // update successors
      _successorByStateAction.insert({stateAction,successor});

      return *this;
    }

    Builder& addTransitions (const std::vector<TransitionInfoType>& infos) {
      for (auto info : infos) {
        this->addTransition(info);
      }
      return *this;
    }

    Builder& setStateState (const StateType& startState) {
      this->addState(startState);
      _startState = startState;
      return *this;
    }

    Builder& addGoalState (const StateType& goalState) {
      this->addState(goalState);
      _goalStates.insert(goalState);
      return *this;
    }

    Builder& addGoalStates (const std::vector<StateType>& goalStates) {
      for (auto state : goalStates) {
        this->addGoalState(state);
      }
      return *this;
    }

    Builder& addGoalTest (const GoalTestType& goalTest) {
      _goalTests.push_back(goalTest);
      return *this;
    }

    SearchProblem build () const {
      if (!_startState.has_value()) {
        throw std::logic_error("start state must be specified");
      }

      SearchProblem result(
        _states,
        _actionsByState,
        _costByStateAction,
        _successorByStateAction,
        *_startState,
        _goalStates,
        _goalTests
      );

      return result;
    }

    ///////////////////////////////////////
    // Private Attributes
    ///////////////////////////////////////

  private:
    std::set<StateType>                      _states;
    std::map<StateType,std::set<ActionType>> _actionsByState;
    std::map<StateAction,double>             _costByStateAction;
    std::map<StateAction,StateType>          _successorByStateAction;
    std::optional<StateType>                 _startState;
    std::set<StateType>                      _goalStates;
    std::vector<GoalTestType>                _goalTests;
  };

  ///////////////////////////////////////////////////////////////////
  //
  // inner class Solution
  //
  ///////////////////////////////////////////////////////////////////

public:

  class Solution
  {
  public:
    Solution (const Solution& orig)            = default;
    Solution (Solution&& orig)                 = delete;
    Solution& operator= (const Solution& orig) = delete;
    ~Solution ()                               = default;

    Solution ()
      : _solutionWasFound(false)
    { }

    void setSolutionWasFound (const bool solutionWasFound) {
      _solutionWasFound = solutionWasFound;
    }

    bool getSolutionWasFound () const {
      return _solutionWasFound;
    }

    void addPathState (const StateType& state) {
      _path.push_back(state);
    }

    const std::vector<StateType>& getPath () const {
      return _path;
    }

  private:
    bool                   _solutionWasFound;
    std::vector<StateType> _path;
  };

  ///////////////////////////////////////////////////////////////////
  //
  // class SearchProblem
  //
  ///////////////////////////////////////////////////////////////////

  ///////////////////////////////////////
  // Big-5
  ///////////////////////////////////////

private:
  SearchProblem (const std::set<StateType>&                      states,
                 const std::map<StateType,std::set<ActionType>>& actionsByState,
                 const std::map<StateAction,double>&             costByStateAction,
                 const std::map<StateAction,StateType>&          successorsByStateAction,
                 const StateType&                                startState,
                 const std::set<StateType>&                      goalStates,
                 const std::vector<GoalTestType>&                goalTests)
    : _states(states),
      _actionsByState(actionsByState),
      _costByStateAction(costByStateAction),
      _successorByStateAction(successorsByStateAction),
      _startState(startState),
      _goalStates(goalStates),
      _goalTests(goalTests)
  { }

public:
  SearchProblem (const SearchProblem& orig)             = default;
  SearchProblem (SearchProblem&& orig)                  = delete;
  SearchProblem& operator= (const SearchProblem& other) = default;
  ~SearchProblem ()                                     = default;

  ///////////////////////////////////////
  // Public interface
  ///////////////////////////////////////

public:
  const std::set<StateType>& getStates () const {
    return _states;
  }

  const StateType& getStartState () const {
    return _startState;
  }

  const std::set<ActionType>& getActionsForState (const StateType& state) const {
    return _actionsByState.at(state);
  }

  const StateType& getActionSuccessor (const StateType& state, const ActionType& action) const {
    StateAction stateAction(state, action);
    return _successorByStateAction.at(stateAction);
  }

  double getActionCost (const StateType& state, const ActionType& action) const {
    StateAction stateAction(state, action);
    return _costByStateAction.at(stateAction);
  }

  double getStateHeuristic (const StateType& state) const {
    return 0.0;
  }

  bool isGoal (const StateType& state) const {
    bool result = false;

    if (!result) {
      result = result || (_goalStates.count(state) != 0);
    }

    if (!result) {
      for (auto goalTest : _goalTests) {
        result = result || goalTest(state);
        if (result) {
          break;
        }
      }
    }

    std::cout << "  isGoal(" << state << "): " << std::boolalpha << result << std::endl;
    return result;
  }

  ///////////////////////////////////////
  // Private Attributes
  ///////////////////////////////////////

private:
  const std::set<StateType>                      _states;
  const std::map<StateType,std::set<ActionType>> _actionsByState;
  const std::map<StateAction,double>             _costByStateAction;
  const std::map<StateAction,StateType>          _successorByStateAction;
  const StateType                                _startState;
  const std::set<StateType>                      _goalStates;
  const std::vector<GoalTestType>                _goalTests;
};

template <typename StateType, typename ActionType>
std::ostream& operator<< (std::ostream& ostr, const typename SearchProblem<StateType,ActionType>::StateAction& sa) {
  ostr << sa.toString();
  return ostr;
}

#endif // __SEARCH_PROBLEM_H__