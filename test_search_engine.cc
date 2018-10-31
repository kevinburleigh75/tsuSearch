#include "search_engine.h"
#include "search_problem.h"


#include <iostream>
#include <string>

using namespace std;

template <typename SEARCHPROBLEMTYPE>
class Dfs : public SearchEngine<SEARCHPROBLEMTYPE>
{
public:
  Dfs (const SEARCHPROBLEMTYPE& problem)
    : SearchEngine<SEARCHPROBLEMTYPE>(problem),
      _counter(0.0)
  { }

  double _impl_getPriority (const typename SearchEngine<SEARCHPROBLEMTYPE>::StateInfo& stateInfo) {
    return _counter--;
  }
  bool _impl_shouldUpdateSeenStates () {
    return false;
  }

private:
  double _counter {0.0};
};

template <typename SEARCHPROBLEMTYPE>
class Bfs : public SearchEngine<SEARCHPROBLEMTYPE>
{
public:
  Bfs (const SEARCHPROBLEMTYPE& problem)
    : SearchEngine<SEARCHPROBLEMTYPE>(problem),
      _counter(0.0)
  { }

  double _impl_getPriority (const typename SearchEngine<SEARCHPROBLEMTYPE>::StateInfo& stateInfo) {
    return _counter++;
  }
  bool _impl_shouldUpdateSeenStates () {
    return false;
  }

private:
  double _counter {0.0};
};

template <typename SEARCHPROBLEMTYPE>
class Ucs : public SearchEngine<SEARCHPROBLEMTYPE>
{
public:
  Ucs (const SEARCHPROBLEMTYPE& problem)
    : SearchEngine<SEARCHPROBLEMTYPE>(problem),
      _counter(0.0)
  { }

  double _impl_getPriority (const typename SearchEngine<SEARCHPROBLEMTYPE>::StateInfo& stateInfo) {
    return stateInfo.pathCost;
  }
  bool _impl_shouldUpdateSeenStates () {
    return true;
  }

private:
  double _counter {0.0};
};

template <typename SEARCHPROBLEMTYPE>
class Gbfs : public SearchEngine<SEARCHPROBLEMTYPE>
{
public:
  Gbfs (const SEARCHPROBLEMTYPE& problem)
    : SearchEngine<SEARCHPROBLEMTYPE>(problem)
  { }

  double _impl_getPriority (const typename SearchEngine<SEARCHPROBLEMTYPE>::StateInfo& stateInfo) {
    return stateInfo.heuristic;
  }
  bool _impl_shouldUpdateSeenStates () {
    return false;
  }
};

template <typename SEARCHPROBLEMTYPE>
class AStar : public SearchEngine<SEARCHPROBLEMTYPE>
{
public:
  AStar (const SEARCHPROBLEMTYPE& problem)
    : SearchEngine<SEARCHPROBLEMTYPE>(problem)
  { }

  double _impl_getPriority (const typename SearchEngine<SEARCHPROBLEMTYPE>::StateInfo& stateInfo) {
    return stateInfo.pathCost + stateInfo.heuristic;
  }
  bool _impl_shouldUpdateSeenStates () {
    return true;
  }
};

int main () {
  SearchProblem<int,string>::Builder spBuilder;

  spBuilder
    .addTransitions({
      {1, "to2", 1.0, 2},
      {1, "to5", 1.0, 5},
      {2, "to4", 3.0, 4},
      {2, "to3", 1.0, 3},
      {3, "to4", 1.0, 4},
      {3, "to6", 1.0, 6},
      {3, "to7", 2.0, 7},
      {5, "to6", 3.0, 6},
      {6, "to7", 3.0, 7},
      {7, "to3", 2.0, 3},
      {7, "to4", 3.0, 4},
    })
    .addStateHeuristics({
      {1, 4.0},
      {2, 2.0},
      {3, 1.0},
      {4, 0.0},
      {5, 5.0},
      {6, 5.0},
      {7, 2.0},
    })
    .setStateState(1)
    .addGoalState(4);

  auto searchProblem = spBuilder.build();

  cout << "===== DFS ===== " << endl;

  {
    auto dfs = Dfs(searchProblem);
    auto soln = dfs.solve();

    cout << "solutionWasFound = " << boolalpha << soln.getSolutionWasFound() << endl;
    cout << "path: ";
    for (auto state : soln.getPath()) {
      cout << state << ", ";
    }
    cout << endl;
  }

  cout << "===== BFS ===== " << endl;

  {
    auto bfs = Bfs(searchProblem);
    auto soln = bfs.solve();

    cout << "solutionWasFound = " << boolalpha << soln.getSolutionWasFound() << endl;
    cout << "path: ";
    for (auto state : soln.getPath()) {
      cout << state << ", ";
    }
    cout << endl;
  }

  cout << "===== UCS ===== " << endl;

  {
    auto ucs = Ucs(searchProblem);
    auto soln = ucs.solve();

    cout << "solutionWasFound = " << boolalpha << soln.getSolutionWasFound() << endl;
    cout << "path: ";
    for (auto state : soln.getPath()) {
      cout << state << ", ";
    }
    cout << endl;
  }

  cout << "===== GBFS ===== " << endl;

  {
    auto gbfs = Gbfs(searchProblem);
    auto soln = gbfs.solve();

    cout << "solutionWasFound = " << boolalpha << soln.getSolutionWasFound() << endl;
    cout << "path: ";
    for (auto state : soln.getPath()) {
      cout << state << ", ";
    }
    cout << endl;
  }

  cout << "===== AStar ===== " << endl;

  {
    auto astar = AStar(searchProblem);
    auto soln = astar.solve();

    cout << "solutionWasFound = " << boolalpha << soln.getSolutionWasFound() << endl;
    cout << "path: ";
    for (auto state : soln.getPath()) {
      cout << state << ", ";
    }
    cout << endl;
  }
}
