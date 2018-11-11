#include "kevin_pq.h"

#include <utility>

bool KevinPq::PrioritySetElem::operator< (const PrioritySetElem& other) const
{
  return std::tie(priority,state) < std::tie(other.priority,other.state);
}

bool KevinPq::isEmpty () const
{
  return _prioritySet.empty();
}

KevinPq::MapTuple KevinPq::pop ()
{
  auto setPos = _prioritySet.begin();
  auto elem = *setPos;
  _prioritySet.erase(setPos);

  auto mapPos = _tupleMap.find(elem.state);
  auto tuple = (*mapPos).second;
  _tupleMap.erase(mapPos);

  return tuple;
}

void KevinPq::push (const MapTuple& tuple)
{
  auto priority = std::get<0>(tuple);
  auto state    = std::get<1>(tuple);
  auto indo     = std::get<2>(tuple);

  PrioritySetElem elem {priority,state};

  _prioritySet.insert(elem);
  _tupleMap.insert({state,tuple});
}

bool KevinPq::contains (const State& state) const
{
  return (_tupleMap.find(state) != _tupleMap.end());
}

KevinPq::MapTuple KevinPq::get (const State& state) const
{
  auto pos = _tupleMap.find(state);
  return (*pos).second;
}

KevinPq::MapTuple KevinPq::remove (const State& state)
{
  auto mapPos = _tupleMap.find(state);
  auto tuple = (*mapPos).second;
  _tupleMap.erase(mapPos);

  auto priority = std::get<0>(tuple);
  auto tnode    = std::get<1>(tuple);
  auto info     = std::get<2>(tuple);

  auto setPos = _prioritySet.find({priority,state});
  auto elem   = *setPos;
  _prioritySet.erase(setPos);

  return tuple;
}
