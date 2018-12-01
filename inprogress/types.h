#ifndef __TYPES_H__
#define __TYPES_H__

#include <experimental/optional>
#include <utility>

typedef int                       State;
typedef double                    Cost;
typedef double                    Heuristic;
typedef State                     Action;
typedef double                    Priority;
typedef std::tuple<State,Action>  StateAction;

struct StateInfo {
  State state;
  std::experimental::optional<State> predecessor;
  Cost pathCost;
  Heuristic heuristic;
};

#endif // __TYPES_H__
