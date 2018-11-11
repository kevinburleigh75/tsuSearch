#ifndef __TYPES_H__
#define __TYPES_H__

#include <tuple>
#include <utility>

typedef int                       State;
typedef double                    Cost;
typedef double                    Heuristic;
typedef double                    Priority;
typedef State                     Action;
typedef std::tuple<State,Action>  StateAction;

bool operator< (const StateAction& lhs, const StateAction& rhs);

#endif // __TYPES_H__
