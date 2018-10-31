#ifndef __SCRATCHPAD__
#define __SCRATCHPAD__

template <typename STATETYPE>
class Scratchpad
{
public:
  struct StateInfo;

  typedef STATETYPE                              StateType;
  typedef std::tuple<double,StateType,StateInfo> TupleType;

  struct StateInfo {
    StateType                state;
    std::optional<StateType> predecessor;
    double                   pathCost;
    double                   heuristic;
  };

  Scratchpad ()                                   = default;
  Scratchpad (const Scratchpad& orig)             = default;
  Scratchpad (Scratchpad&& orig)                  = delete;
  Scratchpad& operator= (const Scratchpad& orig)  = default;
  ~Scratchpad ()                                  = default;

  void frontierPush (const double priority, const StateInfo& stateInfo) {
    //
    // First, remove <stateInfo> from both _visited and/or _frontier.
    // Then insert it into _frontier with priority <priority>.
    //

    _visited.erase(stateInfo.state);
    if (_frontier.contains(stateInfo.state)) {
      _frontier.remove(stateInfo.state);
    }
    _frontier.push({priority,stateInfo.state,stateInfo});
  }

  TupleType frontierPop () {
    auto tuple = _frontier.pop();
    return tuple;
  }

  bool frontierIsEmpty () const {
    return _frontier.isEmpty();
  }

  void addToVisited (const StateInfo& stateInfo) {
    //
    // First, remove <stateInfo> from _frontier (if present).
    // Then add it to _visited, replacing any existing value.
    //

    if (_frontier.contains(stateInfo.state)) {
      _frontier.remove(stateInfo.state);
    }
    _visited.insert({stateInfo.state,stateInfo});
  }

  bool contains (const StateType& state) const {
    return ( _frontier.contains(state) ||
             (_visited.find(state) != _visited.end()) );
  }

  StateInfo getStateInfo (const StateType& state) const {
    //
    // Assumes <state> is contained (per contains() above).
    //

    StateInfo stateInfo;

    auto pos = _visited.find(state);
    if (pos != _visited.end()) {
      stateInfo = pos->second;
    }
    else {
      stateInfo = std::get<2>(_frontier.get(state));
    }

    return stateInfo;
  }

  StateInfo remove (const StateType& state) {
    //
    // Assumes <state> is contained (per contains() above).
    //

    StateInfo stateInfo = getStateInfo(state);

    _visited.erase(state);
    _frontier.remove(state);

    return stateInfo;
  }

private:
  std::map<StateType,StateInfo>       _visited;
  KevinPq<double,StateType,StateInfo> _frontier;
};

#endif // __SCRATCHPAD__