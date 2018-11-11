#ifndef __STATE_INFO__
#define __STATE_INFO__

struct StateInfo
{
  int    state;
  int    predecessor;
  double pathCost;
  double heuristic;
};

#endif // __STATE_INFO__
