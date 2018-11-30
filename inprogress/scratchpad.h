#ifndef __SCRATCHPAD_H__
#define __SCRATCHPAD_H__

#include "kevin_pq.h"
#include "types.h"

#include <map>
#include <utility>

class Scratchpad
{
public:
  typedef std::tuple<Priority,StateInfo> TupleType;

public:
  Scratchpad ()                       = default;
  Scratchpad (const Scratchpad& orig) = default;
  Scratchpad (Scratchpad&& orig)      = delete;
  Scratchpad& operator= (const Scratchpad& other) = default;
  ~Scratchpad ()                      = default;

public:
  bool frontierIsEmpty () const;
  void frontierPush (const Priority& priority,
                     const StateInfo& stateInfo);
  TupleType frontierPop ();

  void addToVisited (const StateInfo& stateInfo);

  bool contains (const State& state) const;
  StateInfo getStateInfo (const State& state) const;
  StateInfo remove (const State& state);

private:
  std::map<State,StateInfo> _visited;
  KevinPq                   _frontier;
};

#endif // __SCRATCHPAD_H__
