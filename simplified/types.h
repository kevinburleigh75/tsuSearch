#ifndef __TYPES_H__
#define __TYPES_H__

#include <experimental/optional>
#include <string>
#include <tuple>
#include <utility>

typedef int                       State;
typedef double                    Cost;
typedef double                    Heuristic;
typedef double                    Priority;
typedef State                     Action;
typedef std::tuple<State,Action>  StateAction;

struct StateInfo {
  State                               state;
  std::experimental::optional<State>  predecessor;
  Cost                                pathCost;
  Heuristic                           heuristic;

  std::string toString () const;
};

bool operator< (const StateAction& lhs, const StateAction& rhs);

#endif // __TYPES_H__
