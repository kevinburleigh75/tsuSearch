#ifndef __KEVIN_PQ__
#define __KEVIN_PQ__

#include "types.h"

#include <map>
#include <set>

class KevinPq
{
public:
  typedef std::tuple<Priority,State,StateInfo> MapTuple;

  struct PrioritySetElem {
    const Priority priority;
    const State    state;

    bool operator< (const PrioritySetElem& other) const;
  };

  KevinPq ()                                = default;
  KevinPq (const KevinPq& orig)             = default;
  KevinPq (KevinPq&& orig)                  = delete;
  KevinPq& operator= (const KevinPq& orig)  = delete;
  ~KevinPq ()                               = default;

  bool isEmpty () const;

  MapTuple pop ();

  void push (const MapTuple& tuple);

  bool contains (const State& state) const;

  MapTuple get (const State& state) const;

  MapTuple remove (const State& state);

private:
  std::set<PrioritySetElem>   _prioritySet;
  std::map<State,MapTuple>    _tupleMap;
};

#endif // __KEVIN_PQ__
