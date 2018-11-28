#ifndef __KEVIN_PQ_H__
#define __KEVIN_PQ_H__

#include <map>
#include <set>

#include "types.h"

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
  KevinPq& operator= (const KevinPq& orig)  = default;
  ~KevinPq ()                               = default;

  bool isEmpty () const;

  MapTuple pop ();
  void push (const MapTuple& thing);

  bool contains (const State& state) const;

  MapTuple get (const State& state) const;
  MapTuple remove (const State& state);

private:
  std::set<PrioritySetElem> _prioritySet;
  std::map<State,MapTuple>  _infoMap;
};

#endif // __KEVIN_PQ_H__
