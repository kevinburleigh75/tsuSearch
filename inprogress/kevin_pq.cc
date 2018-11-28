#include "kevin_pq.h"

#include <utility>

using namespace std;
bool KevinPq::PrioritySetElem::operator< (const PrioritySetElem& other) const
{
  return tie(priority,state) < tie(other.priority,other.state);
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

  auto mapPos = _infoMap.find(elem.state);
  auto tuple = mapPos->second;

  _infoMap.erase(mapPos);

  return tuple;
}

void KevinPq::push (const KevinPq::MapTuple& tuple)
{
  auto priority = std::get<0>(tuple);
  auto state    = std::get<1>(tuple);

  PrioritySetElem elem {priority,state};
  _prioritySet.insert(elem);

  _infoMap.insert({state,tuple});
}

bool KevinPq::contains (const State& state) const
{
  return _infoMap.count(state) > 0;
  // return _infoMap.find(state) != _infoMap.end();
}

KevinPq::MapTuple KevinPq::get (const State& state) const
{
  auto pos = _infoMap.find(state);
  return pos->second;
}

KevinPq::MapTuple KevinPq::remove (const State& state)
{
  auto mapPos = _infoMap.find(state);
  auto tuple = mapPos->second;
  _infoMap.erase(mapPos);

  // auto [priority, state, info] = tuple;

  auto priority = std::get<0>(tuple);
  auto tstate   = std::get<1>(tuple);
  auto info     = std::get<2>(tuple);

  auto setPos = _prioritySet.find({priority,state});
  _prioritySet.erase(setPos);

  return tuple;
}
