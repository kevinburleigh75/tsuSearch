#include "scratchpad.h"

#include <sstream>

std::string Scratchpad::StateInfo::toString () const {
  std::ostringstream ostr;
  State pred = -1;
  if (predecessor) {
    pred = *predecessor;
  }
  ostr << "SI<" << state << "," << pred << "," << pathCost << "," << heuristic << ">";
  return ostr.str();
}

bool Scratchpad::frontierIsEmpty () const
{
  return _frontier.isEmpty();
}

void Scratchpad::frontierPush (const Priority& priority, const StateInfo& stateInfo)
{
  _visited.erase(stateInfo.state);
  if (_frontier.contains(stateInfo.state)) {
    _frontier.remove(stateInfo.state);
  }
  _frontier.push({priority,stateInfo.state,stateInfo});
}

Scratchpad::TupleType Scratchpad::frontierPop ()
{
  auto tuple = _frontier.pop();
  return tuple;
}

void Scratchpad::addToVisited (const StateInfo& stateInfo)
{
  if (_frontier.contains(stateInfo.state)) {
    _frontier.remove(stateInfo.state);
  }
  _visited.insert({stateInfo.state,stateInfo});
}

bool Scratchpad::contains (const State& state)
{
  return ( _frontier.contains(state) ||
           (_visited.find(state) != _visited.end()) );
}

Scratchpad::StateInfo Scratchpad::getStateInfo (const State& state) const
{
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

Scratchpad::StateInfo Scratchpad::remove (const State& state)
{
  StateInfo stateInfo = this->getStateInfo(state);

  _visited.erase(state);
  _frontier.remove(state);

  return stateInfo;
}
