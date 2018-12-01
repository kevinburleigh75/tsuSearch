#include "scratchpad.h"

bool Scratchpad::frontierIsEmpty () const
{
  return _frontier.isEmpty();
}

void Scratchpad::frontierPush (const Priority& priority,
                               const StateInfo& stateInfo)
{
  _visited.erase(stateInfo.state);
  if (_frontier.contains(stateInfo.state)) {
    _frontier.remove(stateInfo.state);
  }
  _frontier.push({priority, stateInfo.state, stateInfo});
}

Scratchpad::TupleType Scratchpad::frontierPop ()
{
  auto mapTuple = _frontier.pop();

  TupleType tupleType({
    std::get<0>(mapTuple),
    std::get<2>(mapTuple)
  });

  return tupleType;
}

void Scratchpad::addToVisited (const StateInfo& stateInfo)
{
  if (_frontier.contains(stateInfo.state)) {
    _frontier.remove(stateInfo.state);
  }
  _visited.insert({stateInfo.state, stateInfo});
}

bool Scratchpad::contains (const State& state) const
{
  return _frontier.contains(state) || (_visited.count(state) != 0);
}

StateInfo Scratchpad::getStateInfo (const State& state) const
{
  // this code assumes that contains(state) returned true

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

StateInfo Scratchpad::remove (const State& state)
{
  auto stateInfo = getStateInfo(state);

  _visited.erase(state);
  _frontier.remove(state);

  return stateInfo;
}


