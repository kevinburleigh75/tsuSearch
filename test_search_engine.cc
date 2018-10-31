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

int main () {
  SearchProblem<int,string>::Builder spBuilder;

  spBuilder
    .addTransitions({
      {1, "to2", 1.0, 2},
      {1, "to3", 2.0, 3},
      {2, "to4", 4.0, 4},
      {2, "to5", 1.0, 5},
      {3, "to6", 2.0, 6},
      {4, "to7", 3.0, 7},
      {5, "to4", 1.0, 4},
      {5, "to7", 1.0, 7},
      {5, "to6", 1.0, 6},
      {6, "to7", 1.0, 7},
      {7, "to4", 3.0, 4},
      {7, "to6", 1.0, 6},
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
}
